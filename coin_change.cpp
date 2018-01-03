//
// Created by blazeq on 2018. 1. 1..
//

#include "catch.hpp"
using namespace std;

namespace {

int countWays(int coins[], int n, int change) {
    if (change == 0) return 1;
    else if (change < 0) return 0;
    else if (n <= 0) return 0;
    else return countWays(coins, n - 1, change) + countWays(coins, n, change - coins[n - 1]);
}

/*
 * i번까지의 코인들만 사용하고 그 중에 i번째 코인은 꼭 포함해서 거스름 돈(change)을 만드는 방법
 * n번까지 모두 더하면 모든 방법의 수를 의미한다.
 */
int countWays2(int coins[], int n, int change) {
    if (change == 0) return 1;
    if (change < 0) return 0;
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        count += countWays(coins, i, change - coins[i - 1]);
    }
    return count;
}

int countWaysDp2(int coins[], int n, int change) {
    int dp[change + 1]; // change를 기준으로 테이블을 만든다.
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = coins[i]; j <= change; ++j) {
            // i번째 코인을 반드시 포함한다면 그 액수만큼 뺀 모든 경우의 수(반드시 미리 계산됨)를 더해주면 된다.
            // 왜냐하면 dp[j]는 아직 i번째 코인을 포함하지 않고 j를 만들 모든 경우의 수를 저장하고 있기 때문이다.
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[change];
}

} // namespace

TEST_CASE("Coin change", "[coin change]") {
    int coins[] = {2, 5, 3, 6};
    REQUIRE(countWays(coins, 4, 10) == 5);
    REQUIRE(countWays2(coins, 4, 10) == 5);
    REQUIRE(countWaysDp2(coins, 4, 10) == 5);
}