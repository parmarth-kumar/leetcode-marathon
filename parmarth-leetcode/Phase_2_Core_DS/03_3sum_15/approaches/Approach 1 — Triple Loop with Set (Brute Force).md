# Approach 1 — Triple Loop with Set (Brute Force)

## 1. Core Idea

Exhaustively enumerate every combination of three distinct indices `(i, j, k)` with `0 <= i < j < k < n`. Whenever `nums[i] + nums[j] + nums[k] == 0`, sort the 3-element triplet `[nums[i], nums[j], nums[k]]` so that equivalent multisets share a single canonical order (`a <= b <= c`), and insert it into a `std::set<vector<int>>` to automatically filter out duplicates.

## 2. Why It Works

1. **Exhaustive Completeness**: By iterating over all $\binom{n}{3}$ index triples `0 <= i < j < k < n`, every valid combination of three distinct array positions is guaranteed to be inspected. Because `i < j < k`, no index is ever reused twice within the same triplet.
2. **Canonical Deduplication**: Two triplets contain the same multiset of three numbers if and only if their sorted forms are identical (e.g., `[-1, 0, 1]` and `[0, 1, -1]` both sort to `[-1, 0, 1]`). Inserting the sorted 3-element `vector<int>` into a `std::set<vector<int>>` enforces uniqueness via lexicographical comparison.

## 3. How To Think About It

1. _"What is the most direct translation of the problem statement?"_
   Pick three distinct indices `i`, `j`, and `k`, and check if their values add up to `0`.
2. _"How do I make sure I never pick the same index twice?"_
   Enforce strict index ordering: `i` from `0` to `n - 3`, `j` from `i + 1` to `n - 2`, and `k` from `j + 1` to `n - 1`.
3. _"How do I stop duplicate triplets from appearing in the output?"_
   Sort the 3 numbers inside each valid triplet (only 3 elements, so $O(1)$ time) and insert them into a `std::set<vector<int>>`. At the end, copy the unique triplets from the `set` into a `vector<vector<int>>`.

## 4. Visual Trace

```text
Input: nums = [-1, 0, 1, 2, -1, -4]   (n = 6)
Indices:        0  1  2  3   4   5

We test all C(6, 3) = 20 index combinations (i, j, k):

  (i, j, k)    Values           Sum    Action
  ─────────    ──────────────   ───    ───────────────────────────────────────
  (0, 1, 2)    [-1,  0,  1]      0  ✓  sort → [-1, 0, 1] → insert into set
  (0, 1, 3)    [-1,  0,  2]      1  ✗
  (0, 1, 4)    [-1,  0, -1]     -2  ✗
  (0, 1, 5)    [-1,  0, -4]     -5  ✗
  (0, 2, 3)    [-1,  1,  2]      2  ✗
  (0, 2, 4)    [-1,  1, -1]     -1  ✗
  (0, 2, 5)    [-1,  1, -4]     -4  ✗
  (0, 3, 4)    [-1,  2, -1]      0  ✓  sort → [-1, -1, 2] → insert into set
  (0, 3, 5)    [-1,  2, -4]     -3  ✗
  (0, 4, 5)    [-1, -1, -4]     -6  ✗
  (1, 2, 3)    [ 0,  1,  2]      3  ✗
  (1, 2, 4)    [ 0,  1, -1]      0  ✓  sort → [-1, 0, 1] → already in set (ignored!)
  ... (remaining 8 triples all have non-zero sum)

Final Set Contents:
  { [-1, -1, 2], [-1, 0, 1] }
```

## 5. Algorithm / Pseudocode

```text
function threeSum(nums):
    n = length(nums)
    uniqueTriplets = empty Set of vector<int>

    for i from 0 to n - 3:
        for j from i + 1 to n - 2:
            for k from j + 1 to n - 1:
                if nums[i] + nums[j] + nums[k] == 0:
                    triplet = [nums[i], nums[j], nums[k]]
                    sort(triplet)  // 3 elements → O(1)
                    uniqueTriplets.insert(triplet)

    return vector<vector<int>>(uniqueTriplets.begin(), uniqueTriplets.end())
```

