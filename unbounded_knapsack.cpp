//
// Created by blazeq on 2018. 2. 19..
//

#include "catch.hpp"
#include <iostream>

using namespace std;

namespace {

int getMaxValue(int v[], int wt[], int n, int w) {
    int dp[w + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= w; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i - wt[j] >= 0) {
                dp[i] = max(dp[i], dp[i - wt[j]] + v[j]);
            }
        }
    }

    return dp[w];
}

int getMaxValue2(int v[], int wt[], int n, int w) {
    int dp[n + 1][w + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= w; ++j) {
            int excluding = dp[i - 1][j];  // don't forget this term!
            int including = 0;
            if (j - wt[i - 1] >= 0) {
                including = dp[i][j - wt[i - 1]] + v[i - 1];
            }

            dp[i][j] = max(excluding, including);
        }
    }

    return dp[n][w];
}

} // namespace

TEST_CASE("Unbounded knapsack", "[unbounded knapsack]") {

    SECTION("Test 1") {
        int v[] = {1, 1};
        int wt[] = {2, 1};
        REQUIRE(3 == getMaxValue(v, wt, 2, 3));
    }

    SECTION("Test 2") {
        int v[] = {1, 4, 5, 7};
        int wt[] = {1, 3, 4, 5};
        REQUIRE(11 == getMaxValue(v, wt, 4, 8));
    }

}