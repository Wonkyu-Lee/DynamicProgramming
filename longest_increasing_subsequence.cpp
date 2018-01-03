//
// Created by blazeq on 2018. 1. 1..
//

#include "catch.hpp"
#include <list>
#include <iostream>

namespace {

using namespace std;

/*
 * example: 10, 22, 9, 33, 21, 50, 41, 60, 80
 *           1   2  1   3   2   4   4   5   6
 */
int lis(int array[], int n) {
    if (n == 0) return 0;

    int dp[n]; dp[0] = 1;
    int maxLen = dp[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (array[j] <= array[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }

    return maxLen;
}

/*
 * example: 10, 22, 9, 33, 21, 50, 41, 60, 80
 *      dp:  1   2  1   3   2   4   4   5   6
 * max Len:  1   2      3       4       5   6
 *   index:  0   1  2   3   4   5   6   7   8
 *    prev: -1   0 -1   1   0   3   3   5   7
 *    80, 60, 50, 33, 22, 10
 */
list<int> lisSubarray(int* array, int n) {
    list<int> seq;
    if (n == 0) return seq;

    int dp[n]; dp[0] = 1;
    int maxLen = dp[0];

    int prev[n];
    memset(prev, -1, sizeof(prev));
    int maxLenAt = 0;

    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (array[j] <= array[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxLenAt = i;
        }
    }

    int curIndex = maxLenAt;
    while (curIndex != -1) {
        seq.push_front(array[curIndex]);
        curIndex = prev[curIndex];
    }

    return seq;
}

} // namespace

TEST_CASE("Longest increasing subsequence", "[lis]") {
    int array[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int n = sizeof(array) / sizeof(int);
    REQUIRE(lis(array, n) == 6);
    REQUIRE(lisSubarray(array, n) == list<int>({10, 22, 33, 50, 60, 80}));
}