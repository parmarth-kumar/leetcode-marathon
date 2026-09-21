// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        int n = nums1.size();
        int m = nums2.size();

        // Instead of erasing elements, maintain the active range
        // of each array.
        int left1 = 0;
        int right1 = n - 1;

        int left2 = 0;
        int right2 = m - 1;

        int remaining = n + m;

        // Remove one smallest and one largest element
        // while more than 2 elements remain.
        while (remaining > 2) {

            // Remove smallest
            if (left1 <= right1 && left2 <= right2) {

                if (nums1[left1] <= nums2[left2]) {
                    left1++;
                } else {
                    left2++;
                }

            } else if (left1 <= right1) {
                left1++;

            } else {
                left2++;
            }

            remaining--;

            // Remove largest
            if (left1 <= right1 && left2 <= right2) {

                if (nums1[right1] >= nums2[right2]) {
                    right1--;
                } else {
                    right2--;
                }

            } else if (left1 <= right1) {
                right1--;

            } else {
                right2--;
            }

            remaining--;
        }

        // One element remains
        if (remaining == 1) {

            if (left1 <= right1) {
                return nums1[left1];
            }

            return nums2[left2];
        }

        // Two elements remain
        if (remaining == 2) {

            int first;
            int second;

            // Get the smallest remaining element
            if (left1 <= right1 && left2 <= right2) {

                if (nums1[left1] <= nums2[left2]) {
                    first = nums1[left1];
                } else {
                    first = nums2[left2];
                }

            } else if (left1 <= right1) {
                first = nums1[left1];

            } else {
                first = nums2[left2];
            }

            // Get the largest remaining element
            if (left1 <= right1 && left2 <= right2) {

                if (nums1[right1] >= nums2[right2]) {
                    second = nums1[right1];
                } else {
                    second = nums2[right2];
                }

            } else if (left1 <= right1) {
                second = nums1[right1];

            } else {
                second = nums2[right2];
            }

            return (first + second) / 2.0;
        }

        return 0.0;
    }
};

bool approxEqual(double a, double b, double eps = 1e-5) {
    return fabs(a - b) < eps;
}

int main() {

    // Test 1: LeetCode example — odd total
    {
        vector<int> n1 = {1, 3};
        vector<int> n2 = {2};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            2.0
        ));
    }

    // Test 2: LeetCode example — even total
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {3, 4};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            2.5
        ));
    }

    // Test 3: One empty array
    {
        vector<int> n1 = {};
        vector<int> n2 = {1};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            1.0
        ));
    }

    // Test 4: Both single elements
    {
        vector<int> n1 = {1};
        vector<int> n2 = {2};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            1.5
        ));
    }

    // Test 5: Disjoint ranges, even total
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {3, 4, 5, 6};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            3.5
        ));
    }

    // Test 6: Other array empty
    {
        vector<int> n1 = {2, 3, 5};
        vector<int> n2 = {};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            3.0
        ));
    }

    // Test 7: Negative values
    {
        vector<int> n1 = {-5, -3, -1};
        vector<int> n2 = {-2, 0, 4};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            -1.5
        ));
    }

    // Test 8: Duplicate values across arrays
    {
        vector<int> n1 = {1, 1, 1};
        vector<int> n2 = {1, 1, 1};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            1.0
        ));
    }

    cout << "All tests passed!" << endl;

    return 0;
}