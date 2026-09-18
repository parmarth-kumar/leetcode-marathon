// ============================================================
// Approach 2 — Single-Pass Direct Indexing
// Type      : Optimized
// Time      : O(N)
// Space     : O(1) auxiliary, O(N) output
// ============================================================

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        // Pre-allocate exact output size (2 * n) to avoid dynamic reallocations
        vector<int> ans(2 * n);

        // Single pass: place each element into both the first and second half
        for (int i = 0; i < n; ++i) {
            ans[i] = nums[i];
            ans[i + n] = nums[i];
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Test 1: Standard three-element case
    {
        vector<int> t1 = {1, 2, 1};
        assert((sol.getConcatenation(t1) == vector<int>{1, 2, 1, 1, 2, 1}));
    }

    // Test 2: Standard four-element case
    {
        vector<int> t2 = {1, 3, 2, 1};
        assert((sol.getConcatenation(t2) == vector<int>{1, 3, 2, 1, 1, 3, 2, 1}));
    }

    // Test 3: Single element (minimum constraint length n = 1)
    {
        vector<int> t3 = {7};
        assert((sol.getConcatenation(t3) == vector<int>{7, 7}));
    }

    // Test 4: All identical elements
    {
        vector<int> t4 = {4, 4, 4};
        assert((sol.getConcatenation(t4) == vector<int>{4, 4, 4, 4, 4, 4}));
    }

    // Test 5: Boundary values
    {
        vector<int> t5 = {1, 1000};
        assert((sol.getConcatenation(t5) == vector<int>{1, 1000, 1, 1000}));
    }

    // Test 6: Decreasing sequence
    {
        vector<int> t6 = {9, 5, 2};
        assert((sol.getConcatenation(t6) == vector<int>{9, 5, 2, 9, 5, 2}));
    }

    cout << "All Approach 2 (Single-Pass Direct Indexing) tests passed!" << endl;
    return 0;
}
