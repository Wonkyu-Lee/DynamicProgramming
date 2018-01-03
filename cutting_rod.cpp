//
// Created by blazeq on 2018. 1. 2..
//

#include "catch.hpp"
using namespace std;

namespace {

/*
 * 두 가지 방법으로 풀었다
 * 두 번째 방법이 더욱 간단하다
 * 이런 유형의 문제는 한 레벨의 값들을 모두 비교해서 최대/최소를 찾는 형태로 풀린다.
 * 시간복잡도는 O(n^2)이지만 공간복잡도를 O(n)으로 만들 수 있다.
 */

int maxTotal(int* p, int m, int l) {
    if (m == 0 || l == 0) return 0;
    int excludingLast = maxTotal(p, m - 1, l);
    int includingLast = (l >= m) ? maxTotal(p, m, l - m) + p[m - 1] : 0;
    return max(excludingLast, includingLast);
}

int maxTotal(int* p, int l) {
    return maxTotal(p, l, l);
}

int maxTotalDp(int* p, int l) {
    int dp[l + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= l; ++i) {
        for (int j = i; j <= l; ++j) {
            int excludingLast = dp[j];
            int includingLast = dp[j - i] + p[i - 1];;
            dp[j] = max(excludingLast, includingLast);
        }
    }
    return dp[l];
}

int maxTotal2(int* p, int l) {
    if (l == 0) return 0;
    int maxPrice = 0;
    for (int i = 1; i <= l; ++i) {
        int price = maxTotal2(p, l - i) + p[i - 1];
        if (price > maxPrice) {
            maxPrice = price;
        }
    }
    return maxPrice;
}

int maxTotalDp2(int* p, int l) {
    int dp[l + 1]; dp[0] = 0;
    for (int i = 1; i <= l; ++i) {
        int maxPrice = 0;
        for (int j = 1; j <= i; ++j) {
            int price = p[j - 1] + dp[i - j];
            if (price > maxPrice) {
                maxPrice = price;
            }
        }
        dp[i] = maxPrice;
    }
    return dp[l];
}

} // namespace

TEST_CASE("Cutting a rod", "[cutting rod]") {

    {
        int p[] = {1, 5, 8, 9, 10, 17, 17, 20};
        int l = 8;
        REQUIRE(maxTotal(p, l) == 22);
        REQUIRE(maxTotal2(p, l) == 22);
        REQUIRE(maxTotalDp(p, l) == 22);
        REQUIRE(maxTotalDp2(p, l) == 22);
    }

    {
        int p[] = {3, 5, 8, 9, 10, 17, 17, 20};
        int l = 8;
        REQUIRE(maxTotal(p, l) == 24);
        REQUIRE(maxTotal2(p, l) == 24);
        REQUIRE(maxTotalDp(p, l) == 24);
        REQUIRE(maxTotalDp2(p, l) == 24);
    }
}