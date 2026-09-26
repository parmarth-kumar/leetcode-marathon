# Approach 2: Recursive Call Stack
Traverse to the tail, then reverse pointer direction upon unwinding.

### Recurrence:
`head->next->next = head; head->next = nullptr;`
### Complexity:
- Time: $O(N)$
- Space: $O(N)$ call stack frames.
