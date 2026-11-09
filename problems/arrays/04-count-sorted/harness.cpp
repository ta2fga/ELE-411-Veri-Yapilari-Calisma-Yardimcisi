static void h_case(std::vector<int> v, int t, int exp) {
    CHECK("countOccurrences(" + vecToString(v) + ", " + std::to_string(t) + ")", countOccurrences(v.data(), (int)v.size(), t), exp);
}
TEST("Boş dizi", "arr = [], target = 3") { h_case({}, 3, 0); }
TEST("Yok", "arr = [1, 2, 4, 5], target = 3") { h_case({1, 2, 4, 5}, 3, 0); }
TEST("Ortada blok", "arr = [1, 2, 2, 2, 3, 5, 5, 8], target = 2") { h_case({1, 2, 2, 2, 3, 5, 5, 8}, 2, 3); }
TEST("Uçlarda", "arr = [4, 4, 6, 9, 9, 9], target = 4 ve 9") { h_case({4, 4, 6, 9, 9, 9}, 4, 2); h_case({4, 4, 6, 9, 9, 9}, 9, 3); }
TEST("Hepsi hedef", "arr = [7, 7, 7, 7, 7], target = 7") { h_case({7, 7, 7, 7, 7}, 7, 5); }
TEST("Tek eleman", "arr = [3], target = 3 ve 1") { h_case({3}, 3, 1); h_case({3}, 1, 0); }
TEST("Sınırların dışında", "arr = [2, 3, 3], target = 1 ve 10") { h_case({2, 3, 3}, 1, 0); h_case({2, 3, 3}, 10, 0); }
TEST("Büyük dizi — O(logN) gerekli", "N = 10.000.000 (her değer 3 kez), 2000 sorgu") {
    const int N = 10000000;
    static std::vector<int> big(N);
    for (int i = 0; i < N; i++) big[i] = i / 3;
    long long total = 0;
    for (int k = 0; k < 2000; k++) total += countOccurrences(big.data(), N, (int)((k * 7919LL) % (N / 3)));
    CHECK("2000 sorgunun toplamı", total, 6000LL);
}
