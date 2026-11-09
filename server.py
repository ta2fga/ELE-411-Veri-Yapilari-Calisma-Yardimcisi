# -*- coding: utf-8 -*-
"""
ELE411 çalışma sitesi — yerel derleme/çalıştırma sunucusu.

Yalnızca Python standart kütüphanesi kullanır. Sadece 127.0.0.1:8000 dinler.

  GET  /                 -> static/index.html
  GET  /api/health       -> {"ok": true, "gxx": "..."}
  GET  /api/problems     -> konu ve soru listesi (problems/ klasöründen)
  POST /run              -> {code, stdin}         : kodu derleyip çalıştırır
  POST /test             -> {problem_id, code}    : sorunun testlerini çalıştırır

Başlatma:  python server.py          (tarayıcıyı da açar)
           python server.py --no-browser
"""
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import threading
import time
from concurrent.futures import ThreadPoolExecutor
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

ROOT = Path(__file__).resolve().parent
STATIC = ROOT / "static"
PROBLEMS = ROOT / "problems"
HEADER = ROOT / "ele411.h"

HOST = "127.0.0.1"
PORT = 8000
RUN_TIMEOUT = 5.0          # saniye (her çalıştırma / her test için)
COMPILE_TIMEOUT = 60.0
OUTPUT_LIMIT = 64 * 1024   # bayt
GXX_FLAGS = ["-std=c++17", "-Wall", "-O0"]
MARK = "@@E411\x1f"

IS_WIN = os.name == "nt"


# ----------------------------------------------------------------------------
#  g++ bulma
# ----------------------------------------------------------------------------
def find_gxx():
    p = shutil.which("g++")
    if p:
        return p
    for cand in (r"C:\msys64\ucrt64\bin\g++.exe", r"C:\msys64\mingw64\bin\g++.exe"):
        if os.path.isfile(cand):
            return cand
    return None


GXX = find_gxx()
CHILD_ENV = dict(os.environ)
if GXX:
    # Derlenen .exe'nin MSYS2 DLL'lerini (libstdc++ vb.) bulabilmesi için.
    CHILD_ENV["PATH"] = str(Path(GXX).parent) + os.pathsep + CHILD_ENV.get("PATH", "")


def gxx_version():
    if not GXX:
        return None
    try:
        out = subprocess.run([GXX, "--version"], capture_output=True, text=True, timeout=20, env=CHILD_ENV)
        return out.stdout.splitlines()[0] if out.stdout else None
    except Exception:
        return None


if IS_WIN:
    # Çöken programlar için Windows hata penceresi açılmasın (alt süreçlere miras kalır).
    try:
        import ctypes
        ctypes.windll.kernel32.SetErrorMode(0x0001 | 0x0002 | 0x8000)
    except Exception:
        pass

WIN_CODES = {
    0xC0000005: "Erişim ihlali (segmentation fault): geçersiz pointer / nullptr erişimi ya da dizi sınırı aşımı.",
    0xC00000FD: "Stack overflow: büyük ihtimalle base case'e ulaşmayan sonsuz recursion.",
    0xC0000094: "Sıfıra bölme (integer divide by zero).",
    0xC0000409: "Program abort edildi (stack buffer overrun / std::terminate).",
    0xC000001D: "Geçersiz komut (illegal instruction).",
    0xC0000374: "Heap bozulması (aynı belleği iki kez delete etmek vb.).",
}


def explain_exit(code):
    if code is None:
        return None
    if code == 70:
        return "Program ele411 hatasıyla durdu (stderr'e bakın)."
    u = code & 0xFFFFFFFF
    if u in WIN_CODES:
        return WIN_CODES[u]
    if code == 3:
        return "abort() çağrıldı (ör. başarısız assert veya yakalanmamış exception)."
    if code < 0:
        return f"Program sinyal {-code} ile sonlandı."
    if code != 0:
        return f"Program {code} çıkış koduyla bitti."
    return None


