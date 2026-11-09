static int h_bound(int n) { int b = 0; while ((1 << (b + 1)) <= n) b++; return n == 0 ? 0 : b + 1; }
static void h_case(int n, int target) {
    std::vector<int> v; for (int i = 0; i < n; i++) v.push_back(2 * i + 1);
    int exp = (target % 2 == 1 && target >= 1 && target <= 2 * n - 1) ? (target - 1) / 2 : -1;
    int c = 0;
    int r = binarySearch(v.data(), n, target, c);
    CHECK("dönen indeks", r, exp);
    CHECK("karşılaştırma ≤ ⌊log₂N⌋+1", c <= h_bound(n) ? std::string("≤ ") + std::to_string(h_bound(n)) : std::to_string(c),
          std::string("≤ ") + std::to_string(h_bound(n)));
}
TEST("Boş dizi", "n = 0, target = 5") { h_case(0, 5); }
TEST("Tek eleman, var", "[1], target = 1") { h_case(1, 1); }
TEST("Ortada", "[1,3,...,15], target = 7") { h_case(8, 7); }
TEST("İlk eleman", "[1,3,...,15], target = 1") { h_case(8, 1); }
TEST("Son eleman", "[1,3,...,15], target = 15") { h_case(8, 15); }
TEST("Yok (en kötü durum)", "[1,3,...,15], target = 100") { h_case(8, 100); }
TEST("Büyük dizi", "n = 1000, target = 999 ve 4") { h_case(1000, 999); h_case(1000, 4); }
