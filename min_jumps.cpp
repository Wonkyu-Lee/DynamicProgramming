#include "catch.hpp"
#include <iostream>

using namespace std;

namespace {

int minJumps(int jumps[], int n) {
    if (n == 0) {
        return INT_MAX;
    }

    // dp[i] means min jumps from start to ith index.
    int dp[n];
    dp[0] = 0;

    for (int i = 1; i < n; ++i) {
        int minVal = INT_MAX;
        for (int j = 0; j < i; ++j) {
            if (j + jumps[j] >= i && dp[j] != INT_MAX) {
                minVal = min(minVal, dp[j] + 1);
            }
        }
        dp[i] = minVal;
    }

    return dp[n - 1];
}

} // namespace

TEST_CASE("Min jumps", "[min jumps]") {

    {
        int jumps[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
        int n = sizeof(jumps)/sizeof(int);
        REQUIRE(minJumps(jumps, n) == 3);
    }

    // 빈 배열이면, 0 INT_MAX
    {
        int jumps[] = {};
        int n = sizeof(jumps)/sizeof(int);
        REQUIRE(minJumps(jumps, n) == INT_MAX);
    }

    // 배열 1개 짜리면, 0 jump
    {
        int jumps[] = {0};
        int n = sizeof(jumps)/sizeof(int);
        REQUIRE(minJumps(jumps, n) == 0);
    }

    // 첫 점프가 0이면 INT_MAX
    {
        int jumps[] = {0, 2};
        int n = sizeof(jumps)/sizeof(int);
        REQUIRE(minJumps(jumps, n) == INT_MAX);
    }

}