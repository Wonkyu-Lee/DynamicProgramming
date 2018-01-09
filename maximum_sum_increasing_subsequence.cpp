#include "catch.hpp"
#include <iostream>
#include <list>

using namespace std;

namespace {

int maximumSum(int A[], int n) {
    int dp[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = A[i]; // 초기화 잊지 말자!
        for (int j = 0; j < i; ++j) {
            if (A[j] <= A[i]) {
                dp[i] = max(dp[i], dp[j] + A[i]);
            }
        }
    }

    int maxSum = 0;
    for (int i = 0; i < n; ++i) {
        maxSum = max(maxSum, dp[i]);
    }

    return maxSum;
}

int maximumSumPrt(int A[], int n) {
    int dp[n];
    int prev[n];

    for (int i = 0; i < n; ++i) {
        dp[i] = A[i]; // 초기화 하는 걸 잊지 말자!
        int jMax = -1;
        for (int j = 0; j < i; ++j) {
            if (A[j] <= A[i]) {
                if (dp[i] < dp[j] + A[i]) {
                    dp[i] = dp[j] + A[i];
                    jMax = j;
                }

            }
        }
        prev[i] = jMax;
    }

    int maxSum = 0;
    int iMax = 0;
    for (int i = 0; i < n; ++i) {
        if (maxSum < dp[i]) {
            maxSum = dp[i];
            iMax = i;
        }
    }

    list<int> seq;
    int i = iMax;
    seq.push_front(A[i]);
    while (prev[i] != -1) {
        seq.push_front(A[prev[i]]);
        i = prev[i];
    }
    for (auto each : seq) {
        cout << each << " ";
    }
    cout << endl;


    return maxSum;
}

} // namespace

TEST_CASE("Maximum sum increasing subsequence", "[maximum sum increasing subsequence]") {
    {
        int A[] = {1, 101, 2, 3, 100, 4, 5};
        int n = sizeof(A)/sizeof(int);
        REQUIRE(maximumSum(A, n) == 106);
    }

    {
        int A[] = {3, 4, 5, 10};
        int n = sizeof(A)/sizeof(int);
        REQUIRE(maximumSum(A, n) == 22);
    }

    {
        int A[] = {10, 5, 4, 3};
        int n = sizeof(A)/sizeof(int);
        REQUIRE(maximumSum(A, n) == 10);
    }
}