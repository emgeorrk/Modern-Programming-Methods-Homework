#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include "avl_tree.h"

using namespace std;

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
    for (int i = 0; i < names.size(); i++) {
        file1 >> names[i];
    }
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
