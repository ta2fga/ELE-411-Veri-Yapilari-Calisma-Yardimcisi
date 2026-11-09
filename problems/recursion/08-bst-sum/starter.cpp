// midterm.pdf — BST'deki elemanların toplamı (recursive)
// class TreeNode { int item; TreeNode* left; TreeNode* right; }   (ele411.h'de hazır)
// Çocuk yoksa pointer nullptr'dır.

int sumBST(TreeNode* root) {
    // Kodunuzu buraya yazın

    return 0;
}

int main() {
    TreeNode* root = makeBST({50, 30, 70, 20, 40, 60, 80});
    cout << sumBST(root) << endl;   // 350
    deleteTree(root);
    return 0;
}
