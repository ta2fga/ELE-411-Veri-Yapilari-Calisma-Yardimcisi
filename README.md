# ELE411 Çalışma Sitesi

ELE411 Data Structures ara sınavı (16 Kasım 2026) için yerel C++ çalışma sitesi.
Sayfa sadece arayüzdür; kodunuz bilgisayarınızdaki **g++** ile derlenip çalıştırılır.
İnternet bağlantısı gerekmez (CodeMirror `static/vendor/` içinde).

## Başlatma

1. `baslat.bat` dosyasını çift tıklayın.
2. Tarayıcı kendiliğinden `http://localhost:8000` adresinde açılır.
3. Çalışmanız bitince açılan siyah pencereyi kapatın.

Gereksinimler: Python 3 (yalnızca standart kütüphane kullanılır, pip paketi gerekmez) ve
MSYS2 UCRT64 g++ (`C:\msys64\ucrt64\bin\g++.exe`). g++ PATH'te değilse `baslat.bat` bu yolu kendisi ekler.

Elle başlatmak için: `python server.py` (tarayıcıyı açmadan: `python server.py --no-browser`).

## İçerik

| Konu | Sorular |
|---|---|
| 1. Recursion | factorial, myMult, Hanoi, writeBackward (Study 5), çarpmasız çarpma (Study 6), Midterm2019 Q1 izleme, Midterm2019 Q2 (listeyi tersten yazdır), midterm.pdf BST toplamı, Midterm2020 “recursion’ı anlat” |
| 2. Big-O | Midterm2019 Q4, Midterm2020 (çoktan seçmeli), binary search karşılaştırma sayısı (Study 8; test + kod) |
| 3. Diziler | ArrayBag, tekrar silme (Study 1), birleştirme (Study 2), sıralı dizide sayma O(logN) (Study 4 / midterm.pdf), Study 10, 11, 14, 15 (LIS), Midterm2019 Q8 |
| 4. Bağlı listeler | toplam (Study 3), uzunluk iteratif+recursive (Study 16), LinkedBag, Midterm2020 bağlı listede bubble sort |
| 5. Stack | midterm.pdf arama, Midterm2020 sayma, Midterm2019 Q6, Study 7, parantez, postfix, infix→postfix |
| 6. Queue | Study 13 (minimum), Study 12 (palindrom), Midterm2019 Q3 ve Midterm2020 testFunction izleme |
| 7. Sıralama | 5 algoritma için izleme aracı (3 hazır dizi + rastgele), Midterm2019/2020 izleme, cocktail sort (Midterm2019 Q7), 5 sıralamayı yazma, karmaşıklık testi |
| 8. Deneme sınavı | Midterm 2020 (15+15+30+25+30+15 dk), midterm.pdf (3×25 dk), Midterm 2019 (120 dk) |

Üstteki **hazırlık çubuğu** çözülen sorulara göre yüzde gösterir (geçmiş sınav soruları 2, deneme sınavları
3 kat ağırlıklı), en zayıf konuyu ve sınava kadar günde kaç soru çözmeniz gerektiğini söyler.

## Kullanım

- **Çalıştır** (`Ctrl+Enter`): kodu kendi `main()`'iniz ile çalıştırır. İsterseniz stdin girişi verebilirsiniz.
- **Test et** (`Ctrl+Shift+Enter`): fonksiyonunuzu sorunun testleriyle sınar. Bu sırada `main()`'iniz yok sayılır.
  Her test için ✓/✗, girdi, beklenen ve gerçek değer gösterilir. Tüm testler geçerse soru "çözüldü" olarak işaretlenir.
- **İpucu**: ipuçlarını birer birer açar. **Çözümü göster**: onay ister ve referans çözümü gösterir.
- **Sıfırla**: başlangıç koduna döner.
- Kodlarınız ve ilerlemeniz tarayıcının `localStorage`'ında saklanır.
- Sınav kuralına aykırı yapılar (ör. "sadece stack" sorusunda `vector`, dizi veya `Queue`) testlerde uyarı olarak çıkar.

