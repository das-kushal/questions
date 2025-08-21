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

// these are important and on the tougher side of questions on trees
// find nodes at distance k from a given node
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

// amount of time to burn a tree
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

// count number of nodes in a complete binary tree
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// construct binary tree from preorder and inorder traversal

/*
    if we are given preorder and postorder traversals then we cannot construct unique binary tree
*/
TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd, map<int, int>& m) {
    if (preStart > preEnd or inStart > inEnd) return NULL;
    TreeNode* root = new TreeNode(preorder[preStart]);
    int rootPos = m[preorder[preStart]];
    int numLeft = rootPos - inStart;
    root->left = buildTreeHelper(preorder, preStart + 1, preStart + numLeft, inorder, inStart, rootPos - 1, m);
    root->right = buildTreeHelper(preorder, preStart + numLeft + 1, preEnd, inorder, rootPos + 1, inEnd, m);

    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    map<int, int> m;
    int n = preorder.size();
    for (int i = 0; i < n; i++) m[inorder[i]] = i;
    TreeNode* root = buildTreeHelper(preorder, 0, n - 1, inorder, 0, n - 1, m);
    return root;
}

// serialise and deserialise a binary tree

class Codec {
   public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        if (!root) return s;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            if (node == NULL)
                s.append("$,");
            else
                s.append(to_string(node->val) + ",");

            if (node) {
                q.push(node->left);
                q.push(node->right);
            }
        }

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<TreeNode*> q;
        if (data == "") return NULL;
        stringstream s(data);
        string str;
        getline(s, str, ',');
        TreeNode* root = new TreeNode(stoi(str));
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            getline(s, str, ',');
            if (str != "$") {
                TreeNode* leftNode = new TreeNode(stoi(str));
                node->left = leftNode;
                q.push(leftNode);
            } else {
                node->left = NULL;
            }
            getline(s, str, ',');
            if (str != "$") {
                TreeNode* rightNode = new TreeNode(stoi(str));
                node->right = rightNode;
                q.push(rightNode);
            } else {
                node->right = NULL;
            }
        }

        return root;
    }
};

int main() {
    return 0;
}