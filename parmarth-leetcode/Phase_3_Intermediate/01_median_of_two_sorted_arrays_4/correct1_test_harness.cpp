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

        // Keep deleting the smallest and largest elements
        // until only 1 or 2 elements remain.
        while (n + m > 2) {

            // -------------------------
            // Delete smallest element
            // -------------------------

            if (n > 0 && m > 0) {

                if (nums1[0] <= nums2[0]) {
                    nums1.erase(nums1.begin());
                    n--;
                }
                else {
                    nums2.erase(nums2.begin());
                    m--;
                }

            }
            else if (n > 0) {
                nums1.erase(nums1.begin());
                n--;
            }
            else {
                nums2.erase(nums2.begin());
                m--;
            }


            // -------------------------
            // Delete largest element
            // -------------------------

            if (n > 0 && m > 0) {

                if (nums1.back() >= nums2.back()) {
                    nums1.pop_back();
                    n--;
                }
                else {
                    nums2.pop_back();
                    m--;
                }

            }
            else if (n > 0) {
                nums1.pop_back();
                n--;
            }
            else {
                nums2.pop_back();
                m--;
            }
        }


        // -------------------------
        // One element remains
        // -------------------------

        if (n + m == 1) {

            if (n == 1)
                return nums1[0];

            return nums2[0];
        }


        // -------------------------
        // Two elements remain
        // -------------------------

        if (n + m == 2) {

            // Both elements are in nums1
            if (n == 2) {
                return (nums1[0] + nums1[1]) / 2.0;
            }

            // One element in each
            if (n == 1 && m == 1) {
                return (nums1[0] + nums2[0]) / 2.0;
            }

            // Both elements are in nums2
            return (nums2[0] + nums2[1]) / 2.0;
        }

        return 0.0;
    }
};


bool approxEqual(double a, double b, double eps = 1e-5) {
    return fabs(a - b) < eps;
}


int main() {

    // Test 1
    {
        vector<int> n1 = {1, 3};
        vector<int> n2 = {2};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            2.0
        ));
    }

    // Test 2
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {3, 4};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            2.5
        ));
    }

    // Test 3
    {
        vector<int> n1 = {};
        vector<int> n2 = {1};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            1.0
        ));
    }

    // Test 4
    {
        vector<int> n1 = {1};
        vector<int> n2 = {2};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            1.5
        ));
    }

    // Test 5
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {3, 4, 5, 6};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            3.5
        ));
    }

    // Test 6
    {
        vector<int> n1 = {2, 3, 5};
        vector<int> n2 = {};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            3.0
        ));
    }

    // Test 7
    {
        vector<int> n1 = {-5, -3, -1};
        vector<int> n2 = {-2, 0, 4};

        assert(approxEqual(
            Solution().findMedianSortedArrays(n1, n2),
            -1.5
        ));
    }

    // Test 8
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