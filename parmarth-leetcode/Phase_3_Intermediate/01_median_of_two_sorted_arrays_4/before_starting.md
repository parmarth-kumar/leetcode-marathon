Problem      : Median of Two Sorted Arrays
LeetCode     : https://leetcode.com/problems/median-of-two-sorted-arrays/
Topic        : Array, Binary Search, Divide and Conquer
Difficulty   : Hard
Google-Tagged: Yes
Phase        : 3 — Intermediate
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given two sorted arrays `nums1` and `nums2` of sizes `m` and `n` respectively. Return the **median** of the combined sorted array formed by merging both arrays.

The overall run time complexity should be **O(log(m + n))**.

### Input & Output

- **Input**: Two sorted (non-decreasing) integer arrays `nums1` and `nums2`.
- **Output**: A single `double` — the median of the combined sorted array.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `0 <= m, n <= 1000` | Either array CAN be empty |
| `1 <= m + n <= 2000` | At least one element exists; total up to 2000 |
| `-10^6 <= nums1[i], nums2[j] <= 10^6` | Negative values; no overflow risk with `int` |
| **Required: O(log(m+n))** | Merging (O(m+n)) is too slow for the optimal ask — must use binary search |

**CPU intuition**: With `m + n ≤ 2000`, even O(N²) passes in practice. But the problem *explicitly* asks for O(log(m+n)), meaning the interviewer expects binary search.

### Terminology

- **Median**: The middle value when all elements are arranged in sorted order.
  - If the total count is **odd**, the median is the single middle element.
  - If the total count is **even**, the median is the **average** of the two middle elements.
- **Sorted array**: Elements arranged in non-decreasing order.
- **Partition**: Dividing an array into a left half and a right half at some index.

### Worked Examples

**Example 1** — Odd total length:
```
nums1 = [1, 3]
nums2 = [2]

Merged = [1, 2, 3]
          ^  ^  ^
          0  1  2

Total = 3 (odd) → median = element at index 1 = 2.0
```

**Example 2** — Even total length:
```
nums1 = [1, 2]
nums2 = [3, 4]

Merged = [1, 2, 3, 4]
          ^  ^  ^  ^
          0  1  2  3

Total = 4 (even) → median = (element[1] + element[2]) / 2 = (2 + 3) / 2 = 2.5
```

**Example 3** — One empty array:
```
nums1 = []
nums2 = [1]

Merged = [1]

Total = 1 (odd) → median = 1.0
```

**Example 4** — Disjoint ranges:
```
nums1 = [1, 2]
nums2 = [3, 4, 5, 6]

Merged = [1, 2, 3, 4, 5, 6]
          0  1  2  3  4  5

Total = 6 (even) → median = (element[2] + element[3]) / 2 = (3 + 4) / 2 = 3.5
```

**Example 5** — Interleaved:
```
nums1 = [1, 5, 9]
nums2 = [2, 6, 10]

Merged = [1, 2, 5, 6, 9, 10]

Total = 6 (even) → median = (5 + 6) / 2 = 5.5
```

### Common Beginner Traps

1. **Integer division**: `(a + b) / 2` with `int a, b` truncates. Must cast to `double`.
2. **Forgetting empty arrays**: `nums1` or `nums2` can be empty — accessing `nums1[0]` without checking causes UB.
3. **Off-by-one in median index**: For `n` total elements, the median indices are `(n-1)/2` and `n/2`.
4. **Assuming equal lengths**: The two arrays can have very different sizes.
5. **Not meeting the time constraint**: Merging is O(m+n), not O(log(m+n)).

### One-Sentence Restatement

> Given two sorted arrays, find the median of their union in O(log(min(m, n))) time by binary-searching for the correct partition point.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Median of a Sorted Sequence

**What it is**: The value separating the higher half from the lower half of a sorted dataset.

**Mechanics**:
- For `n` elements (0-indexed): if `n` is odd, median = `arr[n/2]`. If `n` is even, median = `(arr[n/2 - 1] + arr[n/2]) / 2.0`.

**Example**:
```
[1, 3, 5, 7, 9] → n=5 (odd) → median = arr[2] = 5
[1, 3, 5, 7]     → n=4 (even) → median = (arr[1] + arr[2]) / 2.0 = 4.0
```

**Why it matters here**: The entire problem is about finding this value — but without actually merging the arrays.

### 2. Binary Search on Answer / Search Space

**What it is**: Instead of searching for a target value in a sorted array, you binary search over a *range of possible answers* (or partition points), eliminating half the candidates each iteration.

**Mechanics**:
- Define a `low` and `high` for your search space.
- Compute `mid`, test a condition, then narrow `low` or `high`.
- Each step halves the search space → O(log N).

