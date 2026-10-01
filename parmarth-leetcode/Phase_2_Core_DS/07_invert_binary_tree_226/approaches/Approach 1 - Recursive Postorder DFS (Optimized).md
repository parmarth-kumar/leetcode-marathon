# Approach 1: Recursive Postorder DFS
Recursively invert subtrees and swap child pointers.

### Complexity:
- Time: $O(N)$ visits each node once.
- Space: $O(H)$ where $H$ is tree height (call stack).
