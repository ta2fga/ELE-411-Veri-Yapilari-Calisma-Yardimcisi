// midterm.pdf — BST toplamı (referans çözüm)
int sumBST(TreeNode* root) {
    if (root == nullptr)             // base case: boş (alt) ağaç
        return 0;
    // kendi değeri + sol alt ağaç toplamı + sağ alt ağaç toplamı
    return root->item + sumBST(root->left) + sumBST(root->right);
}

int main() {
    TreeNode* root = makeBST({50, 30, 70, 20, 40, 60, 80});
    cout << sumBST(root) << endl;
    deleteTree(root);
    return 0;
}
