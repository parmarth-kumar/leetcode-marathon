// ============================================================
// Approach 2 — One-Pass Hash Map
// Type      : Optimized
// Time      : O(N) average
// Space     : O(N) auxiliary, O(1) output
// ============================================================

#include <vector>
#include <unordered_map>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Maps each seen number -> its index in `nums`
        unordered_map<int, int> seen;
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];

            // Check BEFORE inserting nums[i] so an element never matches itself
            auto it = seen.find(complement);
            if (it != seen.end()) {
                return {it->second, i};
            }

            seen[nums[i]] = i;
        }

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

    // Test 2: Self-match trap (nums[0] = 3 must not match with itself for target = 6)
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
