//
// Created by blazeq on 2018. 1. 1..
//

#include "catch.hpp"
#include <cmath>
#include <functional>
#include <iostream>

namespace {

using namespace std;

template<int ROWS, int COLS>
int maxSquareSize(int array[ROWS][COLS]) {

    int dp[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j =0; j < COLS; ++j) {
            dp[i][j] = array[i][j];
        }
    }

    int maxSize = 0;
    for (int i = 1; i < ROWS; ++i) {
        for (int j =1; j < COLS; ++j) {
            if (array[i][j] != 0) {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                if (dp[i][j] > maxSize) {
                    maxSize = dp[i][j];
                }
            }
        }
    }

    return maxSize;
};

} // namespace

TEST_CASE("Max size square sub matrix", "[max square size]") {
    int M[6][5] =  {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    REQUIRE((maxSquareSize<6, 5>(M) == 3));
}