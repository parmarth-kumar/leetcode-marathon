# Approach 3 — Sort + Two Pointers (Optimized)

## 1. Core Idea

Sort the array in non-decreasing order ($O(N \log N)$), fix the first element `nums[i]` in an outer loop while skipping duplicate values of `nums[i]`, and use two converging pointers (`left = i + 1`, `right = n - 1`) to find all unique pairs in the sorted suffix `[i + 1 .. n - 1]` that sum to `-nums[i]` in $O(N)$ time and $O(1)$ extra space.

## 2. Why It Works

1. **Monotonic Search Space Elimination (Correctness of Two Pointers)**:
   For a fixed `i`, consider the 2D grid of all pairs `(left, right)` with `i + 1 <= left < right <= n - 1`. Because `nums` is sorted:
   - If `nums[i] + nums[left] + nums[right] < 0`:
     Since `nums[right]` is the **largest** remaining element in `[left .. right]`, pairing `nums[left]` with _any_ index `k < right` produces an even smaller (more negative) sum:
     $$\text{nums}[i] + \text{nums}[\text{left}] + \text{nums}[k] \le \text{nums}[i] + \text{nums}[\text{left}] + \text{nums}[\text{right}] < 0$$
     Therefore, `left` can **never** be part of a valid triplet with any element in `[left + 1 .. right]`. We safely eliminate `left` and increment `left++`.
   - If `nums[i] + nums[left] + nums[right] > 0`:
     Since `nums[left]` is the **smallest** remaining element in `[left .. right]`, pairing `nums[right]` with _any_ index `k > left` produces an even larger (more positive) sum. Therefore, `right` is safely eliminated and we decrement `right--`.
   - If `nums[i] + nums[left] + nums[right] == 0`:
     We record `[nums[i], nums[left], nums[right]]`, advance both pointers inward (`left++`, `right--`), and skip consecutive identical values so the same pair is never recorded twice.

2. **Three-Point In-Place Deduplication Invariant**:
   - **Position 1 (`i`)**: `if (i > 0 && nums[i] == nums[i - 1]) continue;` ensures each distinct value for the smallest element of a triplet is explored only on its **first** index, when the available suffix `[i + 1 .. n - 1]` is maximal.
   - **Positions 2 & 3 (`left` & `right`)**: After recording `[nums[i], nums[left], nums[right]]`, skipping all `nums[left] == nums[left - 1]` and `nums[right] == nums[right + 1]` guarantees the next pair has a strictly larger `nums[left]` and strictly smaller `nums[right]`.

## 3. How To Think About It

1. _"In Approach 2, I sorted the array and then used an $O(N)$ `unordered_set` to solve Two Sum on `[i + 1 .. n - 1]`."_
2. _"Wait — if the subarray `[i + 1 .. n - 1]` is **already sorted**, why am I paying $O(N)$ memory and hash-table overhead to do Two Sum?"_
3. _"On a sorted array, Two Sum is solved in $O(N)$ time and $O(1)$ space by placing `left` at the start and `right` at the end, moving `left++` when the sum is too small and `right--` when the sum is too big!"_
4. _"And because identical elements are adjacent in the sorted array, whenever I find a valid triplet, I just step `left` and `right` past their identical neighbors."_

## 4. Visual Trace

```text
Input: nums = [-2, 0, 0, 2, 2]   (already sorted, n = 5)
Indices:        0  1  2  3  4

────────────────────────────────────────────────────────────────────────
Outer i = 0 (nums[0] = -2):
  Initial pointers: left = 1, right = 4

  [ -2,   0,   0,   2,   2 ]
     ^    ^              ^
     i   left          right

  Step 1: sum = nums[0] + nums[1] + nums[4] = -2 + 0 + 2 = 0  ✓ MATCH!
          Record triplet: [-2, 0, 2]

  Step 2: Advance both pointers once:
          left++  → left = 2
          right-- → right = 3

  [ -2,   0,   0,   2,   2 ]
     ^         ^    ^
     i       left right

  Step 3: Skip duplicate left values (nums[left] == nums[left - 1]):
          nums[2] (0) == nums[1] (0) → left++ → left = 3

  Step 4: Check while (left < right):
          Now left = 3, right = 3 → left < right is FALSE!
          Inner loop terminates without ever re-emitting [-2, 0, 2].

────────────────────────────────────────────────────────────────────────
Outer i = 1 (nums[1] = 0):
  left = 2 (0), right = 4 (2) → sum = 0 + 0 + 2 = 2 > 0 → right-- (right = 3)
  left = 2 (0), right = 3 (2) → sum = 0 + 0 + 2 = 2 > 0 → right-- (right = 2)
  left == right → inner loop ends.

────────────────────────────────────────────────────────────────────────
Outer i = 2 (nums[2] = 0):
  nums[2] == nums[1] (0 == 0) → SKIP (continue)!

Final Output: [[-2, 0, 2]]
```

## 5. Algorithm / Pseudocode

```text
function threeSum(nums):
    sort(nums)
    n = length(nums)
    result = empty vector of vector<int>

    for i from 0 to n - 3:
        // Pruning: smallest element > 0 means no triplet can sum to 0
        if nums[i] > 0:
            break

        // Deduplicate first element
        if i > 0 and nums[i] == nums[i - 1]:
            continue

        left = i + 1
        right = n - 1

        while left < right:
            sum = nums[i] + nums[left] + nums[right]

            if sum < 0:
                left++
            else if sum > 0:
                right--
            else:
                result.push_back([nums[i], nums[left], nums[right]])
                left++
                right--

                // Deduplicate second and third elements
                while left < right and nums[left] == nums[left - 1]:
                    left++
                while left < right and nums[right] == nums[right + 1]:
                    right--

    return result
```

