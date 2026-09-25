# Approach 2: Stack Matching (Optimized)
Push expected closing brackets or verify matching opening brackets on top of stack.

### Invariant:
At any point, the stack contains the opening brackets awaiting their counterparts in exact reverse order.

### Complexity:
- Time: $O(N)$ single pass.
- Space: $O(N)$ maximum stack depth.
