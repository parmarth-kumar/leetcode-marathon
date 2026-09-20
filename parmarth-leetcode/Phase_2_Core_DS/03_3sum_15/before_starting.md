Problem : 3Sum
LeetCode : https://leetcode.com/problems/3sum/
Topic : Array, Two Pointers, Sorting
Difficulty : Medium
Google-Tagged: Yes
Phase : 2 — Core Data Structures
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given an integer array `nums`. Your task is to find **all unique triplets** `[nums[i], nums[j], nums[k]]` such that:

1. The three indices are **distinct**: `i != j`, `i != k`, and `j != k`.
2. The three values **sum to zero**: `nums[i] + nums[j] + nums[k] == 0`.

The returned list of triplets **must not contain duplicate triplets** (two triplets are considered duplicates if they contain the same multiset of three numbers, regardless of order). You may return the triplets and their elements in any order.

### Input & Output Specifications

- **Input**: `vector<int>& nums` — an unsorted array of integers (positive, negative, and/or zero).
- **Output**: `vector<vector<int>>` — a 2D vector where each inner `vector<int>` has size 3, sums to `0`, and no two inner vectors contain the same multiset of values.

### Constraints & Their Implications

| Constraint                 | Implication                                                                                                                                                                                                                                                                 |
| :------------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `3 <= nums.length <= 3000` | The array always has at least 3 elements. However, `N = 3000` is the critical sizing signal.                                                                                                                                                                                |
| `-10^5 <= nums[i] <= 10^5` | Negative numbers, zeros, and positive numbers exist. The sum of any three elements lies in `[-3 * 10^5, 3 * 10^5]`, which easily fits in a standard 32-bit signed `int` (max `~2.14 * 10^9`) — **no integer overflow** for 3Sum (unlike 4Sum where `10^9` values are used). |

**CPU Intuition (`10^8` operations/sec rule)**:

- **$O(N^3)$ Brute Force**: For $N = 3000$, $\binom{3000}{3} \approx \frac{2.7 \times 10^{10}}{6} = 4.5 \times 10^9$ iterations. At $\sim 10^8$ operations per second, $4.5 \times 10^9$ operations take **45+ seconds** $\rightarrow$ guaranteed **Time Limit Exceeded (TLE)**.
- **$O(N^2)$ Target**: For $N = 3000$, $N^2 = 9 \times 10^6$ operations. Even with sorting ($N \log_2 N \approx 3.5 \times 10^4$ ops), $9 \times 10^6$ simple pointer operations execute in **~10–30 milliseconds** $\rightarrow$ easily passes.
- **Takeaway**: The constraint `N <= 3000` is an explicit signal from the problem setter that $O(N^3)$ is forbidden and **$O(N^2)$ is the expected time complexity**.

### Important Terminology Defined Explicitly

- **Triplet**: A group of 3 elements `[nums[i], nums[j], nums[k]]` chosen from `nums` using three distinct indices `i`, `j`, and `k`.
- **Distinct Indices vs. Distinct Values**:
  - You **cannot** reuse the _same index_ twice in a single triplet (e.g., if `nums = [-2, 1]`, you cannot use index `1` twice to form `[-2, 1, 1]`).
  - You **can** use duplicate _values_ within a single triplet if those values appear at _different indices_ in `nums` (e.g., if `nums = [-2, 1, 1]`, indices `(0, 1, 2)` give `[-2, 1, 1]`, which is valid).
- **Unique Triplets (Deduplication)**:
  - The output cannot contain two triplets with the same three values. For example, `[-1, 0, 1]` and `[0, -1, 1]` represent the **same triplet** and must appear **at most once** in the output.
  - Even if the input has multiple copies of `-1`, `0`, and `1` at different indices, `[-1, 0, 1]` is emitted **only once**.

### Concrete Worked Examples

**Example 1 — Standard Mix with Duplicates**:

