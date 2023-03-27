#include <iostream>
#include "Tree.h"
#include <set>

using namespace std;

/*  Here are the functions I added to the code
*   I added is_bst and kth_smallest to the code
*   as the assignment stated, but I also added in
*   some helper functions to help breakdown the code
    so I could understand the concept better.
*/ 

bool is_bst(TreeNode* r);
bool is_bstHelper(TreeNode* r, TreeNode* minNode, TreeNode* maxNode);
int kth_smallest(TreeNode* r, int level);
int kthSmallestHelper(TreeNode* r, int& k);
int countNodes(TreeNode* r);

// Code from the example to test it out
int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);

    cout << is_bst(root) << endl; //Output 1
    cout << kth_smallest(root, 3) << endl; //Output 3

    return 0;
}

// Returns the output of the helper function and passes only the root node onto the function
bool is_bst(TreeNode* r) {
    return is_bstHelper(r, nullptr, nullptr);
}

// Uses recursion to check through the whole tree and return false if any of the values are in the wrong place
// and returns true once the root node is a null pointer indicating the end of the tree
bool is_bstHelper(TreeNode* r, TreeNode* minNode, TreeNode* maxNode) {
    if (r == nullptr) {
        return true;
    }

    if ((minNode != nullptr && r->data <= minNode->data) || (maxNode != nullptr && r->data >= maxNode->data)) {
        return false;
    }

    return is_bstHelper(r->left, minNode, r) && is_bstHelper(r->right, r, maxNode);
}

// Uses the countfunction to find and count all the nodes in the tree
// and if k is greater then the number of nodes it returns false
// otherwise it keeps going onto the helper function
int kth_smallest(TreeNode* r, int k) {
    int count = countNodes(r);
    if (count < k) {
        return -1;
    }

    return kthSmallestHelper(r, k);
}

// Uses recursion to find the kth smallest and returns once it is found
int kthSmallestHelper(TreeNode* r, int& k) {
    //If the current node is equal to nothing then k was not found
    // and it returns false
    if (r == nullptr) {
        return -1;
    }

    int val = kthSmallestHelper(r->left, k);
    if (k == 0) {
        return val;
    }

    if (--k == 0) {
        return r->data;
    }

    return kthSmallestHelper(r->right, k);
}

// Counts and uses recurrsion to count all the nodes in the tree and returns the total
int countNodes(TreeNode* r) {
    if (r == nullptr) {
        return 0;
    }

    return 1 + countNodes(r->left) + countNodes(r->right);
}