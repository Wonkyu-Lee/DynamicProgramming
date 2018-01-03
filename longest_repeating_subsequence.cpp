//
// Created by blazeq on 2017. 12. 30..
//

#include "catch.hpp"
#include <iostream>

using namespace std;

namespace {

/*
 * example:
 * lrs("AABEBCDD") -> 3
 */

/*
 * lrs(a, b, m, n)
 *      = lrs(a, b, m - 1, n - 1) + 1, if a[m - 1] == b[n - 1]
 *      = max(lrs(a, b, m - 1, n), lrs(a, b, m, n - 1)), if a[m - 1] != b[n - 1] and m != n
 *      = 0, if m == 0 || n == 0
 */
int lrs(string a, string b, int m, int n) {
    if (m == 0 || n == 0) return 0;

    if (a[m - 1] == b[n - 1] && m != n)
        return lrs(a, b, m - 1, n - 1) + 1;
    else
        return max(lrs(a, b, m - 1, n), lrs(a, b, m, n - 1));
}

int lrs(string s) {
    return lrs(s, s, s.length(), s.length());
}

/*
 * dp[n + 1][n + 1]
 * dp[i][0] = 0, for i = 0..m
 * dp[0][j] = 0, for j = 0..n
 */
int lrsDp(string s) {
    int n = s.length();
    int dp[n + 1][n + 1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][n];
}

string lrsDpPrt(string s) {
    int n = s.length();
    int dp[n + 1][n + 1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    stringstream out;
    int i = n;
    int j = n;
    while(0 < i && 0 < j) {
        if (dp[i][j] == dp[i - 1][j - 1] + 1) {
            out << s[i - 1];
            --i;
            --j;
        } else if (dp[i][j] == dp[i - 1][j]) {
            --i;
        } else {
            --j;
        }
    }

    string r = out.str();
    reverse(r.begin(), r.end());
    return r;
}

} // namespace

TEST_CASE("Longest repeating subsequence", "[lrs]") {
    REQUIRE(lrs("AABEBCDD") == 3);
    REQUIRE(lrsDp("AABEBCDD") == 3);
    REQUIRE(lrsDpPrt("AABEBCDD") == "ABD");
}