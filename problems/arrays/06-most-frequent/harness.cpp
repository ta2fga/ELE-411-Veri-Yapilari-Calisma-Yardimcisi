static void h_case(std::vector<int> v, int exp) {
    CHECK("mostFrequent(" + vecToString(v) + ")", mostFrequent(v.data(), (int)v.size()), exp);
}
TEST("Tek eleman", "[5]") { h_case({5}, 5); }
TEST("Açık kazanan", "[1, 3, 2, 3, 1, 3]") { h_case({1, 3, 2, 3, 1, 3}, 3); }
TEST("Eşitlik: önce görülen", "[4, 4, 7, 7]") { h_case({4, 4, 7, 7}, 4); }
TEST("Eşitlik, dağınık", "[2, 1, 1, 2]") { h_case({2, 1, 1, 2}, 2); }
TEST("Hepsi farklı", "[9, 8, 7]") { h_case({9, 8, 7}, 9); }
TEST("Negatifler", "[-1, -2, -2, 0, -1, -2]") { h_case({-1, -2, -2, 0, -1, -2}, -2); }
