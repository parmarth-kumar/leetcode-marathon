// ============================================================
// leetcode_types.h — Shared LeetCode type definitions
//
// Include this header in any .cpp that needs ListNode, TreeNode,
// or other standard LeetCode types. This avoids redefining them
// in every problem file.
//
// Usage (from a problem folder):
//   #include "../../include/leetcode_types.h"
//
// For Phase 1 (arrays/strings), this header is not needed.
// It becomes essential starting Phase 2 (Linked Lists).
// ============================================================

#ifndef LEETCODE_TYPES_H
#define LEETCODE_TYPES_H

#include <vector>
#include <string>
#include <iostream>

// ---- Linked List ----

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Build a linked list from a vector (for testing)
inline ListNode* buildList(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// Convert a linked list to a vector (for assert comparisons)
inline std::vector<int> listToVec(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Print a linked list (for debugging)
inline void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Free a linked list (prevent memory leaks in test harnesses)
inline void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ---- Binary Tree ----

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// ---- N-ary Tree (used in some problems) ----

// struct Node {
//     int val;
//     std::vector<Node*> children;
//     Node() : val(0) {}
//     Node(int _val) : val(_val) {}
//     Node(int _val, std::vector<Node*> _children) : val(_val), children(_children) {}
// };

#endif // LEETCODE_TYPES_H
