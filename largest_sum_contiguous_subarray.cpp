//
// Created by blazeq on 2017. 12. 31..
//

#include "catch.hpp"

namespace {

using namespace std;

/*
 * example: {-2, -3, 4, -1, -2, 1, 5, -3}
 *  ending:  -2  -3  4   3   1  2  7   4
 *  maxSum:  -2      4             7
 */
int largestSum(int array[], int n) {
    if (n == 0) return 0;

    int ending = array[0];
    int maxSum = array[0];
    for (int i = 1; i < n; ++i) {
        if (ending < 0) {
            ending = array[i];
        } else {
            ending += array[i];
        }
        if (ending > maxSum) {
            maxSum = ending;
        }
    }

    return maxSum;
}

/*
 * example: {-2, -3, 4, -1, -2, 1, 5, -3}
 *  ending:  -2  -3  4   3   1  2  7   4
 *  maxSum:  -2      4             7
 *       s:   0   1  2
 *       e:   0   1  2   3   4  5  6
 */
pair<int, int> largestSumSubarray(int array[], int n) {
    pair<int, int> maxSumRange(-1, -1);

    if (n == 0) return maxSumRange;

    int ending = array[0];
    int maxSum = array[0];
    pair<int, int> sumRange(0, 0);
    maxSumRange.first = 0;
    maxSumRange.second = 0;
    for (int i = 1; i < n; ++i) {
        if (ending < 0) {
            ending = array[i];
            sumRange.first = i;
            sumRange.second = i;
        } else {
            ending += array[i];
            sumRange.second = i;
        }
        if (ending > maxSum) {
            maxSum = ending;
            maxSumRange = sumRange;
        }
    }

    return maxSumRange;
}

} // namespace

TEST_CASE("Largest sum contiguous subarray", "[lscs]") {
    {
        int array[] = {-2, -3, 4, -1, -2, 1, 5, -3};
        int n = sizeof(array)/sizeof(int);
        REQUIRE(largestSum(array, n) == 7);
        REQUIRE(largestSumSubarray(array, n) == make_pair(2, 6));
    }

    {
        int array[] = {-2, -3, -4, -1, -2, -5, -3};
        int n = sizeof(array)/sizeof(int);
        REQUIRE(largestSum(array, n) == -1);
        REQUIRE(largestSumSubarray(array, n) == make_pair(3, 3));
    }

}