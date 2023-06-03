#include <iostream>
#include <fstream>
#include <random>
#include <set>

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
            cout << node->key << " " << node->info->fullname << endl;
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
        else cout << "Not found" << endl;
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

int main() {
    int n;
    cout << "Number of students:";
    cin >> n;

    random_device rd;
    uniform_int_distribution<int> uid_names(0, 19947);
    uniform_int_distribution<int> uid_surnames(0, 9486);
    uniform_int_distribution<int> uid_midnames(0, 1466);
    uniform_int_distribution<int> uid_day(1, 30);
    uniform_int_distribution<int> uid_month(1, 12);
    uniform_int_distribution<int> uid_year(1999, 2004);
    uniform_int_distribution<int> uid_room(100, 1000);
    uniform_int_distribution<int> uid_dorm(1, 23);
    uniform_int_distribution<int> uid_uni(0, 5);
    uniform_int_distribution<int> uid_passid(100'000, 999'999);
    set<int> ids;
    while (ids.size() < n) ids.insert(uid_passid(rd));
    vector<string> universities = {"SPbU", "ITMO", "HSE", "MSU", "MIPT", "MIFI"};

    fstream file1, file2, file3;
    file1.open("names.txt");
    file2.open("surnames.txt");
    file3.open("midnames.txt");

    vector<string> names(19948), surnames(9487), midnames(1467);
    for (int i = 0; i < names.size(); i++) file1 >> names[i];
    for (int i = 0; i < surnames.size(); i++) file2 >> surnames[i];
    for (int i = 0; i < midnames.size(); i++) file3 >> midnames[i];

    vector<information> info;
    auto it = ids.begin();
    for (int i = 0; i < n; i++) {
        string nm = names[uid_names(rd)] + " " + surnames[uid_surnames(rd)] + " " + midnames[uid_midnames(rd)];
        string bday = to_string(uid_day(rd)) + "." + to_string(uid_month(rd)) + "." + to_string(uid_year(rd));
        string rm = to_string(uid_room(rd));
        string drm = to_string(uid_dorm(rd));
        string uni = universities[uid_uni(rd)];
        int id = *it;
        it++;
        information temp(id, nm, bday, rm, drm, uni);
        info.push_back(temp);
    }

    AVLTree<int> id_tree;
    AVLTree<string> name_tree;

    //AVLTree_string name_tree;

    // create duplicates
    information myself(123, "Merkushev Egor Alexeyevich", "01.01.2004", "603", "10", "SPbU");
    information myself_copy(641, "Merkushev Egor Alexeyevich", "30.11.2002", "705", "14", "SPbU");
    id_tree.insert(myself.passid, &myself);
    name_tree.insert(myself.fullname, &myself);
    id_tree.insert(myself_copy.passid, &myself_copy);
    name_tree.insert(myself_copy.fullname, &myself_copy);

    for (int i = 0; i < info.size(); i++) {
        id_tree.insert(info[i].passid, &info[i]);
        name_tree.insert(info[i].fullname, &info[i]);
    }
    cout << "1 - Find by id\n2 - Find by full name\n3 - Print sorted by id\n4 - Print sorted by name\n0 - exit" << endl;
    int request;
    while (true) {
        cout << "Your request:";
        cin >> request;
        if (request == 0) exit(0);
        if (request == 1) {
            int searchid;
            cout << "id:";
            cin >> searchid;
            id_tree.search(searchid);
        }
        if (request == 2) {
            string fullname;
            cout << "Full name:";
            cin.ignore();
            getline(cin, fullname);
            name_tree.search(fullname);
        }
        if (request == 3) id_tree.print();
        if (request == 4) name_tree.print();
    }
}
