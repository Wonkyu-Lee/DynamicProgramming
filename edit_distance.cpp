//
// Created by blazeq on 2018. 1. 26..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;


enum Edit { NONE = -1, MATCH, INSERT, DELETE };
struct Cell { int cost; Edit parent; };

int editDistance(const string& s1, const string& s2) {

    const int m = s1.length();
    const int n = s2.length();
    Cell table[m + 1][n + 1];

    auto initRow = [&](int r) {
        table[0][r].cost = r;
        table[0][r].parent = (r == 0) ? NONE : INSERT;
    };

    auto initCol = [&](int c) {
        table[c][0].cost = c;
        table[c][0].parent = (c == 0) ? NONE : DELETE;
    };

    for (int r = 0; r <= m; ++r) {
        initRow(r);
    }

    for (int c = 0; c <= n; ++c) {
        initCol(c);
    }

    auto costMatch = [](char x, char y) {
        return (x == y) ? 0 : 1;
    };

    auto costInDel = [](char c) {
        return 1;
    };

    auto goalCell = [&]() {
        return table[m][n];
    };

    int options[3];
    for (int r = 1; r <= m; ++r) {
        for (int c = 1; c <= n; ++c) {
            options[MATCH] = table[r - 1][c - 1].cost + costMatch(s1[r - 1], s2[c - 1]);
            options[INSERT] = table[r][c - 1].cost + costInDel(s2[c - 1]);
            options[DELETE] = table[r - 1][c].cost + costInDel(s1[r - 1]);

            table[r][c].cost = options[MATCH];
            table[r][c].parent = MATCH;
            for (int i = INSERT; i <= DELETE; ++i) {
                if (options[i] > table[r][c].cost) {
                    table[r][c].cost = options[i];
                    table[r][c].parent = (Edit)i;
                }
            }
        }
    }

    return goalCell().cost;
}

} // namespace

TEST_CASE("Edit distance", "[edit distance]") {
    REQUIRE(editDistance("cat", "crt") == 1);
    REQUIRE(editDistance("geek", "gesek") == 1);
    REQUIRE(editDistance("saturday", "sunday") == 3);
}