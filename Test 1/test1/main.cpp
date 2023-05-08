#include <iostream>
#include <vector>
#include <random>

using namespace std;

int n = 31;
vector<int> tree(n+1);
vector<int> tree_null(n+1);
vector<vector<int>> g(n+1);

void generate_tree() {
    uniform_int_distribution<int> vertex(-20, 20);
    uniform_int_distribution<int> is_null(0, 4);
    random_device rd;

    tree[1] = vertex(rd); // корень
    tree_null[1] = 1;
    for (int i = 2; i < n+1; i++) {
        if (is_null(rd) == 0) {
            tree[i] = NULL;
            tree_null[i] = 0;
        }
        else {
            if (tree[i/2] == NULL) {
                tree[i] = NULL;
                tree_null[i] = 0;
            }
            else {
                tree[i] = vertex(rd);
                tree_null[i] = 1;
            }
        }
    }

    for (int i = 1; i < n+1; i++) {
        if (tree_null[i] == 1) {
            if (i*2 < n+1 && tree_null[i*2] == 1) g[i].push_back(i*2);
            if (i*2+1 < n+1 && tree_null[i*2+1] == 1) g[i].push_back(i*2+1);
            if (i != 1) g[i].push_back(i/2);
        }
    }
}

vector<int> used(n+1);
int mx;
int vertex;
vector<int> ans_path;

void dfs(int v, int temp_max, vector<int> path) {
    temp_max += tree[v];
    path.push_back(v);
    if (temp_max > mx || (temp_max == mx && path.size() < ans_path.size())) {
        mx = temp_max;
        vertex = v;
        ans_path = path;
    }
    used[v] = 1;
    for (auto to : g[v]) {
        if (used[to] == 0) {
            dfs(to, temp_max, path);
        }
    }
}

int main() {
    generate_tree();
    int k = 1;
    int p = 1;
    for (int i = 1; i < n+1; i++) {
        if (tree_null[i] == 0) cout << "NULL ";
        else cout << tree[i] << " ";
        if (p == k) {
            cout << endl;
            k*=2;
            p = 0;
        }
        p++;
    }
    cout << endl;
    vector<int> final_path, path;
    int final_sum = 0;
    vector<int> leafs;
    for (int i = 1; i < n+1; i++) {
        if (g[i].size() == 1 && g[i][0] == i/2) leafs.push_back(i);
    }
    for (auto v : leafs) {
        mx = 0;
        vertex = -1;
        ans_path.resize(0);
        path.resize(0);
        used.erase(used.begin(), used.end());
        dfs(v, 0, path);
        if (mx > final_sum || (mx == final_sum && final_path.size() > ans_path.size())) {
            final_sum = mx;
            final_path = ans_path;
        }
    }
    for (auto v : final_path) cout << tree[v] << " ";
}