```text
Input: nums = [-1, 0, 1, 2, -1, -4]
Indices:        0  1  2  3   4   5

All index-triplets (i, j, k) that sum to 0:
  - Indices (0, 1, 2) → [-1,  0,  1] (sum = 0)
  - Indices (0, 3, 4) → [-1,  2, -1] (sum = 0) → sorted: [-1, -1, 2]
  - Indices (1, 2, 4) → [ 0,  1, -1] (sum = 0) → sorted: [-1,  0, 1] (DUPLICATE of first!)

Unique triplets output:
  [[-1, -1, 2], [-1, 0, 1]]
```

**Example 2 — No Valid Triplet**:

```text
Input: nums = [0, 1, 1]
Indices:       0  1  2

Only one triplet of indices exists: (0, 1, 2)
  nums[0] + nums[1] + nums[2] = 0 + 1 + 1 = 2 != 0

Output: []
```

**Example 3 — All Zeros (Multiple Copies of the Same Value)**:

```text
Input: nums = [0, 0, 0, 0]
Indices:       0  1  2  3

Index triplets:
  (0, 1, 2) → [0, 0, 0]
  (0, 1, 3) → [0, 0, 0] (duplicate)
  (0, 2, 3) → [0, 0, 0] (duplicate)
  (1, 2, 3) → [0, 0, 0] (duplicate)

Unique triplets output:
  [[0, 0, 0]]
```

**Example 4 — Multiple Pairs Sharing the Same First Element**:

```text
Input: nums = [-2, 0, 1, 1, 2]
Sorted:       [-2, 0, 1, 1, 2]
               ^   ^        ^  → -2 + 0 + 2 = 0  ✓  [-2, 0, 2]
               ^      ^  ^     → -2 + 1 + 1 = 0  ✓  [-2, 1, 1]

Unique triplets output:
  [[-2, 0, 2], [-2, 1, 1]]
```

### Common Beginner Traps

1. **Confusing "no duplicate triplets" with "no duplicate elements inside a triplet"**:
   - Beginner bug: Skipping `nums[j] == nums[i]` _before_ testing `nums[i] + nums[j] + nums[k] == 0`. That misses valid triplets like `[-1, -1, 2]` or `[0, 0, 0]`!
2. **Stopping after the first match for a fixed `nums[i]`**:
   - In Two Sum, there was only one pair. In 3Sum, a single `nums[i]` (like `-2` in Example 4) can participate in **multiple distinct triplets** (`[-2, 0, 2]` and `[-2, 1, 1]`). You must keep searching after finding a valid pair!
3. **Comparing `nums[i] == nums[i + 1]` instead of `nums[i] == nums[i - 1]`**:
   - If you skip when `nums[i] == nums[i + 1]`, then on `[-1, -1, 2]`, at `i = 0` (`nums[0] == -1`), you see `nums[1] == -1` and skip `i = 0`! Now `i = 1` only has `[2]` to its right and can never form a triplet of size 3. Always skip a duplicate `i` **after** its first occurrence has been processed (`i > 0 && nums[i] == nums[i - 1]`).
4. **Relying on `std::set<vector<int>>` to deduplicate in an $O(N^2)$ loop**:
   - Inserting into a balanced BST (`std::set`) adds a $\log U$ overhead per triplet and consumes $O(U)$ extra memory, which interviewers immediately ask you to eliminate.

### One-Sentence Restatement

> Find all unique multisets of three elements from `nums` (at distinct indices) that sum to `0` in $O(N^2)$ time and $O(1)$ auxiliary space beyond sorting.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Problem Reduction ($k$-Sum $\rightarrow$ $(k-1)$-Sum)

- **What it is**: Transforming a harder problem with 3 variables into a known problem with 2 variables by **fixing** one variable at a time.
- **Minimum mechanics**:
  $$\text{nums}[i] + \text{nums}[j] + \text{nums}[k] = 0 \iff \text{nums}[j] + \text{nums}[k] = -\text{nums}[i]$$
  Once index `i` is fixed in an outer loop, finding `(j, k)` with `j, k > i` is literally **Two Sum** with `target = -nums[i]`.
