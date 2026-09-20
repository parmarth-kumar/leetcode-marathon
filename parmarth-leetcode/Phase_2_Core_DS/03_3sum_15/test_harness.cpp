// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // YOUR CODE HERE
        (void)nums;
        return {};
    }
};

// Test helper: canonicalizes triplet order and element order so any valid order passes
vector<vector<int>> normalize(vector<vector<int>> triplets) {
    for (auto& t : triplets) {
        sort(t.begin(), t.end());
    }
    sort(triplets.begin(), triplets.end());
    return triplets;
}

int main() {
    Solution sol;

    // Test 1: Standard LeetCode example with duplicate values and multiple valid triplets
    {
        vector<int> nums = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 2: LeetCode example with no valid triplet
    {
        vector<int> nums = {0, 1, 1};
        vector<vector<int>> expected = {};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 3: Minimum length array of all zeros
    {
        vector<int> nums = {0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 4: Many zeros — must emit [0, 0, 0] only once (deduplication stress test)
    {
        vector<int> nums = {0, 0, 0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 5: Single fixed first element participating in multiple distinct pairs
    {
        vector<int> nums = {-2, 0, 1, 1, 2};
        vector<vector<int>> expected = {{-2, 0, 2}, {-2, 1, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 6: Heavy inner-pointer duplicates on both left and right
    {
        vector<int> nums = {-2, 0, 0, 2, 2};
        vector<vector<int>> expected = {{-2, 0, 2}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 7: All positive numbers — early termination edge case
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        vector<vector<int>> expected = {};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 8: Boundary values (-10^5 and 10^5)
    {
        vector<int> nums = {-100000, 0, 100000, -100000, 100000};
        vector<vector<int>> expected = {{-100000, 0, 100000}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
