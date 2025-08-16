#include "header.h"

#define endl "\n";
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void mapParent(TreeNode* root, map<TreeNode*, TreeNode*>& parent) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        if (node->left) {
            parent[node->left] = node;
            q.push(node->left);
        }

        if (node->right) {
            parent[node->right] = node;
            q.push(node->right);
        }
    }
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    map<TreeNode*, TreeNode*> findParent;
    mapParent(root, findParent);

    int curLevel = 0;
    unordered_map<TreeNode*, bool> visited;
    queue<TreeNode*> q;

    q.push(target);
    visited[target] = true;
    while (!q.empty()) {
        int n = q.size();
        if (curLevel == k) break;
        curLevel++;
        for (int i = 0; i < n; ++i) {
            auto node = q.front();
            q.pop();
            // we try to move radially out from the target node to each direction

            if (node->left and !visited[node->left]) {
                visited[node->left] = true;
                q.push(node->left);
            }
            if (node->right and !visited[node->right]) {
                visited[node->right] = true;
                q.push(node->right);
            }

            if (findParent[node] and !visited[findParent[node]]) {
                visited[findParent[node]] = true;
                q.push(findParent[node]);
            }
        }
    }
    vector<int> ans;
    while (!q.empty()) {
        ans.push_back(q.front()->val);
        q.pop();
    }
    return ans;
}

void findNode(TreeNode* root, int start, TreeNode*& value) {
    if (!root) return;
    findNode(root->left, start, value);
    if (root->val == start) {
        value = root;
        return;
    }
    findNode(root->right, start, value);
}

int amountOfTime(TreeNode* root, int start) {
    map<TreeNode*, TreeNode*> parents;
    mapParent(root, parents);

    int time = 0;

    queue<TreeNode*> q;
    TreeNode* value = NULL;
    findNode(root, start, value);
    cout << value->val << endl;
    q.push(value);
    unordered_map<TreeNode*, bool> visited;
    bool flag = false;
    visited[value] = true;
    while (!q.empty()) {
        int n = q.size();
        flag = false;
        for (int i = 0; i < n; ++i) {
            auto node = q.front();
            q.pop();

            if (node->left and !visited[node->left]) {
                flag = true;  // if someone in the adjacent is burned then marked as true
                q.push(node->left);
                visited[node->left] = true;
            }

            if (node->right and !visited[node->right]) {
                flag = true;
                q.push(node->right);
                visited[node->right] = true;
            }

            if (parents[node] and !visited[parents[node]]) {
                flag = true;
                q.push(parents[node]);
                visited[parents[node]] = true;
            }
        }

        if (flag)
            time++;
    }

    return time;
}

int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    return 0;
}