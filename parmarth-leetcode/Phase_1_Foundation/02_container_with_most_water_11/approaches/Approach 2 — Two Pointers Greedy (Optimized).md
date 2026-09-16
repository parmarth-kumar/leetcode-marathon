# Approach 2 — Two Pointers Greedy (Optimized)

## 1. Core Idea

Place two pointers at opposite ends of the array (`left = 0`, `right = n - 1`) so that the container starts with the maximum possible width. At each step, compute the current area, update the maximum, and **greedily move the pointer pointing to the shorter wall inward** until the pointers meet.

## 2. Why It Works

Suppose at the current step we have indices `(left, right)` with `left < right`, and without loss of generality suppose `height[left] <= height[right]`.
- The current container area is `(right - left) * height[left]`.
- Consider **any** other container that keeps `left` as its left wall and pairs it with some interior right wall `right'` where `left < right' < right`:
  1. Its width is `right' - left < right - left` (strictly narrower).
  2. Its limiting height is `min(height[left], height[right']) <= height[left]` (cannot exceed the shorter wall `height[left]`).
  3. Therefore:
     $$\text{area}(left, right') = (right' - left) \times \min(height[left], height[right']) < (right - left) \times height[left] = \text{area}(left, right)$$
- Since `(left, right)` dominates every pair `(left, right')` for all `right' < right`, index `left` can **never** be part of a strictly better container with any remaining candidate. Moving `left++` safely eliminates `right - left - 1` pairs in $O(1)$ time without missing the global optimum.
- By symmetry, when `height[right] < height[left]`, moving `right--` safely eliminates all remaining pairs involving `right`.

## 3. How To Think About It

1. "Area is `width * min(height[left], height[right])`."
2. "If I start at `left = 0` and `right = n - 1`, `width` is as large as it can ever be."
3. "Every time I move a pointer inward, `width` shrinks by 1."
4. "To compensate for a shrinking width, I **must** try to increase `min(height[left], height[right])`."
5. "The only way to possibly increase the minimum of two numbers is to replace the smaller number. Replacing the larger number can never increase the minimum."
6. "So I always move whichever pointer has the smaller height inward, and stop when `left == right`."

## 4. Visual Trace

```text
height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
indices:  0  1  2  3  4  5  6  7  8

Iteration 1: L = 0 (h=1), R = 8 (h=7)
  [1, 8, 6, 2, 5, 4, 8, 3, 7]
   ^                       ^
   L                       R
  area = (8 - 0) * min(1, 7) = 8 * 1 = 8     | best = 8
  h[L]=1 <= h[R]=7 → move L++ (eliminates (0,7), (0,6), ..., (0,1))

Iteration 2: L = 1 (h=8), R = 8 (h=7)
  [1, 8, 6, 2, 5, 4, 8, 3, 7]
      ^                    ^
      L                    R
  area = (8 - 1) * min(8, 7) = 7 * 7 = 49    | best = 49
  h[L]=8 > h[R]=7  → move R-- (eliminates (2,8), (3,8), ..., (7,8))

Iteration 3: L = 1 (h=8), R = 7 (h=3)
  [1, 8, 6, 2, 5, 4, 8, 3, 7]
      ^                 ^
      L                 R
  area = (7 - 1) * min(8, 3) = 6 * 3 = 18    | best = 49
  h[L]=8 > h[R]=3  → move R--

Iteration 4: L = 1 (h=8), R = 6 (h=8)
  [1, 8, 6, 2, 5, 4, 8, 3, 7]
      ^              ^
      L              R
  area = (6 - 1) * min(8, 8) = 5 * 8 = 40    | best = 49
  h[L]=8 <= h[R]=8 → move L++

Iteration 5: L = 2 (h=6), R = 6 (h=8) → area = 4 * 6 = 24 | best = 49 → move L++
Iteration 6: L = 3 (h=2), R = 6 (h=8) → area = 3 * 2 = 6  | best = 49 → move L++
Iteration 7: L = 4 (h=5), R = 6 (h=8) → area = 2 * 5 = 10 | best = 49 → move L++
Iteration 8: L = 5 (h=4), R = 6 (h=8) → area = 1 * 4 = 4  | best = 49 → move L++
Stop: L = 6, R = 6 (L < R is false)

Return best = 49 ✓
```

## 5. Algorithm / Pseudocode

```text
function maxArea(height):
    left = 0
    right = length(height) - 1
    bestArea = 0

    while left < right:
        width = right - left
        waterHeight = min(height[left], height[right])
        bestArea = max(bestArea, width * waterHeight)

        if height[left] <= height[right]:
            left = left + 1
        else:
            right = right - 1

    return bestArea
```

## 6. Complexity

### Time

- **Claim**: $O(N)$
- **Proof**: Initially `left = 0` and `right = N - 1`, so the distance `right - left` is `N - 1`. In every iteration of the `while (left < right)` loop, either `left` increments by `1` or `right` decrements by `1`. Thus, `right - left` decreases by exactly `1` per iteration. The loop terminates when `right - left == 0`, meaning it executes **exactly `N - 1` iterations**. Each iteration performs $O(1)$ work (two array lookups, a subtraction, a multiplication, `min`, `max`, and one pointer increment/decrement). Total time: $\Theta(N)$.
- **Lower bound**: Any correct algorithm must inspect every element in `height` at least once in the worst case (otherwise an uninspected element could be $10^4$ while all others are $0$), giving a theoretical lower bound of $\Omega(N)$. Our $O(N)$ algorithm is therefore **asymptotically optimal**.

### Space

- **Output space**: $O(1)$ — returns a single `int`.
- **Auxiliary space**: $O(1)$ — uses only three integer state variables (`left`, `right`, `bestArea`) and temporary loop scalars.
- **Interviewer note**: Both time ($O(N)$) and auxiliary space ($O(1)$) are at their theoretical lower bounds.

## 7. C++ Mechanics

- **Loop condition `while (left < right)`**: Ensures we never evaluate a zero-width container (`left == right`) and guarantees termination after `n - 1` steps.
- **Branch prediction & tie-breaking (`<=` vs `<`)**: Whether ties (`height[left] == height[right]`) increment `left` (`<=`) or decrement `right` (`<`) does not affect correctness or iteration count.
- **No dynamic allocation**: Because we only move integer indices over the existing `vector<int>& height`, zero heap allocations occur.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Minimum length (`n = 2`) | `left = 0, right = 1`; loop executes once, computes `1 * min(h[0], h[1])`, and terminates. |
| All heights equal (e.g., `[5, 5, 5, 5]`) | First iteration `(0, 3)` records max area `3 * 5 = 15`; subsequent steps have narrower widths and cannot beat `15`. |
| All heights zero (`[0, 0, 0]`) | `bestArea` stays `0`; `left` advances each step until `left == right`. |
| Tallest walls adjacent in the middle (`[1, 100, 100, 1]`) | Outer low walls are discarded first (`0` then `3`), bringing `left = 1` and `right = 2` together to find area `100`. |

## 9. Common Mistakes

1. **Moving the taller pointer instead of the shorter pointer**: Doing `if (height[left] >= height[right]) left++;` shrinks the width while keeping the shorter bottleneck, missing optimal interior pairs like `[1, 100, 100, 1]`.
2. **Using `while (left <= right)`**: When `left == right`, `width` is `0`, adding an unnecessary iteration.
3. **Sorting the array before running two pointers**: Sorting scrambles the original x-coordinates, making `right - left` meaningless.

## 10. When To Prefer This Approach

- **Always in interviews and production**: It is shorter, cleaner, and strictly faster ($O(N)$ vs. $O(N^2)$) than brute force while using the exact same $O(1)$ memory.
- Whenever a two-endpoint optimization problem allows you to prove that one endpoint has reached its best possible partner and can be safely discarded.
