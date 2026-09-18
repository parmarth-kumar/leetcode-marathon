// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        // YOUR CODE HERE
        (void)nums;
        return {};
    }
};

int main() {
    Solution sol;

    // Test 1: Standard three-element case from problem statement
    {
        vector<int> t1 = {1, 2, 1};
        assert((sol.getConcatenation(t1) == vector<int>{1, 2, 1, 1, 2, 1}));
    }

    // Test 2: Standard four-element case from problem statement
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

    // Test 5: Constraint boundary values (1 and 1000)
    {
        vector<int> t5 = {1, 1000};
        assert((sol.getConcatenation(t5) == vector<int>{1, 1000, 1, 1000}));
    }

    // Test 6: Strictly decreasing order (verifies order preservation, not sorting)
    {
        vector<int> t6 = {9, 5, 2};
        assert((sol.getConcatenation(t6) == vector<int>{9, 5, 2, 9, 5, 2}));
    }

    // Test 7: Palindromic / symmetric values with boundary extremes
    {
        vector<int> t7 = {1000, 1, 1000};
        assert((sol.getConcatenation(t7) == vector<int>{1000, 1, 1000, 1000, 1, 1000}));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
