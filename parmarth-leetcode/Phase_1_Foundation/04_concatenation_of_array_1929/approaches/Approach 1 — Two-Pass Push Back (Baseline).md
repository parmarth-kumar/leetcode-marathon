# Approach 1 — Two-Pass Push Back (Baseline)

## 1. Core Idea

Create an empty result vector `ans`, iterate through `nums` from left to right and append each element to `ans`, then iterate through `nums` a second time and append each element again.

## 2. Why It Works

Concatenating `nums` with itself means producing the sequence `nums[0], nums[1], ..., nums[n-1]` followed immediately by another copy of `nums[0], nums[1], ..., nums[n-1]`. Because `push_back` always appends at the end of the dynamic array, completing one full left-to-right pass over `nums` places the first copy into indices `0 .. n-1`, and completing a second identical pass places the second copy into indices `n .. 2n-1`.

## 3. How To Think About It

1. *"What does the output array look like?"* → All of `nums` in order, followed by all of `nums` in order again.
2. *"How do I build an array sequentially when I just want to append items?"* → Start with an empty `vector<int> ans` and call `ans.push_back(val)`.
3. *"How do I append two copies?"* → Run a loop over `nums` to append the first copy, then run a second loop over `nums` to append the second copy.
4. *"Do I need any index math?"* → No! `push_back` tracks the current end position automatically.

## 4. Visual Trace

```text
Input: nums = [1, 2, 1]   (n = 3)
Initial: ans = []

--- Pass 1 (First Copy) ---
Read nums[0] = 1 -> ans.push_back(1) -> ans = [1]
Read nums[1] = 2 -> ans.push_back(2) -> ans = [1, 2]
Read nums[2] = 1 -> ans.push_back(1) -> ans = [1, 2, 1]

--- Pass 2 (Second Copy) ---
Read nums[0] = 1 -> ans.push_back(1) -> ans = [1, 2, 1, 1]
Read nums[1] = 2 -> ans.push_back(2) -> ans = [1, 2, 1, 1, 2]
Read nums[2] = 1 -> ans.push_back(1) -> ans = [1, 2, 1, 1, 2, 1]

Return ans = [1, 2, 1, 1, 2, 1] ✓
```

## 5. Algorithm / Pseudocode

```text
function getConcatenation(nums):
    ans = empty vector of int

    // Pass 1: append the first copy
    for each x in nums:
        ans.push_back(x)

    // Pass 2: append the second copy
    for each x in nums:
        ans.push_back(x)

    return ans
```

**Loop Invariant**:
- During Pass 1, after processing `k` elements, `ans` contains `nums[0 .. k-1]` of length `k`.
- During Pass 2, after processing `k` elements, `ans` contains `nums[0 .. n-1]` followed by `nums[0 .. k-1]` of total length `n + k`.

## 6. Complexity

### Time

- **Claim**: `O(N)`
- **Proof**: Pass 1 executes `N` iterations and Pass 2 executes `N` iterations, performing `2N` calls to `push_back` in total. When a `std::vector` grows dynamically without prior `reserve()`, its capacity doubles (`1 → 2 → 4 → 8 → ... → 2^k`). The total number of element copies across all reallocations up to size `2N` is bounded by `1 + 2 + 4 + ... + 2N < 4N = O(N)`. Thus, `2N` appends + `< 4N` reallocation copies = `O(N)` total time (`O(1)` amortized per append).
- **Lower bound**: Since the output contains `2N` elements that must all be written, `Ω(N)` time is the theoretical lower bound.

### Space

- **Output space**: `O(N)` — the returned vector `ans` stores `2N` integers.
- **Auxiliary space**: `O(1)` — only loop variables are used beyond the returned container.
- **Interviewer note**: If you call `ans.reserve(2 * nums.size())` before the first loop, you eliminate the intermediate buffer reallocations while keeping the exact same two-pass `push_back` code.

## 7. C++ Mechanics

- **Range-based `for` loop (`for (int val : nums)`)**: Cleanly iterates over all elements of `nums` from index `0` to `n - 1` by value without manual index variables.
- **Amortized Doubling in `std::vector::push_back`**: Each `push_back` checks if `size == capacity`. If full, it allocates a new buffer (2x in GCC/Clang `libstdc++`/`libc++`, 1.5x in MSVC), copies old elements, frees the old buffer, and appends the new element.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Single element (`nums = [7]`) | Pass 1 appends `7`, Pass 2 appends `7` → returns `[7, 7]` |
| All duplicates (`nums = [4, 4, 4]`) | Each loop copies every element regardless of value → `[4, 4, 4, 4, 4, 4]` |
| Boundary values (`1` and `1000`) | Fits inside `int`; copied verbatim without arithmetic |
| Max length (`n = 1000`) | `2000` appends complete in `< 0.01 ms` |

## 9. Common Mistakes

1. **Appending directly to `nums` inside a range-based loop (`for (int x : nums) nums.push_back(x)`)**: Modifying a vector while iterating over it with a range-based `for` loop invalidates the internal iterators as soon as `nums` reallocates, causing **Undefined Behavior (UB)** / memory corruption.
2. **Appending directly to `nums` using `i < nums.size()`**: Because `nums.size()` increases by `1` on every `nums.push_back(...)`, the termination condition `i < nums.size()` is never reached, resulting in an infinite loop (`Memory Limit Exceeded`).
3. **Nesting the two loops instead of placing them sequentially**: Putting the second loop *inside* the first loop produces `N^2` elements instead of `2N`.

## 10. When To Prefer This Approach

- When you want the **most literal, zero-arithmetic baseline** that directly mirrors the English problem description ("append `nums`, then append `nums` again").
- When streaming or filtering elements where the final output size is not easily known upfront.
- In an interview, state this baseline briefly in one sentence, then immediately transition to **Approach 2 (Single-Pass Direct Indexing)** to avoid two passes and dynamic reallocations.
