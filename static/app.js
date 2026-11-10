/* ELE411 çalışma sitesi — arayüz
 * Sunucu: server.py (POST /run, POST /test, GET /api/problems, GET /api/health)
 * İlerleme ve kodlar localStorage'da saklanır (anahtar öneki "ele411.").
 */
(function () {
  "use strict";

  const EXAM_DATE = new Date(2026, 10, 16, 9, 0, 0); // 16 Kasım 2026 Pazartesi
  const state = { topics: [], problems: [], byId: {}, serverUp: null, editors: [], timer: null };

  // ================================================================ yardımcılar
  const $ = (sel, root) => (root || document).querySelector(sel);
  const $$ = (sel, root) => Array.from((root || document).querySelectorAll(sel));
  const esc = (s) => String(s == null ? "" : s).replace(/[&<>"']/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c]));
  function el(tag, attrs, html) {
    const e = document.createElement(tag);
    if (attrs) for (const k in attrs) {
      if (k === "class") e.className = attrs[k];
      else if (k.startsWith("on")) e.addEventListener(k.slice(2), attrs[k]);
      else e.setAttribute(k, attrs[k]);
    }
    if (html != null) e.innerHTML = html;
    return e;
  }
  const btn = (cls, html, onclick) => el("button", { class: "btn " + cls, type: "button", onclick }, html);
  const store = {
    get(k, d) { try { const v = localStorage.getItem("ele411." + k); return v === null ? d : JSON.parse(v); } catch (e) { return d; } },
    set(k, v) { try { localStorage.setItem("ele411." + k, JSON.stringify(v)); } catch (e) { /* özel pencere vb. */ } },
    del(k) { try { localStorage.removeItem("ele411." + k); } catch (e) { } },
    delPrefix(pre) { try { Object.keys(localStorage).filter((k) => k.startsWith("ele411." + pre)).forEach((k) => localStorage.removeItem(k)); } catch (e) { } },
  };
  const normTokens = (s) => String(s || "").toLowerCase().replace(/boş|bos|empty|yok/g, " ").match(/-?\d+|[a-zçğıöşü]+/g) || [];
  const sameTokens = (a, b) => { const x = normTokens(a), y = normTokens(b); return x.length === y.length && x.every((t, i) => t === y[i]); };
  const fmtTime = (ms) => { const s = Math.max(0, Math.round(ms / 1000)); const h = Math.floor(s / 3600), m = Math.floor((s % 3600) / 60), r = s % 60; return (h ? h + ":" + String(m).padStart(2, "0") : m) + ":" + String(r).padStart(2, "0"); };

  const isSolvable = (p) => p.type === "code" ? !!p.has_tests : ["trace", "mcq", "sorttrace", "open", "exam"].includes(p.type);
  const isSolved = (p, prefix) => !!store.get((prefix || "") + "solved." + p.id, null);
  const daysLeft = () => Math.ceil((EXAM_DATE - new Date()) / 86400000);

  async function api(path, body) {
    const opt = body === undefined ? {} : { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(body) };
    let r;
    try { r = await fetch(path, opt); } catch (e) { setServer(false); throw new Error("Sunucuya ulaşılamadı. baslat.bat açık mı?"); }
    setServer(true);
    const data = await r.json().catch(() => ({ error: "Sunucudan geçersiz yanıt" }));
    if (!r.ok && !data.error) data.error = "HTTP " + r.status;
    return data;
  }

  // ================================================================ sunucu durumu
  function setServer(up) {
    if (state.serverUp === up) return;
    state.serverUp = up;
    $("#server-banner").hidden = up;
  }
  async function pollHealth() {
    try {
      const r = await fetch("/api/health", { cache: "no-store" });
      const d = await r.json();
      setServer(!!d.ok);
      if (d.gxx) $("#gxx-info").textContent = d.gxx.replace(/\(.*?\)\s*/, "");
      $("#gxx-info").title = d.gxx_path || "";
    } catch (e) { setServer(false); }
  }

  // ================================================================ tema, menü, geri sayım
  function currentTheme() {
    const t = document.documentElement.getAttribute("data-theme");
    if (t) return t;
    return window.matchMedia && matchMedia("(prefers-color-scheme: dark)").matches ? "dark" : "light";
  }
  function updateThemeButton() { $("#theme-toggle").textContent = currentTheme() === "dark" ? "☀ Açık tema" : "☾ Koyu tema"; }
  $("#theme-toggle").addEventListener("click", () => {
    const next = currentTheme() === "dark" ? "light" : "dark";
    document.documentElement.setAttribute("data-theme", next);
    store.set("theme", next);
    updateThemeButton();
  });
  $("#menu-toggle").addEventListener("click", () => $("#sidebar").classList.toggle("open"));

  function renderCountdown() {
    const days = daysLeft();
    const box = $("#countdown");
    if (days > 1) box.innerHTML = `Ara sınava <b>${days} gün</b> kaldı<br><span class="muted small">16 Kasım 2026 Pazartesi</span>`;
    else if (days === 1) box.innerHTML = `Ara sınav <b>yarın</b>! Bol şans.`;
    else if (days === 0) box.innerHTML = `Ara sınav <b>bugün</b>! Bol şans.`;
    else box.hidden = true;
  }

  // ================================================================ ilerleme ve hazırlık durumu
  const topicProblems = (tid) => state.problems.filter((p) => p.topic === tid);
  function topicProgress(tid) {
    const ps = topicProblems(tid).filter(isSolvable);
    return { solved: ps.filter((p) => isSolved(p)).length, total: ps.length };
  }
  // Geçmiş sınav soruları 2 kat, deneme sınavları 3 kat ağırlıklı.
  function readiness() {
    let tw = 0, sw = 0, n = 0, solved = 0, exams = 0, examsDone = 0;
    for (const p of state.problems) {
      if (!isSolvable(p)) continue;
      if (p.type === "exam") { exams++; tw += 3; if (isSolved(p)) { examsDone++; sw += 3; } continue; }
      const w = /midterm/i.test(p.source || "") ? 2 : 1;
      n++; tw += w;
      if (isSolved(p)) { solved++; sw += w; }
    }
    let weakest = null;
    for (const t of state.topics) {
      if (t.id === "exam") continue;
      const pr = topicProgress(t.id);
      if (!pr.total) continue;
      const r = pr.solved / pr.total;
      if (!weakest || r < weakest.r) weakest = { t, r, pr };
    }
    const pct = tw ? Math.round(100 * sw / tw) : 0;
    const level = pct >= 85 ? ["Sınava hazır", "lvl-4"] : pct >= 60 ? ["İyi gidiyor", "lvl-3"] : pct >= 30 ? ["Yolun yarısı", "lvl-2"] : ["Başlangıç", "lvl-1"];
    return { pct, level, n, solved, exams, examsDone, weakest };
  }
  function renderStatusBar() {
    const r = readiness();
    const d = Math.max(daysLeft(), 1);
    const left = r.n - r.solved;
    const perDay = Math.ceil(left / d);
    const bar = $("#statusbar");
    bar.className = "statusbar " + r.level[1];
    bar.innerHTML = `
      <div class="sb-main" title="Çözülen sorulara göre hesaplanır. Geçmiş sınav soruları 2 kat, deneme sınavları 3 kat ağırlıklıdır.">
        <span class="sb-label">Sınava hazırlık</span>
        <span class="sb-pct">%${r.pct}</span>
        <span class="sb-bar"><span style="width:${r.pct}%"></span></span>
        <span class="sb-level">${r.level[0]}</span>
      </div>
      <div class="sb-meta">
        <span><b>${r.solved}/${r.n}</b> soru</span>
        <span><b>${r.examsDone}/${r.exams}</b> deneme sınavı</span>
        ${r.weakest && r.weakest.r < 1 ? `<span>En zayıf: <a href="#/t/${r.weakest.t.id}">${esc(r.weakest.t.title)} (${r.weakest.pr.solved}/${r.weakest.pr.total})</a></span>` : ""}
        ${left > 0 && daysLeft() >= 0 ? `<span>Hedef: günde ~${perDay} soru</span>` : ""}
      </div>`;
  }

  function renderNav() {
    const nav = $("#topic-nav");
    nav.innerHTML = "";
    for (const t of state.topics) {
      const pr = topicProgress(t.id);
      const a = el("a", { href: "#/t/" + t.id, class: "nav-item", "data-topic": t.id });
      const unit = t.id === "exam" ? "bitti" : "çözüldü";
      a.innerHTML = `<span class="nav-num">${t.num}</span><span class="nav-title">${esc(t.title)}</span>` +
        `<span class="nav-prog${pr.total && pr.solved === pr.total ? " done" : ""}">${pr.total ? `${pr.solved}/${pr.total} ${unit}` : "—"}</span>`;
      nav.appendChild(a);
    }
    highlightNav();
  }
  function highlightNav() {
    const m = location.hash.match(/^#\/(?:t|exam)\/([\w-]+)/);
    let tid = m && m[1];
    if (location.hash.startsWith("#/exam/")) tid = "exam";
    $$(".nav-item").forEach((a) => a.classList.toggle("active", !!tid && a.dataset.topic === tid));
  }
  function refreshProgress() {
    renderNav();
    renderStatusBar();
    const m = location.hash.match(/^#\/t\/([\w-]+)/);
    if (m) {
      const pr = topicProgress(m[1]);
      const tp = $(".topic-prog");
      if (tp) tp.textContent = `${pr.solved}/${pr.total} ${m[1] === "exam" ? "bitti" : "çözüldü"}`;
      const bar = $(".topic-progress > span");
      if (bar) bar.style.width = (pr.total ? (100 * pr.solved / pr.total) : 0) + "%";
    }
  }

  // ================================================================ yönlendirme
  function route() {
    clearInterval(state.timer);
    state.editors = [];
    highlightNav();
    $("#sidebar").classList.remove("open");
    const h = location.hash;
    let m;
    if ((m = h.match(/^#\/exam\/([\w-]+)/))) renderExamPage(m[1]);
    else if ((m = h.match(/^#\/t\/([\w-]+)/))) renderTopic(m[1]);
    else renderHome();
    $("#main").focus({ preventScroll: true });
    window.scrollTo(0, 0);
  }
  window.addEventListener("hashchange", route);
  const refreshEditors = () => setTimeout(() => state.editors.forEach((ed) => ed.refresh()), 0);

  // ================================================================ ana sayfa
  function renderHome() {
    const main = $("#main");
    const r = readiness();
    main.innerHTML = `
      <section class="home-hero">
        <h1>ELE411 Data Structures — Ara Sınav Çalışması</h1>
        <p class="muted">Ders notları, örnek sorular ve geçmiş sınavlardan derlenmiş sorular. Kodunuz bilgisayarınızdaki
        <b>g++</b> ile derlenip çalıştırılır; testler kenar durumları ve “sırayı koru” koşulunu kontrol eder.</p>
        <p><b>${r.solved}/${r.n}</b> soru çözüldü · <b>${r.examsDone}/${r.exams}</b> deneme sınavı bitti.</p>
      </section>
      <div class="topic-grid" id="topic-grid"></div>
      <section class="tips">
        <h3>Nasıl kullanılır?</h3>
        <ul>
          <li><b>Çalıştır</b> (<kbd>Ctrl</kbd>+<kbd>Enter</kbd>): kodunuzu kendi <code>main()</code>’iniz ile çalıştırır. İsterseniz stdin girişi verebilirsiniz.</li>
          <li><b>Test et</b> (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Enter</kbd>): fonksiyonunuzu sorunun testleriyle sınar (<code>main()</code>’iniz yok sayılır). Hepsi geçerse soru “çözüldü” olur.</li>
          <li>İzleme sorularında tahmininizi yazıp kontrol edin; sıralama izlemede her adımı kutulara yazın.</li>
          <li><code>Stack</code>, <code>Queue</code>, <code>Node</code>, <code>StringNode</code> sınıfları sınavdaki UML ile aynıdır ve otomatik eklenir. <code>pop()</code> değer döndürmez!</li>
          <li>Önerilen sıra: konuları çalış → <a href="#/t/exam">deneme sınavları</a>. Üstteki çubuk sınava hazırlık düzeyinizi gösterir.</li>
        </ul>
      </section>`;
    const grid = $("#topic-grid");
    for (const t of state.topics) {
      const pr = topicProgress(t.id);
      const a = el("a", { href: "#/t/" + t.id, class: "topic-card" });
      a.innerHTML = `<div class="tc-num">KONU ${t.num}</div><div class="tc-title">${esc(t.title)}</div>` +
        `<div class="progress"><span style="width:${pr.total ? 100 * pr.solved / pr.total : 0}%"></span></div><div class="muted small">${pr.solved}/${pr.total} ${t.id === "exam" ? "bitti" : "çözüldü"}</div>`;
      grid.appendChild(a);
    }
  }

  // ================================================================ konu sayfası
  function renderTopic(tid) {
    const t = state.topics.find((x) => x.id === tid);
    const main = $("#main");
    if (!t) { main.innerHTML = `<div class="placeholder">Konu bulunamadı.</div>`; return; }
    const ps = topicProblems(tid);
    const pr = topicProgress(tid);
    main.innerHTML = `
      <div class="topic-head"><h1>${t.num}. ${esc(t.title)}</h1><span class="topic-prog">${pr.solved}/${pr.total} ${tid === "exam" ? "bitti" : "çözüldü"}</span></div>
      <div class="progress topic-progress"><span style="width:${pr.total ? 100 * pr.solved / pr.total : 0}%"></span></div>`;
    if (t.summary) {
      const d = el("details", { class: "summary" });
      if (store.get("summaryOpen." + tid, true)) d.open = true;
      d.innerHTML = `<summary>${tid === "exam" ? "Nasıl çalışır?" : "Konu özeti (ders notlarından)"}</summary><div class="summary-body">${t.summary}</div>`;
      d.addEventListener("toggle", () => store.set("summaryOpen." + tid, d.open));
      main.appendChild(d);
    }
    if (tid !== "exam" && ps.length > 2) {
      const toc = el("nav", { class: "toc" });
      toc.innerHTML = ps.map((p, i) => `<a href="#p-${p.id}" data-id="${p.id}" class="${isSolved(p) ? "done" : ""}">${t.num}.${i + 1} ${esc(p.title)}</a>`).join("");
      toc.addEventListener("click", (e) => { const a = e.target.closest("a"); if (!a) return; e.preventDefault(); const c = document.getElementById("p-" + a.dataset.id); if (c) c.scrollIntoView({ behavior: "smooth" }); });
      main.appendChild(toc);
    }
    ps.forEach((p, i) => main.appendChild(p.type === "exam" ? renderExamCard(p) : renderProblem(p, `${t.num}.${i + 1}`)));
    refreshEditors();
  }

  // ================================================================ soru kartı (ortak)
  // opts: { prefix: "" | "exam.<id>.", locked: bool }
  function renderProblem(p, num, opts) {
    opts = Object.assign({ prefix: "", locked: false }, opts || {});
    const solved = isSolved(p, opts.prefix);
    const card = el("article", { class: "card" + (solved ? " solved" : ""), id: "p-" + p.id });
    const diff = (p.difficulty || "").toLowerCase().replace("ı", "i");
    card.innerHTML = `
      <div class="card-head">
        <span class="card-num">${num}</span>
        <h3>${esc(p.title)}</h3>
        <div class="chips">
          ${p.source ? `<span class="chip src">${esc(p.source)}</span>` : ""}
          ${p.difficulty ? `<span class="chip diff-${esc(diff)}">${esc(p.difficulty)}</span>` : ""}
          <span class="chip solved-chip"${solved ? "" : " hidden"}>✓ ${p.type === "open" ? "Tamamlandı" : "Çözüldü"}</span>
        </div>
      </div>
      <div class="statement">${p.statement || ""}</div>`;
    if (p.io && (p.io.inputs || p.io.outputs)) {
      const li = (arr) => (arr || []).map((x) => `<li>${x}</li>`).join("");
      card.appendChild(el("div", { class: "io" }, `<div><h5>Girdiler</h5><ul>${li(p.io.inputs)}</ul></div><div><h5>Çıktılar</h5><ul>${li(p.io.outputs)}</ul></div>`));
    }
    if (p.signature) card.appendChild(el("div", { class: "sig" }, `İmza: <code>${esc(p.signature)}</code>`));
    const ctx = {
      p, card, opts,
      key: (k) => opts.prefix + k + "." + p.id,
      solved: () => {
        if (!isSolved(p, opts.prefix)) store.set(opts.prefix + "solved." + p.id, Date.now());
        card.classList.add("solved");
        $(".solved-chip", card).hidden = false;
        refreshProgress();
      },
    };
    if (opts.locked) card.appendChild(el("div", { class: "lock-note" }, "🔒 Sınav sürüyor: ipucu, çözüm ve kontrol kapalı."));
    const builders = { code: buildCodeUI, trace: buildTraceUI, mcq: buildMcqUI, open: buildOpenUI, sorttrace: buildSortTraceUI };
    if (builders[p.type]) builders[p.type](ctx);
    else card.appendChild(el("div", { class: "out-note" }, esc(p.error || "Bilinmeyen soru tipi")));
    return card;
  }

  function makeEditor(parent, value, extra) {
    const ed = CodeMirror(parent, Object.assign({
      value, mode: "text/x-c++src", lineNumbers: true,
      indentUnit: 4, tabSize: 4, indentWithTabs: false, smartIndent: true,
      matchBrackets: true, autoCloseBrackets: true, viewportMargin: Infinity,
    }, extra || {}));
    if (extra && extra.readOnly) ed.getWrapperElement().classList.add("CodeMirror-readonly");
    state.editors.push(ed);
    return ed;
  }

  function solutionToggle(ctx, getContentEl) {
    const b = btn("", "Çözümü göster");
    const box = el("div", { class: "solution", hidden: "" });
    let built = false;
    b.addEventListener("click", () => {
      if (!box.hidden) { box.hidden = true; b.textContent = "Çözümü göster"; return; }
      if (!confirm("Çözümü görmek istediğinize emin misiniz?\n\nÖnce kendiniz denemeniz önerilir.")) return;
      if (!built) { getContentEl(box); built = true; }
      box.hidden = false;
      b.textContent = "Çözümü gizle";
      refreshEditors();
    });
    return { button: b, box };
  }

  // ---------------------------------------------------------------- kod yazma
  function buildCodeUI(ctx) {
    const { p, card, opts } = ctx;
    const wrap = el("div", { class: "editor-wrap" });
    card.appendChild(wrap);
    const saved = store.get(ctx.key("code"), null);
    const ed = makeEditor(wrap, saved != null ? saved : (p.starter || ""), {
      extraKeys: {
        "Ctrl-Enter": () => run(), "Cmd-Enter": () => run(),
        "Shift-Ctrl-Enter": () => test(), "Shift-Cmd-Enter": () => test(),
        Tab: (cm) => cm.somethingSelected() ? cm.indentSelection("add") : cm.replaceSelection("    ", "end"),
        "Shift-Tab": (cm) => cm.indentSelection("subtract"),
      },
    });
    let saveTimer = null;
    ed.on("change", () => {
      clearErrorMarks(ed);
      clearTimeout(saveTimer);
      saveTimer = setTimeout(() => store.set(ctx.key("code"), ed.getValue()), 400);
    });

    const stdinBox = el("details", { class: "stdin-box" });
    const stdinSaved = store.get(ctx.key("stdin"), "");
    if (stdinSaved) stdinBox.open = true;
    stdinBox.innerHTML = `<summary>stdin girişi (isteğe bağlı, sadece “Çalıştır” için)</summary><textarea spellcheck="false" placeholder="ör. 3 4"></textarea>`;
    const stdinTa = $("textarea", stdinBox);
    stdinTa.value = stdinSaved;
    stdinTa.addEventListener("input", () => store.set(ctx.key("stdin"), stdinTa.value));
    card.appendChild(stdinBox);

    const hints = p.hints || [];
    const actions = el("div", { class: "actions" });
    const bRun = btn("btn-primary", "▶ Çalıştır <kbd>Ctrl+Enter</kbd>", () => run());
    const bTest = btn("btn-ok", "✓ Test et", () => test());
    const bHint = btn("", "", null);
    const bReset = btn("btn-ghost", "↺ Sıfırla", null);
    const status = el("span", { class: "status" });
    const sol = solutionToggle(ctx, (box) => {
      box.innerHTML = `<div class="solution-head">Referans çözüm <span class="spacer"></span></div><div class="sol-ed"></div>` +
        (p.solutionNote ? `<div class="solution-note">${p.solutionNote}</div>` : "");
      const copy = btn("btn-sm", "Editöre kopyala", () => { if (confirm("Editördeki kodunuz çözümle değiştirilecek. Emin misiniz?")) ed.setValue(p.solution); });
      $(".solution-head", box).appendChild(copy);
      makeEditor($(".sol-ed", box), p.solution, { readOnly: true });
    });
    actions.append(bRun);
    if (p.has_tests && !opts.locked) actions.append(bTest);
    if (hints.length && !opts.locked) actions.append(bHint);
    if (p.solution && !opts.locked) actions.append(sol.button);
    actions.append(el("span", { class: "spacer" }), status, bReset);
    card.appendChild(actions);

    const hintBox = el("div", { class: "hints" });
    const out = el("div", { class: "output" });
    card.append(hintBox, out, sol.box);

    let shown = Math.min(store.get(ctx.key("hints"), 0), hints.length);
    function drawHints() {
      hintBox.innerHTML = opts.locked ? "" : hints.slice(0, shown).map((h, i) => `<div class="hint"><b>İpucu ${i + 1}:</b> ${esc(h)}</div>`).join("");
      bHint.textContent = `💡 İpucu (${shown}/${hints.length})`;
      bHint.disabled = shown >= hints.length;
    }
    drawHints();
    bHint.addEventListener("click", () => { shown = Math.min(shown + 1, hints.length); store.set(ctx.key("hints"), shown); drawHints(); });

    bReset.addEventListener("click", () => {
      if (!confirm("Kodunuz silinip başlangıç koduna dönülecek. Emin misiniz?")) return;
      ed.setValue(p.starter || "");
      store.del(ctx.key("code"));
      out.innerHTML = "";
    });

    function busy(on, msg) { bRun.disabled = bTest.disabled = on; status.textContent = msg || ""; }
    async function run() {
      if (bRun.disabled) return;
      store.set(ctx.key("code"), ed.getValue());
      busy(true, "Derleniyor ve çalıştırılıyor…");
      try {
        const r = await api("/run", { code: ed.getValue(), stdin: stdinTa.value });
        out.innerHTML = "";
        out.appendChild(r.error ? errorPanel(r.error) : renderRun(r, ed));
        busy(false, r.compile_ok ? `${r.time_ms} ms` : "");
      } catch (e) { out.innerHTML = ""; out.appendChild(errorPanel(e.message)); busy(false); }
    }
    async function test() {
      if (!p.has_tests || bTest.disabled || opts.locked) return;
      store.set(ctx.key("code"), ed.getValue());
      busy(true, "Derleniyor ve testler çalıştırılıyor…");
      try {
        const r = await api("/test", { problem_id: p.id, code: ed.getValue() });
        out.innerHTML = "";
        out.appendChild(r.error && !r.tests ? errorPanel(r.error) : renderTest(r, ed));
        if (r.all_passed) ctx.solved();
        busy(false, r.time_ms ? `${(r.time_ms / 1000).toFixed(1)} sn` : "");
      } catch (e) { out.innerHTML = ""; out.appendChild(errorPanel(e.message)); busy(false); }
    }
    card._runTests = test; // deneme sınavı özetinden çağrılır
  }

  // ---------------------------------------------------------------- izleme (kod çıktısı)
  function buildTraceUI(ctx) {
    const { p, card, opts } = ctx;
    const codeWrap = el("div", { class: "editor-wrap" });
    card.appendChild(codeWrap);
    makeEditor(codeWrap, p.code, { readOnly: true });
    const savedAns = store.get(ctx.key("trace"), []);
    const form = el("div", { class: "blanks" });
    const inputs = p.blanks.map((b, i) => {
      const row = el("label", { class: "blank" });
      row.innerHTML = `<span class="blank-label">${esc(b.label)}</span><input type="text" spellcheck="false" autocomplete="off" placeholder="tahmininiz">` +
        `<span class="blank-mark"></span>`;
      const inp = $("input", row);
      inp.value = savedAns[i] || "";
      inp.addEventListener("input", () => { savedAns[i] = inp.value; store.set(ctx.key("trace"), savedAns); });
      inp.addEventListener("keydown", (e) => { if (e.key === "Enter") { e.preventDefault(); check(true); } });
      form.appendChild(row);
      return inp;
    });
    card.appendChild(form);
    const actions = el("div", { class: "actions" });
    const out = el("div", { class: "output" });
    const status = el("span", { class: "status" });
    const bCheck = btn("btn-ok", "▶ Çalıştırıp kontrol et", () => check(true));
    const sol = solutionToggle(ctx, (box) => {
      box.innerHTML = `<div class="solution-head">Doğru cevaplar ve açıklama</div><div class="solution-note">` +
        `<ul>${p.blanks.map((b) => `<li>${esc(b.label)}: <b>${esc(b.answer)}</b></li>`).join("")}</ul>${p.explanation || ""}</div>`;
    });
    if (!opts.locked) actions.append(bCheck, sol.button);
    actions.append(el("span", { class: "spacer" }), status);
    card.append(actions, out, sol.box);

    async function check(runIt) {
      if (opts.locked) return;
      let ok = true;
      p.blanks.forEach((b, i) => {
        const good = sameTokens(inputs[i].value, b.answer);
        ok = ok && good;
        const mark = inputs[i].parentElement.querySelector(".blank-mark");
        mark.textContent = good ? "✓" : "✗";
        mark.className = "blank-mark " + (good ? "good" : "bad");
        inputs[i].parentElement.classList.toggle("bad", !good);
        inputs[i].parentElement.classList.toggle("good", good);
      });
      out.innerHTML = "";
      const head = el("div", { class: "test-summary " + (ok ? "all" : "some") }, ok ? "✓ Hepsi doğru!" : "Bazı cevaplar yanlış (✗). Tekrar düşünün ya da çözüme bakın.");
      const panel = el("div", { class: "out-panel" });
      panel.appendChild(head);
      out.appendChild(panel);
      if (ok) {
        ctx.solved();
        if (p.explanation) panel.appendChild(el("div", { class: "solution-note" }, p.explanation));
      }
      if (runIt && p.runCode) {
        status.textContent = "Program çalıştırılıyor…";
        bCheck.disabled = true;
        try {
          const r = await api("/run", { code: p.runCode, stdin: "" });
          panel.appendChild(el("div", { class: "out-label" }, "Gerçek program çıktısı (kontrol noktaları için eklenmiş yazdırmalarla)"));
          panel.appendChild(el("pre", { class: "out-pre" }, esc(r.compile_ok ? r.stdout : r.compile_output)));
        } catch (e) { panel.appendChild(el("div", { class: "out-note" }, esc(e.message))); }
        status.textContent = "";
        bCheck.disabled = false;
      }
    }
  }

  // ---------------------------------------------------------------- çoktan seçmeli
  function buildMcqUI(ctx) {
    const { p, card, opts } = ctx;
    const saved = store.get(ctx.key("mcq"), {});
    const list = el("div", { class: "mcq" });
    p.items.forEach((it, i) => {
      const options = it.options || p.options || [];
      const item = el("div", { class: "mcq-item" });
      item.innerHTML = `<div class="mcq-q">${it.q}</div>` + (it.code ? `<pre class="snippet">${esc(it.code)}</pre>` : "") +
        `<div class="mcq-opts">${options.map((o) => `<label class="opt"><input type="radio" name="${opts.prefix}${p.id}-${i}" value="${esc(o)}"${saved[i] === o ? " checked" : ""}><span>${esc(o)}</span></label>`).join("")}</div>` +
        `<div class="mcq-exp" hidden></div>`;
      $$("input", item).forEach((r) => r.addEventListener("change", () => { saved[i] = r.value; store.set(ctx.key("mcq"), saved); item.classList.remove("good", "bad"); }));
      list.appendChild(item);
    });
    card.appendChild(list);
    const actions = el("div", { class: "actions" });
    const out = el("div", { class: "output" });
    const bCheck = btn("btn-ok", "✓ Kontrol et", () => {
      let correct = 0;
      $$(".mcq-item", list).forEach((item, i) => {
        const it = p.items[i];
        const ok = saved[i] === it.answer;
        if (ok) correct++;
        item.classList.toggle("good", ok);
        item.classList.toggle("bad", !ok);
        const exp = $(".mcq-exp", item);
        exp.hidden = false;
        exp.innerHTML = (ok ? "✓ Doğru. " : `✗ ${saved[i] ? "Yanlış" : "Boş"} — doğru cevap: <b>${esc(it.answer)}</b>. `) + (it.explain || "");
      });
      const all = correct === p.items.length;
      out.innerHTML = "";
      out.appendChild(el("div", { class: "out-panel" }, `<div class="test-summary ${all ? "all" : "some"}">${all ? "✓ Hepsi doğru!" : `${correct}/${p.items.length} doğru`}</div>`));
      if (all) ctx.solved();
    });
    const bReset = btn("btn-ghost", "↺ Temizle", () => {
      for (const k in saved) delete saved[k];
      store.del(ctx.key("mcq"));
      $$("input", list).forEach((r) => { r.checked = false; });
      $$(".mcq-item", list).forEach((x) => { x.classList.remove("good", "bad"); $(".mcq-exp", x).hidden = true; });
      out.innerHTML = "";
    });
    if (!opts.locked) actions.append(bCheck);
    actions.append(el("span", { class: "spacer" }), bReset);
    card.append(actions, out);
  }

  // ---------------------------------------------------------------- açık uçlu
  function buildOpenUI(ctx) {
    const { p, card, opts } = ctx;
    const ta = el("textarea", { class: "open-answer", spellcheck: "true", placeholder: "Cevabınızı buraya yazın (otomatik kaydedilir)…" });
    ta.value = store.get(ctx.key("open"), "");
    const count = el("span", { class: "status" });
    const upd = () => { count.textContent = `${ta.value.trim() ? ta.value.trim().split(/\s+/).length : 0} kelime`; };
    upd();
    ta.addEventListener("input", () => { store.set(ctx.key("open"), ta.value); upd(); });
    card.appendChild(ta);
    const actions = el("div", { class: "actions" });
    const sol = solutionToggle(ctx, (box) => { box.innerHTML = `<div class="solution-head">Örnek cevap</div><div class="solution-note">${p.sampleAnswer || ""}</div>`; });
    sol.button.textContent = "Örnek cevabı göster";
    const bDone = btn("btn-ok", "✓ Tamamlandı olarak işaretle", () => {
      if (ta.value.trim().split(/\s+/).length < 30 && !confirm("Cevabınız oldukça kısa. Yine de tamamlandı olarak işaretlensin mi?")) return;
      ctx.solved();
    });
    if (!opts.locked) actions.append(sol.button, bDone);
    actions.append(el("span", { class: "spacer" }), count);
    card.append(actions, sol.box);
  }

  // ---------------------------------------------------------------- sıralama izleme
  const ALGO_INFO = {
    selection: ["Selection sort (maksimumu seçen)", "Her geçişte sıralanmamış kısmın en büyüğü, kısmın son elemanıyla takas edilir. Her geçişten sonraki diziyi yazın."],
    insertion: ["Insertion sort", "Her adımda sıradaki eleman sıralı kısımda yerine yerleştirilir (1. elemandan başlayarak). Her yerleştirmeden sonraki diziyi yazın."],
    bubble: ["Bubble sort", "Her geçişte komşular karşılaştırılıp takas edilir. Takas yapılan her geçişten sonraki diziyi yazın; takas olmayan geçişte durulur (yazılmaz)."],
    quick: ["Quick sort (son eleman pivot)", "Lomuto bölümleme: pivot = alt dizinin son elemanı; ≤ pivot olanlar sola toplanır, sonra pivot yerine konur. Uzunluğu ≥ 2 olan her bölümlemeden sonraki diziyi yazın (önce sol parça)."],
    merge: ["Merge sort", "Orta = ⌊(first+last)/2⌋, önce sol yarı. Her birleştirmeden sonraki diziyi yazın."],
  };
  function sortSteps(algo, input) {
    const a = input.slice(), n = a.length, steps = [];
    const swap = (i, j) => { const t = a[i]; a[i] = a[j]; a[j] = t; };
    const snap = (label) => steps.push({ arr: a.slice(), label });
    if (algo === "selection") {
      for (let last = n - 1; last >= 1; last--) {
        let big = 0;
        for (let i = 1; i <= last; i++) if (a[i] > a[big]) big = i;
        swap(big, last);
        snap(`Geçiş ${n - last}`);
      }
    } else if (algo === "insertion") {
      for (let u = 1; u < n; u++) {
        const x = a[u];
        let loc = u;
        while (loc > 0 && a[loc - 1] > x) { a[loc] = a[loc - 1]; loc--; }
        a[loc] = x;
        snap(`Adım ${u}: ${x} yerleştirildi`);
      }
    } else if (algo === "bubble") {
      for (let pass = 1; pass < n; pass++) {
        let swapped = false;
        for (let i = 0; i < n - pass; i++) if (a[i] > a[i + 1]) { swap(i, i + 1); swapped = true; }
        if (!swapped) break;
        snap(`Geçiş ${pass}`);
      }
    } else if (algo === "quick") {
      let k = 0;
      (function qs(lo, hi) {
        if (lo >= hi) return;
        const pivot = a[hi];
        let i = lo - 1;
        for (let j = lo; j < hi; j++) if (a[j] <= pivot) { i++; swap(i, j); }
        swap(i + 1, hi);
        snap(`Bölümleme ${++k}: [${lo}..${hi}], pivot = ${pivot}`);
        qs(lo, i);
        qs(i + 2, hi);
      })(0, n - 1);
    } else if (algo === "merge") {
      let k = 0;
      (function ms(lo, hi) {
        if (lo >= hi) return;
        const mid = Math.floor((lo + hi) / 2);
        ms(lo, mid);
        ms(mid + 1, hi);
        const tmp = [];
        let i = lo, j = mid + 1;
        while (i <= mid && j <= hi) tmp.push(a[i] <= a[j] ? a[i++] : a[j++]);
        while (i <= mid) tmp.push(a[i++]);
        while (j <= hi) tmp.push(a[j++]);
        for (let t = 0; t < tmp.length; t++) a[lo + t] = tmp[t];
        snap(`Birleştirme ${++k}: [${lo}..${mid}] + [${mid + 1}..${hi}]`);
      })(0, n - 1);
    }
    return steps;
  }
  window.ele411SortSteps = sortSteps; // konsoldan kontrol için

  function buildSortTraceUI(ctx) {
    const { p, card, opts } = ctx;
    const algos = p.algos;
    let algo = algos[0];
    const presets = p.arrays.map((a) => a.slice());
    let randArr = store.get(ctx.key("strand"), null);
    let arrIdx = 0;

    const controls = el("div", { class: "st-controls" });
    if (algos.length > 1) {
      const tabs = el("div", { class: "seg" });
      algos.forEach((a) => {
        const b = btn("btn-sm", esc(ALGO_INFO[a][0]), () => { algo = a; draw(); });
        b.dataset.algo = a;
        tabs.appendChild(b);
      });
      controls.appendChild(tabs);
    }
    let sel = null;
    if (presets.length > 1 || p.random) {
      sel = el("select", { class: "st-select" });
      const fill = () => {
        sel.innerHTML = presets.map((a, i) => `<option value="${i}">${a.join(" ")}</option>`).join("") +
          (randArr ? `<option value="r">Rastgele: ${randArr.join(" ")}</option>` : "");
        sel.value = arrIdx === -1 ? "r" : String(arrIdx);
      };
      fill();
      sel.addEventListener("change", () => { arrIdx = sel.value === "r" ? -1 : +sel.value; draw(); });
      controls.appendChild(sel);
      if (p.random) controls.appendChild(btn("btn-sm", "🎲 Rastgele dizi üret", () => {
        const n = 7 + Math.floor(Math.random() * 4), pool = [];
        while (pool.length < n) { const v = 1 + Math.floor(Math.random() * 99); if (!pool.includes(v)) pool.push(v); }
        randArr = pool;
        store.set(ctx.key("strand"), randArr);
        arrIdx = -1; fill(); draw();
      }));
    }
    card.appendChild(controls);
    const body = el("div", { class: "st-body" });
    card.appendChild(body);

    const doneKey = (a) => opts.prefix + "stdone." + p.id + "." + a;
    function draw() {
      $$(".seg .btn", controls).forEach((b) => { b.classList.toggle("active", b.dataset.algo === algo); b.classList.toggle("done-algo", !!store.get(doneKey(b.dataset.algo), false)); });
      const arr = arrIdx === -1 && randArr ? randArr : presets[Math.max(arrIdx, 0)];
      const steps = sortSteps(algo, arr);
      const ansKey = `${opts.prefix}st.${p.id}.${algo}.${arr.join("_")}`;
      const saved = store.get(ansKey, []);
      body.innerHTML = `<div class="st-info"><b>${esc(ALGO_INFO[algo][0])}</b> — ${esc(ALGO_INFO[algo][1])}</div>`;
      const grid = el("div", { class: "st-grid" });
      const mkRow = (label, values, editable, rowIdx) => {
        const row = el("div", { class: "st-row" });
        row.appendChild(el("div", { class: "st-label" }, esc(label)));
        const cells = el("div", { class: "st-cells" });
        values.forEach((v, j) => {
          if (!editable) { cells.appendChild(el("span", { class: "cell fixed" }, esc(v))); return; }
          const inp = el("input", { class: "cell", type: "text", inputmode: "numeric", autocomplete: "off", "aria-label": `${label}, kutu ${j + 1}` });
          inp.value = (saved[rowIdx] || [])[j] || "";
          cells.appendChild(inp);
        });
        row.appendChild(cells);
        row.appendChild(el("span", { class: "st-mark" }));
        grid.appendChild(row);
        return row;
      };
      mkRow("Başlangıç", arr, false);
      const rows = steps.map((s, i) => mkRow(s.label, s.arr, true, i));
      body.appendChild(grid);
      body.appendChild(el("div", { class: "muted small" }, `${steps.length} adım · Kutular arasında boşluk/Enter ile geçebilir, bir satırı “1 2 3 …” diye yapıştırabilirsiniz.`));

      const allInputs = $$("input.cell", grid);
      const saveAll = () => store.set(ansKey, rows.map((r) => $$("input", r).map((x) => x.value.trim())));
      allInputs.forEach((inp, idx) => {
        inp.addEventListener("input", () => {
          if (/\s/.test(inp.value)) {
            const parts = inp.value.trim().split(/[\s,]+/).filter(Boolean);
            parts.forEach((v, k) => { if (allInputs[idx + k]) allInputs[idx + k].value = v; });
            const nx = allInputs[idx + parts.length];
            if (nx) nx.focus();
          }
          inp.closest(".st-row").classList.remove("good", "bad");
          inp.classList.remove("good", "bad");
          saveAll();
        });
        inp.addEventListener("keydown", (e) => {
          if (e.key === "Enter" || (e.key === " " && inp.value)) { e.preventDefault(); const nx = allInputs[idx + 1]; if (nx) nx.focus(); }
          else if (e.key === "Backspace" && !inp.value && idx > 0) { e.preventDefault(); allInputs[idx - 1].focus(); }
        });
      });

      const actions = el("div", { class: "actions" });
      const out = el("div", { class: "output" });
      const bCheck = btn("btn-ok", "✓ Kontrol et", () => {
        let okRows = 0;
        rows.forEach((row, i) => {
          let rowOk = true;
          $$("input", row).forEach((inp, j) => {
            const good = inp.value.trim() === String(steps[i].arr[j]);
            inp.classList.toggle("good", good);
            inp.classList.toggle("bad", !good);
            rowOk = rowOk && good;
          });
          row.classList.toggle("good", rowOk);
          row.classList.toggle("bad", !rowOk);
          $(".st-mark", row).textContent = rowOk ? "✓" : "✗";
          if (rowOk) okRows++;
        });
        const all = okRows === steps.length;
        out.innerHTML = `<div class="out-panel"><div class="test-summary ${all ? "all" : "some"}">${all ? "✓ Tüm adımlar doğru!" : `${okRows}/${steps.length} adım doğru`}</div></div>`;
        if (all) {
          store.set(doneKey(algo), true);
          $$(".seg .btn", controls).forEach((b) => b.classList.toggle("done-algo", !!store.get(doneKey(b.dataset.algo), false)));
          if (algos.every((a) => store.get(doneKey(a), false))) ctx.solved();
          else out.firstChild.appendChild(el("div", { class: "muted small", style: "padding:6px 14px" }, "Soruyu tamamlamak için diğer algoritmaları da yapın: " + algos.filter((a) => !store.get(doneKey(a), false)).map((a) => ALGO_INFO[a][0]).join(", ")));
        }
      });
      const bShow = btn("", "Doğru izlemeyi göster", () => {
        if (!confirm("Doğru adımlar gösterilsin mi?")) return;
        rows.forEach((row, i) => {
          if ($(".st-answer", row)) return;
          row.appendChild(el("div", { class: "st-answer" }, steps[i].arr.join(" ")));
        });
      });
      const bClear = btn("btn-ghost", "↺ Temizle", () => { store.del(ansKey); draw(); });
      if (!opts.locked) actions.append(bCheck, bShow);
      actions.append(el("span", { class: "spacer" }), bClear);
      body.append(actions, out);
    }
    draw();
  }

  // ================================================================ çıktı panelleri
  function errorPanel(msg) {
    return el("div", { class: "out-panel out-err" }, `<div class="out-head"><span class="tag">Hata</span></div><div class="out-note">${esc(msg)}</div>`);
  }
  function clearErrorMarks(ed) {
    (ed._errLines || []).forEach((h) => ed.removeLineClass(h, "background", "cm-error-line"));
    ed._errLines = [];
  }
  function parseDiagnostics(text) {
    const res = [];
    const re = /^(user\.cpp):(\d+):(\d+):\s+(fatal error|error|warning|note):\s+(.*)$/gm;
    let m;
    while ((m = re.exec(text))) res.push({ line: +m[2], col: +m[3], kind: m[4], msg: m[5] });
    return res;
  }
  function compilePanel(text, ed, ok) {
    const diags = parseDiagnostics(text).filter((d) => d.kind !== "note");
    const panel = el("div", { class: "out-panel " + (ok ? "out-warn" : "out-err") });
    const errs = diags.filter((d) => d.kind !== "warning");
    const warns = diags.filter((d) => d.kind === "warning");
    panel.appendChild(el("div", { class: "out-head" },
      ok ? `<span class="tag">Derleyici uyarıları</span><span class="muted">${warns.length} uyarı</span>`
        : `<span class="tag">Derleme hatası</span><span class="muted">${errs.length} hata${warns.length ? ", " + warns.length + " uyarı" : ""}</span>`));
    if (diags.length) {
      const ul = el("ul", { class: "err-list" });
      clearErrorMarks(ed);
      for (const d of diags) {
        const li = el("li", { class: d.kind === "warning" ? "warn" : "" });
        li.innerHTML = `<a title="Satıra git">Satır ${d.line}:${d.col}</a> <span>${d.kind === "warning" ? "uyarı" : "hata"}: ${esc(d.msg)}</span>`;
        $("a", li).addEventListener("click", () => { ed.focus(); ed.setCursor({ line: d.line - 1, ch: d.col - 1 }); ed.scrollIntoView(null, 80); });
        ul.appendChild(li);
        if (d.kind !== "warning" && d.line - 1 < ed.lineCount()) ed._errLines.push(ed.addLineClass(d.line - 1, "background", "cm-error-line"));
      }
      panel.appendChild(ul);
    }
    const raw = el("details", { class: "raw-out" });
    if (!diags.length) raw.open = true;
    raw.innerHTML = `<summary>Derleyicinin tam çıktısı</summary><pre class="out-pre">${esc(text.trim())}</pre>`;
    panel.appendChild(raw);
    return panel;
  }
  function renderRun(r, ed) {
    const frag = document.createDocumentFragment();
    if (!r.compile_ok) { frag.appendChild(compilePanel(r.compile_output || "", ed, false)); return frag; }
    clearErrorMarks(ed);
    if (r.compile_output && r.compile_output.trim()) frag.appendChild(compilePanel(r.compile_output, ed, true));
    const bad = r.timed_out || (r.exit_code !== 0);
    const panel = el("div", { class: "out-panel " + (bad ? "out-err" : "out-ok") });
    const tag = r.timed_out ? "⏱ Zaman aşımı (5 sn) — program durduruldu" : (r.exit_code === 0 ? "Program bitti" : "Program hatayla bitti");
    panel.appendChild(el("div", { class: "out-head" }, `<span class="tag">${tag}</span><span class="muted">çıkış kodu: ${r.exit_code == null ? "—" : r.exit_code} · ${r.time_ms} ms</span>`));
    if (r.exit_note) panel.appendChild(el("div", { class: "out-note" }, esc(r.exit_note)));
    panel.appendChild(el("div", { class: "out-label" }, "Çıktı (stdout)"));
    panel.appendChild(el("pre", { class: "out-pre" }, r.stdout ? esc(r.stdout) : `<span class="empty-out">(çıktı yok)</span>`));
    if (r.stderr) {
      panel.appendChild(el("div", { class: "out-label" }, "Hata akışı (stderr)"));
      panel.appendChild(el("pre", { class: "out-pre stderr" }, esc(r.stderr)));
    }
    frag.appendChild(panel);
    return frag;
  }
  function renderTest(r, ed) {
    const frag = document.createDocumentFragment();
    if (!r.compile_ok) { frag.appendChild(compilePanel(r.compile_output || "", ed, false)); return frag; }
    clearErrorMarks(ed);
    if (r.compile_output && parseDiagnostics(r.compile_output).some((d) => d.kind === "warning")) frag.appendChild(compilePanel(r.compile_output, ed, true));
    const panel = el("div", { class: "out-panel" });
    const all = r.all_passed;
    const pct = r.total ? 100 * r.passed / r.total : 0;
    panel.appendChild(el("div", { class: "test-summary " + (all ? "all" : "some") },
      `<span>${all ? "✓ Tüm testler geçti!" : (r.passed === r.total && r.violations && r.violations.length ? "Testler geçti ama kural ihlali var" : `${r.passed}/${r.total} test geçti`)}</span>` +
      `<span class="bar"><span style="width:${pct}%"></span></span><span class="muted small">${(r.time_ms / 1000).toFixed(1)} sn</span>`));
    if (r.violations && r.violations.length) {
      panel.appendChild(el("div", { class: "violations" },
        `<b>⚠ Sınav kuralı ihlali</b> — sınavda puan kaybettirir:<ul>${r.violations.map((v) => `<li>Satır ${v.line}: ${esc(v.rule)} <code>${esc(v.text)}</code></li>`).join("")}</ul>`));
    }
    if (r.error) panel.appendChild(el("div", { class: "out-note" }, esc(r.error)));
    const list = el("div", { class: "tests" });
    for (const t of r.tests || []) {
      const box = el("div", { class: "test " + (t.passed ? "pass collapsed" : "fail") });
      const row = el("div", { class: "test-row" },
        `<span class="test-icon">${t.passed ? "✓" : "✗"}</span><span class="test-name">${esc(t.name)}</span>` +
        `<span class="test-input" title="${esc(t.input)}">${esc(t.input)}</span><span class="test-time">${t.time_ms} ms</span>`);
      row.addEventListener("click", () => box.classList.toggle("collapsed"));
      box.appendChild(row);
      const det = el("div", { class: "test-detail" });
      det.appendChild(el("div", { class: "muted small" }, `<b>Girdi:</b> <code>${esc(t.input)}</code>`));
      if (t.problem) det.appendChild(el("div", { class: "test-problem" }, esc(t.problem)));
      if (t.checks && t.checks.length) {
        const tbl = el("table", { class: "checks" });
        tbl.innerHTML = `<tr><th></th><th>Kontrol</th><th>Beklenen</th><th>Sizin sonucunuz</th></tr>` + t.checks.map((c) =>
          `<tr class="${c.pass ? "good" : "bad"}"><td>${c.pass ? "✓" : "✗"}</td><td>${esc(c.label)}</td><td class="v">${esc(c.expected)}</td><td class="v actual">${esc(c.actual)}</td></tr>`).join("");
        det.appendChild(tbl);
      } else if (!t.problem) det.appendChild(el("div", { class: "test-problem" }, "Hiçbir kontrol çalışmadı."));
      (t.notes || []).forEach((n) => det.appendChild(el("div", { class: "muted small" }, esc(n))));
      if (t.output) det.appendChild(el("div", { class: "test-extra" }, "<b>Fonksiyonunuzun ekrana yazdıkları:</b>\n" + esc(t.output)));
      if (t.stderr) det.appendChild(el("div", { class: "test-extra stderr" }, esc(t.stderr)));
      box.appendChild(det);
      list.appendChild(box);
    }
    panel.appendChild(list);
    frag.appendChild(panel);
    return frag;
  }

  // ================================================================ deneme sınavı
  const examTotal = (p) => p.sections.reduce((s, x) => s + x.minutes, 0);
  function renderExamCard(p) {
    const st = store.get("exam." + p.id, null);
    const card = el("article", { class: "card exam-card" + (isSolved(p) ? " solved" : "") });
    const status = !st ? "Başlanmadı" : st.finished ? "✓ Bitti" : "⏱ Devam ediyor";
    card.innerHTML = `
      <div class="card-head"><h3>${esc(p.title)}</h3><div class="chips"><span class="chip src">${esc(p.source)}</span><span class="chip">${examTotal(p)} dk</span><span class="chip ${st && st.finished ? "solved-chip" : ""}">${status}</span></div></div>
      <div class="statement">${p.statement || ""}</div>
      <ol class="exam-sections">${p.sections.map((s) => { const q = state.byId[s.problem]; return `<li>${esc(q ? q.title : s.problem)} <span class="muted">· ${s.minutes} dk</span></li>`; }).join("")}</ol>
      <div class="actions"><a class="btn btn-primary" href="#/exam/${p.id}">${!st ? "Sınava başla →" : st.finished ? "Sonuçları gör →" : "Devam et →"}</a></div>`;
    return card;
  }

  function examAdvance(p, st, now) {
    // Kapalı kalınan süre dahil, süresi dolan bölümleri atla
    while (!st.finished) {
      const end = st.secStart + p.sections[st.sec].minutes * 60000;
      if (now < end) break;
      if (st.sec + 1 < p.sections.length) { st.sec++; st.secStart = end; }
      else { st.finished = true; st.finishedAt = end; }
    }
    return st;
  }
  function finishExam(p, st) {
    st.finished = true;
    st.finishedAt = Date.now();
    store.set("exam." + p.id, st);
    store.set("solved." + p.id, Date.now());
    refreshProgress();
  }

  function renderExamPage(id) {
    const p = state.byId[id];
    const main = $("#main");
    if (!p || p.type !== "exam") { main.innerHTML = `<div class="placeholder">Sınav bulunamadı.</div>`; return; }
    let st = store.get("exam." + id, null);
    const prefix = "exam." + id + ".";
    main.innerHTML = `<div class="topic-head"><h1>${esc(p.title)}</h1><a href="#/t/exam" class="muted">← Deneme sınavları</a></div>`;

    if (!st) {
      const intro = el("section", { class: "card" });
      intro.innerHTML = `<div class="statement">${p.statement || ""}<p>Toplam süre <b>${examTotal(p)} dakika</b>, ${p.sections.length} bölüm. Sınav başladığında ipuçları, çözümler ve otomatik kontroller kilitlenir. Her bölümün süresi bitince sonraki bölüme geçilir; isterseniz erken geçebilirsiniz. Sayfayı kapatsanız da süre işlemeye devam eder.</p></div>
        <ol class="exam-sections">${p.sections.map((s) => `<li>${esc((state.byId[s.problem] || {}).title || s.problem)} <span class="muted">· ${s.minutes} dk</span></li>`).join("")}</ol>`;
      const a = el("div", { class: "actions" });
      a.appendChild(btn("btn-primary", "⏱ Sınavı başlat", () => {
        store.delPrefix(prefix);
        store.set("exam." + id, { start: Date.now(), sec: 0, secStart: Date.now(), finished: false });
        renderExamPage(id);
      }));
      intro.appendChild(a);
      main.appendChild(intro);
      return;
    }

    st = examAdvance(p, st, Date.now());
    if (st.finished && !isSolved(p)) finishExam(p, st);
    store.set("exam." + id, st);

    if (!st.finished) {
      const s = p.sections[st.sec];
      const q = state.byId[s.problem];
      const bar = el("div", { class: "exam-bar" });
      bar.innerHTML = `<div><b>Bölüm ${st.sec + 1}/${p.sections.length}</b> · <span class="muted">${esc(q ? q.title : s.problem)}</span></div>
        <div class="exam-timers"><span>Bölümde kalan <b class="t-sec">--:--</b></span><span>Toplam kalan <b class="t-tot">--:--</b></span></div>`;
      const acts = el("div", { class: "exam-actions" });
      if (st.sec + 1 < p.sections.length) acts.appendChild(btn("btn-sm", "Sonraki bölüm →", () => {
        if (!confirm("Bu bölüme geri dönemezsiniz (kalan süresi iptal olur). Geçilsin mi?")) return;
        st.sec++; st.secStart = Date.now(); store.set("exam." + id, st); renderExamPage(id);
      }));
      acts.appendChild(btn("btn-sm btn-danger", "Sınavı bitir", () => {
        if (!confirm("Sınav bitirilsin mi? Çözümler ve kontroller açılacak.")) return;
        finishExam(p, st); renderExamPage(id);
      }));
      bar.appendChild(acts);
      main.appendChild(bar);
      const steps = el("ol", { class: "exam-steps" });
      steps.innerHTML = p.sections.map((x, i) => `<li class="${i < st.sec ? "past" : i === st.sec ? "now" : ""}">${i + 1}</li>`).join("");
      main.appendChild(steps);
      if (q) main.appendChild(renderProblem(q, `${st.sec + 1}`, { prefix, locked: true }));
      refreshEditors();
      const tick = () => {
        const now = Date.now();
        const secEnd = st.secStart + s.minutes * 60000;
        const rest = p.sections.slice(st.sec + 1).reduce((a, x) => a + x.minutes * 60000, 0);
        const ts = $(".t-sec", bar), tt = $(".t-tot", bar);
        if (ts) { ts.textContent = fmtTime(secEnd - now); ts.classList.toggle("urgent", secEnd - now < 60000); }
        if (tt) tt.textContent = fmtTime(secEnd - now + rest);
        if (now >= secEnd) {
          clearInterval(state.timer);
          const before = st.sec;
          examAdvance(p, st, now);
          store.set("exam." + id, st);
          if (st.finished) finishExam(p, st);
          alert(st.finished ? "Süre bitti! Sınav sona erdi; çözümler açıldı." : `Bölüm ${before + 1} süresi doldu. Bölüm ${st.sec + 1}'e geçiliyor.`);
          renderExamPage(id);
        }
      };
      tick();
      state.timer = setInterval(tick, 1000);
      return;
    }

    // ---- bitti: sonuçlar
    const used = Math.min(st.finishedAt - st.start, examTotal(p) * 60000);
    const summary = el("section", { class: "card exam-summary" });
    const rows = p.sections.map((s, i) => {
      const q = state.byId[s.problem];
      const ok = q && isSolved(q, prefix);
      const auto = q && (q.type !== "open");
      return `<tr><td>${i + 1}</td><td><a href="#sec-${i}" data-sec="${i}">${esc(q ? q.title : s.problem)}</a></td><td>${s.minutes} dk</td>` +
        `<td class="res-${i}">${ok ? '<span class="good">✓ Doğru</span>' : auto ? '<span class="muted">Kontrol edilmedi / yanlış</span>' : '<span class="muted">Örnek cevapla karşılaştırın</span>'}</td></tr>`;
    }).join("");
    summary.innerHTML = `<h2>Sınav bitti</h2><p>Kullanılan süre: <b>${fmtTime(used)}</b> / ${examTotal(p)} dk. Aşağıda her bölümde cevaplarınızı kontrol edebilir, çözümleri görebilirsiniz.</p>
      <table class="tbl"><tr><th>#</th><th>Bölüm</th><th>Süre</th><th>Sonuç</th></tr>${rows}</table>`;
    const acts = el("div", { class: "actions" });
    const bTestAll = btn("btn-ok", "✓ Tüm kod sorularını test et", async () => {
      bTestAll.disabled = true;
      for (const c of $$(".exam-review .card")) if (c._runTests) await c._runTests();
      bTestAll.disabled = false;
      renderExamSummaryResults();
    });
    acts.append(bTestAll, el("span", { class: "spacer" }), btn("btn-ghost", "↺ Sınavı sıfırla", () => {
      if (!confirm("Bu sınavdaki tüm cevaplarınız silinip sınav sıfırlansın mı?")) return;
      store.delPrefix(prefix); store.del("exam." + id); store.del("solved." + id);
      refreshProgress(); renderExamPage(id);
    }));
    summary.appendChild(acts);
    main.appendChild(summary);
    $$("a[data-sec]", summary).forEach((a) => a.addEventListener("click", (e) => { e.preventDefault(); const c = document.getElementById("sec-" + a.dataset.sec); if (c) c.scrollIntoView({ behavior: "smooth" }); }));
    const review = el("div", { class: "exam-review" });
    p.sections.forEach((s, i) => {
      const q = state.byId[s.problem];
      if (!q) return;
      const c = renderProblem(q, `${i + 1}`, { prefix, locked: false });
      c.id = "sec-" + i;
      review.appendChild(c);
    });
    main.appendChild(review);
    refreshEditors();
    function renderExamSummaryResults() {
      p.sections.forEach((s, i) => {
        const q = state.byId[s.problem];
        const cell = $(".res-" + i, summary);
        if (q && cell && isSolved(q, prefix)) cell.innerHTML = '<span class="good">✓ Doğru</span>';
      });
    }
    const obs = setInterval(() => { if (!document.body.contains(summary)) clearInterval(obs); else renderExamSummaryResults(); }, 1500);
  }

  // ================================================================ başlat
  async function load() {
    try {
      const r = await fetch("/api/problems", { cache: "no-store" });
      if (!r.ok) throw new Error();
      const d = await r.json();
      state.topics = d.topics.sort((a, b) => a.num - b.num);
      state.problems = d.problems;
      state.byId = {};
      d.problems.forEach((p) => { state.byId[p.id] = p; });
      setServer(true);
      renderNav();
      renderStatusBar();
      route();
    } catch (e) {
      setServer(false);
      $("#main").innerHTML = `<div class="placeholder"><h2>Sunucu çalışmıyor</h2><p><code>calisma-sitesi</code> klasöründeki <b>baslat.bat</b> dosyasını çift tıklayın. Sunucu açılınca bu sayfa kendiliğinden yüklenecek.</p></div>`;
      setTimeout(load, 3000);
    }
  }

  updateThemeButton();
  if (window.matchMedia) matchMedia("(prefers-color-scheme: dark)").addEventListener("change", updateThemeButton);
  renderCountdown();
  pollHealth();
  setInterval(pollHealth, 5000);
  load();
})();
