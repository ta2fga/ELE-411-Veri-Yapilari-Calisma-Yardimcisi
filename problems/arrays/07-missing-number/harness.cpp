static void h_case(std::vector<int> v, int exp) {
    CHECK("findMissing(" + vecToString(v) + ")", findMissing(v.data(), (int)v.size()), exp);
}
TEST("Örnek", "[3, 0, 1]") { h_case({3, 0, 1}, 2); }
TEST("0 eksik", "[1]") { h_case({1}, 0); }
TEST("n eksik", "[0]") { h_case({0}, 1); }
TEST("Ortada", "[1, 2, 3, 4, 0, 6]") { h_case({1, 2, 3, 4, 0, 6}, 5); }
TEST("En büyük eksik", "[0, 1, 2, 3]") { h_case({0, 1, 2, 3}, 4); }
TEST("Büyük karışık dizi", "n = 10000, 4321 eksik") {
    std::vector<int> v; for (int i = 10000; i >= 0; i--) if (i != 4321) v.push_back(i);
    for (size_t i = 0; i + 7 < v.size(); i += 7) std::swap(v[i], v[i + 7]);
    CHECK("findMissing(...)", findMissing(v.data(), (int)v.size()), 4321);
}
