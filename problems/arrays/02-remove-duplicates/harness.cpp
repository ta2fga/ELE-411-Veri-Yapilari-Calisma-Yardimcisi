static void h_case(std::vector<int> v, const char* exp) {
    int n = removeDuplicates(v.data(), (int)v.size());
    CHECK_TEXT("ilk n eleman (sıra korunmalı)", arrToString(v.data(), n), exp);
}
TEST("Boş dizi", "arr = []") { h_case({}, "[]"); }
TEST("Tek eleman", "arr = [5]") { h_case({5}, "[5]"); }
TEST("Tekrar yok", "arr = [4, 1, 3]") { h_case({4, 1, 3}, "[4, 1, 3]"); }
TEST("Sırasız tekrarlar", "arr = [3, 1, 3, 2, 1]") { h_case({3, 1, 3, 2, 1}, "[3, 1, 2]"); }
TEST("Hepsi aynı", "arr = [7, 7, 7, 7]") { h_case({7, 7, 7, 7}, "[7]"); }
TEST("Sıralı (sd.pdf örneği)", "arr = [1, 2, 2, 3, 4, 4, 4, 5, 5]") { h_case({1, 2, 2, 3, 4, 4, 4, 5, 5}, "[1, 2, 3, 4, 5]"); }
TEST("Negatifler", "arr = [-1, 0, -1, 2, 0]") { h_case({-1, 0, -1, 2, 0}, "[-1, 0, 2]"); }
