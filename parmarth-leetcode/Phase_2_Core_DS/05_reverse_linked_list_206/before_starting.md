# 206. Reverse Linked List

## Intuition & Pointer Invariant
Given the `head` of a singly linked list, reverse the list, and return the reversed list.

### Mental Model:
Maintain three pointers:
- `prev`: points to the head of the already reversed segment (initially `nullptr`).
- `curr`: points to the current node being processed.
- `next`: temporary store for `curr->next` before breaking the link.
