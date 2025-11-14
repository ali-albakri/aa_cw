#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

//  ╦ ╦┌─┐┬─┐┌┬┐
//  ║║║│ │├┬┘ ││
//  ╚╩╝└─┘┴└──┴┘
//  ╔═╗┬ ┬┌┬┐┌─┐┌─┐┌─┐┌┬┐┌─┐┬  ┌─┐┌┬┐┌─┐
//  ╠═╣│ │ │ │ ││  │ ││││├─┘│  ├┤  │ ├┤
//  ╩ ╩└─┘ ┴ └─┘└─┘└─┘┴ ┴┴  ┴─┘└─┘ ┴ └─┘

// Put the dictionary.txt under the same directory.

class AVLNode {
public:
    string key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string k):
        key(k), left(nullptr), right(nullptr), height(1) {
    }
};

class AVLTree {
private:
    // pointer to the root
    AVLNode* root;

    // each node carries height & balance factor
    // height calculator for node
    int height(AVLNode* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // balance factor for node
    int balanceFactor(AVLNode* node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // right rotation for a subtree
    AVLNode* rightRotate(AVLNode* y)
    {
        //saving their positions before rotation
        //     y
        //    /
        //   x
        //  / \
        // T1  T2

        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // perform rotation O(1)
        x->right = y;
        y->left = T2;
        //     x
        //    / \
        //   T1  y
        //      /
        //     T2


        // updating the heights
        y->height
            = max(height(y->left), height(y->right)) + 1;
        x->height
            = max(height(x->left), height(x->right)) + 1;

        // return new root
        return x;
    }

    AVLNode* leftRotate(AVLNode* x)
    {
        //saving their positions before rotation
        //     x
        //      \
        //       y
        //      / \
        //     T2  T3

        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // perform rotation O(1)
        y->left = x;
        x->right = T2;
        //       y
        //      / \
        //     x   T3
        //    / \
        //   T1  T2

        /// updating the heights
        x->height
            = max(height(x->left), height(x->right)) + 1;
        y->height
            = max(height(y->left), height(y->right)) + 1;

        // return new root
        return y;
    }

    AVLNode* insert(AVLNode* node, string key)
    {
        // performing the normal binary search tree insertion
        if (node == nullptr)
            return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // for duplicate key cases
        
        // the node here is the ancestor node
        // update height of node
        node->height = max(height(node->left), height(node->right)) + 1;

        // get the balance factor of node
        int balance = balanceFactor(node);

        // balance can only range from {-1, 0, 1} if not we do the following:

        // left left case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // right right case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // left right case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // right left case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void FIND_ALL_WITH_PREFIX(AVLNode* node, string& prefix, vector<string>& output)
    {
        if (node == nullptr)
            return;

        // requirement 1: go to the first node that could contain the prefix
        if (node->key < prefix) {
            FIND_ALL_WITH_PREFIX(node->right, prefix, output);
            return;
        }
        if (node->key.compare(0, prefix.size(), prefix) < 0) {
            FIND_ALL_WITH_PREFIX(node->right, prefix, output);
            return;
        }

        // requirement 2: modified inorder
        // traverse to left subtree if there is any match
        if (node->key >= prefix)
            FIND_ALL_WITH_PREFIX(node->left, prefix, output);

        // traverse to current node
        if (node->key.compare(0, prefix.size(), prefix) == 0)
            output.push_back(node->key);

        // traverse right subtree if there are any matches
        if (node->key <= prefix + char(255)) // largest possible character for upper bound
            FIND_ALL_WITH_PREFIX(node->right, prefix, output);
    }

    public:
        AVLTree() 
            : root(nullptr) 
        {}

        void insert(string key) {
            root = insert(root, key);
        }

        vector<string> FIND_ALL_WITH_PREFIX(string prefix) {
            vector<string> output;
            FIND_ALL_WITH_PREFIX(root, prefix, output);
            return output;
        }
};

void loadDictionary(AVLTree& tree, const string& dictionary) {
    ifstream file(dictionary);
    if (!file.is_open()) {
        cerr << "Error" << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        tree.insert(word);
    }
    file.close();
}

int main() {
    AVLTree tree;
    loadDictionary(tree, "dictionary.txt");

    string input;
    cout << "< WORD AUTOCOMPLETE >" << endl;
    cout << "Type a word: " << endl;

    while (true) {
        char c = _getch(); //used for live input

        if (c == 13) { // enter button
            if (!input.empty()) {
                vector<string> results = tree.FIND_ALL_WITH_PREFIX(input);
                if (!results.empty()) {
                    cout << endl << "< RESULTS >" << endl;
                    for (auto& r : results) {
                        cout << " - " << r << endl;
                    }
                }
            }
            break; // exit program
        }
        else if (c == 8) { // backspace button
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (isprint(c)) {
            input += c;
        }

        system("cls");
        cout << "< WORD AUTOCOMPLETE >" << endl;
        cout << "Type a word: " << input << endl;

        if (!input.empty()) {
            vector<string> results = tree.FIND_ALL_WITH_PREFIX(input);
            for (auto& r : results) {
                cout << " - " << r << endl;
            }
        }
    }
}