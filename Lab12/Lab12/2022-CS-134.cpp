#include <iostream>
#include <algorithm>

using namespace std;

class AVLTree {
private:
    class Node {
    public:
        int value;
        Node* left;
        Node* right;
        int height;

        Node(int v)
        {
            value = v;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int heightDifference(Node* n) {
        return height(n->left) - height(n->right);
    }

    bool isBalanced(Node* n) {
        return abs(heightDifference(n)) <= 1;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = heightDifference(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr)
            return root;

        if (value < root->value)
            root->left = deleteNode(root->left, value);
        else if (value > root->value)
            root->right = deleteNode(root->right, value);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = heightDifference(root);

        if (balance > 1 && heightDifference(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && heightDifference(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && heightDifference(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && heightDifference(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void printTree(Node* root, int space = 0) {
        if (root != nullptr) {
            printTree(root->right, space + 5);
            cout << std::string(space, ' ') << root->value << "\n";
            printTree(root->left, space + 5);
        }
    }

    void printTree() {
        printTree(root);
    }
};

int main() {
    AVLTree avl;

    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    cout << "AVL Tree after insertions:\n";
    avl.printTree();

    avl.remove(30);

    cout << "\nAVL Tree after deletion:\n";
    avl.printTree();

    return 0;
}


//Question 01


//class Solution {
//public:
//    bool isBalanced(TreeNode* root) {
//        // If the tree is empty, we can say it’s balanced...
//        if (root == NULL)  return true;
//        // Height Function will return -1, when it’s an unbalanced tree...
//        if (Height(root) == -1)  return false;
//        return true;
//    }
//    // Create a function to return the “height” of a current subtree using recursion...
//    int Height(TreeNode* root) {
//        // Base case...
//        if (root == NULL)  return 0;
//        // Height of left subtree...
//        int leftHeight = Height(root->left);
//        // Height of height subtree...
//        int rightHight = Height(root->right);
//        // In case of left subtree or right subtree unbalanced or their heights differ by more than ‘1’, return -1...
//        if (leftHeight == -1 || rightHight == -1 || abs(leftHeight - rightHight) > 1)  return -1;
//        // Otherwise, return the height of this subtree as max(leftHeight, rightHight) + 1...
//        return max(leftHeight, rightHight) + 1;
//    }
//};




// Question02


///**
// * Definition for a binary tree node.
// * struct TreeNode {
// *     int val;
// *     TreeNode *left;
// *     TreeNode *right;
// *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
// *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// * };
// */
//class Solution {
//public:
//    int makeVine(TreeNode* grand, int cnt = 0) {
//        auto n = grand->right;
//        while (n != nullptr) {
//            if (n->left != nullptr) {
//                auto old_n = n;
//                n = n->left;
//                old_n->left = n->right;
//                n->right = old_n;
//                grand->right = n;
//            }
//            else {
//                ++cnt;
//                grand = n;
//                n = n->right;
//            }
//        }
//        return cnt;
//    }
//    void compress(TreeNode* grand, int m) {
//        auto n = grand->right;
//        while (m-- > 0) {
//            auto old_n = n;
//            n = n->right;
//            grand->right = n;
//            old_n->right = n->left;
//            n->left = old_n;
//            grand = n;
//            n = n->right;
//        }
//    }
//    TreeNode* balanceBST(TreeNode* root) {
//        TreeNode grand;
//        grand.right = root;
//        auto cnt = makeVine(&grand);
//        int m = pow(2, int(log2(cnt + 1))) - 1;
//        compress(&grand, cnt - m);
//        for (m = m / 2; m > 0; m /= 2)
//            compress(&grand, m);
//        return grand.right;
//    }
//};