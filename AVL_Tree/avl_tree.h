#include <iostream>
//#include "main.cpp"

using namespace std;

struct information {
    int passid;
    string fullname;
    string birthday;
    string room;
    string dorm;
    string university;

    information(int id, string name, string bday, string rm, string drm, string uni) {
        passid = id;
        fullname = name;
        birthday = bday;
        room = rm;
        dorm = drm;
        university = uni;
    }
};

template <class T>
class AVLNode {
public:
    T key;
    int height;
    AVLNode<T> *left;
    AVLNode<T> *right;
    information *info;

    AVLNode(T k, information* t) {
        key = k;
        height = 1;
        left = NULL;
        right = NULL;
        info = t;
    }
};

template <class T>
class AVLTree {
private:
    int height(AVLNode<T> *node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(AVLNode<T> *node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode<T> *node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = max(leftHeight, rightHeight) + 1;
    }

    AVLNode<T> *rotateLeft(AVLNode<T> *node) {
        AVLNode<T> *rightChild = node->right;
        AVLNode<T> *leftGrandChild = rightChild->left;
        rightChild->left = node;
        node->right = leftGrandChild;
        updateHeight(node);
        updateHeight(rightChild);
        return rightChild;
    }

    AVLNode<T> *rotateRight(AVLNode<T> *node) {
        AVLNode<T> *leftChild = node->left;
        AVLNode<T> *rightGrandChild = leftChild->right;
        leftChild->right = node;
        node->left = rightGrandChild;
        updateHeight(node);
        updateHeight(leftChild);
        return leftChild;
    }

    AVLNode<T> *balance(AVLNode<T> *node) {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        } else if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode<T> *insertHelper(AVLNode<T> *node, T key, information *t) {
        if (node == NULL) {
            return new AVLNode(key, t);
        }
        if (key < node->key) {
            node->left = insertHelper(node->left, key, t);
        } else {
            node->right = insertHelper(node->right, key, t);
        }
        return balance(node);
    }

    void printHelper(AVLNode<T> *node) {
        if (node != NULL) {
            printHelper(node->left);
            cout << node->info->passid << " " << node->info->fullname << endl;
            printHelper(node->right);
        }
    }

    void searchHelper(AVLNode<T> *node, T key) {
        if (node != NULL) {
            if (node->key == key)
                print_information(node);
            if (node->key > key) {
                searchHelper(node->left, key);
            }
            else {
                searchHelper(node->right, key);
            }
        }
        //else cout << "Not found" << endl;
    }

public:
    AVLNode<T> *root;

    AVLTree() {
        root = NULL;
    }

    void insert(T key, information *t) {
        root = insertHelper(root, key, t);
    }

    void print() {
        printHelper(root);
        cout << endl;
    }

    void print_information(AVLNode<T> *node) {
        cout << "Id: " << node->info->passid << "\nName: " << node->info->fullname << "\nBirthday: " << node->info->birthday\
        << "\nUniversity: " << node->info->university << "\nDorm: " << node->info->dorm << "\nRoom: " << node->info->room << endl;
    }

    void search(T key) {
        searchHelper(root, key);
    }
};