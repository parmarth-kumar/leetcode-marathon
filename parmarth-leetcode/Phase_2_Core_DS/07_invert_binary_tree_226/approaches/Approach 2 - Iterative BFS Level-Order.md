# Approach 2: Iterative BFS Level-Order
Use a FIFO queue to traverse level by level, swapping child pointers for each dequeued node.

### Complexity:
- Time: $O(N)$
- Space: $O(N)$ for queue breadth.
