// YANLIŞ: sağ alt ağacı unutuyor
int sumBST(TreeNode* root) {
    if (root == nullptr) return 0;
    return root->item + sumBST(root->left);
}
