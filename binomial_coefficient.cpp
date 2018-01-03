//
// Created by blazeq on 2017. 12. 30..
//

#include "catch.hpp"

namespace {
using namespace std;

int binomialCoeff(int n, int k) {
    if (k == 0 || k == n) return 1;
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

int binomialCoeffDp(int n, int k) {
    int dp[n + 1][k + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }

    return dp[n][k];
}

int binomialCoeffDp2(int n, int k) {
    int dp[k + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = min(i, k); 1 <= j; --j) {
            dp[j] = dp[j - 1] + dp[j];
        }
    }

    return dp[k];
}

int binomialCoeff2(int n, int k) {
    if (k == 0 || k == n) return 1;

    if (n - k < k)
        k = n - k;

    int r = 1;
    for (int i = 1; i <= k; ++i) {
        r *= (n - i + 1) / i;
    }

    return r;
}

} // namespace

TEST_CASE("binomial coefficient", "[binomial coefficient]") {
    REQUIRE(binomialCoeff(5, 3) == 10);
    REQUIRE(binomialCoeffDp(5, 3) == 10);
    REQUIRE(binomialCoeff2(5, 3) == 10);
    REQUIRE(binomialCoeffDp2(5, 3) == 10);
}