#include "catch.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace {

struct Line {
    int e;
    int x;
    vector<int> a;
    vector<int> t;
    Line(int e, int x, const vector<int>& a, const vector<int>& t) :e(e), x(x), a(a), t(t) {}
    int length() { return a.size(); }
};

int carAssembly(Line& l1, Line& l2, int n) {
    assert (l1.length() == n && l2.length() == n);

    int time1[n];
    int time2[n];

    time1[0] = l1.e + l1.a[0];
    time2[0] = l2.e + l2.a[0];

    for (int i = 1; i < n; ++i) {
        time1[i] = min(time1[i - 1], time2[i - 1] + l2.t[i]) + l1.a[i];
        time2[i] = min(time2[i - 1], time1[i - 1] + l1.t[i]) + l2.a[i];
    }

    return min(time1[n - 1] + l1.x, time2[n - 1] + l2.x);
}

} // namespace

TEST_CASE("car_assembly", "[car_assembly]") {
    Line l1(10, 18, {4, 5, 3, 2}, {0, 7, 4, 5});
    Line l2(12, 7, {2, 10, 1, 4}, {0, 9, 2, 8});
    int n = 4;
    REQUIRE(carAssembly(l1, l2, n) ==  35);
}