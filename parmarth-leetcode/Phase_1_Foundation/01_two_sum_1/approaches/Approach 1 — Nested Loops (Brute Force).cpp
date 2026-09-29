// ============================================================
// Approach 1 — Nested Loops
// Type      : Brute Force
// Time      : O(N^2)
// Space     : O(1) auxiliary, O(1) output
// ============================================================

#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());

        // Outer loop picks the first index of the pair
        for (int i = 0; i < n; i++) {
            // Inner loop starts at i + 1 so we:
            //   1. Never use the same element twice (i != j)
            //   2. Never test both (i, j) and (j, i)
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }

        // Unreachable under problem constraints (solution always exists),
        // required to satisfy compiler control-flow analysis (-Wreturn-type).
        return {};
    }
};

int main() {
    Solution sol;

    // Test 1: Standard positive numbers
    {
        vector<int> nums = {2, 7, 11, 15};
        assert((sol.twoSum(nums, 9) == vector<int>{0, 1}));
    }

    // Test 2: Self-match trap (nums[0] + nums[0] == 6 must not be chosen)
    {
        vector<int> nums = {3, 2, 4};
        assert((sol.twoSum(nums, 6) == vector<int>{1, 2}));
    }

    // Test 3: Duplicate values at different indices
    {
        vector<int> nums = {3, 3};
        assert((sol.twoSum(nums, 6) == vector<int>{0, 1}));
    }

    // Test 4: Negative numbers
    {
        vector<int> nums = {-1, -2, -3, -4, -5};
        assert((sol.twoSum(nums, -8) == vector<int>{2, 4}));
    }

    // Test 5: Zeros with target 0
    {
        vector<int> nums = {0, 4, 3, 0};
        assert((sol.twoSum(nums, 0) == vector<int>{0, 3}));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
