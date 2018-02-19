#include "catch.hpp"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

namespace {

bool hasSubsetSum(int* set, int n, int sum) {
    bool dp[n + 1][sum + 1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            if (j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else {
                dp[i][j] = dp[i - 1][j];
                if (dp[i - 1][j] == false && j - set[i - 1] >= 0) {
                    dp[i][j] = dp[i - 1][j - set[i - 1]];
                }
            }
        }
    }

    return dp[n][sum];
}

bool hasSubsetSumPrt(int* set, int n, int sum) {
    // solve
    bool dp[n + 1][sum + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            if (j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else {
                dp[i][j] = dp[i - 1][j];
                if (dp[i - 1][j] == false && j - set[i - 1] >= 0) {
                    dp[i][j] = dp[i - 1][j - set[i - 1]];
                }
            }
        }
    }

    // print just one case
//    if (dp[n][sum]) {
//        list<int> subset;
//        int i = n;
//        int j = sum;
//        while (i > 0 && j > 0) {
//            if (dp[i - 1][j]) {
//                --i;
//            } else {
//                subset.push_front(set[i - 1]);
//                j -= set[i - 1];
//                --i;
//            }
//        }
//        for (auto each : subset) {
//            cout << each << " ";
//        }
//        cout << endl;
//    }


    return dp[n][sum];
}

bool hasSubsetSum2(int set[], int n, int sum) {
    bool dp[2][sum + 1];
    bool* dpPrev = dp[0];
    bool* dpCurr = dp[1];

    for (int i = 0; i <= n; ++i) {
        swap(dpPrev, dpCurr);
        for (int j = 0; j <= sum; ++j) {
            if (j == 0) {
                dpCurr[j] = true;
            } else if (i == 0) {
                dpCurr[j] = false;
            } else {
                dpCurr[j] = dpPrev[j];
                if (dpPrev[j] == false && j - set[i - 1] >= 0) {
                    dpCurr[j] = dpPrev[j - set[i - 1]];
                }
            }
        }
    }

    return dpCurr[sum];
}

// S(n, sum) = S(n - 1, sum) + S(n - 1, sum - set[n - 1])
int countAllSubsetSum(int set[], int n, int sum) {
    int dp[n + 1][sum + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            if (j == 0) {
                dp[i][j] = 1;
            } else  if (i == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i - 1][j];
                if (j >= set[i - 1]) {
                    dp[i][j] += dp[i - 1][j - set[i - 1]];
                }
            }
        }
    }
    return dp[n][sum];
}

// S(i, j) = S(i - 1, j) + S(i - 1, j - set[i - 1])
//
int countAllSubsetSumPrt(int set[], int n, int sum) {
    int dp[n + 1][sum + 1];

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            if (j == 0) {
                dp[i][j] = 1;
            } else  if (i == 0) {
                dp[i][j] = 0;
            } else {
                int left = 0;
                int right = 0;
                left = dp[i - 1][j];

                if (j >= set[i - 1]) {
                    right = dp[i - 1][j - set[i - 1]];
                }
                dp[i][j] = left + right;
            }
        }
    }


    function<void(int, int, list<int>&)> prt = [&](int i, int j, list<int>& subset) {
        if (dp[i][j] == 0) return;

        if (j == 0) {
            for (auto e : subset) {
                cout << e << " ";
            }
            cout << endl;

            return;
        }

        if (dp[i-1][j] > 0) {
            prt(i - 1, j, subset);
        }

        if (j >= set[i - 1] && dp[i - 1][j - set[i - 1]] > 0) {
            subset.push_back(set[i - 1]);
            prt(i - 1, j - set[i - 1], subset);
            subset.pop_back();
        }
    };

    list<int> _subset;
    prt(n, sum, _subset);

    return dp[n][sum];
}

} // namespace

TEST_CASE("Subset sum", "[subset sum]") {
    int set[] = {3, 34, 4, 12, 5, 2};
    int n = sizeof(set)/sizeof(int);
    REQUIRE(hasSubsetSumPrt(set, n, 9));
    REQUIRE(hasSubsetSumPrt(set, n, 1) == false);
    REQUIRE(hasSubsetSumPrt(set, n, 17));

    REQUIRE(countAllSubsetSum(set, n, 17) == 2);
    //REQUIRE(countAllSubsetSumPrt(set, n, 17) == 2);
}