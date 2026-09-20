// ============================================================
// Approach 2 — Fix One + Hash Set
// Type      : Baseline
// Time      : O(N^2)
// Space     : O(N) auxiliary, O(U) output
// ============================================================

#include <vector>
#include <unordered_set>
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
            // Since the array is sorted, three positive numbers can never sum to 0
            if (nums[i] > 0) {
                break;
            }
            // Skip duplicate values for the first element of the triplet
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            unordered_set<int> seen;
            for (int j = i + 1; j < n; ++j) {
                int complement = -nums[i] - nums[j];
                if (seen.count(complement)) {
                    result.push_back({nums[i], complement, nums[j]});
                    // Skip consecutive identical nums[j] so the same triplet is not emitted twice
                    while (j + 1 < n && nums[j] == nums[j + 1]) {
                        ++j;
                    }
                }
                seen.insert(nums[j]);
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

    // Test 1: Standard mix with duplicates
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

    // Test 3: All zeros
    {
        vector<int> nums = {0, 0, 0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 4: Multiple pairs sharing the same first element
    {
        vector<int> nums = {-2, 0, 1, 1, 2};
        vector<vector<int>> expected = {{-2, 0, 2}, {-2, 1, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 5: Heavy inner duplicates
    {
        vector<int> nums = {-2, 0, 0, 2, 2};
        vector<vector<int>> expected = {{-2, 0, 2}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    cout << "All tests passed! (Approach 2 — Fix One + Hash Set)" << endl;
    return 0;
}
