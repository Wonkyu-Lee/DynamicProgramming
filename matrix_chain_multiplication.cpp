//
// Created by blazeq on 2018. 2. 4..
//

#include "catch.hpp"
#include <climits>
#include <iostream>

namespace {

using namespace std;

int matrixChainOrder(int p[], int m) {
    int n = m - 1;
    int table[n][n];

    for (int l = 1; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l - 1;
            if (i == j) {
                table[i][j] = 0;
            } else {
                table[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    int order = table[i][k] + table[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    table[i][j] = min(table[i][j], order);
                }
            }
        }
    }

    return table[0][n - 1];
}

} // namespace

TEST_CASE("Matrix chain multiplication", "[matrix chain multiplication]") {
    int p[] = {1, 2, 3, 4};
    int n = sizeof(p)/sizeof(int);

    printf("Minimum number of multiplications is %d.\n", matrixChainOrder(p, n));
}