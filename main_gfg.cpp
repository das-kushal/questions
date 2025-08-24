#include "header_gfg.h"

Node *flatten(Node *root) {
}

int isSumProperty(Node *root) {
    if (!root or (!root->left and !root->right)) return 1;

    int leftChild = 0, rightChild = 0;
    if (root->left) leftChild = root->left->data;
    if (root->right) rightChild = root->right->data;

    return root->data == (leftChild + rightChild) and isSumProperty(root->left) and isSumProperty(root->right);
}

int main() {
    cout << "hello\n";
    return 0;
}