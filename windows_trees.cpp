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

int maxPath(TreeNode *root, int &sum)
{
    if (!root)
        return 0;
    int left = maxPath(root->left, sum);
    int right = maxPath(root->right, sum);
    if (left < 0)
        left = 0;
    if (right < 0)
        right = 0;
    sum = max(sum, root->val + left + right);
    return root->val + max(left, right);
}

int maxPathSum(TreeNode *root)
{
    int sum = -1e8;
    maxPath(root, sum);
    return sum;
}

int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int> pq;
    for (auto it : nums)
        pq.push(it);
    while (k-- > 0)
    {
        pq.pop();
    }
    return pq.top();
}

void inorder(TreeNode *root, vector<int> &ins)
{
    if (!root)
        return;
    inorder(root->left, ins);
    ins.push_back(root->val);
    inorder(root->right, ins);
}

vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> ins;
    inorder(root, ins);
    return ins;
}

bool isAnagram(string s, string t)
{
    map<char, int> m;
    for (auto it : s)
        m[it]++;
    for (auto it : t)
        m[it]--;
    for (auto it : m)
        if (it.second != 0)
            return false;
    return true;
}

TreeNode *invertTree(TreeNode *root)
{
    if (!root || (!root->right and !root->left))
        return root;
    root->left = invertTree(root->left);
    root->right = invertTree(root->right);
    swap(root->left, root->right);
    return root;
}

TreeNode *searchBST(TreeNode *root, int val)
{
    if (!root)
        return root;
    if (root->val == val)
        return root;
    if (root->val < val)
        return searchBST(root->right, val);

    return searchBST(root->left, val);
}

void kthSmallestHelper(TreeNode *root, int &k, int &ans)
{
    if (!root)
        return;
    kthSmallestHelper(root->left, k, ans);
    k--;

    if (k == 0)
    {
        ans = root->val;
    }

    kthSmallestHelper(root->right, k, ans);
}
int kthSmallest(TreeNode *root, int k)
{
    int ans = -1;
    kthSmallestHelper(root, k, ans);
    return ans;
}

class TwoSum4
{
private:
    void inorder(TreeNode *root, int k, vector<int> &ans)
    {
        if (!root)
            return;
        inorder(root->left, k, ans);
        ans.push_back(root->val);
        inorder(root->right, k, ans);
    }
    bool findTarget(TreeNode *root, int k)
    {
        vector<int> ans;
        inorder(root, k, ans);

        int low = 0, high = ans.size() - 1;
        while (low < high)
        {
            int sum = ans[low] + ans[high];
            if (sum == k)
                return true;
            else if (sum > k)
                high--;
            else
                low++;
        }

        return false;
    }
};

class RecoverBST
{
private:
    void inorder(TreeNode *root, vector<int> &ans)
    {
        if (!root)
            return;
        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
    int ind = 0;
    void check(TreeNode *root, vector<int> nums)
    {
        if (!root)
            return;
        check(root->left, nums);
        if (root->val != nums[ind])
        {
            root->val = nums[ind];
        }
        ind++;
        check(root->right, nums);
    }

    void recoverTree(TreeNode *root)
    {
        vector<int> ans;
        inorder(root, ans);
        sort(ans.begin(), ans.end());
        check(root, ans);
    }
};

int main()
{
    return 0;
}