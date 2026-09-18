# Approach 2 — Single-Pass Direct Indexing (Optimized)

## 1. Core Idea

Pre-allocate the result vector `ans` of exact length `2 * n` upfront, then iterate once from `i = 0` to `n - 1` and assign both `ans[i] = nums[i]` and `ans[i + n] = nums[i]` in the same loop iteration.

## 2. Why It Works

Because the output consists of two consecutive copies of `nums` (each of length `n`), the first copy occupies indices `0` through `n - 1` and the second copy occupies indices `n` through `2n - 1`. Every source index `i` (`0 <= i < n`) maps deterministically to two non-overlapping target indices:
- First copy position: `i`
- Second copy position: `i + n`

Since `0 <= i < n`, the two index ranges `[0, n - 1]` and `[n, 2n - 1]` are completely disjoint and cover all `2n` indices of `ans` without gaps or collisions.

## 3. How To Think About It

1. *"What is the overhead in Approach 1?"* → It traverses `nums` twice and relies on `push_back`, which checks capacity on every append and may reallocate the heap buffer multiple times.
2. *"Do we know the exact output size before looping?"* → Yes, `2 * n`. So we can allocate `vector<int> ans(2 * n)` once at the very start.
3. *"If I am looking at `nums[i]`, where does it go in `ans`?"* → Into slot `i` (first half) and slot `i + n` (second half).
4. *"Can I write both slots in a single pass?"* → Yes: `ans[i] = ans[i + n] = nums[i];`.

## 4. Visual Trace

```text
Input: nums = [1, 3, 2, 1]   (n = 4)

Step 0: Pre-allocate ans of size 2 * 4 = 8
ans = [ 0, 0, 0, 0, 0, 0, 0, 0 ]
idx:    0  1  2  3  4  5  6  7

Iteration i = 0 (nums[0] = 1):
  Write ans[0] = 1 and ans[0 + 4 = 4] = 1
  ans = [ 1, 0, 0, 0, 1, 0, 0, 0 ]
          ^           ^

Iteration i = 1 (nums[1] = 3):
  Write ans[1] = 3 and ans[1 + 4 = 5] = 3
  ans = [ 1, 3, 0, 0, 1, 3, 0, 0 ]
             ^           ^

Iteration i = 2 (nums[2] = 2):
  Write ans[2] = 2 and ans[2 + 4 = 6] = 2
  ans = [ 1, 3, 2, 0, 1, 3, 2, 0 ]
                ^           ^

Iteration i = 3 (nums[3] = 1):
  Write ans[3] = 1 and ans[3 + 4 = 7] = 1
  ans = [ 1, 3, 2, 1, 1, 3, 2, 1 ]
                   ^           ^

Return ans = [1, 3, 2, 1, 1, 3, 2, 1] ✓
```

## 5. Algorithm / Pseudocode

```text
function getConcatenation(nums):
    n = length(nums)
    ans = vector of size (2 * n)

    for i from 0 to n - 1:
        ans[i] = nums[i]
        ans[i + n] = nums[i]

    return ans
```

**Loop Invariant**:
- Before iteration `i`, for all `0 <= k < i`, `ans[k] == nums[k]` and `ans[k + n] == nums[k]`.
- At termination (`i = n`), all `2n` slots of `ans` hold their final concatenated values.

## 6. Complexity

### Time

- **Claim**: `O(N)`
- **Proof**: Constructing `vector<int> ans(2 * n)` performs a single heap allocation of `2N` integers (`O(N)` initialization). The `for` loop runs `N` times; each iteration performs one read (`nums[i]`), one addition (`i + n`), and two direct array writes (`ans[i]` and `ans[i + n]`), each costing `O(1)`. Total time is `O(N)` with zero dynamic reallocations.
- **Lower bound**: Returning `2N` elements requires `Ω(N)` writes, so `O(N)` is optimal.

### Space

- **Output space**: `O(N)` — `ans` holds `2N` elements required by the function return type.
- **Auxiliary space**: `O(1)` — only two scalar `int` variables (`n` and `i`) are used beyond the output vector.
- **Interviewer note**: When an interviewer asks for "`O(1)` extra space," they mean `O(1)` auxiliary space excluding the returned result vector. This solution achieves `O(1)` auxiliary space and performs exactly one heap allocation.

## 7. C++ Mechanics

- **`vector<int> ans(2 * n)` vs. `ans.reserve(2 * n)`**:
  - `vector<int> ans(2 * n)` sets both `capacity` and `size` to `2 * n`, making `ans[0 .. 2n-1]` valid indices for `operator[]`.
  - `ans.reserve(2 * n)` only allocates raw capacity while leaving `size() == 0`; indexing `ans[i]` after `reserve()` without resizing is **Undefined Behavior**.
- **`static_cast<int>(nums.size())`**: `nums.size()` returns an unsigned `size_t`. Casting to `int` prevents signed/unsigned comparison warnings (`-Wsign-compare`) in the loop `for (int i = 0; i < n; ++i)`.
- **Chained assignment (`ans[i] = ans[i + n] = nums[i]`)**: In C++, the assignment operator `=` is right-associative and returns a reference to the left operand, so `nums[i]` is read once and written to both positions.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Single element (`n = 1`, `nums = [7]`) | Allocates size `2`; `i = 0` writes `ans[0] = 7` and `ans[0 + 1] = 7` → `[7, 7]` |
| All identical elements (`[4, 4, 4]`) | Writes `4` to `ans[i]` and `ans[i + 3]` for `i = 0, 1, 2` → `[4, 4, 4, 4, 4, 4]` |
| Boundary values (`1` and `1000`) | Stored directly without value overflow |
| Maximum length (`n = 1000`) | Allocates `2000` ints (`8 KB`, fits entirely in L1 CPU cache) |

## 9. Common Mistakes

1. **Declaring `vector<int> ans;` (empty) and writing `ans[i] = nums[i]`**: Accessing `ans[i]` on a vector of size `0` writes out-of-bounds memory and crashes with a segmentation fault or sanitizer error.
2. **Writing `ans[i + n - 1]` instead of `ans[i + n]`**: If you use `i + n - 1`, then for `i = 0` you overwrite `ans[n - 1]` (the last slot of the first copy) and never write `ans[2n - 1]`.
3. **Looping `i` up to `2 * n` and indexing `nums[i]`**: `nums` only has valid indices `0 .. n - 1`. Looping `i` to `2 * n - 1` requires `nums[i % n]` (which adds an unnecessary integer division/modulo operation on every step).

## 10. When To Prefer This Approach

- **Always in interviews and production**: Whenever the final size of a transformed array is known in advance (`2 * n`), pre-allocating and writing by index in a single pass is cleaner, avoids dynamic growth overhead, reads the input array only once, and demonstrates mastery of index arithmetic.