**Example**: Finding the partition point `i` in `nums1` such that `i ∈ [0, m]`:
```
low = 0, high = m
mid = (low + high) / 2
Test condition → adjust low or high
```

**Why it matters here**: We binary search over the partition index of the smaller array to find where to "cut" both arrays so the left halves form the correct lower half of the merged result.

### 3. Array Partitioning

**What it is**: Splitting an array at index `i` means elements `[0..i-1]` go to the left half and `[i..n-1]` go to the right half.

**Mechanics**:
- If you take `i` elements from `nums1`, you need `half - i` elements from `nums2` (where `half = (m + n + 1) / 2`).
- The partition is valid when: `maxLeft1 <= minRight2` AND `maxLeft2 <= minRight1`.

**Why it matters here**: This is the core insight — instead of merging, we search for the correct partition.

### 4. Sentinel Values (±∞)

**What it is**: Using `INT_MIN` and `INT_MAX` as boundary sentinels when a partition leaves one side empty.

**Mechanics**:
- If `i = 0` (no elements from `nums1` on the left), set `maxLeft1 = INT_MIN` (it should never block a valid partition).
- If `i = m` (all elements from `nums1` on the left), set `minRight1 = INT_MAX`.

**Why it matters here**: Edge cases where the partition sits at the boundary of an array.

### 5. Merge Sort Merge Step (for the baseline approach)

**What it is**: The merge operation from merge sort — combining two sorted sequences into one sorted sequence in O(m + n).

**Mechanics**: Two pointers, one per array. Compare, pick the smaller, advance that pointer.

**Why it matters here**: The brute-force / baseline approach merges then picks the median.

---

> 🛑 **STOP HERE AND ATTEMPT THE PROBLEM FIRST.**
>
> Open `test_harness.cpp`, write your solution inside the empty `Solution` class, compile, and test it against the provided edge cases.
>
> Only open the sections below if you are stuck or want to compare after solving.

---

<details>
<summary>🔍 Layer 3 — How To Think Through The Problem (click to reveal)</summary>

### Starting Observation

The median splits the merged array into two equal halves (or halves differing by 1). If we could find the correct "cut" in both arrays such that:
- Every element in the left halves ≤ every element in the right halves
- The left halves contain exactly `⌈(m+n)/2⌉` elements combined

...then we can compute the median directly from the boundary elements.

### Step-by-Step Reasoning

**Step 1 — Think about what the median means structurally**:
```
Merged: [... left half ... | ... right half ...]
                           ^
                        median boundary

Left half has ⌈(m+n)/2⌉ elements.
Right half has ⌊(m+n)/2⌋ elements.
```

**Step 2 — Each array contributes some elements to each half**:
```
nums1: [  left1  |  right1  ]    takes i elements for left half
nums2: [  left2  |  right2  ]    takes j elements for left half

where i + j = ⌈(m+n)/2⌉, so j = ⌈(m+n)/2⌉ - i
```

**Step 3 — What makes a partition "correct"?**

Since both arrays are individually sorted, we only need to check the cross-boundaries:
```
maxLeft1 ≤ minRight2   (largest from nums1's left ≤ smallest from nums2's right)
maxLeft2 ≤ minRight1   (largest from nums2's left ≤ smallest from nums1's right)
```

If both hold, the partition is valid.

**Step 4 — Binary search on the partition index `i`**:

- If `maxLeft1 > minRight2`: we took too many from `nums1` → decrease `i` (move `high` left).
- If `maxLeft2 > minRight1`: we took too few from `nums1` → increase `i` (move `low` right).
- Otherwise: correct partition found.

**Step 5 — Always binary search on the SMALLER array**:

Searching over `i ∈ [0, m]` where `m = min(m, n)` gives O(log(min(m, n))) ⊆ O(log(m + n)).

### Visual Trace (Example 2)

```
nums1 = [1, 2]     m = 2
nums2 = [3, 4]     n = 2
half = (2 + 2 + 1) / 2 = 2

Binary search on nums1 (smaller array, m=2):
low=0, high=2

Iteration 1: i = (0+2)/2 = 1
             j = 2 - 1 = 1
  nums1: [1 | 2]       maxLeft1 = 1,  minRight1 = 2
  nums2: [3 | 4]       maxLeft2 = 3,  minRight2 = 4
  Check: maxLeft1(1) ≤ minRight2(4) ✓
         maxLeft2(3) ≤ minRight1(2) ✗  →  3 > 2, need more from nums1
  Move: low = i + 1 = 2

Iteration 2: i = (2+2)/2 = 2
             j = 2 - 2 = 0
  nums1: [1, 2 | ]     maxLeft1 = 2,  minRight1 = +∞
  nums2: [ | 3, 4]     maxLeft2 = -∞, minRight2 = 3
  Check: maxLeft1(2) ≤ minRight2(3) ✓
         maxLeft2(-∞) ≤ minRight1(+∞) ✓  → FOUND!

  Total even → median = (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0
            = (max(2, -∞) + min(+∞, 3)) / 2.0
            = (2 + 3) / 2.0 = 2.5 ✓
```

