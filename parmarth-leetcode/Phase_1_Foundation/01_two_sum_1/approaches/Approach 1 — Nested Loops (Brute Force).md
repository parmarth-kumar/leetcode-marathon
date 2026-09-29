# Approach 1 — Nested Loops (Brute Force)

## 1. Core Idea

Use two nested loops to exhaustively inspect every unique pair of indices `(i, j)` with `0 <= i < j < n`. As soon as we find a pair where `nums[i] + nums[j] == target`, return `{i, j}`.

## 2. Why It Works

The problem asks for two distinct indices `i` and `j` whose values sum to `target`. Since addition is commutative (`nums[i] + nums[j] == nums[j] + nums[i]`), any valid pair of distinct indices has one smaller index `i` and one larger index `j` (`i < j`). By iterating `i` from `0` to `n - 1` and `j` from `i + 1` to `n - 1`, we systematically visit every possible 2-element subset of indices without ever pairing an index with itself (`i != j`) or checking the same pair twice.

## 3. How To Think About It

1. *"I need to find two positions `i` and `j` (`i != j`) such that `nums[i] + nums[j] == target`."*
2. *"What if I fix the first position `i` using an outer loop?"*
3. *"Then I just need to check all remaining positions after `i` (`j = i + 1, i + 2, ..., n - 1`) to see if any `nums[j]` completes the sum."*
4. *"Why start `j` at `i + 1` instead of `0`? Because indices before `i` were already tested when the outer loop was at those earlier positions, and `j = i` is forbidden since we cannot use the same element twice."*

## 4. Visual Trace

**Trace 1**: `nums = [3, 2, 4], target = 6`
```
Index:    0   1   2
Value:  [ 3,  2,  4 ]

Outer loop i = 0 (nums[0] = 3):
  Inner loop j = 1 (nums[1] = 2):  3 + 2 = 5 != 6  ✗
  Inner loop j = 2 (nums[2] = 4):  3 + 4 = 7 != 6  ✗

Outer loop i = 1 (nums[1] = 2):
  Inner loop j = 2 (nums[2] = 4):  2 + 4 = 6 == 6  ✓  → return {1, 2}
```

**Trace 2**: `nums = [2, 7, 11, 15], target = 9`
```
Outer loop i = 0 (nums[0] = 2):
  Inner loop j = 1 (nums[1] = 7):  2 + 7 = 9 == 9  ✓  → return {0, 1}
(Terminates immediately on the very first comparison!)
```

## 5. Algorithm / Pseudocode

```text
function twoSum(nums, target):
    n = length(nums)
    for i from 0 to n - 1:
        for j from i + 1 to n - 1:
            if nums[i] + nums[j] == target:
                return [i, j]
    return []
```

## 6. Complexity

### Time

- **Claim**: $O(N^2)$ worst-case and average-case; $O(1)$ best-case (when `(0, 1)` is the answer).
- **Proof**:
  - When `i = 0`, the inner loop runs `N - 1` times (`j = 1 .. N - 1`).
  - When `i = 1`, the inner loop runs `N - 2` times (`j = 2 .. N - 1`).
  - ...
  - When `i = N - 2`, the inner loop runs `1` time (`j = N - 1`).
  - Total pair comparisons in the worst case:
    $$(N - 1) + (N - 2) + \dots + 1 + 0 = \frac{N(N - 1)}{2} = \frac{1}{2}N^2 - \frac{1}{2}N = O(N^2)$$
- **Lower bound**: Reading the input requires $\Omega(N)$ time in the worst case, so $O(N^2)$ has a quadratic gap above the $\Omega(N)$ lower bound (which Approach 2 closes).

### Space

- **Output space**: $O(1)$ — the returned `vector<int>` always contains exactly 2 integers (`{i, j}`).
- **Auxiliary space**: $O(1)$ — only loop counter variables `n`, `i`, and `j` are allocated on the stack.
- **Interviewer note**: If an interviewer asks *"What is the advantage of Brute Force over the Hash Map approach?"*, the answer is **$O(1)$ auxiliary memory** and **zero hash-table allocation overhead** for tiny arrays.

## 7. C++ Mechanics

- **Initializer-list return (`return {i, j};`)**: C++11 and later automatically constructs the return type `vector<int>` of length 2 from `{i, j}`, avoiding verbose `vector<int> ans; ans.push_back(i); ans.push_back(j);`.
- **Signed size comparison (`int n = nums.size();`)**: `nums.size()` returns an unsigned `size_t`. Storing it in `int n` avoids signed/unsigned comparison warnings under `-Wall`.
- **Fallback `return {};`**: Even though the problem guarantees a solution exists, the C++ compiler's control-flow analyzer cannot prove that `nums[i] + nums[j] == target` will always trigger. Without `return {};` at the end of the function, `g++ -Wall -Werror` fails with `-Wreturn-type`.

## 8. Edge Cases

| Case | Input | How Nested Loops Handle It |
|:---|:---|:---|
| Minimum length (`N = 2`) | `nums = [3, 3], target = 6` | `i = 0, j = 1` checks `nums[0] + nums[1] = 6` and returns `{0, 1}`. |
| Self-sum trap (`2 * nums[i] == target`) | `nums = [3, 2, 4], target = 6` | Because `j` starts at `i + 1`, `i = 0` (`3`) is never paired with `j = 0` (`3`). |
| Negative numbers | `nums = [-1, -2, -3, -4, -5], target = -8` | Addition works identically for negative integers; `i = 2, j = 4` finds `-3 + (-5) = -8`. |
| Zeros | `nums = [0, 4, 3, 0], target = 0` | `i = 0, j = 3` finds `0 + 0 = 0` and returns `{0, 3}`. |

## 9. Common Mistakes

1. **Starting the inner loop at `j = 0` without checking `i != j`**: This allows `i == j`, matching an element with itself when `2 * nums[i] == target`.
2. **Starting the inner loop at `j = 0` with `if (i != j)`**: While correct, it does **twice as much work** ($N(N-1)$ comparisons instead of $N(N-1)/2$) by checking both `(i, j)` and `(j, i)`. Always start at `j = i + 1`.
3. **Returning `{nums[i], nums[j]}` instead of `{i, j}`**: Returning the element values instead of their 0-based positions.

## 10. When To Prefer This Approach

- **First 60 seconds of an interview**: State this approach verbally first (`"The brute-force solution checks all N(N-1)/2 pairs in O(N^2) time and O(1) auxiliary space..."`) to establish a baseline before presenting the $O(N)$ hash map optimization.
- **Strictly memory-constrained embedded environments**: When dynamic heap allocation (`unordered_map`) is prohibited and $N$ is small.
