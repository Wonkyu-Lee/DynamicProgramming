//
// Created by blazeq on 2018. 1. 9..
//

#include "catch.hpp"
#include <iostream>
#include <memory>
#include <list>

using namespace std;

namespace {

int optCost(int freq[], int n) {
    int fs[n];
    int dp[n][n];

    fs[0] = freq[0];
    for (int i = 1; i < n; ++i) {
        fs[i] = fs[i - 1] + freq[i];
    }

    // len: diagonal length
    for (int len = n; len >= 1; --len) {
        int delta = n - len;
        for (int i = 0; i < len; ++i) {
            int j = i + delta;
            int freqSum = fs[j] - ((i >= 1) ? fs[i - 1] : 0);

            dp[i][j] = INT_MAX;
            for (int r = i; r <= j; ++r) {
                int val = 0;
                if (r > i) {
                    val += dp[i][r - 1];
                }
                if (r < j) {
                   val += dp[r + 1][j];
                }
                if (val < dp[i][j]) {
                    dp[i][j] = val;
                }
            }
            dp[i][j] += freqSum;
        }
    }

    return dp[0][n - 1];
}

struct Node {
    static shared_ptr<Node> create(int key) {
        return shared_ptr<Node>(new Node(key));
    }

    shared_ptr<Node> left;
    shared_ptr<Node> right;
    int key{0};

private:
    Node(int key):key(key){}
};
using NodePtr = shared_ptr<Node>;

void print(NodePtr tree) {
    list<NodePtr> queue;
    queue.push_back(tree);

    // print tree
    while (!queue.empty()) {
        int size = queue.size();

        for (int i = 0; i < size; ++i) {
            NodePtr u = queue.front();
            cout << u->key << " ";

            queue.pop_front();

            if (u->left != nullptr) {
                queue.push_back(u->left);
            }
            if (u->right != nullptr) {
                queue.push_back(u->right);
            }
        }

        cout << endl;
    }
}

template<int N>
NodePtr createOptBst(int keys[N], int dp[N][N], int root[N][N], int i, int j) {
    if (i > j)
        return nullptr;

    int r = root[i][j];
    int key = keys[r];
    NodePtr node = Node::create(key);
    node->left = createOptBst(keys, dp, root, i, r - 1);
    node->right = createOptBst(keys, dp, root, r + 1, j);
    return node;
}

template<int N>
NodePtr optCostPrt(int keys[N], int freq[N]) {
    int fs[N];
    int dp[N][N];
    int root[N][N];

    fs[0] = freq[0];
    for (int i = 1; i < N; ++i) {
        fs[i] = fs[i - 1] + freq[i];
    }

    // len: diagonal length
    for (int len = N; len >= 1; --len) {
        int delta = N - len;
        for (int i = 0; i < len; ++i) {
            int j = i + delta;
            int freqSum = fs[j] - ((i >= 1) ? fs[i - 1] : 0);

            dp[i][j] = INT_MAX;
            for (int r = i; r <= j; ++r) {
                int val = 0;
                if (r > i) {
                    val += dp[i][r - 1];
                }
                if (r < j) {
                    val += dp[r + 1][j];
                }
                if (val < dp[i][j]) {
                    dp[i][j] = val;
                    root[i][j] = r;
                }
            }
            dp[i][j] += freqSum;
        }
    }

    return createOptBst<N>(keys, dp, root, 0, N - 1);
}

} // namespace

TEST_CASE("Optimal binary search tree", "[optBST]") {
    int keys[] = {1, 2, 3, 4, 5, 6};
    int freq[] = {34, 8, 50, 22, 14, 19};

    SECTION("optimal cost")
    {
        REQUIRE(293 == optCost(freq, 6));
    }

    SECTION("print BST")
    {
        NodePtr tree = optCostPrt<6>(keys, freq);
        //print(tree);
    }
}