# ----------------------------------------------------------------------------
#  Derleme ve çalıştırma
# ----------------------------------------------------------------------------
def clean_compiler_output(text, tmpdir):
    t = text.replace("\r\n", "\n")
    for d in {str(tmpdir), str(tmpdir).replace("\\", "/"), os.path.realpath(tmpdir)}:
        t = t.replace(d + os.sep, "").replace(d + "/", "").replace(d, "")
    hdr = str(HEADER)
    t = t.replace(hdr, "ele411.h").replace(hdr.replace("\\", "/"), "ele411.h")
    t = t.replace("ele411_user_main", "main")
    return t


def compile_cpp(tmpdir, source_name, exe_name):
    cmd = [GXX] + GXX_FLAGS + ["-include", str(HEADER), source_name, "-o", exe_name]
    try:
        p = subprocess.run(cmd, cwd=tmpdir, capture_output=True, timeout=COMPILE_TIMEOUT, env=CHILD_ENV)
    except subprocess.TimeoutExpired:
        return False, "Derleme zaman aşımına uğradı."
    out = (p.stdout + p.stderr).decode("utf-8", errors="replace")
    return p.returncode == 0, clean_compiler_output(out, tmpdir)


def run_process(cmd, cwd, stdin_text="", timeout=RUN_TIMEOUT, limit=OUTPUT_LIMIT):
    """Programı çalıştırır; süre ve çıktı boyutu sınırlıdır."""
    start = time.perf_counter()
    proc = subprocess.Popen(cmd, cwd=cwd, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE, env=CHILD_ENV)
    bufs = {"out": bytearray(), "err": bytearray()}
    truncated = {"out": False, "err": False}

    def reader(stream, key):
        try:
            while True:
                chunk = stream.read1(4096) if hasattr(stream, "read1") else stream.read(4096)
                if not chunk:
                    break
                b = bufs[key]
                if len(b) < limit:
                    b.extend(chunk[: limit - len(b)])
                if len(b) >= limit and not truncated[key]:
                    truncated[key] = True
                    try:
                        proc.kill()  # çıktı sınırı aşıldı: süreci durdur
                    except Exception:
                        pass
        except Exception:
            pass

    def writer():
        try:
            if stdin_text:
                proc.stdin.write(stdin_text.encode("utf-8"))
            proc.stdin.close()
        except Exception:
            pass

    threads = [threading.Thread(target=reader, args=(proc.stdout, "out"), daemon=True),
               threading.Thread(target=reader, args=(proc.stderr, "err"), daemon=True),
               threading.Thread(target=writer, daemon=True)]
    for t in threads:
        t.start()
    timed_out = False
    try:
        proc.wait(timeout=timeout)
    except subprocess.TimeoutExpired:
        timed_out = True
        proc.kill()
        proc.wait()
    for t in threads:
        t.join(timeout=2)
    elapsed = int((time.perf_counter() - start) * 1000)
    out = bufs["out"].decode("utf-8", errors="replace").replace("\r\n", "\n")
    err = bufs["err"].decode("utf-8", errors="replace").replace("\r\n", "\n")
    if truncated["out"]:
        out += f"\n... [çıktı {OUTPUT_LIMIT // 1024} KB sınırında kesildi]"
    if truncated["err"]:
        err += f"\n... [stderr {OUTPUT_LIMIT // 1024} KB sınırında kesildi]"
    return {
        "stdout": out,
        "stderr": err,
        "exit_code": None if timed_out else proc.returncode,
        "timed_out": timed_out,
        "time_ms": elapsed,
        "truncated": truncated["out"] or truncated["err"],
    }


def exe_path(tmpdir, name="prog"):
    return os.path.join(tmpdir, name + (".exe" if IS_WIN else ""))


