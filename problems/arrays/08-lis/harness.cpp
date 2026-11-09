static void h_case(std::vector<int> v, int exp) {
    CHECK("lengthOfLIS(" + vecToString(v) + ")", lengthOfLIS(v.data(), (int)v.size()), exp);
}
TEST("Soru örneği", "[10, 9, 2, 5, 3, 7, 101, 18]") { h_case({10, 9, 2, 5, 3, 7, 101, 18}, 4); }
TEST("sd.pdf örneği", "[10, 22, 9, 33, 21, 50, 41, 60]") { h_case({10, 22, 9, 33, 21, 50, 41, 60}, 5); }
TEST("Boş dizi", "[]") { h_case({}, 0); }
TEST("Azalan", "[5, 4, 3, 2, 1]") { h_case({5, 4, 3, 2, 1}, 1); }
TEST("Hepsi eşit (kesin artan)", "[7, 7, 7]") { h_case({7, 7, 7}, 1); }
TEST("Artan", "[1, 2, 3, 4, 5, 6]") { h_case({1, 2, 3, 4, 5, 6}, 6); }
TEST("Karışık", "[0, 8, 4, 12, 2, 10, 6, 14, 1, 9]") { h_case({0, 8, 4, 12, 2, 10, 6, 14, 1, 9}, 4); }
