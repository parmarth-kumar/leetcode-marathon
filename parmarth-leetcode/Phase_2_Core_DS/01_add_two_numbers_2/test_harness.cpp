// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <vector>
#include <cassert>
#include <iostream>
#if __has_include("../../include/leetcode_types.h")
#include "../../include/leetcode_types.h"
#else
#include "../../../include/leetcode_types.h"
#endif
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // YOUR CODE HERE
        return nullptr;
    }
};

int main() {
    Solution sol;

    // Test 1: Standard LeetCode example (342 + 465 = 807)
    {
        ListNode* l1 = buildList({2, 4, 3});
        ListNode* l2 = buildList({5, 6, 4});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{7, 0, 8}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 2: Both inputs are zero (0 + 0 = 0)
    {
        ListNode* l1 = buildList({0});
        ListNode* l2 = buildList({0});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 3: Unequal lengths + cascading carries (9999999 + 9999 = 10009998)
    {
        ListNode* l1 = buildList({9, 9, 9, 9, 9, 9, 9});
        ListNode* l2 = buildList({9, 9, 9, 9});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{8, 9, 9, 9, 0, 0, 0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 4: Lingering final carry after both lists end (99 + 1 = 100)
    {
        ListNode* l1 = buildList({9, 9});
        ListNode* l2 = buildList({1});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0, 0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 5: Single-digit carry producing two-node result (5 + 5 = 10)
    {
        ListNode* l1 = buildList({5});
        ListNode* l2 = buildList({5});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 6: First list shorter than second list (1 + 999 = 1000)
    {
        ListNode* l1 = buildList({1});
        ListNode* l2 = buildList({9, 9, 9});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0, 0, 0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 7: Adding zero to a multi-digit number (0 + 73 = 73)
    {
        ListNode* l1 = buildList({0});
        ListNode* l2 = buildList({3, 7});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{3, 7}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    cout << "All tests passed!" << endl;
    return 0;
}
