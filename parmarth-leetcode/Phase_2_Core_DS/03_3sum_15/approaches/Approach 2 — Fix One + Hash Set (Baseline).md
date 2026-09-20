# Approach 2 — Fix One + Hash Set (Baseline)

## 1. Core Idea

Reduce **3Sum** to $N$ instances of **Two Sum**: sort the array first so duplicate first elements (`nums[i]`) can be skipped trivially, then for each fixed `nums[i]`, scan `j` from `i + 1` to `n - 1` using an `unordered_set<int> seen` to check in $O(1)$ average time whether `complement = -nums[i] - nums[j]` has already appeared between `i + 1` and `j - 1`.

## 2. Why It Works

1. **Algebraic Reduction**:
   $$\text{nums}[i] + \text{nums}[j] + \text{nums}[k] = 0 \iff \text{complement} = -\text{nums}[i] - \text{nums}[j]$$
   As `j` scans left-to-right from `i + 1` to `n - 1`, `seen` holds every value `nums[k]` for `k` in `[i + 1 .. j - 1]`. Thus, whenever `seen.count(complement)` is true, there exists an index `k` (`i < k < j`) such that `nums[i] + nums[k] + nums[j] == 0`.
2. **Duplicate Prevention Without `std::set<vector<int>>`**:
   - **Outer duplicates**: Because `nums` is sorted, skipping `i` when `i > 0 && nums[i] == nums[i - 1]` guarantees the first element of the triplet is never repeated.
   - **Inner duplicates**: Because `nums` is sorted, if `nums[j]` forms a valid triplet (`complement` is in `seen`), any immediately following identical values `nums[j + 1] == nums[j]` would look up the exact same `complement` in `seen` and produce a duplicate triplet. Advancing `j` past identical neighbors **after** a match (`while (j + 1 < n && nums[j] == nums[j + 1]) ++j;`) prevents duplicate emissions while still allowing two identical numbers (`nums[k] == nums[j]`, like `[0, 0, 0]` or `[-2, 1, 1]`) to pair with each other on the first encounter.

## 3. How To Think About It

1. _"I already know how to solve Two Sum in $O(N)$ time using a Hash Set (from Phase 1, Problem 01)."_
2. _"In 3Sum, if I lock down `nums[i]` in an outer loop, I just need two numbers to the right of `i` that add up to `-nums[i]`."_
3. _"How do I avoid duplicate triplets cleanly?"_
   Sort the array first ($O(N \log N)$ is free inside an $O(N^2)$ algorithm). Skip duplicate `nums[i]` values before starting the inner loop, and whenever `nums[j]` completes a valid triplet, fast-forward `j` over any identical consecutive values.

## 4. Visual Trace

```text
Input: nums = [-1, 0, 1, 2, -1, -4]
After sort :  [-4, -1, -1,  0,  1,  2]
Indices    :    0   1   2   3   4   5

────────────────────────────────────────────────────────────────────────
Outer i = 0 (nums[0] = -4):
  seen = {}
  j = 1 (-1): complement = 5 → not in seen. seen = {-1}
  j = 2 (-1): complement = 5 → not in seen. seen = {-1}
  j = 3 ( 0): complement = 4 → not in seen. seen = {-1, 0}
  j = 4 ( 1): complement = 3 → not in seen. seen = {-1, 0, 1}
  j = 5 ( 2): complement = 2 → not in seen. seen = {-1, 0, 1, 2}

────────────────────────────────────────────────────────────────────────
Outer i = 1 (nums[1] = -1):
  seen = {}
  j = 2 (-1): complement = -(-1) - (-1) = 2 → not in seen.
              Insert -1 → seen = {-1}
  j = 3 ( 0): complement = -(-1) - 0 = 1    → not in seen.
              Insert  0 → seen = {-1, 0}
  j = 4 ( 1): complement = -(-1) - 1 = 0    → 0 IS IN seen! ✓
              Record [-1, 0, 1].
              Insert  1 → seen = {-1, 0, 1}
  j = 5 ( 2): complement = -(-1) - 2 = -1   → -1 IS IN seen! ✓
              Record [-1, -1, 2].
              Insert  2 → seen = {-1, 0, 1, 2}

────────────────────────────────────────────────────────────────────────
Outer i = 2 (nums[2] = -1):
  nums[2] == nums[1] (-1 == -1) → SKIP!

────────────────────────────────────────────────────────────────────────
Outer i = 3 (nums[3] = 0):
  seen = {}
  j = 4 ( 1): complement = -1 → not in seen. seen = {1}
  j = 5 ( 2): complement = -2 → not in seen. seen = {1, 2}

────────────────────────────────────────────────────────────────────────
Outer i = 4 (nums[4] = 1):
  nums[4] > 0 → BREAK early!

Final Output: [[-1, 0, 1], [-1, -1, 2]]
```

## 5. Algorithm / Pseudocode