## 6. Complexity

### Time

- **Claim**: $O(N^2)$
- **Proof**:
  1. **Sorting**: `std::sort` on $N$ elements takes $O(N \log N)$ comparisons.
  2. **Outer Loop**: Index `i` runs from `0` to at most $N - 3$.
  3. **Inner Two-Pointer Sweep**: For each fixed `i`, `left` starts at `i + 1` and only increments; `right` starts at `n - 1` and only decrements. Every iteration of `while (left < right)` (including the inner duplicate-skipping `while` loops) increases `left` or decreases `right` by at least 1. Since the initial distance `right - left` is $N - 2 - i$, the pointers cross in at most $N - 1 - i$ steps.
  4. **Summation**:
     $$\sum_{i=0}^{N-3} (N - 1 - i) = \frac{(N - 1)(N - 2)}{2} = \Theta(N^2)$$
  5. **Total Time**: $O(N \log N) + \Theta(N^2) = O(N^2)$.
- **Lower bound**: In the worst case, an array can have $\Theta(N^2)$ unique valid triplets (for example, $N/3$ negative numbers, $N/3$ zeros/positives arranged so many pairs match), and under the 3SUM conjecture any general algorithm requires $\Omega(N^2)$ time.

### Space

- **Output space**: $O(U)$ — to store the $U$ unique triplets required by the return type `vector<vector<int>>`.
- **Auxiliary space**: $O(\log N)$ — `std::sort` (Introsort) uses $O(\log N)$ call-stack space; the two-pointer phase itself uses strictly $O(1)$ auxiliary variables (`i`, `left`, `right`, `sum`).
- **Interviewer note**: _"When an interviewer asks for '$O(1)$ space' on 3Sum, they mean $O(1)$ auxiliary space beyond sorting (as opposed to the $O(N)$ hash table in Approach 2 or the $O(U)$ `std::set` in Approach 1)."_

## 7. C++ Mechanics

- **Cache-Friendly Contiguous Memory**: Unlike `std::unordered_set` (which allocates linked-list bucket nodes on the heap and suffers pointer-chasing cache misses), `nums[left]` and `nums[right]` traverse contiguous `std::vector<int>` memory, allowing the CPU hardware prefetcher to keep L1 cache hot.
- **Initializer List Push**: `result.push_back({nums[i], nums[left], nums[right]});` (or `result.emplace_back(...)`) constructs the 3-element inner `vector<int>` cleanly.
- **Amortized `push_back`**: Appending to `result` doubles capacity geometrically when full, so $U$ appends take $O(U)$ total amortized time.

## 8. Edge Cases

| Edge Case                                                      | How Approach 3 Handles It                                                                                                    |
| :------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------- |
| `nums = [0, 0, 0]` (minimum size $N = 3$)                      | `i = 0`, `left = 1`, `right = 2` $\rightarrow$ `sum = 0`, records `[0, 0, 0]`, advances `left = 2, right = 1`, loop ends.    |
| `nums = [0, 0, 0, 0, 0]`                                       | `i = 0` records `[0, 0, 0]`, inner `while` skips remaining `0`s; outer `i = 1, 2` are skipped by `nums[i] == nums[i - 1]`.   |
| `nums = [-1, -1, 2]` (duplicate shared between `i` and `left`) | At `i = 0` (`-1`), `left` starts at `1` (`-1`), so `nums[0] + nums[1] + nums[2] = 0` is tested _before_ any inner skip runs. |
| All positive `[1, 2, 3, 4]`                                    | `if (nums[i] > 0) break;` terminates immediately at `i = 0`.                                                                 |
| All negative `[-5, -4, -3, -2]`                                | For each `i`, `sum < 0` every step so `left` walks to `right` and returns `{}`.                                              |

## 9. Common Mistakes

1. **Writing `if (nums[i] == nums[i + 1]) continue;` in the outer loop**:
   - This skips the **first** copy of a duplicated number instead of the second, which destroys valid triplets of the form `[a, a, b]` (like `[-1, -1, 2]`). Always write `if (i > 0 && nums[i] == nums[i - 1]) continue;`.
2. **Forgetting `left < right` inside the duplicate-skipping `while` loops**:
   - On `[0, 0, 0]`, after `left++` (`2`) and `right--` (`1`), if you write `while (nums[left] == nums[left - 1]) left++;` without `left < right`, `left` will walk right off the end of the array (`left = 3` $\rightarrow$ **out-of-bounds Undefined Behavior / crash**)!
3. **Only advancing `left++` (or `break`ing) when `sum == 0`**:
   - If you `break` on `sum == 0`, you miss other pairs for the same `nums[i]` (e.g., `[-2, 0, 2]` and `[-2, 1, 1]`).
   - Since both `nums[left]` and `nums[right]` are now consumed (and any duplicates will be skipped), you can advance **both** `left++` and `right--` simultaneously.

## 10. When To Prefer This Approach

- **Always in interviews and competitive programming**: This is the canonical, expected optimal solution for **3Sum (LC 15)** at Google and all top-tier tech companies.
- Directly serves as the core building block for **3Sum Closest (LC 16)**, **3Sum Smaller (LC 259)**, **4Sum (LC 18)**, and general **$k$-Sum**.
