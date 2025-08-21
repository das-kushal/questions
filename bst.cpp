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

// delete a node in BST -- this is an important question

TreeNode* deleteNode(TreeNode* root, int key) {
}

void inorderKthSmallest(TreeNode* root, int& k, int& ans) {
    if (!root) return;
    inorderKthSmallest(root->left, k, ans);
    k--;
    if (k == 0) {
        ans = root->val;
        return;
    }

    inorderKthSmallest(root->right, k, ans);
}

int kthSmallest(TreeNode* root, int k) {
    if (!root) return -1;
    int ans = -1;
    inorderKthSmallest(root, k, ans);
    return ans;
}

bool checkBST(TreeNode* root, long long low, long long high) {
    if (!root) return true;
    return root->val > low && root->val < high && checkBST(root->left, low, root->val) && checkBST(root->right, root->val, high);
}

bool isValidBST(TreeNode* root) {
    if (!root) return true;
    return checkBST(root, LONG_MIN, LONG_MAX);
}

int main() {
    return 0;
}