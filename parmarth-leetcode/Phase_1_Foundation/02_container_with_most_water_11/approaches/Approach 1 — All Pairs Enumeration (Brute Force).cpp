// ============================================================
// Approach 1 — All Pairs Enumeration
// Type      : Brute Force
// Time      : O(N^2)
// Space     : O(1) auxiliary, O(1) output
// ============================================================

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = static_cast<int>(height.size());
        int bestArea = 0;

        // Check every possible pair of left and right walls
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right < n; right++) {
                int width = right - left;
                // Water overflows the shorter wall, so the shorter wall is the bottleneck
                int waterHeight = min(height[left], height[right]);
                bestArea = max(bestArea, width * waterHeight);
            }
        }

        return bestArea;
    }
};

int main() {
    Solution sol;

    vector<int> h1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(sol.maxArea(h1) == 49);

    vector<int> h2 = {1, 1};
    assert(sol.maxArea(h2) == 1);

    vector<int> h3 = {0, 0, 0};
    assert(sol.maxArea(h3) == 0);

    vector<int> h4 = {1, 2, 100, 100, 2, 1};
    assert(sol.maxArea(h4) == 100);

    vector<int> h5 = {5, 1, 1, 1, 1, 1, 5};
    assert(sol.maxArea(h5) == 30);

    cout << "All tests passed!" << endl;
    return 0;
}
