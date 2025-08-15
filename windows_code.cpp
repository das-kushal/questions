#include "header.h"

using namespace std;

/**
 *
 * THESE CHANGES ARE DONE IN WINDOWS 11 MACHINE AND SOLELY FROM WINDOWS
 *
 */

bool help(TreeNode *root, int node, vector<int> &path)
{
    if (!root)
        return false;
    path.push_back(root->val);
    if (root->val == node)
    {
        return true;
    }

    if (help(root->left, node, path) or help(root->right, node, path))
        return true;
    path.pop_back();
    return false;
}

vector<int> solve(TreeNode *A, int B)
{
    vector<int> path;
    if (!A)
        return path;
    help(A, B, path);
    return path;
}

void binHelper(TreeNode *root, vector<string> &ans, string path)
{
    if (!root->left && !root->right)
        ans.push_back(path);
    if (root->left)
        binHelper(root->left, ans, path + "->" + to_string(root->left->val));
    if (root->right)
        binHelper(root->right, ans, path + "->" + to_string(root->right->val));
}
vector<string> binaryTreePaths(TreeNode *root)
{
    // all root to leaf paths
    vector<string> ans;
    if (!root)
        return ans;
    string path = to_string(root->val);
    binHelper(root, ans, path);

    return ans;
}

bool check(TreeNode *leftChild, TreeNode *rightChild)
{
    if (!leftChild and !rightChild)
        return true;
    if (!leftChild or !rightChild)
        return false;
    return leftChild->val == rightChild->val && check(leftChild->left, rightChild->right) && check(leftChild->right, rightChild->left);
}

bool isSymmetric(TreeNode *root)
{
    if (!root || (!root->right && !root->left))
        return true;

    return check(root->left, root->right);
}

int maxPathSum(TreeNode *root)
{
}

int main()
{
    return 0;
}