- **Why it matters here**: Instead of searching a 3D space $(i, j, k)$ in $O(N^3)$, fixing `i` reduces the inner problem to a 1D scan over `[i + 1 .. N - 1]` in $O(N)$, yielding $N \times O(N) = O(N^2)$ total time.

### 2. Sorting as a Structural Enabler (`std::sort`)

- **What it is**: Rearranging the array into non-decreasing order (`nums[0] <= nums[1] <= ... <= nums[n-1]`) in $O(N \log N)$ time.
- **Minimum mechanics**:
  ```cpp
  #include <algorithm>
  std::sort(nums.begin(), nums.end()); // O(N log N) time, O(log N) stack space
  ```
- **Tiny example**:
  ```text
  Before: [-1, 0, 1, 2, -1, -4]
  After : [-4, -1, -1, 0, 1, 2]
  ```
- **Why it matters here**: Because our target time is $O(N^2)$, sorting first for $O(N \log N)$ is **asymptotically free** ($O(N \log N + N^2) = O(N^2)$) and unlocks three massive advantages:
  1. **Duplicate grouping**: Identical values sit next to each other, so deduplication becomes a simple adjacent check (`nums[i] == nums[i - 1]`).
  2. **Monotonicity for Two Pointers**: Moving a left pointer right increases the sum; moving a right pointer left decreases the sum.
  3. **Canonical triplet order**: Since `i < left < right` in a sorted array, every discovered triplet `[nums[i], nums[left], nums[right]]` is automatically sorted (`a <= b <= c`).

### 3. Converging Two Pointers on a Sorted Array (2Sum II Pattern)

- **What it is**: Using two indices — `left` starting at the beginning of a sorted subarray and `right` starting at the end — that move toward each other based on whether the current sum is too small or too large.
- **Minimum mechanics**:
  ```cpp
  int left = i + 1, right = n - 1;
  while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum < 0)      left++;   // Need a larger sum
      else if (sum > 0) right--;  // Need a smaller sum
      else { /* record triplet, advance both & skip duplicates */ }
  }
  ```
- **Why it matters here**: Replaces the $O(N)$-space hash table from standard Two Sum with an **$O(1)$-space** linear scan over the remaining sorted subarray.

### 4. In-Place Adjacent Deduplication

- **What it is**: Skipping consecutive identical values in a sorted array so that each distinct value is tried only once at each position of the triplet.
- **Minimum mechanics**:
  - For the outer loop index `i`:
    ```cpp
    if (i > 0 && nums[i] == nums[i - 1]) continue;
    ```
  - For `left` and `right` **after** recording a valid triplet:
    ```cpp
    left++; right--;
    while (left < right && nums[left] == nums[left - 1]) left++;
    while (left < right && nums[right] == nums[right + 1]) right--;
    ```
- **Why it matters here**: Eliminates the need for `std::set` or custom tuple hashing to filter out duplicate triplets.

### 5. Hash Sets (`std::unordered_set`) for Complement Lookup

- **What it is**: A hash-table-backed collection of unique keys supporting $O(1)$ average-time insertion and lookup.
- **Minimum mechanics**:
  ```cpp
  #include <unordered_set>
  unordered_set<int> seen;
  if (seen.count(complement)) { /* found */ }
  seen.insert(nums[j]);
  ```
- **Why it matters here**: Powers the intermediate $O(N^2)$ time, $O(N)$ space approach when reducing 3Sum directly to Hash-Set Two Sum.

---

> 🛑 **STOP HERE AND ATTEMPT THE PROBLEM FIRST.**
>
> Open `test_harness.cpp`, write your solution inside the empty `Solution` class, compile, and test it against the provided edge cases.
>
> Only open the sections below if you are stuck or want to compare after solving.

---

<details>
<summary>🔍 Layer 3 — How To Think Through The Problem (click to reveal)</summary>

### 1. What Should Be Noticed First?

Look at two things in the problem statement:

1. **The return value**: You are returning **values** (`[nums[i], nums[j], nums[k]]`), **not original indices**!
   - _Contrast with Two Sum (LC 1)_: In Two Sum, you had to return the _original indices_, which meant sorting the array directly would destroy the original indices unless you stored `(value, index)` pairs.
   - _In 3Sum_: Because only the **values** matter, we are completely free to **sort the array in-place**!
