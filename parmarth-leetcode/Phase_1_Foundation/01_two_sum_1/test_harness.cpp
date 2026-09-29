// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // YOUR CODE HERE
        return {};
    }
};

// Helper to normalize pair order so {0, 1} and {1, 0} both pass
bool sameIndices(vector<int> actual, vector<int> expected) {
    if (actual.size() != 2) return false;
    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    return actual == expected;
}

int main() {
    Solution sol;

    // Test 1: Standard case from problem statement
    {
        vector<int> nums = {2, 7, 11, 15};
        assert(sameIndices(sol.twoSum(nums, 9), {0, 1}));
    }

    // Test 2: Unsorted array where first element is half of target (self-match trap)
    {
        vector<int> nums = {3, 2, 4};
        assert(sameIndices(sol.twoSum(nums, 6), {1, 2}));
    }

    // Test 3: Duplicate values at different indices (minimum length N = 2)
    {
        vector<int> nums = {3, 3};
        assert(sameIndices(sol.twoSum(nums, 6), {0, 1}));
    }

    // Test 4: Negative numbers
    {
        vector<int> nums = {-1, -2, -3, -4, -5};
        assert(sameIndices(sol.twoSum(nums, -8), {2, 4}));
    }

    // Test 5: Zeros in the array with target = 0
    {
        vector<int> nums = {0, 4, 3, 0};
        assert(sameIndices(sol.twoSum(nums, 0), {0, 3}));
    }

    // Test 6: Mix of positive and negative numbers
    {
        vector<int> nums = {-3, 4, 3, 90};
        assert(sameIndices(sol.twoSum(nums, 0), {0, 2}));
    }

    // Test 7: Large boundary values near +/- 10^9
    {
        vector<int> nums = {1000000000, -500000000, 1000000000};
        assert(sameIndices(sol.twoSum(nums, 2000000000), {0, 2}));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
