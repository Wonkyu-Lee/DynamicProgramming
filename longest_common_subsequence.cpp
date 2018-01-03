//
// Created by blazeq on 2017. 12. 30..
//

#include "catch.hpp"
#include <iostream>
using namespace std;

namespace {

/*
 * example:
 * lcs("ABCDGH", "AEDFHR") -> 3 // "ADH"
 */

/*
 * lcs(a, b, m, n)
 *      = lcs(a, b, m - 1, n - 1) + 1, if a[m - 1] == b[n - 1]
 *      = max(lcs(a, b, m - 1, n), lcs(a, b, m, n - 1)), if a[m - 1] != b[n - 1]
 *      = 0, if m == 0 || n == 0
 */

int lcs(string a, string b, int m, int n) {
    if (m == 0 || n == 0) return 0;
    if (a[m - 1] == b[n - 1])
        return lcs(a, b, m - 1, n - 1) + 1;
    else
        return max(lcs(a, b, m - 1, n), lcs(a, b, m, n - 1));
}

int lcs(string a, string b) {
    return lcs(a, b, a.length(), b.length());
}

/*
 * dp[m + 1][n + 1]
 * dp[i][0] = 0, for i = 0..m
 * dp[0][j] = 0, for j = 0..n
 */
int lcsDp(string a, string b) {
    int m = a.length();
    int n = b.length();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

string lcsDpPrt(string a, string b) {
    int m = a.length();
    int n = b.length();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    stringstream out;
    int i = m;
    int j = n;
    while(0 < i && 0 < j) {
        if (dp[i][j] == dp[i - 1][j - 1] + 1) {
            out << a[i - 1];
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


TEST_CASE("Longest common subsequence", "[lcs]") {
    REQUIRE(lcs("ABCDGH", "AEDFHR") == 3);
    REQUIRE(lcs("AGGTAB", "GXTXAYB") == 4);

    REQUIRE(lcsDp("ABCDGH", "AEDFHR") == 3);
    REQUIRE(lcsDp("AGGTAB", "GXTXAYB") == 4);

    REQUIRE(lcsDpPrt("ABCDGH", "AEDFHR") == "ADH");
    REQUIRE(lcsDpPrt("AGGTAB", "GXTXAYB") == "GTAB");
}