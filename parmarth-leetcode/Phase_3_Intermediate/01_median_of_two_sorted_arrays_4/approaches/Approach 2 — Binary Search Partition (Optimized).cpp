// ============================================================
// Approach 2 — Binary Search Partition
// Type      : Optimized
// Time      : O(log(min(m, n)))
// Space     : O(1) auxiliary
// ============================================================

#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Always binary search on the smaller array
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        int m = nums1.size(), n = nums2.size();
        int low = 0, high = m;
        int half = (m + n + 1) / 2;  // Left half gets the extra element when odd

        while (low <= high) {
            int i = (low + high) / 2;  // Partition index in nums1
            int j = half - i;           // Corresponding partition index in nums2

            // Sentinel values for boundary partitions
            int maxL1  = (i == 0) ? INT_MIN : nums1[i - 1];
            int minR1 = (i == m) ? INT_MAX : nums1[i];
            int maxL2  = (j == 0) ? INT_MIN : nums2[j - 1];
            int minR2 = (j == n) ? INT_MAX : nums2[j];

            if (maxL1 <= minR2 && maxL2 <= minR1) {
                // Found the correct partition
                if ((m + n) % 2 == 1)
                    return max(maxL1, maxL2);
                else
                    return (max(maxL1, maxL2) + min(minR1, minR2)) / 2.0;
            }
            else if (maxL1 > minR2) {
                // Took too many from nums1 — move partition left
                high = i - 1;
            }
            else {
                // Took too few from nums1 — move partition right
                low = i + 1;
            }
        }

        // Should never reach here with valid input
        return -1.0;
    }
};

bool approxEqual(double a, double b, double eps = 1e-5) {
    return fabs(a - b) < eps;
}

int main() {
    Solution sol;

    vector<int> n1 = {1, 3}, n2 = {2};
    assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 2.0));

    vector<int> n3 = {1, 2}, n4 = {3, 4};
    assert(approxEqual(sol.findMedianSortedArrays(n3, n4), 2.5));

    vector<int> n5 = {}, n6 = {1};
    assert(approxEqual(sol.findMedianSortedArrays(n5, n6), 1.0));

    vector<int> n7 = {1}, n8 = {2};
    assert(approxEqual(sol.findMedianSortedArrays(n7, n8), 1.5));

    vector<int> n9 = {-5, -3, -1}, n10 = {-2, 0, 4};
    assert(approxEqual(sol.findMedianSortedArrays(n9, n10), -1.5));

    cout << "All tests passed!" << endl;
    return 0;
}
