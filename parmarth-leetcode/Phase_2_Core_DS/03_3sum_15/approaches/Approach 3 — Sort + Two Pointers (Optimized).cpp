// ============================================================
// Approach 3 — Sort + Two Pointers
// Type      : Optimized
// Time      : O(N^2)
// Space     : O(log N) auxiliary (sorting stack), O(U) output
// ============================================================

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        vector<vector<int>> result;

        for (int i = 0; i < n - 2; ++i) {
            // In a sorted array, if the smallest element of the triplet is > 0,
            // no three elements from i onward can sum to 0.
            if (nums[i] > 0) {
                break;
            }

            // Skip duplicate values for the first element of the triplet
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    // Sum is too negative; move left pointer right to increase sum
                    ++left;
                } else if (sum > 0) {
                    // Sum is too positive; move right pointer left to decrease sum
                    --right;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    ++left;
                    --right;

                    // Skip adjacent duplicates for the second and third elements
                    while (left < right && nums[left] == nums[left - 1]) {
                        ++left;
                    }
                    while (left < right && nums[right] == nums[right + 1]) {
                        --right;
                    }
                }
            }
        }

        return result;
    }
};

vector<vector<int>> normalize(vector<vector<int>> triplets) {
    for (auto& t : triplets) {
        sort(t.begin(), t.end());
    }
    sort(triplets.begin(), triplets.end());
    return triplets;
}

int main() {
    Solution sol;

    // Test 1: Standard LeetCode example
    {
        vector<int> nums = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 2: No valid triplets
    {
        vector<int> nums = {0, 1, 1};
        vector<vector<int>> expected = {};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 3: Minimum size all zeros
    {
        vector<int> nums = {0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 4: Many zeros
    {
        vector<int> nums = {0, 0, 0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 5: Multiple pairs sharing the same first element
    {
        vector<int> nums = {-2, 0, 1, 1, 2};
        vector<vector<int>> expected = {{-2, 0, 2}, {-2, 1, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 6: Heavy inner-pointer duplicates
    {
        vector<int> nums = {-2, 0, 0, 2, 2};
        vector<vector<int>> expected = {{-2, 0, 2}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 7: Boundary extremes
    {
        vector<int> nums = {-100000, 0, 100000, -100000, 100000};
        vector<vector<int>> expected = {{-100000, 0, 100000}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    cout << "All tests passed! (Approach 3 — Sort + Two Pointers)" << endl;
    return 0;
}
