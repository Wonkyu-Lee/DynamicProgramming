//
// Created by blazeq on 2017. 12. 31..
//
#include "catch.hpp"
#include <queue>

namespace {

/*
 * numbers whose only prime numbers are 2, 3, 5
 * sequence: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ...
 *        n: 1  2  3  4  5  6  7  8   9  10  11
 *
 *  prime[3] = {2, 3, 5}
 *  index[3] = {1, 1, 1}
 *
 *    q(2): 1x2 2x2 3x2
 *   index:  1   2   3
 *    q(3): 1x3 2x3 3x3
 *   index:  1   2   3
 *    q(5): 1x5 2x5
 *   index:  1   2
 *      dp:  0  1  2  3  4  5  6
 */
int uglyNumber(int n, int prime[], int m) {
    if (m == 0) return 0;

    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;

    int index[m];
    for (int i = 0; i < m; ++i) index[i] = 1;

    int q[m];
    for (int i = 0; i < m; ++i) q[i] = prime[i];

    for (int i = 2; i <= n; ++i) {
        int minValue = q[0];
        for (int j = 1; j < m; ++j) {
            if (q[j] < minValue) {
                minValue = q[j];
            }
        }

        dp[i] = minValue;

        for (int j = 0; j < m; ++j) {
            if (q[j] == minValue) {
                ++index[j];
                q[j] = prime[j] * dp[index[j]];
            }
        }
    }

    return dp[n];
}

} // namespace

TEST_CASE("Ugly numbers", "[ugly numbers]") {
    int prime[] = {2, 3, 5};
    int m = sizeof(prime)/sizeof(int);
    auto un = [&](int n) { return uglyNumber(n, prime, m); };

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20};
    for (int i = 0; i < sizeof(expected)/sizeof(int); ++i) {
        REQUIRE(expected[i] == un(i));
    }
}