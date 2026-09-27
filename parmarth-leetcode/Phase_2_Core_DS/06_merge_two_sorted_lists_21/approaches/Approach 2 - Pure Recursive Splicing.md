# Approach 2: Recursive Splicing
Return whichever head is smaller, setting its `next` to the recursive result of the remaining lists.

### Complexity:
- Time: $O(N + M)$
- Space: $O(N + M)$ stack frames.