### Questions an Interviewer Expects You to Ask

1. "Can either array be empty?" → Yes.
2. "Can they have duplicate values?" → Yes.
3. "Is it guaranteed that at least one element exists?" → Yes (`1 ≤ m + n`).
4. "When you say O(log(m+n)), is O(log(min(m,n))) acceptable?" → Yes, it's strictly better.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Merge and Pick (Brute Force)

- **Type**: Brute Force
- **Time**: O(m + n)
- **Space**: O(m + n) output (merged array), O(1) auxiliary
- Merge both arrays using two pointers, then directly index the median.
- 📄 [Approach 1 — Merge and Pick (Brute Force).md](<./approaches/Approach 1 — Merge and Pick (Brute Force).md>)
- 💻 [Approach 1 — Merge and Pick (Brute Force).cpp](<./approaches/Approach 1 — Merge and Pick (Brute Force).cpp>)

### Approach 2 — Binary Search Partition (Optimized)

- **Type**: Optimized
- **Time**: O(log(min(m, n)))
- **Space**: O(1) auxiliary
- Binary search for the correct partition point on the smaller array; compute the median from boundary elements without merging.
- 📄 [Approach 2 — Binary Search Partition (Optimized).md](<./approaches/Approach 2 — Binary Search Partition (Optimized).md>)
- 💻 [Approach 2 — Binary Search Partition (Optimized).cpp](<./approaches/Approach 2 — Binary Search Partition (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Binary Search on Partition / Binary Search on Answer**: Instead of processing the data linearly, define a search space (partition indices) and use binary search to find the correct split in O(log N).

### 2. Mental Model

> "Whenever you see two sorted arrays and need a positional statistic (median, k-th element), think **binary search on partition** — cut both arrays so the left sides contain exactly the right number of elements, and validate the cross-boundaries."

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- The formula: `j = half - i` where `half = (m + n + 1) / 2`
- The validity condition: `maxLeft1 ≤ minRight2` AND `maxLeft2 ≤ minRight1`
- Always binary search on the smaller array
- Use `INT_MIN` / `INT_MAX` as sentinels for empty partitions

**SHOULD UNDERSTAND**:
- Why the partition approach works (the median splits merged array into two equal halves)
- Why we only need to check cross-boundaries (within-array order is guaranteed by sortedness)
- How the binary search narrows: too many from A → decrease, too few → increase

**SHOULD BE ABLE TO RE-DERIVE**:
- The median formula from boundary elements (odd: `max(left1, left2)`, even: average with `min(right1, right2)`)
- Why O(log(min(m,n))) and not O(log(m+n)) — searching on the smaller array

### 4. Previously Seen Patterns (Cross-Reference)

You saw **binary search** logic in Phase 3 for the first time here. The **two-pointer merge** from Approach 1 is the same merge technique you may recognize from any merge-based problem.

### 5. Related LeetCode Problems

| Problem | Why Related |
|:--------|:------------|
| [LC 295 — Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | Median maintenance with streaming data; uses heaps instead of binary search |
| [LC 34 — Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | Binary search on sorted array — foundational binary search practice |
| [LC 33 — Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | Binary search with modified conditions on a sorted structure |
| [LC 215 — Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | Positional statistic (k-th element); uses quickselect or heap |
| [LC 378 — Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) | Binary search on answer space to find k-th element in a structured dataset |

### 6. Interview Questions

1. "Walk me through why you binary search on the smaller array." → Reduces the search space from O(log(m+n)) to O(log(min(m,n))).
2. "What happens when one array is empty?" → The partition takes 0 elements from it; sentinels handle the boundary.
3. "Can you extend this to find the k-th element instead of the median?" → Yes, set `half = k` instead of `(m+n+1)/2`.
4. "What's the time complexity if you just merged and picked?" → O(m+n), which doesn't meet the requirement.
5. "Why not use the `nth_element` or partial sort approach?" → Those require random access into a single container and are O(N) average, not O(log N).

### 7. Leftover Important Details

- The `(m + n + 1) / 2` formula (with `+1`) ensures the left half gets the extra element when total is odd — this makes the odd-case formula cleaner (`max(maxLeft1, maxLeft2)` is the median).
- Even though the constraint says O(log(m+n)), the optimal solution is actually O(log(min(m,n))) — strictly better.
- This problem is a classic Google interview question. Expect follow-ups about k-th smallest element.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