### Hazır sınıflar (`ele411.h`, otomatik eklenir)

| Sınıf | Arayüz (sınav UML'i ile aynı) |
|---|---|
| `Stack` | `isEmpty()`, `push(int)`, `pop()` → **bool** (değer döndürmez), `peek()` → int |
| `Queue` | `isEmpty()`, `enqueue(int)`, `dequeue()` → **bool**, `peekFront()` → int |
| `Node` / `StringNode` | public `item`, `next` + `getItem()`, `getNext()`, `setItem()`, `setNext()` |
| `TreeNode` | public `int item; TreeNode* left; TreeNode* right;` |

Yardımcılar: `makeStack({1,2,3})` (alttan üste), `makeQueue(...)` (önden arkaya), `makeList(...)`,
`makeStringList(...)`, `makeBST(...)`, `printStack/printQueue/printList`,
`stackToString/queueToString/listToString`, `deleteList`, `deleteTree`.
`iostream`, `string`, `sstream` dahil edilir ve `using namespace std;` hazırdır.

Boş bir yapıda `peek()`/`peekFront()` çağırmak programı açıklayıcı bir hata mesajıyla durdurur.

## Sunucu

- Sadece `127.0.0.1:8000` dinler, dışarıdan erişilemez.
- `POST /run` `{code, stdin}` → `{compile_ok, compile_output, stdout, stderr, exit_code, time_ms, timed_out}`
- `POST /test` `{problem_id, code}` → derleme sonucu + test sonuçları
- Derleme: `g++ -std=c++17 -Wall -O0 -include ele411.h`. Her çalıştırma ve her test en fazla **5 saniye** sürer,
  çıktı **64 KB** ile sınırlıdır, geçici dosyalar silinir.
- Test modunda kodunuz ayrı bir `user.cpp` dosyası olarak `#include` edilir; bu yüzden derleme hatalarındaki
  satır numaraları editördeki satırlarla aynıdır. Her test ayrı bir süreçte çalışır: bir testteki sonsuz döngü
  veya çökme diğer testleri etkilemez.

## Yeni soru ekleme

Her soru `problems/<konu>/<klasör>/` altında bir klasördür. `<konu>` şu kimliklerden biridir:
`recursion`, `bigo`, `arrays`, `linked`, `stack`, `queue`, `sorting`, `exam` (bkz. `problems/topics.json`).

```
problems/stack/08-yeni-soru/
  problem.json      # başlık, metin, girdi/çıktı, ipuçları, kurallar
  starter.cpp       # öğrencinin göreceği başlangıç kodu (imza + açıklama yorumları + deneme main'i)
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

### Diğer soru tipleri (`"type"` alanı; sadece `problem.json` yeterli)

- `"trace"`: `code` (gösterilen kod), `runCode` (çalıştırılan, cevapları sırayla yazdıran sürüm),
  `blanks: [{label, answer}]`, `explanation`. Cevaplar sayı/kelime dizisi olarak karşılaştırılır
  (virgül, köşeli parantez önemsiz; "boş" = boş).
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

Konu özetleri `problems/topics/<konu>.html` dosyalarındadır.

## Doğrulama

```
python verify.py          # tüm sorular
python verify.py stack    # sadece stack soruları
```

Her kod sorusu için şunları kontrol eder: referans çözüm tüm testleri geçiyor mu, her `wrong_*.cpp`
en az bir testten kalıyor mu, başlangıç kodu derleniyor mu. İzleme sorularında programın gerçek
çıktısının cevap anahtarıyla aynı olduğunu, çoktan seçmelilerde cevabın şıklarda olduğunu, deneme
sınavlarında bölümlerin var olduğunu kontrol eder. Ayrıca sonsuz döngü, sonsuz çıktı,
derleme hatası, çökme, yasak yapı ve stdin durumlarını dener.
