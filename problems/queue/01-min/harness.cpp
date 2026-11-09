static void h_case(std::initializer_list<int> items, int exp) {
    Queue q = makeQueue(items);
    std::string before = queueToString(q);
    CHECK("findMin", findMin(q), exp);
    CHECK_TEXT("çağrıdan sonra queue (ön→arka)", queueToString(q), before);
}
TEST("Tek eleman", "q = [5]") { h_case({5}, 5); }
TEST("Ortada", "q = [7, 3, 9, 1, 4]") { h_case({7, 3, 9, 1, 4}, 1); }
TEST("Önde", "q = [0, 5, 6]") { h_case({0, 5, 6}, 0); }
TEST("Arkada", "q = [8, 6, 2]") { h_case({8, 6, 2}, 2); }
TEST("Tekrarlı minimum", "q = [3, 1, 2, 1]") { h_case({3, 1, 2, 1}, 1); }
TEST("Negatifler", "q = [-2, 4, -9, 0]") { h_case({-2, 4, -9, 0}, -9); }
