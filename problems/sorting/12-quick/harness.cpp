static void h_case(std::vector<int> v) {
    std::vector<int> exp = v; std::sort(exp.begin(), exp.end());
    std::vector<int> a = v;
    int* arr = a.data(); int n = (int)a.size();
    quickSort(arr, 0, n - 1);
    CHECK_TEXT("sıralanmış dizi", vecToString(a), vecToString(exp));
}
TEST("Boş dizi", "[]") { h_case({}); }
TEST("Tek eleman", "[42]") { h_case({42}); }
TEST("Study 9 dizisi", "[7, 2, 12, 5, 6, 4, 9]") { h_case({7, 2, 12, 5, 6, 4, 9}); }
TEST("Midterm 2019 dizisi", "[38, 81, 22, 48, 13, 69, 75, 41, 45, 58, 79, 60]") { h_case({38, 81, 22, 48, 13, 69, 75, 41, 45, 58, 79, 60}); }
TEST("Zaten sıralı", "[1, 2, 3, 4, 5]") { h_case({1, 2, 3, 4, 5}); }
TEST("Ters sıralı", "[9, 7, 5, 3, 1, 0]") { h_case({9, 7, 5, 3, 1, 0}); }
TEST("Tekrarlar ve negatifler", "[3, -1, 3, 0, -1, 2, 2]") { h_case({3, -1, 3, 0, -1, 2, 2}); }
TEST("Rastgele 300 eleman", "sabit tohumlu rastgele dizi") {
    std::vector<int> v; unsigned s = 12345;
    for (int i = 0; i < 300; i++) { s = s * 1103515245u + 12345u; v.push_back((int)((s >> 8) % 1000) - 500); }
    h_case(v);
}
