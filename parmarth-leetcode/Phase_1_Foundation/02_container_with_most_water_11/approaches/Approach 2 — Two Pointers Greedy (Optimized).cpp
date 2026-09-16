// ============================================================
// Approach 2 — Two Pointers Greedy
// Type      : Optimized
// Time      : O(N)
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
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int bestArea = 0;

        while (left < right) {
            int width = right - left;
            int waterHeight = min(height[left], height[right]);
            bestArea = max(bestArea, width * waterHeight);

            // Greedily discard the shorter wall: keeping it while shrinking width
            // can never increase the limiting height or produce a larger area.
            if (height[left] <= height[right]) {
                left++;
            } else {
                right--;
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