def do_run(code, stdin_text):
    with tempfile.TemporaryDirectory(prefix="ele411_") as tmp:
        Path(tmp, "user.cpp").write_text(code, encoding="utf-8")
        exe = exe_path(tmp)
        ok, cout = compile_cpp(tmp, "user.cpp", exe)
        res = {"compile_ok": ok, "compile_output": cout, "stdout": "", "stderr": "",
               "exit_code": None, "time_ms": 0, "timed_out": False}
        if not ok:
            return res
        r = run_process([exe], tmp, stdin_text)
        res.update(r)
        res["exit_note"] = explain_exit(r["exit_code"])
        return res


# ----------------------------------------------------------------------------
#  Sorular
# ----------------------------------------------------------------------------
FORBIDDEN_PRESETS = {
    "array": ([r"\b(?:int|char|string|double|float|long|bool|auto|short|unsigned|Node\s*\*?)\s+\**\s*\w+\s*\[",
               r"\bnew\s+\w+\s*\["],
              "Dizi (array) kullanmak bu soruda yasak."),
    "stl": ([r"\b(?:vector|deque|list|forward_list|map|multimap|set|multiset|unordered_\w+|array|stack|queue|priority_queue)\s*<"],
            "STL konteynerleri (vector, std::stack, std::queue ...) bu soruda yasak."),
    "queue": ([r"\bQueue\b"], "Bu soruda Queue kullanmak yasak (sadece Stack)."),
    "stack": ([r"\bStack\b"], "Bu soruda Stack kullanmak yasak."),
    "multiply": ([r"(?<![*/])\*(?![*/=])\s*[\w(]", r"\*="], "Çarpma operatörü (*) bu soruda yasak."),
    "sort": ([r"\bsort\s*\(", r"\bqsort\s*\("], "Hazır sıralama fonksiyonu (std::sort) bu soruda yasak."),
    "noloop": ([r"\b(?:for|while|do)\b\s*[({]?"], "Döngü (for/while) yasak — fonksiyonu recursive yazın."),
}


def strip_comments_and_strings(code):
    pattern = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)

    def repl(m):
        s = m.group(0)
        if s.startswith("/"):
            return "\n" * s.count("\n")
        return '""'
    return pattern.sub(repl, code)


def check_forbidden(code, rules):
    stripped = strip_comments_and_strings(code)
    # main() içindeki deneme kodları kontrol dışı kalsın
    m = re.search(r"\bint\s+main\s*\(", stripped)
    if m:
        stripped = stripped[: m.start()]
    found = []
    for rule in rules or []:
        if isinstance(rule, str):
            pats, msg = FORBIDDEN_PRESETS.get(rule, ([], ""))
        else:
            pats, msg = [rule["pattern"]], rule.get("message", "Yasak ifade")
        for pat in pats:
            mm = re.search(pat, stripped)
            if mm:
                line = stripped.count("\n", 0, mm.start()) + 1
                found.append({"rule": msg, "line": line, "text": mm.group(0).strip()})
                break
    return found


def read_text(p):
    return p.read_text(encoding="utf-8") if p.exists() else ""


def load_problem_dir(d):
    meta = json.loads((d / "problem.json").read_text(encoding="utf-8"))
    meta.setdefault("id", d.name)
    meta.setdefault("topic", d.parent.name)
    meta.setdefault("type", "code")
    meta["_dir"] = str(d)
    for key, fname in (("starter", "starter.cpp"), ("solution", "solution.cpp")):
        if key not in meta and (d / fname).exists():
            meta[key] = read_text(d / fname)
    meta["has_tests"] = (d / "harness.cpp").exists()
    return meta


def load_all():
    topics = json.loads((PROBLEMS / "topics.json").read_text(encoding="utf-8"))
    for t in topics:
        f = PROBLEMS / "topics" / f"{t['id']}.html"
        t["summary"] = read_text(f)
    problems = []
    for pj in sorted(PROBLEMS.glob("*/*/problem.json")):
        try:
            problems.append(load_problem_dir(pj.parent))
        except Exception as e:  # bozuk bir dosya tüm siteyi düşürmesin
            problems.append({"id": pj.parent.name, "topic": pj.parent.parent.name, "type": "broken",
                             "title": f"Yüklenemedi: {pj.parent.name}", "error": str(e)})
    problems.sort(key=lambda p: (p.get("topic", ""), p.get("order", 999), p.get("id", "")))
    return topics, problems