2. **The constraint `N <= 3000`**:
   - $O(N^2)$ is the target. Since $O(N \log N)$ is strictly smaller than $O(N^2)$, sorting at the very start costs nothing in Big-O terms.

### 2. Naive Thought Process & Its Two Bottlenecks

If you solve this by hand without any optimization, you try every combination of three indices `(i, j, k)` with `0 <= i < j < k < n`:

- **Bottleneck A (Time — $O(N^3)$)**: After picking `nums[i]` and `nums[j]`, the third number you need is uniquely determined: `nums[k] = -(nums[i] + nums[j])`. Spending an $O(N)$ loop just to look for that single number is wasteful.
- **Bottleneck B (Deduplication)**: With `nums = [-1, 0, 1, 2, -1, -4]`, index triplet `(0, 1, 2)` gives `[-1, 0, 1]` and index triplet `(1, 2, 4)` gives `[0, 1, -1]`. How do you prevent adding both?

### 3. How Sorting Solves BOTH Bottlenecks Simultaneously

Let's sort `nums = [-1, 0, 1, 2, -1, -4]`:

```text
Sorted nums:  [-4, -1, -1,  0,  1,  2]
Indices    :    0   1   2   3   4   5
```

Now suppose we fix the smallest element of the triplet at index `i`, and we need two elements to its right (`left` and `right`, with `i < left < right`) such that:
$$\text{nums}[i] + \text{nums}[\text{left}] + \text{nums}[\text{right}] = 0$$

#### Solving Bottleneck A (Search in $O(N)$ per `i` via Two Pointers):

Place `left = i + 1` (smallest remaining candidate) and `right = n - 1` (largest remaining candidate).
Compute `sum = nums[i] + nums[left] + nums[right]`:

- **Case 1 (`sum < 0`)**: The sum is too negative. Since `right` is already as large as possible in our current window, the **only** way to increase the sum is to increase `nums[left]` $\rightarrow$ `left++`.
- **Case 2 (`sum > 0`)**: The sum is too positive. Since `left` is already as small as possible in our current window, the **only** way to decrease the sum is to decrease `nums[right]` $\rightarrow$ `right--`.
- **Case 3 (`sum == 0`)**: We found a valid triplet `[nums[i], nums[left], nums[right]]`! Record it, then advance **both** `left++` and `right--` to look for other pairs.

#### Solving Bottleneck B (Deduplication in $O(1)$ without a Set):

Why could duplicate triplets ever be produced when the array is sorted?

1. **Same `nums[i]` chosen again**:
   Look at indices `1` and `2` in `[-4, -1, -1, 0, 1, 2]`.
   - At `i = 1`, `nums[1] = -1`, and we search the subarray `[-1, 0, 1, 2]`. This finds ALL triplets whose smallest element is `-1` (namely `[-1, -1, 2]` and `[-1, 0, 1]`).
   - At `i = 2`, `nums[2] = -1` again, and we would search `[0, 1, 2]`, which is a **strict subset** of what we already searched at `i = 1`!
   - **Rule 1**: If `i > 0 && nums[i] == nums[i - 1]`, `continue` (skip `i`).
2. **Same `nums[left]` or `nums[right]` chosen again for the same `i`**:
   Suppose `nums = [-2, 0, 0, 2, 2]` and `i = 0` (`nums[0] = -2`).
   - `left = 1` (`0`), `right = 4` (`2`) $\rightarrow$ `-2 + 0 + 2 = 0`. Record `[-2, 0, 2]`.
   - If we only do `left++` and `right--`, now `left = 2` (`0`) and `right = 3` (`2`), which would record `[-2, 0, 2]` a second time!
   - **Rule 2**: After recording a match, increment `left` while `nums[left] == nums[left - 1]`, and decrement `right` while `nums[right] == nums[right + 1]`.

### 4. Bonus Observation — Early Pruning

