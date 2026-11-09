static void h_case(std::initializer_list<int> items, int exp) {
    Node* h = makeList(items);
    std::string before = listToString(h);
    CHECK("sumList(" + before + ")", sumList(h), exp);
    CHECK_TEXT("liste değişmemeli", listToString(h), before);
    deleteList(h);
}
TEST("Boş liste", "head = nullptr") { h_case({}, 0); }
TEST("Tek düğüm", "5") { h_case({5}, 5); }
TEST("sd.pdf örneği", "7 -> 6 -> 8 -> 4 -> 1") { h_case({7, 6, 8, 4, 1}, 26); }
TEST("Negatifler", "-3 -> 3 -> -10") { h_case({-3, 3, -10}, -10); }
TEST("Uzun liste", "1 -> 2 -> ... -> 10") { h_case({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 55); }
