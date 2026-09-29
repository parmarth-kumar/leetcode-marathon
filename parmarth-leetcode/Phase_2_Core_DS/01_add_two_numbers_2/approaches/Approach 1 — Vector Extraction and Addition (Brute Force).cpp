// ============================================================
// Approach 1 — Vector Extraction and Addition
// Type      : Brute Force
// Time      : O(max(M, N))
// Space     : O(M + N) auxiliary, O(max(M, N)) output
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
        // Pass 1: Extract all digits from both linked lists into vectors.
        // We cannot convert to long long because 100-digit lists overflow 64-bit ints.
        vector<int> digits1;
        vector<int> digits2;

        for (ListNode* curr = l1; curr != nullptr; curr = curr->next) {
            digits1.push_back(curr->val);
        }
        for (ListNode* curr = l2; curr != nullptr; curr = curr->next) {
            digits2.push_back(curr->val);
        }

        // Pass 2: Simulate grade-school column addition on the extracted vectors.
        vector<int> resultDigits;
        int n1 = static_cast<int>(digits1.size());
        int n2 = static_cast<int>(digits2.size());
        int i = 0, j = 0, carry = 0;

        while (i < n1 || j < n2 || carry > 0) {
            int val1 = (i < n1) ? digits1[i++] : 0;
            int val2 = (j < n2) ? digits2[j++] : 0;

            int sum = val1 + val2 + carry;
            resultDigits.push_back(sum % 10);
            carry = sum / 10;
        }

        // Pass 3: Build the output linked list from resultDigits using a dummy head.
        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (int d : resultDigits) {
            tail->next = new ListNode(d);
            tail = tail->next;
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

    cout << "All tests passed!" << endl;
    return 0;
}
