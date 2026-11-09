static void h_case(std::initializer_list<int> items, int exp) {
    TreeNode* root = makeBST(items);
    CHECK("sumBST", sumBST(root), exp);
    deleteTree(root);
}
TEST("Boş ağaç", "root = nullptr") { h_case({}, 0); }
TEST("Tek düğüm", "BST: 42") { h_case({42}, 42); }
TEST("Dengeli ağaç", "ekleme sırası 50 30 70 20 40 60 80") { h_case({50, 30, 70, 20, 40, 60, 80}, 350); }
TEST("Sadece sola dallanan", "ekleme sırası 5 4 3 2 1") { h_case({5, 4, 3, 2, 1}, 15); }
TEST("Sadece sağa dallanan", "ekleme sırası 1 2 3 4") { h_case({1, 2, 3, 4}, 10); }
TEST("Negatifler", "ekleme sırası 0 -5 5 -10 3") { h_case({0, -5, 5, -10, 3}, -7); }
