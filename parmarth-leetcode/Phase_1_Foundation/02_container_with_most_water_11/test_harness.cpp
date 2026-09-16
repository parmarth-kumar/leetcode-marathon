// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // YOUR CODE HERE
        return 0;
    }
};

int main() {
    Solution sol;

    // Test 1: Standard LeetCode example
    {
        vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        assert(sol.maxArea(h) == 49);
    }

    // Test 2: Minimum length (n = 2)
    {
        vector<int> h = {1, 1};
        assert(sol.maxArea(h) == 1);
    }

    // Test 3: All zero-height lines
    {
        vector<int> h = {0, 0, 0};
        assert(sol.maxArea(h) == 0);
    }

    // Test 4: Narrow & tall container beats wide & short
    {
        vector<int> h = {1, 2, 100, 100, 2, 1};
        assert(sol.maxArea(h) == 100);
    }

    // Test 5: Wide & short container beats narrow interior lines
    {
        vector<int> h = {5, 1, 1, 1, 1, 1, 5};
        assert(sol.maxArea(h) == 30);
    }

    // Test 6: Strictly increasing heights
    {
        vector<int> h = {1, 2, 3, 4, 5};
        assert(sol.maxArea(h) == 6);
    }

    // Test 7: Strictly decreasing heights
    {
        vector<int> h = {5, 4, 3, 2, 1};
        assert(sol.maxArea(h) == 6);
    }

    cout << "All tests passed!" << endl;
    return 0;
}
