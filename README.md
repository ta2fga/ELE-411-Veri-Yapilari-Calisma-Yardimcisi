# ELE 411 Veri Yapıları Çalışma Yardımcısı

Hacettepe Üniversitesi **ELE 411 Data Structures** dersinin ara sınavına hazırlanmak için hazırlanmış,
bilgisayarınızda çalışan bir **C++ alıştırma sitesi**. LeetCode benzeri bir arayüzde soruyu okursunuz,
çözümünüzü tarayıcıdaki editöre yazarsınız, tek tuşla derleyip çalıştırırsınız ve otomatik testlerle
doğru olup olmadığını görürsünüz.

Sorular derste anlatılan konulardan, çalışma materyallerinden (Study Materials) ve geçmiş yılların
sınavlarından (Midterm 2019, Midterm 2020, midterm.pdf) derlenmiştir.

---

## İçindekiler

- [Ne işe yarar?](#ne-işe-yarar)
- [Gereksinimler](#gereksinimler)
- [Kurulum](#kurulum)
- [Başlatma](#başlatma)
- [Kullanım](#kullanım)
- [Konular ve sorular](#konular-ve-sorular)
- [Hazır sınıflar (`ele411.h`)](#hazır-sınıflar-ele411h)
- [Sorun giderme](#sorun-giderme)
- [Geliştiriciler için](#geliştiriciler-için)

---

## Ne işe yarar?

- **53 soru, 8 konu:** recursion, Big-O, diziler, bağlı listeler, stack, queue, sıralama ve deneme sınavları.
- **Gerçek derleme:** Kodunuz bilgisayarınızdaki `g++` ile derlenip çalıştırılır. Tarayıcı yalnızca arayüzdür.
- **Otomatik testler:** "Test et" dediğinizde fonksiyonunuz hazır testlerle sınanır. Her test için girdi,
  beklenen değer ve sizin değeriniz yan yana gösterilir.
- **Sınav kurallarına uygunluk:** "Yalnızca stack kullanın" gibi kurallara aykırı yapılar (dizi, `vector`,
  `Queue` vb.) yakalanır ve uyarı verilir.
- **Farklı soru tipleri:** kod yazma, kod izleme (çıktıyı tahmin etme), çoktan seçmeli, açık uçlu ve
  sıralama algoritmalarını adım adım izleme.
- **Süreli deneme sınavları:** Geçmiş sınavlar gerçek sürelerine göre zamanlayıcıyla çözülebilir.
- **İpucu ve çözüm:** İpuçları birer birer açılır. Takılırsanız Türkçe açıklamalı referans çözümü görebilirsiniz.
- **İlerleme takibi:** Üstteki hazırlık çubuğu kaç soru çözdüğünüzü, en zayıf konunuzu ve sınava kadar günde
  kaç soru çözmeniz gerektiğini gösterir.
- **İnternet gerekmez:** Her şey yerelde çalışır. Kodlarınız ve ilerlemeniz tarayıcınızda saklanır.

---

## Gereksinimler

| Gereksinim | Neden gerekli? | Sürüm |
|---|---|---|
| **Python 3** | Siteyi sunan yerel sunucu (`server.py`) | 3.8 veya üstü. Yalnızca standart kütüphane kullanılır, `pip install` gerekmez. |
| **g++ (C++ derleyicisi)** | Yazdığınız kodu derlemek için | C++17 destekleyen herhangi bir sürüm. Windows'ta **MSYS2 UCRT64** önerilir. |
| **Web tarayıcısı** | Arayüz için | Chrome, Edge, Firefox vb. güncel bir tarayıcı |

Proje Windows için hazırlanmıştır (`baslat.bat`). Python ve g++ kurulu olduğu sürece macOS ve Linux'ta da
`python3 server.py` ile çalıştırılabilir.

---

## Kurulum

### 1. Python 3'ü kurun

Kurulu olup olmadığını kontrol etmek için bir komut istemi (cmd veya PowerShell) açıp şunu yazın:

```bash
python --version
```

`Python 3.x.x` gibi bir çıktı görüyorsanız bu adımı atlayın. Görmüyorsanız:

**Yöntem A: Resmî yükleyici**

1. <https://www.python.org/downloads/> adresinden Python 3 yükleyicisini indirin.
2. Yükleyiciyi çalıştırın ve ilk ekrandaki **"Add python.exe to PATH"** kutusunu **mutlaka işaretleyin**.
3. "Install Now" ile kurulumu tamamlayın.

**Yöntem B: winget (Windows 10/11)**

```bash
winget install Python.Python.3.12
```

Kurulumdan sonra komut istemini kapatıp yeniden açın ve `python --version` ile tekrar kontrol edin.

### 2. g++ derleyicisini kurun (MSYS2)

Kurulu olup olmadığını kontrol edin:

```bash
g++ --version
```

Bir sürüm bilgisi görüyorsanız bu adımı atlayabilirsiniz. Görmüyorsanız:

1. <https://www.msys2.org/> adresinden MSYS2 yükleyicisini indirip kurun. **Kurulum klasörünü varsayılan
   değerde (`C:\msys64`) bırakın.** Site g++'ı bu klasörde arar.

   winget ile de kurabilirsiniz:

   ```bash
   winget install MSYS2.MSYS2
   ```

2. Başlat menüsünden **"MSYS2 UCRT64"** uygulamasını açın (diğer MSYS2 uygulamalarını değil).
3. Paketleri güncelleyin. Pencere kapanırsa yeniden açıp komutu bir kez daha çalıştırın:

   ```bash
   pacman -Syu
   ```

4. g++'ı kurun:

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```

5. *(İsteğe bağlı)* `C:\msys64\ucrt64\bin` klasörünü Windows **PATH** ortam değişkenine ekleyin. Böylece g++'ı
   her yerden kullanabilirsiniz. Bu adımı atlarsanız da sorun olmaz: `baslat.bat` ve `server.py` g++'ı
   `C:\msys64\ucrt64\bin` klasöründe kendileri bulur.

**macOS:** `xcode-select --install` · **Ubuntu/Debian:** `sudo apt install g++ python3`

### 3. Projeyi indirin

Git kuruluysa:

```bash
git clone https://github.com/ta2fga/ELE-411-Veri-Yapilari-Calisma-Yardimcisi.git
```

Git kurulu değilse GitHub sayfasında **Code → Download ZIP** ile indirip bir klasöre çıkarın.

---

## Başlatma

### Windows (en kolay yol)

1. Proje klasöründeki **`baslat.bat`** dosyasına çift tıklayın.
2. Tarayıcı kendiliğinden <http://localhost:8000> adresinde açılır.
3. Çalışmanız bitince açılan siyah komut penceresini kapatın.

`baslat.bat` önce Python ve g++'ın kurulu olup olmadığını kontrol eder. Biri eksikse ne yapmanız gerektiğini
söyleyen bir hata mesajı gösterir.

### Elle başlatma (tüm sistemler)

Proje klasöründe:

```bash
python server.py
```

Tarayıcıyı otomatik açmadan başlatmak için:

```bash
python server.py --no-browser
```

Ardından tarayıcıda <http://localhost:8000> adresini açın. macOS/Linux'ta `python` yerine `python3` yazın.

---

## Kullanım

1. Sol menüden bir **konu** ve **soru** seçin. Soru metni, girdi/çıktı açıklaması ve fonksiyon imzası görünür.
2. Editördeki başlangıç kodunu tamamlayın.
3. Aşağıdaki düğmeleri kullanın:

| Düğme | Kısayol | Ne yapar? |
|---|---|---|
| **Çalıştır** | `Ctrl+Enter` | Kodu kendi `main()` fonksiyonunuzla çalıştırır. İsterseniz stdin girişi verebilirsiniz. |
| **Test et** | `Ctrl+Shift+Enter` | Fonksiyonunuzu sorunun testleriyle sınar. Bu sırada `main()` yok sayılır. Tüm testler geçerse soru "çözüldü" olarak işaretlenir. |
| **İpucu** | | İpuçlarını birer birer açar. |
| **Çözümü göster** | | Onay ister, sonra referans çözümü gösterir. |
| **Sıfırla** | | Kodu başlangıç hâline döndürür. |

**Notlar**

- Kodlarınız ve ilerlemeniz tarayıcının `localStorage` alanında saklanır. Tarayıcı verilerini silerseniz
  ya da başka bir tarayıcı kullanırsanız ilerlemeniz görünmez.
- Her çalıştırma en fazla **5 saniye** sürebilir. Sonsuz döngüye giren program otomatik olarak durdurulur.
- Derleme hatalarındaki satır numaraları editördeki satırlarla aynıdır.
- Hazırlık çubuğunda geçmiş sınav soruları 2 kat, deneme sınavları 3 kat ağırlıklı sayılır.

---

## Konular ve sorular

| # | Konu | Sorular |
|---|---|---|
| 1 | **Recursion** | factorial, myMult, Hanoi kuleleri, writeBackward (Study 5), çarpmasız çarpma (Study 6), Midterm2019 Q1 izleme, Midterm2019 Q2 (listeyi tersten yazdırma), Midterm2020 "recursion'ı anlat" |
| 2 | **Big-O** | Midterm2019 Q4, Midterm2020 (çoktan seçmeli), binary search karşılaştırma sayısı (Study 8; test + kod) |
| 3 | **Diziler** | ArrayBag, tekrar silme (Study 1), birleştirme (Study 2), sıralı dizide O(log N) sayma (Study 4 / midterm.pdf), Study 10, 11, 14, 15 (LIS), Midterm2019 Q8 |
| 4 | **Bağlı listeler** | toplam (Study 3), uzunluk iteratif + recursive (Study 16), LinkedBag, Midterm2020 bağlı listede bubble sort |
| 5 | **Stack** | midterm.pdf arama, Midterm2020 sayma, Midterm2019 Q6, Study 7, parantez dengesi, postfix hesaplama, infix → postfix |
| 6 | **Queue** | Study 13 (minimum), Study 12 (palindrom), Midterm2019 Q3 ve Midterm2020 testFunction izleme |
| 7 | **Sıralama** | 5 algoritma için adım adım izleme aracı (3 hazır dizi + rastgele dizi), Midterm2019/2020 izleme, cocktail sort (Midterm2019 Q7), 5 sıralama algoritmasını yazma, karmaşıklık testi |
| 8 | **Deneme sınavı** | Midterm 2020 (15+15+30+25+30+15 dk), midterm.pdf (2×25 dk), Midterm 2019 (120 dk) |

Her konunun bir de özet sayfası vardır (`problems/topics/<konu>.html`).

---

## Hazır sınıflar (`ele411.h`)

`ele411.h` her derlemede otomatik olarak eklenir, kodunuza `#include` yazmanız gerekmez. Arayüzler sınav
kâğıtlarındaki UML diyagramlarıyla birebir aynıdır.

| Sınıf | Arayüz |
|---|---|
| `Stack` | `isEmpty()`, `push(int)`, `pop()` → **bool** (değer döndürmez), `peek()` → int |
| `Queue` | `isEmpty()`, `enqueue(int)`, `dequeue()` → **bool**, `peekFront()` → int |
| `Node` / `StringNode` | public `item`, `next` + `getItem()`, `getNext()`, `setItem()`, `setNext()` |

> **Dikkat:** Sınavdaki gibi `pop()` ve `dequeue()` değeri **döndürmez**. Değeri almak için önce
> `peek()` / `peekFront()` çağırın. Boş bir yapıda `peek()` çağırmak programı açıklayıcı bir hata
> mesajıyla durdurur.

**Yardımcı fonksiyonlar** (kendi denemeleriniz için):
`makeStack({1,2,3})` (alttan üste, 3 en üstte), `makeQueue({1,2,3})` (önden arkaya, 1 en önde),
`makeList(...)`, `makeStringList(...)`, `printStack` / `printQueue` / `printList`,
`stackToString` / `queueToString` / `listToString`, `deleteList`.

`iostream`, `string` ve `sstream` zaten eklidir ve `using namespace std;` hazırdır.

---

## Sorun giderme

| Belirti | Çözüm |
|---|---|
| `[HATA] Python bulunamadi` | Python kurulu değil ya da PATH'e eklenmemiş. Python'u yeniden kurup **"Add python.exe to PATH"** kutusunu işaretleyin, sonra komut penceresini yeniden açın. |
| `python` yazınca Microsoft Store açılıyor | Windows Ayarları → Uygulamalar → Gelişmiş uygulama ayarları → **Uygulama yürütme diğer adları** bölümünden `python.exe` ve `python3.exe` seçeneklerini kapatın. |
| `[HATA] g++ bulunamadi` | MSYS2'yi `C:\msys64` klasörüne kurup **MSYS2 UCRT64** penceresinde `pacman -S mingw-w64-ucrt-x86_64-gcc` komutunu çalıştırın. |
| `8000 portu kullanımda` | Sunucu zaten açık olabilir. Sadece tarayıcıda <http://localhost:8000> adresini açın ya da eski komut penceresini kapatıp yeniden başlatın. |
| Program "libstdc++-6.dll bulunamadı" gibi bir hatayla çöküyor | `C:\msys64\ucrt64\bin` klasörünü PATH'e ekleyin ya da siteyi `baslat.bat` ile başlatın. |
| Sayfa açılıyor ama hiçbir şey çalışmıyor | Siyah komut penceresinin hâlâ açık olduğundan emin olun. Kapatılırsa sunucu da kapanır. |

---

## Geliştiriciler için

### Klasör yapısı

```
calisma-sitesi/
├── baslat.bat          # Windows için tek tıkla başlatma
├── server.py           # Yerel sunucu: derleme, çalıştırma, test (yalnızca standart kütüphane)
├── verify.py           # Tüm soruları ve testleri doğrulayan betik
├── ele411.h            # Stack, Queue, Node, StringNode ve test makroları
├── static/             # Arayüz (index.html, app.js, style.css, vendor/codemirror)
└── problems/
    ├── topics.json     # Konu listesi
    ├── topics/         # Konu özetleri (HTML)
    └── <konu>/<soru>/  # Her soru bir klasör
```

### Sunucu

- Yalnızca `127.0.0.1:8000` adresini dinler, dışarıdan erişilemez.
- `POST /run` `{code, stdin}` → `{compile_ok, compile_output, stdout, stderr, exit_code, time_ms, timed_out}`
- `POST /test` `{problem_id, code}` → derleme sonucu + test sonuçları
- Derleme komutu: `g++ -std=c++17 -Wall -O0 -include ele411.h`. Her çalıştırma ve her test en fazla
  **5 saniye** sürer, çıktı **64 KB** ile sınırlıdır, geçici dosyalar silinir.
- Test modunda kod ayrı bir `user.cpp` dosyası olarak `#include` edilir. Her test ayrı bir süreçte çalışır;
  bir testteki sonsuz döngü veya çökme diğer testleri etkilemez.

### Yeni soru ekleme

Her soru `problems/<konu>/<klasör>/` altında bir klasördür. `<konu>` şunlardan biridir:
`recursion`, `bigo`, `arrays`, `linked`, `stack`, `queue`, `sorting`, `exam`.

```
problems/stack/08-yeni-soru/
  problem.json      # başlık, metin, girdi/çıktı, ipuçları, kurallar
  starter.cpp       # başlangıç kodu (imza + açıklama yorumları + deneme main'i)
  solution.cpp      # referans çözüm (Türkçe yorumlu)
  harness.cpp       # testler
  wrong_*.cpp       # (önerilir) testlerin yakalaması gereken yanlış çözümler
```

`problem.json` örneği:

```json
{
  "id": "stack-yeni-soru",
  "order": 8,
  "title": "Sorunun başlığı",
  "source": "Midterm2021 Q5",
  "difficulty": "Orta",
  "statement": "<p>Soru metni (HTML).</p>",
  "io": { "inputs": ["<code>myStack</code>: ..."], "outputs": ["..."] },
  "signature": "int f(Stack& myStack)",
  "forbidden": ["array", "stl", "queue"],
  "hints": ["İpucu 1", "İpucu 2"],
  "solutionNote": "<b>Karmaşıklık:</b> O(N)"
}
```

**Diğer soru tipleri** (`"type"` alanı; bunlar için yalnızca `problem.json` yeterli):

- `"trace"`: `code` (gösterilen kod), `runCode` (cevapları sırayla yazdıran sürüm),
  `blanks: [{label, answer}]`, `explanation`. Cevaplar sayı/kelime dizisi olarak karşılaştırılır
  (virgül ve köşeli parantez önemsizdir; "boş" = boş).
- `"mcq"`: `options` (ortak şıklar) ve `items: [{q, code?, options?, answer, explain}]`.
- `"open"`: `sampleAnswer` (HTML).
- `"sorttrace"`: `algos` (`selection`, `insertion`, `bubble`, `quick`, `merge`), `arrays`, `random`.
- `"exam"`: `sections: [{problem: "<soru id>", minutes: 15}, ...]`.

`forbidden` için hazır kurallar: `array`, `stl`, `queue`, `stack`, `multiply`, `sort`, `noloop`
(tanımları `server.py` içindeki `FORBIDDEN_PRESETS`'te). Özel kural da yazılabilir:
`{"pattern": "regex", "message": "açıklama"}`.

`harness.cpp` örneği (kullanıcının kodundan sonra derlenir, `main` yazmayın):

```cpp
static void h_case(std::initializer_list<int> items, int expected) {
    Stack s = makeStack(items);
    std::string before = stackToString(s);
    CHECK("dönüş değeri", f(s), expected);                       // değer karşılaştırma
    CHECK_TEXT("stack sırası", stackToString(s), before);         // metin karşılaştırma
}
TEST("Boş stack", "myStack = []") { h_case({}, 0); }
TEST("Ekrana yazdırma", "n = 3") {
    std::string out = ele411::capture([] { printSomething(3); });  // cout/printf çıktısını yakalar
    CHECK_TEXT("çıktı", ele411::trimOutput(out), "1\n2\n3");
}
```

### Doğrulama

```bash
python verify.py          # tüm sorular
python verify.py stack    # yalnızca stack soruları
```

Her kod sorusu için referans çözümün tüm testleri geçtiğini, her `wrong_*.cpp` dosyasının en az bir
testten kaldığını ve başlangıç kodunun derlendiğini kontrol eder. İzleme sorularında programın gerçek
çıktısının cevap anahtarıyla aynı olduğunu, çoktan seçmelilerde cevabın şıklarda bulunduğunu, deneme
sınavlarında bölümlerin var olduğunu doğrular. Ayrıca sonsuz döngü, sonsuz çıktı, derleme hatası, çökme,
yasak yapı ve stdin durumlarını dener.
