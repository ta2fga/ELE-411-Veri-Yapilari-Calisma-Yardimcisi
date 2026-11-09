# -*- coding: utf-8 -*-
"""
Tüm soruları doğrular (sunucuyu başlatmaya gerek yok):

  * solution.cpp   -> tüm testleri GEÇMELİ ve yasak kurallara uymalı
  * wrong_*.cpp    -> en az bir testten KALMALI (testlerin hatayı yakaladığını gösterir)
  * starter.cpp    -> DERLENMELİ (öğrenci boş haliyle "Test et" diyebilmeli)
  * main()'li solution.cpp -> "Çalıştır" ile de hatasız çalışmalı

Ek olarak sonsuz döngü, derleme hatası ve çökme durumlarını dener.

Kullanım:  python verify.py            (hepsi)
           python verify.py stack      (sadece adı/konusu 'stack' içerenler)
"""
import sys
import time
from pathlib import Path

import server

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

OK, FAIL = "  OK ", "HATA "


def summarize(res):
    if res.get("error"):
        return "error: " + res["error"]
    if not res["compile_ok"]:
        return "derlenmedi:\n" + res["compile_output"]
    lines = [f"{res['passed']}/{res['total']} geçti"]
    for t in res["tests"]:
        if not t["passed"]:
            bad = [c for c in t["checks"] if not c["pass"]]
            detail = "; ".join(f"{c['label']}: beklenen={c['expected']!r} gerçek={c['actual']!r}" for c in bad[:2])
            lines.append(f"      ✗ {t['name']}: {t['problem'] or detail}")
    if res.get("violations"):
        lines.append("      kural ihlali: " + ", ".join(v["rule"] for v in res["violations"]))
    return "\n".join(lines)


def norm_tokens(s):
    """app.js'teki normTokens ile aynı: 'boş' / [] / virgüller yok sayılır."""
    import re
    s = re.sub(r"boş|bos|empty|yok", " ", s.lower())
    return re.findall(r"-?\d+|[a-zçğıöşü]+", s)