def find_problem(pid):
    for pj in PROBLEMS.glob("*/*/problem.json"):
        if pj.parent.name == pid:
            return load_problem_dir(pj.parent)
        try:
            if json.loads(pj.read_text(encoding="utf-8")).get("id") == pid:
                return load_problem_dir(pj.parent)
        except Exception:
            pass
    return None


WRAPPER = """// otomatik üretilen test sarmalayıcısı
#define main ele411_user_main
#include "user.cpp"
#undef main
#include "harness.cpp"
int main(int argc, char** argv) { return ele411::runTests(argc, argv); }
"""


def parse_marked(stdout):
    """Test programının çıktısını, işaretli satırlar ve kullanıcı çıktısı olarak ayırır."""
    records, user_lines = [], []
    for line in stdout.split("\n"):
        if line.startswith(MARK):
            fields = [unesc(f) for f in line[len(MARK):].split("\x1f")]
            records.append(fields)
        else:
            user_lines.append(line)
    user_out = "\n".join(user_lines).strip("\n")
    return records, user_out


def unesc(s):
    out, i = [], 0
    while i < len(s):
        c = s[i]
        if c == "\\" and i + 1 < len(s):
            n = s[i + 1]
            out.append("\n" if n == "n" else n)
            i += 2
        else:
            out.append(c)
            i += 1
    return "".join(out)


def do_test(problem_id, code):
    prob = find_problem(problem_id)
    if prob is None:
        return {"error": f"Soru bulunamadı: {problem_id}"}
    harness = Path(prob["_dir"]) / "harness.cpp"
    if not harness.exists():
        return {"error": "Bu sorunun otomatik testi yok."}
    start = time.perf_counter()
    violations = check_forbidden(code, prob.get("forbidden"))
    with tempfile.TemporaryDirectory(prefix="ele411_") as tmp:
        Path(tmp, "user.cpp").write_text(code, encoding="utf-8")
        shutil.copyfile(harness, Path(tmp, "harness.cpp"))
        Path(tmp, "_main.cpp").write_text(WRAPPER, encoding="utf-8")
        exe = exe_path(tmp)
        ok, cout = compile_cpp(tmp, "_main.cpp", exe)
        res = {"compile_ok": ok, "compile_output": cout, "tests": [], "passed": 0, "total": 0,
               "violations": violations, "all_passed": False}
        if not ok:
            res["time_ms"] = int((time.perf_counter() - start) * 1000)
            return res
        lst = run_process([exe, "--list"], tmp)
        recs, _ = parse_marked(lst["stdout"])
        tests = [{"index": int(r[1]), "name": r[2], "input": r[3]} for r in recs if r and r[0] == "TEST"]
        if not tests:
            res["error"] = "Test listesi alınamadı.\n" + lst["stderr"]
            return res

        def run_one(t):
            r = run_process([exe, "--run", str(t["index"])], tmp)
            recs, user_out = parse_marked(r["stdout"])
            checks, notes, ended = [], [], False
            for f in recs:
                if f[0] == "CHECK" and len(f) >= 5:
                    checks.append({"label": f[1], "expected": f[2], "actual": f[3], "pass": f[4] == "1"})
                elif f[0] == "NOTE":
                    notes.append(f[1] if len(f) > 1 else "")
                elif f[0] == "END":
                    ended = True
            problem = None
            if r["timed_out"]:
                problem = f"Zaman aşımı: {RUN_TIMEOUT:g} saniyede bitmedi (sonsuz döngü / sonsuz recursion?)."
            elif r["exit_code"] not in (0, None) or not ended:
                problem = explain_exit(r["exit_code"]) or "Program test bitmeden sonlandı."
            passed = ended and not r["timed_out"] and r["exit_code"] == 0 and bool(checks) and all(c["pass"] for c in checks)
            return dict(t, checks=checks, notes=notes, output=user_out, stderr=r["stderr"].strip(),
                        timed_out=r["timed_out"], exit_code=r["exit_code"], problem=problem,
                        passed=passed, time_ms=r["time_ms"])

        with ThreadPoolExecutor(max_workers=4) as ex:
            results = list(ex.map(run_one, tests))
        res["tests"] = results
        res["total"] = len(results)
        res["passed"] = sum(1 for t in results if t["passed"])
        res["all_passed"] = res["passed"] == res["total"] and not violations
        res["time_ms"] = int((time.perf_counter() - start) * 1000)
        return res


