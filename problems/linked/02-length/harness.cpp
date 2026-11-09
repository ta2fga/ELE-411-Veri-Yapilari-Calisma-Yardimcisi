static void h_case(std::initializer_list<int> items) {
    Node* h = makeList(items);
    int n = (int)items.size();
    CHECK("lengthIterative", lengthIterative(h), n);
    CHECK("lengthRecursive", lengthRecursive(h), n);
    deleteList(h);
}
TEST("Boş liste", "head = nullptr") { h_case({}); }
TEST("Tek düğüm", "9") { h_case({9}); }
TEST("Beş düğüm", "3 -> 1 -> 4 -> 1 -> 5") { h_case({3, 1, 4, 1, 5}); }
TEST("İki düğüm", "0 -> 0") { h_case({0, 0}); }
TEST("Uzun liste", "1000 düğüm") {
    Node* h = nullptr; for (int i = 0; i < 1000; i++) h = new Node(i, h);
    CHECK("lengthIterative", lengthIterative(h), 1000);
    CHECK("lengthRecursive", lengthRecursive(h), 1000);
    deleteList(h);
}