In a sorted array, `nums[i] <= nums[left] <= nums[right]`.
What if `nums[i] > 0`?
Then all three numbers are strictly positive (`0 < nums[i] <= nums[left] <= nums[right]`), so their sum is strictly greater than `0`. Not only can the current `i` never form a zero-sum triplet, **no future `i` can either**!

- **Rule 3**: If `nums[i] > 0`, `break` out of the outer loop immediately.

### 5. Complete Manual Trace on `nums = [-1, 0, 1, 2, -1, -4]`

```text
Step 0: Sort the array
  nums = [-4, -1, -1,  0,  1,  2]
           0   1   2   3   4   5

──────────────────────────────────────────────────────────
Outer i = 0 (nums[0] = -4):
  left = 1 (-1), right = 5 (2) → sum = -4 + (-1) + 2 = -3 < 0 → left++
  left = 2 (-1), right = 5 (2) → sum = -4 + (-1) + 2 = -3 < 0 → left++
  left = 3 ( 0), right = 5 (2) → sum = -4 +   0  + 2 = -2 < 0 → left++
  left = 4 ( 1), right = 5 (2) → sum = -4 +   1  + 2 = -1 < 0 → left++
  left = 5 == right → inner loop ends.

──────────────────────────────────────────────────────────
Outer i = 1 (nums[1] = -1):
  left = 2 (-1), right = 5 (2)
    sum = -1 + (-1) + 2 = 0  ✓  Record [-1, -1, 2]
    Advance: left = 3 (0), right = 4 (1)
  left = 3 ( 0), right = 4 (1)
    sum = -1 + 0 + 1 = 0     ✓  Record [-1, 0, 1]
    Advance: left = 4, right = 3 → left >= right → inner loop ends.

──────────────────────────────────────────────────────────
Outer i = 2 (nums[2] = -1):
  nums[2] == nums[1] (-1 == -1) → SKIP (continue)!

──────────────────────────────────────────────────────────
Outer i = 3 (nums[3] = 0):
  left = 4 (1), right = 5 (2) → sum = 0 + 1 + 2 = 3 > 0 → right--
  left = 4 == right → inner loop ends.

──────────────────────────────────────────────────────────
Outer i = 4 (nums[4] = 1):
  nums[4] > 0 → BREAK early!

Final Result: [[-1, -1, 2], [-1, 0, 1]]
```

### 6. Questions an Interviewer Expects You to Ask

1. _"Can I modify the input array in-place (by sorting it), or must the input array remain read-only?"_
   - Usually yes. If the interviewer says the input is `const` and cannot be modified, you can either copy it ($O(N)$ space) or use the Hash Set approach.
2. _"Does the order of triplets or the order of numbers inside each triplet matter?"_
   - No, any order is accepted.
3. _"What are the bounds on `nums[i]`? Do we need to worry about 32-bit `int` overflow when summing three elements?"_
   - Here `|nums[i]| <= 10^5`, so `int` is safe, unlike 4Sum where values reach `10^9` and require `long long`. Asking this proactively shows strong production engineering habits.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Triple Loop with Set (Brute Force)

- **Type**: Brute Force
- **Time**: $O(N^3 \log U)$ (where $U$ is the number of unique triplets)
- **Space**: $O(U)$ auxiliary (for `std::set`), $O(U)$ output
- Exhaustively checks every index triplet `(i, j, k)`, sorts each matching 3-element triplet, and inserts it into a `std::set<vector<int>>` to remove duplicates.
- 📄 [Approach 1 — Triple Loop with Set (Brute Force).md](<./approaches/Approach 1 — Triple Loop with Set (Brute Force).md>)
- 💻 [Approach 1 — Triple Loop with Set (Brute Force).cpp](<./approaches/Approach 1 — Triple Loop with Set (Brute Force).cpp>)

### Approach 2 — Fix One + Hash Set (Baseline)

