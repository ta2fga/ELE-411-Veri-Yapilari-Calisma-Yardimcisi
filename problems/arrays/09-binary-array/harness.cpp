static void h_case(std::vector<int> v) {
    std::vector<int> exp = v; std::sort(exp.begin(), exp.end());
    std::string in = vecToString(v);
    sortBinaryArray(v.data(), (int)v.size());
    CHECK_TEXT("sıralanmış dizi", vecToString(v), vecToString(exp));
}
TEST("Boş dizi", "[]") { h_case({}); }
TEST("Hepsi 0", "[0, 0, 0]") { h_case({0, 0, 0}); }
TEST("Hepsi 1", "[1, 1]") { h_case({1, 1}); }
TEST("Karışık", "[1, 0, 1, 1, 0, 0, 1, 0]") { h_case({1, 0, 1, 1, 0, 0, 1, 0}); }
TEST("Ters sıralı", "[1, 1, 1, 0]") { h_case({1, 1, 1, 0}); }
TEST("Tek eleman", "[1]") { h_case({1}); }
TEST("Büyük dizi", "N = 100000 karışık") {
    std::vector<int> v(100000); for (int i = 0; i < 100000; i++) v[i] = (i * 7 + 3) % 5 < 2 ? 1 : 0;
    int zeros = (int)std::count(v.begin(), v.end(), 0);
    sortBinaryArray(v.data(), (int)v.size());
    // Çıktı sınırını aşmamak için 100000 elemanı yazdırmak yerine özet karşılaştırılır
    bool ok = std::is_sorted(v.begin(), v.end()) && std::count(v.begin(), v.end(), 0) == zeros;
    CHECK_TEXT("sıralı mı + 0 sayısı korunmuş mu", ok ? "evet" : "hayır (ilk 0/1 sınırı: " + std::to_string(std::count(v.begin(), v.end(), 0)) + ")", "evet");
}
