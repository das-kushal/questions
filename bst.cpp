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

class LowestCommonAncestor {
   private:
    // for binary tree
    // O(N) N is the traversal time to traverse through the tree
    TreeNode* lowestCommonAncestorBT(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) return root;
        TreeNode* leftSide = lowestCommonAncestorBT(root->left, p, q);
        TreeNode* rightSide = lowestCommonAncestorBT(root->right, p, q);
        if (leftSide && rightSide) return root;
        return leftSide ? leftSide : rightSide;
    }

    // for binary search tree
    /*
        here we take advantage of the property of BST that anything on left subtree is smaller than root and anything on
        right subtree is larger than root.
        so if our both nodes lie to left or right then we go otherwise the moment there is a split like we have to go left and right i.e. one node lies to the left
        and other lies to the right then that is the LCA O(height)
    */

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return root;

        if (root->val > p->val and root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        }

        if (root->val < p->val and root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        }

        return root;
    }
};

// construct a BST from preorder traversal

class ConstructBSTFromPreorder {
   protected:
    // O(NlogN) {for sorting} + O(N)
    TreeNode* constructBST(int preStart, int preEnd, vector<int>& preorder, int inStart, int inEnd, vector<int>& inorder, map<int, int>& m) {
        if (preStart > preEnd || inStart > inEnd) return NULL;
        TreeNode* root = new TreeNode(preorder[preStart]);

        int rootPos = m[root->val];
        int numLeft = rootPos - inStart;
        root->left = constructBST(preStart + 1, preStart + numLeft, preorder, inStart, rootPos - 1, inorder, m);
        root->right = constructBST(preStart + numLeft + 1, preEnd, preorder, rootPos + 1, inEnd, inorder, m);
        return root;
    }
    TreeNode* bstFromPreorderInorderPreorder(vector<int>& preorder) {
        vector<int> inorder = preorder;
        sort(inorder.begin(), inorder.end());
        map<int, int> mp;
        int n = preorder.size();
        for (int i = 0; i < n; ++i) {
            mp[inorder[i]] = i;
        }
        return constructBST(0, n - 1, preorder, 0, n - 1, inorder, mp);
    }

    // optimal approach O(N)
    /*
        we will take a upper bound for each index in teh array and then try to build a node to left with the node as upper bound and when we go to right then the upper bound is the parent's upper bound
    */
   public:
    TreeNode* buildBST(vector<int>& preorder, int& ind, int upperBound) {
        if (ind == preorder.size() || preorder[ind] > upperBound) return NULL;
        TreeNode* root = new TreeNode(preorder[ind++]);

        root->left = buildBST(preorder, ind, root->val);
        root->right = buildBST(preorder, ind, upperBound);

        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int ind = 0;
        return buildBST(preorder, ind, INT_MAX);
    }
};
