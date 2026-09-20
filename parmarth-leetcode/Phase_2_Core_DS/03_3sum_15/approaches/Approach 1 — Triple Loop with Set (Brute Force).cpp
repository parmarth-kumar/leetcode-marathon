// ============================================================
// Approach 1 — Triple Loop with Set
// Type      : Brute Force
// Time      : O(N^3 log U)
// Space     : O(U) auxiliary, O(U) output
// ============================================================

#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        set<vector<int>> uniqueTriplets;

        // Enumerate all index triplets 0 <= i < j < k < n
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> triplet = {nums[i], nums[j], nums[k]};
                        // Canonicalize triplet order so equivalent multisets match in std::set
                        sort(triplet.begin(), triplet.end());
                        uniqueTriplets.insert(triplet);
                    }
                }
            }
        }

        return vector<vector<int>>(uniqueTriplets.begin(), uniqueTriplets.end());
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
        vector<int> nums = {0, 0, 0, 0};
        vector<vector<int>> expected = {{0, 0, 0}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    // Test 4: Multiple pairs sharing the same first element
    {
        vector<int> nums = {-2, 0, 1, 1, 2};
        vector<vector<int>> expected = {{-2, 0, 2}, {-2, 1, 1}};
        assert(normalize(sol.threeSum(nums)) == normalize(expected));
    }

    cout << "All tests passed! (Approach 1 — Triple Loop with Set)" << endl;
    return 0;
}