## 6. Complexity

### Time

- **Claim**: $O(N^3 \log U)$, where $U$ is the number of unique zero-sum triplets ($U \le \binom{N}{3}$).
- **Proof**:
  1. The three nested loops iterate over all $\binom{N}{3} = \frac{N(N - 1)(N - 2)}{6} = \Theta(N^3)$ index triples.
  2. Inside the innermost loop, summing 3 integers is $O(1)$, and sorting a 3-element vector takes at most 3 comparisons, which is $O(1)$.
  3. Inserting a 3-element `vector<int>` into a `std::set` of size at most $U$ takes $O(\log U)$ triplet comparisons (each comparing 3 integers in $O(1)$).
  4. Total time: $O(N^3 \log U)$.
- **Lower bound**: Any algorithm must at least inspect all input elements ($\Omega(N)$) and write all $U$ output triplets ($\Omega(U)$). The $\Theta(N^3)$ search here is non-optimal because the third index `k` is searched linearly instead of via complement lookup or two pointers.

### Space

- **Output space**: $O(U)$ — to return the `vector<vector<int>>` containing all $U$ unique triplets.
- **Auxiliary space**: $O(U)$ — the `std::set<vector<int>>` stores a red-black tree node for each of the $U$ unique triplets before copying them to the output vector.
- **Interviewer note**: _"In an interview, state this brute-force bound in 30 seconds to establish the baseline and identify the two bottlenecks — the $O(N)$ inner loop for `k` and the $O(U)$ set for deduplication — before immediately moving to $O(N^2)$."_

## 7. C++ Mechanics

- `std::set<vector<int>>`: C++'s `std::vector` defines `operator<` lexicographically out of the box, so `std::set<vector<int>>` works **without** writing a custom comparator! (By contrast, `std::unordered_set<vector<int>>` does _not_ compile without a custom hash functor because the C++ standard library does not provide `std::hash<vector<int>>`).
- **Range constructor**: `vector<vector<int>>(uniqueTriplets.begin(), uniqueTriplets.end())` copies all elements from the `std::set` into the result `std::vector` in $O(U)$ time.

## 8. Edge Cases

| Edge Case                                       | How Approach 1 Handles It                                                                                            |
| :---------------------------------------------- | :------------------------------------------------------------------------------------------------------------------- |
| All zeros `[0, 0, 0, 0]`                        | Every `(i, j, k)` sums to `0` and sorts to `[0, 0, 0]`; `std::set` collapses all 4 copies into a single `[0, 0, 0]`. |
| No valid triplets `[0, 1, 1]`                   | Condition `nums[i] + nums[j] + nums[k] == 0` is never met; returns empty vector `{}`.                                |
| Negative & positive extremes `[-10^5, 0, 10^5]` | Sum fits inside 32-bit signed `int` without overflow.                                                                |

## 9. Common Mistakes

1. **Forgetting to sort the 3-element triplet before inserting into `std::set`**:
   - Without `sort(triplet.begin(), triplet.end())`, `[-1, 0, 1]` and `[0, 1, -1]` are treated as distinct vectors by `std::set`, causing duplicate triplets in the output.
2. **Starting inner loops at `0` instead of `i + 1` and `j + 1`**:
   - Writing `for (int j = 0; j < n; j++)` allows `i == j`, reusing the same element twice and violating the distinct-index rule.
3. **Attempting `unordered_set<vector<int>>` without a custom hash**:
   - Results in a template compilation error in C++ because `std::hash<std::vector<int>>` is not specialized in the standard library.

## 10. When To Prefer This Approach

- **Never in production or for $N = 3000$** (it will TLE on LeetCode's large test cases).
- **Use for**:
  1. The first 30 seconds of an interview to articulate the baseline and pinpoint why sorting + two pointers is needed.
  2. Writing a **stress-test oracle** on small random arrays ($N \le 50$) to verify that your optimized $O(N^2)$ pointer-skipping logic never misses or duplicates a triplet.
