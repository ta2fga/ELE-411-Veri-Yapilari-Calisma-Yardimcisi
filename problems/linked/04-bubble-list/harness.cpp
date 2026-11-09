static void h_case(std::vector<int> v) {
    Node* h = nullptr; for (int i = (int)v.size() - 1; i >= 0; i--) h = new Node(v[i], h);
    std::vector<int> e = v; std::sort(e.begin(), e.end());
    Node* he = nullptr; for (int i = (int)e.size() - 1; i >= 0; i--) he = new Node(e[i], he);
    bubbleSortList(h);
    CHECK_TEXT("liste", listToString(h), listToString(he));
    deleteList(h); deleteList(he);
}
TEST("Boş liste", "headPtr = nullptr") { h_case({}); }
TEST("Tek düğüm", "4") { h_case({4}); }
TEST("Örnek", "5 -> 1 -> 4 -> 2 -> 8") { h_case({5, 1, 4, 2, 8}); }
TEST("Zaten sıralı", "1 -> 2 -> 3 -> 4") { h_case({1, 2, 3, 4}); }
TEST("Ters sıralı", "9 -> 7 -> 5 -> 3 -> 1") { h_case({9, 7, 5, 3, 1}); }
TEST("Tekrarlar ve negatifler", "3 -> -1 -> 3 -> 0 -> -1") { h_case({3, -1, 3, 0, -1}); }
TEST("İki düğüm", "2 -> 1") { h_case({2, 1}); }