# ----------------------------------------------------------------------------
#  HTTP
# ----------------------------------------------------------------------------
class Handler(SimpleHTTPRequestHandler):
    server_version = "ELE411/1.0"

    def __init__(self, *a, **kw):
        super().__init__(*a, directory=str(STATIC), **kw)

    def log_message(self, fmt, *args):
        if "/api/health" in (self.path or ""):
            return
        sys.stderr.write("[%s] %s\n" % (time.strftime("%H:%M:%S"), fmt % args))

    def end_headers(self):
        self.send_header("Cache-Control", "no-store")
        super().end_headers()

    def send_json(self, obj, status=200):
        data = json.dumps(obj, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        if path == "/api/health":
            return self.send_json({"ok": True, "gxx": GXX_VERSION, "gxx_path": GXX})
        if path == "/api/problems":
            topics, problems = load_all()
            for p in problems:
                p.pop("_dir", None)
            return self.send_json({"topics": topics, "problems": problems})
        return super().do_GET()

    def do_POST(self):
        path = self.path.split("?", 1)[0]
        try:
            n = int(self.headers.get("Content-Length", "0"))
            if n > 1_000_000:
                return self.send_json({"error": "İstek çok büyük"}, 413)
            body = json.loads(self.rfile.read(n).decode("utf-8") or "{}")
        except Exception:
            return self.send_json({"error": "Geçersiz JSON"}, 400)
        if not GXX:
            return self.send_json({"error": "g++ bulunamadı. MSYS2 UCRT64 g++ kurulu mu?"}, 500)
        try:
            if path == "/run":
                return self.send_json(do_run(str(body.get("code", "")), str(body.get("stdin", ""))))
            if path == "/test":
                return self.send_json(do_test(str(body.get("problem_id", "")), str(body.get("code", ""))))
        except Exception as e:
            return self.send_json({"error": f"Sunucu hatası: {e}"}, 500)
        return self.send_json({"error": "Bilinmeyen adres"}, 404)


GXX_VERSION = None


def main():
    global GXX_VERSION
    if not GXX:
        print("HATA: g++ bulunamadı. PATH'i veya C:\\msys64\\ucrt64\\bin\\g++.exe yolunu kontrol edin.")
        sys.exit(1)
    GXX_VERSION = gxx_version()
    url = f"http://localhost:{PORT}"
    try:
        httpd = ThreadingHTTPServer((HOST, PORT), Handler)
    except OSError:
        print(f"{PORT} portu kullanımda — sunucu zaten çalışıyor olabilir. Tarayıcı açılıyor: {url}")
        if "--no-browser" not in sys.argv:
            import webbrowser
            webbrowser.open(url)
        return
    print(f"ELE411 çalışma sitesi: {url}")
    print(f"Derleyici: {GXX_VERSION}  ({GXX})")
    print("Durdurmak için bu pencereyi kapatın veya Ctrl+C basın.")
    if "--no-browser" not in sys.argv:
        import webbrowser
        threading.Timer(0.6, lambda: webbrowser.open(url)).start()
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()


if __name__ == "__main__":
    main()