```text
function threeSum(nums):
    sort(nums)
    n = length(nums)
    result = empty vector of vector<int>

    for i from 0 to n - 3:
        if nums[i] > 0:
            break  // Remaining elements are all > 0
        if i > 0 and nums[i] == nums[i - 1]:
            continue  // Skip duplicate first element

        seen = empty unordered_set<int>
        for j from i + 1 to n - 1:
            complement = -nums[i] - nums[j]
            if complement is in seen:
                result.push_back([nums[i], complement, nums[j]])
                // Skip consecutive identical nums[j] to avoid duplicate triplets
                while j + 1 < n and nums[j] == nums[j + 1]:
                    j++
            seen.insert(nums[j])

    return result
```

## 6. Complexity

### Time

- **Claim**: $O(N^2)$ average time.
- **Proof**:
  1. Sorting `nums` takes $O(N \log N)$ comparisons.
  2. The outer loop runs at most $N - 2$ times.
  3. For each `i`, the inner loop advances `j` from `i + 1` to `n - 1` (at most $N - 1 - i$ steps). Even with the inner `while` loop skipping duplicates, `j` only ever increments, so the inner loop body executes at most $N - 1 - i$ times.
  4. Each hash set lookup (`seen.count`) and insertion (`seen.insert`) takes $O(1)$ amortized/average time.
  5. Total runtime: $O(N \log N) + \sum_{i=0}^{N-3} O(N - i) = O(N \log N + N^2) = O(N^2)$.
- **Lower bound**: Under the 3SUM conjecture, $\Omega(N^2)$ is the asymptotic time barrier for general comparison/hashing models.

### Space

- **Output space**: $O(U)$ — to store the $U$ unique triplets in `result`.
- **Auxiliary space**: $O(N)$ — for each outer iteration `i`, `unordered_set<int> seen` holds up to $N - 1$ integers on the heap (plus $O(\log N)$ stack space for `std::sort`).
- **Interviewer note**: _"While this achieves the optimal $O(N^2)$ time complexity, it allocates a hash table of size $O(N)$ on every outer iteration. Because the array is already sorted, we can replace `unordered_set` with converging two pointers (Approach 3) to drop auxiliary space to $O(1)$ beyond sorting and drastically improve cache performance."_

## 7. C++ Mechanics

- `unordered_set<int> seen;` declared **inside** the outer `for (int i ...)` loop: Automatically starts empty for each new `nums[i]` and is destroyed at the end of the iteration.
- **Order of operations in the inner loop**:
  1. Check `seen.count(complement)` **first**.
  2. If found, push `{nums[i], complement, nums[j]}` and fast-forward `j` across duplicates.
  3. Call `seen.insert(nums[j])` **last**.
  - _Why this order matters_: Inserting `nums[j]` _after_ checking `seen` prevents `nums[j]` from matching with _itself_ at the same index, while fast-forwarding `j` _only after a match_ ensures the first occurrence of a duplicate value (e.g., the first `1` in `[-2, 1, 1]`) gets inserted into `seen` so the second `1` can match with it!

## 8. Edge Cases

| Edge Case                | How Approach 2 Handles It                                                                                                                                                                 |
| :----------------------- | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `[0, 0, 0, 0]`           | At `i = 0`: `j = 1` inserts `0` into `seen`; `j = 2` finds `0` in `seen`, emits `[0, 0, 0]`, and fast-forwards `j` to `3`. Outer `i = 1, 2, 3` are skipped.                               |
| `[-2, 1, 1]`             | At `i = 0` (`-2`): `j = 1` (`1`) does not find `1` in `seen` yet, so it does NOT fast-forward; it inserts `1` into `seen`. Then `j = 2` (`1`) finds `1` in `seen` and emits `[-2, 1, 1]`. |
| All positive `[1, 2, 3]` | `if (nums[i] > 0) break;` exits immediately on `i = 0`.                                                                                                                                   |

## 9. Common Mistakes

1. **Skipping duplicate `nums[j]` _before_ checking `seen`**:
   - If you write `if (j > i + 1 && nums[j] == nums[j - 1]) continue;` at the top of the inner loop, then on `[-2, 1, 1]`, `j = 1` inserts `1` into `seen`, and `j = 2` sees `nums[2] == nums[1]` and skips `j = 2` before ever checking `seen`! You must only fast-forward `j` **after** recording a valid triplet.
2. **Inserting `nums[j]` into `seen` _before_ checking `seen.count(complement)`**:
   - On `[-2, 1, 5]`, at `i = 0` (`-2`) and `j = 1` (`1`), `complement` is `1`. If you inserted `nums[1] = 1` into `seen` first, `seen.count(1)` would return true, falsely using index `1` twice to form `[-2, 1, 1]`!

## 10. When To Prefer This Approach

- As a **natural conceptual bridge** from Two Sum (LC 1) during an interview before optimizing space to Two Pointers.
- In variants where **sorting the array is forbidden** AND copying the array is undesirable (a no-sort variant of this approach can use an outer `unordered_set<int>` of processed `nums[i]` values and a canonical triplet set, though at higher memory cost).
