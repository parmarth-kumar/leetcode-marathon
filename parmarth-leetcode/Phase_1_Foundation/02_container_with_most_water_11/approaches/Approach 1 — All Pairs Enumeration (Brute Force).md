# Approach 1 — All Pairs Enumeration (Brute Force)

## 1. Core Idea

Enumerate every possible pair of vertical lines `(left, right)` with `0 <= left < right < n`, compute the water area formed by that pair using `(right - left) * min(height[left], height[right])`, and keep track of the maximum area seen.

## 2. Why It Works

Since a valid container is uniquely defined by its left wall index and right wall index (`left < right`), there are exactly $\binom{n}{2} = \frac{n(n - 1)}{2}$ valid containers. By exhaustively evaluating the area of every single pair and taking the maximum, we are guaranteed to inspect the globally optimal pair.

## 3. How To Think About It

1. "I need to pick two distinct indices `left` and `right` (`left < right`) that maximize the area."
2. "How many such pairs exist? For each `left` from `0` to `n - 2`, `right` can be anything from `left + 1` to `n - 1`."
3. "For a fixed `(left, right)`, the width is `right - left` and the water level is capped by the shorter wall `min(height[left], height[right])`."
4. "I can maintain a running variable `bestArea = 0` and update it with `max(bestArea, area)` for every pair."

## 4. Visual Trace

```text
height = [1, 2, 4, 3]
indices:  0  1  2  3

left = 0 (height = 1):
  right = 1 (height = 2): width = 1, minH = min(1,2) = 1 → area = 1, best = 1
  right = 2 (height = 4): width = 2, minH = min(1,4) = 1 → area = 2, best = 2
  right = 3 (height = 3): width = 3, minH = min(1,3) = 1 → area = 3, best = 3

left = 1 (height = 2):
  right = 2 (height = 4): width = 1, minH = min(2,4) = 2 → area = 2, best = 3
  right = 3 (height = 3): width = 2, minH = min(2,3) = 2 → area = 4, best = 4

left = 2 (height = 4):
  right = 3 (height = 3): width = 1, minH = min(4,3) = 3 → area = 3, best = 4

All 6 pairs checked → return best = 4
```

## 5. Algorithm / Pseudocode

```text
function maxArea(height):
    n = length(height)
    bestArea = 0

    for left from 0 to n - 2:
        for right from left + 1 to n - 1:
            width = right - left
            waterHeight = min(height[left], height[right])
            area = width * waterHeight
            bestArea = max(bestArea, area)

    return bestArea
```

## 6. Complexity

### Time

- **Claim**: $O(N^2)$
- **Proof**: For `left = 0`, the inner loop runs `N - 1` times. For `left = 1`, it runs `N - 2` times, down to `1` time for `left = N - 2`. Each inner-loop iteration performs $O(1)$ arithmetic and comparisons (`min`, `max`, subtraction, multiplication). Summing across all iterations:
  $$\sum_{i=0}^{N-2} (N - 1 - i) = (N - 1) + (N - 2) + \dots + 1 = \frac{N(N - 1)}{2} = \Theta(N^2)$$
- **Lower bound**: Reading every element at least once requires $\Omega(N)$ time. Here, $O(N^2)$ is asymptotically slower than the $\Omega(N)$ lower bound and exceeds LeetCode's time limit for $N = 10^5$.

### Space

- **Output space**: $O(1)$ — returns a single integer `bestArea`.
- **Auxiliary space**: $O(1)$ — uses only a constant number of scalar `int` variables (`left`, `right`, `width`, `waterHeight`, `area`, `bestArea`).
- **Interviewer note**: Even though the space complexity is already optimal ($O(1)$ auxiliary), the $O(N^2)$ time complexity is unacceptable for $N = 10^5$, motivating the two-pointer optimization.

## 7. C++ Mechanics

- `static_cast<int>(height.size())`: `std::vector::size()` returns an unsigned `size_t`. Casting to `int` avoids signed/unsigned comparison warnings (`-Wsign-compare` under `-Wall`) when comparing with `int left` and `int right`.
- `std::min` and `std::max` (`<algorithm>`): Both take `const T&` and run in $O(1)$ time.
- `const vector<int>&` vs `vector<int>&`: Passing by reference avoids an $O(N)$ copy of the input vector.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Minimum length (`n = 2`) | Outer loop runs for `left = 0`, inner loop runs for `right = 1`; evaluates the single pair correctly. |
| All heights are `0` | `waterHeight` is always `0`, so `bestArea` remains `0`. |
| Duplicate heights | `min(h, h)` returns `h`; handled without special logic. |
| Large valid inputs (`n = 10^5`, `h = 10^4`) | Maximum area is $(10^5 - 1) \times 10^4 < 10^9$, which does not overflow 32-bit signed `int`, though the loop count ($\approx 5 \times 10^9$) will TLE on online judges. |

## 9. Common Mistakes

1. **Starting inner loop at `right = 0` or `right = left`**: A container requires two distinct lines (`left < right`). Starting at `right = left` wastes time checking zero-width pairs (`right - left == 0`), and starting at `0` checks every pair twice and requires `abs(right - left)`.
2. **Computing width as `right - left + 1`**: That counts the number of lines in `[left..right]`, not the horizontal distance between `left` and `right`.
3. **Using `max(height[left], height[right])` for water height**: Water overflows the shorter wall, so the height is always `min`.

## 10. When To Prefer This Approach

- **First 60 seconds of an interview**: State this brute-force baseline verbally to establish the objective function `(right - left) * min(height[left], height[right])` and demonstrate that you understand the problem before optimizing.
- **Stress-testing / Fuzzing**: Use this simple $O(N^2)$ implementation on small random arrays ($N \le 100$) to verify the correctness of your $O(N)$ solution.
- **Never** submit this as your final solution when $N = 10^5$.
