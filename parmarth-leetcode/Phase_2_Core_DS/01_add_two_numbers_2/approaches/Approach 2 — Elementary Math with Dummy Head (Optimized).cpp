// ============================================================
// Approach 2 — Elementary Math with Dummy Head
// Type      : Optimized
// Time      : O(max(M, N))
// Space     : O(1) auxiliary, O(max(M, N)) output
// ============================================================

#include <vector>
#include <cassert>
#include <iostream>
#if __has_include("../../../include/leetcode_types.h")
#include "../../../include/leetcode_types.h"
#else
#include "../../../../include/leetcode_types.h"
#endif
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Stack-allocated sentinel node avoids special-casing the head node
        // and requires no manual delete before returning.
        ListNode dummy(0);
        ListNode* tail = &dummy;
        int carry = 0;

        // Continue while either list still has digits OR a final carry remains.
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;

            int sum = val1 + val2 + carry;
            carry = sum / 10;

            tail->next = new ListNode(sum % 10);
            tail = tail->next;

            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        return dummy.next;
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

    // Test 2: Both zeros (0 + 0 = 0)
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

    // Test 4: Lingering final carry (99 + 1 = 100)
    {
        ListNode* l1 = buildList({9, 9});
        ListNode* l2 = buildList({1});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0, 0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    // Test 5: Single-digit carry (5 + 5 = 10)
    {
        ListNode* l1 = buildList({5});
        ListNode* l2 = buildList({5});
        ListNode* ans = sol.addTwoNumbers(l1, l2);
        assert((listToVec(ans) == vector<int>{0, 1}));
        freeList(l1); freeList(l2); freeList(ans);
    }

    cout << "All tests passed!" << endl;
    return 0;
}
