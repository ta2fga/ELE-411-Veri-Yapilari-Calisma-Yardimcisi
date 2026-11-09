static void h_case(std::vector<int> a, std::vector<int> b) {
    std::vector<int> exp = a; exp.insert(exp.end(), b.begin(), b.end()); std::sort(exp.begin(), exp.end());
    std::vector<int> out(a.size() + b.size() + 1, -999);
    mergeArrays(a.data(), b.data(), (int)a.size(), (int)b.size(), out.data());
    CHECK_TEXT("arr3", arrToString(out.data(), (int)(a.size() + b.size())), vecToString(exp));
}
TEST("sd.pdf örneği", "[1,3,5,7] + [2,4,6,8]") { h_case({1, 3, 5, 7}, {2, 4, 6, 8}); }
TEST("İkisi boş", "[] + []") { h_case({}, {}); }
TEST("Biri boş", "[] + [1,2] ve [3,4] + []") { h_case({}, {1, 2}); h_case({3, 4}, {}); }
TEST("Biri tamamen önce", "[1,2,3] + [10,20]") { h_case({1, 2, 3}, {10, 20}); }
TEST("Farklı uzunluk", "[5] + [1,2,3,4,6]") { h_case({5}, {1, 2, 3, 4, 6}); }
TEST("Tekrarlar", "[1,2,2,5] + [2,2,3]") { h_case({1, 2, 2, 5}, {2, 2, 3}); }
TEST("Negatifler", "[-5,-1,4] + [-3,0]") { h_case({-5, -1, 4}, {-3, 0}); }
