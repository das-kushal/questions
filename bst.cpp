#include "treeHeader.h"

TreeNode* searchBST(TreeNode* root, int val) {
    if (!root) return NULL;
    if (root->val == val) return root;
    if (root->val > val) return searchBST(root->left, val);
    return searchBST(root->right, val);
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    TreeNode* cur = root;
    // just find the leaf position where the node should be inserted and then insert it -- simple
    while (true) {
        if (cur->val < val) {
            if (cur->right)
                cur = cur->right;
            else {
                cur->right = new TreeNode(val);
                break;
            }
        } else {
            if (cur->left)
                cur = cur->left;
            else {
                cur->left = new TreeNode(val);
                break;
            }
        }
    }

    return root;
}

int main() {
    return 0;
}