//
// Created by blazeq on 2018. 1. 1..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>
#include <list>

namespace {
using namespace std;

int maxValueSum(int* weights, int* values, int n, int capacity) {
    if (capacity <= 0) return 0;
    if (n <= 0) return 0;

    int excludingLast = maxValueSum(weights, values, n - 1, capacity);
    int includingLast = capacity >= weights[n - 1] ?
                        maxValueSum(weights, values, n - 1, capacity - weights[n - 1]) + values[n - 1] :
                        0;
    return max(excludingLast, includingLast);
}

int maxValueSumMm(int* weights, int* values, int n, int capacity) {
    unordered_map<int, int> memo[n + 1];

    function<int(int, int)> _maxValueSum = [&](int i, int j) {
        if (j <= 0) return 0;
        if (i <= 0) return 0;
        if (memo[i].find(j) != memo[i].end()) {
            return memo[i][j];
        }

        int excludingLast = _maxValueSum(i - 1, j);
        int includingLast = j >= weights[i - 1] ? _maxValueSum(i - 1, j - weights[i - 1]) + values[i - 1] : 0;
        return memo[i][j] = max(excludingLast, includingLast);
    };

    return _maxValueSum(n, capacity);
}

int maxValueSumDp(int* weights, int* values, int n, int capacity) {
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= capacity; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                int excludingLast = dp[i - 1][j]; // don't forget this term!
                int includingLast = 0;
                if (j >= weights[i - 1]) {
                    includingLast = dp[i - 1][j - weights[i - 1]] + values[i - 1];
                }
                dp[i][j] = max(excludingLast, includingLast);
            }
        }
    }
    return dp[n][capacity];
}

int maxValueSumDp2(int* weights, int* values, int n, int capacity) {
    int dp[2][capacity + 1];
    memset(dp, 0, sizeof(dp));
    int* prev = dp[0];
    int* curr = dp[1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= capacity; ++j) {
            if (i == 0 || j == 0) {
                curr[j] = 0;
            } else {
                int excludingLast = prev[j]; // don't forget this term!
                int includingLast = 0;
                if (j >= weights[i - 1]) {
                    includingLast = prev[j - weights[i - 1]] + values[i - 1];
                }
                curr[j] = max(excludingLast, includingLast);
            }
        }

        swap(prev, curr);
    }

    return prev[capacity];
}

list<int> maxValueSumMmPrt(int* weights, int* values, int n, int capacity) {
    unordered_map<int, int> memo[n + 1];

    // tracking
    unordered_map<int, int> selection[n + 1];
    unordered_map<int, pair<int, int>> prev[n + 1];

    function<int(int, int)> _maxValueSum = [&](int i, int j) {
        if (i <= 0 || j <= 0) { selection[i][j] = -1; return 0; }
        if (memo[i].find(j) != memo[i].end()) {
            return memo[i][j];
        }

        int excludingLast = _maxValueSum(i - 1, j);
        int includingLast = j >= weights[i - 1] ? _maxValueSum(i - 1, j - weights[i - 1]) + values[i - 1] : 0;

        // store current selection and previous reference
        if (excludingLast >= includingLast) {
            prev[i][j] = make_pair(i - 1, j);
        } else {
            prev[i][j] = make_pair(i - 1, j - weights[i - 1]);
            selection[i][j] = i - 1;
        }

        return memo[i][j] = max(excludingLast, includingLast);
    };

    // run recursion
    _maxValueSum(n, capacity);

    // collect selections at each step
    pair<int, int> current = make_pair(n, capacity);
    list<int> selections;
    while (prev[current.first].find(current.second) != prev[current.first].end()) {
        if (selection[current.first].find(current.second) != selection[current.first].end()) {
            selections.push_front(selection[current.first][current.second]);
        }
        current = prev[current.first][current.second];
    }

    return selections;
}

} // namespace

TEST_CASE("0-1 Knapsack", "[knapsack]") {
    {
        int n = 3;
        int capacity = 4;
        int weights[] = {4, 5, 1};
        int values[] = {1, 2, 3};

        REQUIRE(maxValueSum(weights, values, n, capacity) == 3);
        REQUIRE(maxValueSumMm(weights, values, n, capacity) == 3);
        REQUIRE(maxValueSumDp(weights, values, n, capacity) == 3);
        REQUIRE(maxValueSumDp2(weights, values, n, capacity) == 3);
        REQUIRE((maxValueSumMmPrt(weights, values, n, capacity) == list<int>({2})));
    }

    {
        int n = 3;
        int capacity = 50;
        int weights[] = {10, 20,30};
        int values[] = {60, 100, 120};

        REQUIRE(maxValueSum(weights, values, n, capacity) == 220);
        REQUIRE(maxValueSumMm(weights, values, n, capacity) == 220);
        REQUIRE(maxValueSumDp(weights, values, n, capacity) == 220);
        REQUIRE(maxValueSumDp2(weights, values, n, capacity) == 220);
        REQUIRE((maxValueSumMmPrt(weights, values, n, capacity) == list<int>({1, 2})));
    }

}