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
        // YOUR CODE HERE
        // Trying Approach 1

        
    }
};

bool approxEqual(double a, double b, double eps = 1e-5) {
    return fabs(a - b) < eps;
}

int main() {
    Solution sol;

    // Test 1: LeetCode example — odd total
    {
        vector<int> n1 = {1, 3}, n2 = {2};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 2.0));
    }

    // Test 2: LeetCode example — even total
    {
        vector<int> n1 = {1, 2}, n2 = {3, 4};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 2.5));
    }

    // Test 3: One empty array
    {
        vector<int> n1 = {}, n2 = {1};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 1.0));
    }

    // Test 4: Both single elements
    {
        vector<int> n1 = {1}, n2 = {2};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 1.5));
    }

    // Test 5: Disjoint ranges, even total
    {
        vector<int> n1 = {1, 2}, n2 = {3, 4, 5, 6};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 3.5));
    }

    // Test 6: Other array empty
    {
        vector<int> n1 = {2, 3, 5}, n2 = {};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 3.0));
    }

    // Test 7: Negative values
    {
        vector<int> n1 = {-5, -3, -1}, n2 = {-2, 0, 4};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), -1.5));
    }

    // Test 8: Duplicate values across arrays
    {
        vector<int> n1 = {1, 1, 1}, n2 = {1, 1, 1};
        assert(approxEqual(sol.findMedianSortedArrays(n1, n2), 1.0));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