- **Type**: Baseline
- **Time**: $O(N^2)$
- **Space**: $O(N)$ auxiliary (for the `unordered_set`), $O(U)$ output
- Sorts the array to skip duplicate `i` values easily, then for each fixed `nums[i]`, runs a single-pass `unordered_set` Two Sum over `j > i` to find complements `-(nums[i] + nums[j])`.
- 📄 [Approach 2 — Fix One + Hash Set (Baseline).md](<./approaches/Approach 2 — Fix One + Hash Set (Baseline).md>)
- 💻 [Approach 2 — Fix One + Hash Set (Baseline).cpp](<./approaches/Approach 2 — Fix One + Hash Set (Baseline).cpp>)

### Approach 3 — Sort + Two Pointers (Optimized)

- **Type**: Optimized
- **Time**: $O(N^2)$
- **Space**: $O(\log N)$ auxiliary (stack space for `std::sort`; $O(1)$ extra beyond sorting), $O(U)$ output
- Sorts the array once, fixes `nums[i]` with early positive-value pruning, and sweeps converging `left` and `right` pointers across `[i + 1 .. N - 1]` while skipping adjacent duplicates in-place.
- 📄 [Approach 3 — Sort + Two Pointers (Optimized).md](<./approaches/Approach 3 — Sort + Two Pointers (Optimized).md>)
- 💻 [Approach 3 — Sort + Two Pointers (Optimized).cpp](<./approaches/Approach 3 — Sort + Two Pointers (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Sort + Fix One + Converging Two Pointers ($k$-Sum Reduction Pattern)**:
When asked to find unique tuples of size $k$ that satisfy a sum condition, sort the array in $O(N \log N)$, fix $k - 2$ elements using nested loops with adjacent duplicate skipping (`nums[idx] == nums[idx - 1]`), and solve the innermost 2-element problem in $O(N)$ time and $O(1)$ space using converging two pointers.

### 2. Mental Model

> _"Whenever you see an unsorted array problem asking for **values** (not original indices) of triplets/quadruplets that sum to a target — and $N \le 3000$ allows $O(N^2)$ — **sort first**. Sorting is free under $O(N^2)$, makes two-pointer search $O(1)$-space, and turns deduplication into a simple neighbor check."_

### 3. Memorization vs Understanding

**MUST REMEMBER**:

- Outer duplicate skip: `if (i > 0 && nums[i] == nums[i - 1]) continue;` (always compare with `i - 1`, **never** `i + 1`).
- Inner duplicate skip (only after finding a valid sum):
  ```cpp
  left++; right--;
  while (left < right && nums[left] == nums[left - 1]) left++;
  while (left < right && nums[right] == nums[right + 1]) right--;
  ```
- Early termination: `if (nums[i] > 0) break;` (in a sorted array, three positive numbers cannot sum to 0).

**SHOULD UNDERSTAND**:

- Why `nums[i] == nums[i - 1]` works without losing triplets like `[-1, -1, 2]`: at the _first_ `-1` (`i = 1`), `left` starts at `i + 1 = 2` (the _second_ `-1`), so `[-1, -1, 2]` is already discovered during the first `-1`'s iteration!
- Why converging two pointers never miss a valid `(left, right)` pair (monotonic elimination of rows/columns in the 2D pair matrix).

**SHOULD BE ABLE TO RE-DERIVE**:

- How to generalize this exact structure to **4Sum** (add one more outer loop `j` from `i + 1`, skip `j > i + 1 && nums[j] == nums[j - 1]`, and use `long long` for the sum) or **$k$-Sum** via recursion.

### 4. Previously Seen Patterns (Cross-Reference)

1. **[Problem 01 — Two Sum (LC 1)](../../Phase_1_Foundation/01_two_sum_1/)**:
   - You used an `unordered_map` to find `complement = target - nums[j]` in $O(N)$ time.
   - **Approach 2** of 3Sum directly reuses that exact complement-lookup idea inside an outer loop (`target = -nums[i]`).
   - **Key difference**: Two Sum asked for _original indices_ (preventing in-place value sorting) and guaranteed _exactly one answer_ (no deduplication needed). 3Sum asks for _unique value triplets_, which makes sorting + two pointers superior to hashing.
2. **[Problem 02 — Container With Most Water (LC 11)](../../Phase_1_Foundation/02_container_with_most_water_11/)**:
   - You used **converging `left` and `right` pointers** starting at opposite ends of the array and moving inward based on a greedy elimination rule.
   - **Approach 3** of 3Sum uses the same converging pointer mechanics on the sorted subarray `[i + 1 .. N - 1]`, eliminating an entire row or column of pairs each time `sum < 0` (`left++`) or `sum > 0` (`right--`).

### 5. Related LeetCode Problems

| Problem                                                                                                        | Why It Is Directly Related                                                                                                                                   |
| :------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [LC 167 — Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Literally the inner `while (left < right)` loop of Approach 3 in isolation.                                                                                  |
| [LC 16 — 3Sum Closest](https://leetcode.com/problems/3sum-closest/)                                            | Identical Sort + Fix `i` + Two Pointers template; instead of collecting `sum == 0`, track the sum that minimizes `abs(target - sum)`.                        |
| [LC 259 — 3Sum Smaller](https://leetcode.com/problems/3sum-smaller/)                                           | Same template; when `nums[i] + nums[left] + nums[right] < target`, all indices from `left + 1` to `right` are automatically valid (`count += right - left`). |
| [LC 18 — 4Sum](https://leetcode.com/problems/4sum/)                                                            | Direct extension: fix `i` and `j`, then run the same converging two pointers (`left`, `right`) with `long long` overflow protection.                         |
| [LC 611 — Valid Triangle Number](https://leetcode.com/problems/valid-triangle-number/)                         | Sort + Fix the largest side `c = nums[k]`, then use converging two pointers to count pairs with `a + b > c`.                                                 |

### 6. Interview Questions

1. **Q**: _"Why is Sort + Two Pointers preferred over the Hash Set approach in interviews when both have $O(N^2)$ time complexity?"_
   - **A**: Three reasons: (1) **Auxiliary Space** drops from $O(N)$ to $O(\log N)$ (or $O(1)$ beyond sorting), (2) **Cache Locality & Constant Factor**: sequential array access with `left++`/`right--` is 5–10x faster on modern CPUs than hashing and heap-allocating `unordered_set` nodes, and (3) **Cleaner Deduplication** via pointer skipping.
2. **Q**: _"What if the interviewer forbids modifying the input array AND forbids copying the array (strict $O(1)$ space, read-only input)?"_
   - **A**: You cannot sort in-place or use an $O(N)$ hash set, so you would fall back to $O(N^3)$ brute force (checking before emitting whether the triplet's values appeared at earlier indices). That's why interviewers either allow sorting `nums` (or a copy of `nums`) or allow $O(N)$ auxiliary space.
3. **Q**: _"Can 3Sum be solved in strictly sub-quadratic time, like $O(N^{1.5})$?"_
   - **A**: In the standard comparison/RAM model with arbitrary integers, the **3SUM conjecture** in theoretical computer science states that 3Sum requires $\Omega(N^2)$ time (ignoring polylogarithmic bit-trick/FFT speedups for bounded integer ranges). So $O(N^2)$ is asymptotically optimal for general inputs.

### 7. Leftover Important Details

- **Even Tighter Pruning in the Outer Loop**:
  Besides `if (nums[i] > 0) break;`, you can also check:
  - `if (nums[i] + nums[i + 1] + nums[i + 2] > 0) break;` (even the three smallest available elements exceed 0 $\rightarrow$ stop immediately).
  - `if (nums[i] + nums[n - 2] + nums[n - 1] < 0) continue;` (`nums[i]` is so negative that even pairing it with the two largest elements in the entire array can't reach 0 $\rightarrow$ skip this `i` immediately in $O(1)$!).
- **`std::sort` Auxiliary Space Nuance**:
  C++'s `std::sort` uses **Introsort** (a hybrid of Quicksort, Heapsort, and Insertion Sort), which uses $O(\log N)$ recursion stack space. In an interview, always state: _"Auxiliary space is $O(1)$ beyond the $O(\log N)$ stack space used by `std::sort`, excluding the output vector."_

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