def main():
    flt = sys.argv[1] if len(sys.argv) > 1 else ""
    _, problems = server.load_all()
    errors = 0
    checked = 0
    t0 = time.time()
    ids = {p["id"] for p in problems}
    for p in problems:
        if flt and flt not in p["id"] and flt not in p.get("topic", ""):
            continue
        t = p.get("type")
        if t == "trace":
            checked += 1
            rr = server.do_run(p["runCode"], "")
            got = norm_tokens(rr["stdout"])
            exp = [tok for b in p["blanks"] for tok in norm_tokens(b["answer"])]
            good = rr["compile_ok"] and got == exp
            print(f"{OK if good else FAIL} trace {p['id']}: program çıktısı cevaplarla uyumlu" + ("" if good else f" — çıktı={got} cevaplar={exp} {rr['compile_output'][:300]}"))
            errors += not good
        elif t == "mcq":
            checked += 1
            bad = [it["q"] for it in p["items"] if it["answer"] not in it.get("options", p.get("options", []))]
            print(f"{OK if not bad else FAIL} mcq {p['id']}: {len(p['items'])} soru" + (f" — şıkta olmayan cevap: {bad}" if bad else ""))
            errors += bool(bad)
        elif t == "exam":
            checked += 1
            missing = [s["problem"] for s in p["sections"] if s["problem"] not in ids]
            print(f"{OK if not missing else FAIL} sınav {p['id']}: {len(p['sections'])} bölüm, {sum(s['minutes'] for s in p['sections'])} dk" + (f" — eksik: {missing}" if missing else ""))
            errors += bool(missing)
    for p in problems:
        if flt and flt not in p["id"] and flt not in p.get("topic", ""):
            continue
        d = Path(p.get("_dir", ""))
        if p.get("type") == "broken":
            print(f"{FAIL} {p['id']}: yüklenemedi: {p.get('error')}")
            errors += 1
            continue
        if not p.get("has_tests"):
            continue
        checked += 1
        print(f"== {p['topic']}/{p['id']}  ({p['title']})")
        sol = (d / "solution.cpp").read_text(encoding="utf-8")
        r = server.do_test(p["id"], sol)
        good = r.get("all_passed", False)
        print(f"{OK if good else FAIL} çözüm: {summarize(r)}")
        errors += not good

        if "int main" in sol:
            rr = server.do_run(sol, "")
            good = rr["compile_ok"] and rr["exit_code"] == 0 and not rr["timed_out"]
            print(f"{OK if good else FAIL} çözüm 'Çalıştır': çıkış={rr['exit_code']} çıktı={rr['stdout'].strip()[:80]!r}")
            errors += not good

        wrongs = sorted(d.glob("wrong_*.cpp"))
        if not wrongs:
            print("   - (yanlış örnek çözüm yok)")
        for w in wrongs:
            r = server.do_test(p["id"], w.read_text(encoding="utf-8"))
            caught = not r.get("all_passed", False)
            print(f"{OK if caught else FAIL} {w.name} yakalandı mı: {summarize(r).splitlines()[0]}")
            errors += not caught

        st = d / "starter.cpp"
        if st.exists():
            r = server.do_test(p["id"], st.read_text(encoding="utf-8"))
            good = r.get("compile_ok", False)
            print(f"{OK if good else FAIL} başlangıç kodu derleniyor ({r.get('passed', 0)}/{r.get('total', 0)} geçiyor)")
            errors += not good

    # --- Özel durumlar ---
    print("== özel durumlar")
    r = server.do_run("int main(){ while(true){} }", "")
    good = r["timed_out"] and r["time_ms"] < 9000
    print(f"{OK if good else FAIL} sonsuz döngü {r['time_ms']} ms sonra durduruldu (timed_out={r['timed_out']})")
    errors += not good

    r = server.do_run("int main(){ while(true) cout << \"spam spam spam\\n\"; }", "")
    good = r["truncated"] and len(r["stdout"]) <= server.OUTPUT_LIMIT + 200
    print(f"{OK if good else FAIL} sonsuz çıktı 64 KB'de kesildi (uzunluk={len(r['stdout'])})")
    errors += not good

    r = server.do_run("int main(){\n  int x = 5\n  cout << x;\n}", "")
    good = (not r["compile_ok"]) and "user.cpp:2" in r["compile_output"]
    print(f"{OK if good else FAIL} derleme hatası satır numarasıyla: {r['compile_output'].splitlines()[1] if good else r['compile_output'][:200]}")
    errors += not good

    r = server.do_test("stack-search", "bool searchStack(Stack& s, int t) {\n  return s.peek() == t\n}\n")
    good = (not r["compile_ok"]) and "user.cpp:2" in r["compile_output"]
    print(f"{OK if good else FAIL} test modunda derleme hatası satırı doğru (user.cpp:2)")
    errors += not good

    r = server.do_test("stack-count", "int countItem(Stack& s, int t) { int c = 0; while (!s.isEmpty()) { if (s.peek() == t) c++; } return c; }")
    good = r["compile_ok"] and all(t["timed_out"] for t in r["tests"] if t["input"] and "[]" not in t["input"]) and r["passed"] < r["total"]
    print(f"{OK if good else FAIL} test modunda sonsuz döngü: {r['passed']}/{r['total']} geçti, süre {r.get('time_ms')} ms")
    errors += not good

    r = server.do_run("int f(int n){ return f(n+1)+1; }\nint main(){ cout << f(0); }", "")
    good = r["exit_code"] not in (0, None) and r.get("exit_note")
    print(f"{OK if good else FAIL} sonsuz recursion çökmesi: {r.get('exit_note')}")
    errors += not bool(good)

    r = server.do_run("int main(){ Node* p = nullptr; cout << p->item; }", "")
    good = r["exit_code"] not in (0, None)
    print(f"{OK if good else FAIL} nullptr erişimi: {r.get('exit_note')}")
    errors += not good

    r = server.do_test("stack-search", "#include <vector>\nbool searchStack(Stack& s, int t) {\n  std::vector<int> v;\n  return false;\n}\n")
    good = bool(r.get("violations")) and not r["all_passed"]
    print(f"{OK if good else FAIL} yasak yapı (vector) tespit edildi: {[v['rule'] for v in r.get('violations', [])]}")
    errors += not good

    r = server.do_run("int main(){ int a, b; cin >> a >> b; cout << a + b << endl; }", "3 4")
    good = r["stdout"].strip() == "7"
    print(f"{OK if good else FAIL} stdin ile çalıştırma: {r['stdout'].strip()!r}")
    errors += not good

    print()
    print(f"{checked} soru kontrol edildi, {int(time.time() - t0)} sn. ", end="")
    print("HEPSİ TAMAM ✓" if errors == 0 else f"{errors} HATA ✗")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
