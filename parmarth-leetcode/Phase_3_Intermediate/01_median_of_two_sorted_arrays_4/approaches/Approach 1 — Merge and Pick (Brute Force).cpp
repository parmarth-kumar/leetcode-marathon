// ============================================================
// Approach 1 — Merge and Pick
// Type      : Brute Force
// Time      : O(m + n)
// Space     : O(m + n) merged array, O(1) auxiliary
// ============================================================

#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<int> merged;
        merged.reserve(m + n);

        // Standard two-pointer merge of two sorted arrays
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j])
                merged.push_back(nums1[i++]);
            else
                merged.push_back(nums2[j++]);
        }
        while (i < m) merged.push_back(nums1[i++]);
        while (j < n) merged.push_back(nums2[j++]);

        int total = m + n;
        // Even total: average of two middle elements
        // Odd total:  single middle element
        if (total % 2 == 0)
            return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
        else
            return merged[total / 2];
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

    cout << "All tests passed!" << endl;
    return 0;
}
