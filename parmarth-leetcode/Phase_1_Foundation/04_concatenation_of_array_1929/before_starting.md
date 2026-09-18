Problem      : Concatenation of Array
LeetCode     : https://leetcode.com/problems/concatenation-of-array/
Topic        : Array, Simulation
Difficulty   : Easy
Google-Tagged: No
Phase        : 1 — Foundation
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given an integer array `nums` of length `n`. You need to build and return a new array `ans` of length `2n` that consists of two complete copies of `nums` placed one right after the other in their original left-to-right order.

Specifically, for every index `i` (`0 <= i < n`):
- `ans[i] == nums[i]` (first copy)
- `ans[i + n] == nums[i]` (second copy)

Return the array `ans` without rearranging or modifying the input array.

### Input & Output

- **Input**: An integer array `nums` of length `n`.
- **Output**: A new integer array `ans` of length `2n` representing the concatenation of `nums` with itself.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `n == nums.length` | Let `n` denote the number of elements in the input array |
| `1 <= n <= 1000` | The input is never empty; output size `2n` is at most `2000` elements |
| `1 <= nums[i] <= 1000` | All values are positive integers that easily fit inside a standard 32-bit `int` |

**CPU intuition**: A modern CPU performs roughly `10^8` operations per second. With `n <= 1000`, writing `2n <= 2000` integers takes a fraction of a microsecond. Furthermore, because the problem requires returning an array of `2n` elements, any valid algorithm must perform at least `2n` writes — meaning `Ω(n)` time and `O(n)` output space is the theoretical lower bound.

### Terminology

- **Concatenation**: Joining two sequences end-to-end so the second sequence starts immediately after the first ends. For arrays, `[a, b]` concatenated with `[a, b]` is `[a, b, a, b]` (NOT element-wise addition `[2a, 2b]`).
- **0-Indexed**: The first copy occupies indices `0` to `n - 1`, and the second copy occupies indices `n` to `2n - 1`.
- **Offset (`+ n`)**: Because the first copy has length `n`, every element at index `i` in the first copy appears at index `i + n` in the second copy.

### Worked Examples

**Example 1** — Standard three-element array with duplicates:
```text
nums = [1, 2, 1]   (n = 3)

First copy  (indices 0..2): [1, 2, 1]
Second copy (indices 3..5): [1, 2, 1]

ans  = [1, 2, 1, 1, 2, 1]
idx:    0  1  2  3  4  5
```

**Example 2** — Four-element array:
```text
nums = [1, 3, 2, 1]   (n = 4)

First copy  (indices 0..3): [1, 3, 2, 1]
Second copy (indices 4..7): [1, 3, 2, 1]

ans  = [1, 3, 2, 1, 1, 3, 2, 1]
idx:    0  1  2  3  4  5  6  7
```

**Example 3** — Minimum length (`n = 1`):
```text
nums = [7]   (n = 1)

First copy  (index 0): [7]
Second copy (index 1): [7]

ans  = [7, 7]
idx:    0  1
```

**Example 4** — All identical elements:
```text
nums = [5, 5, 5]   (n = 3)

ans  = [5, 5, 5, 5, 5, 5]
idx:    0  1  2  3  4  5
```

### Common Beginner Traps

1. **Adding instead of concatenating**: `[1, 2]` concatenated with itself is `[1, 2, 1, 2]`, NOT `[2, 4]`.
2. **Interleaving elements**: Duplicating each element adjacent to itself (`[1, 1, 2, 2]`) is interleaving, not concatenation.
3. **Reversing the second half**: Both halves follow the exact same left-to-right order (`[1, 2, 3, 1, 2, 3]`, NOT `[1, 2, 3, 3, 2, 1]`).
4. **Off-by-one in the offset**: For source index `i`, the second copy sits at `i + n`, NOT `i + n - 1` or `2 * i`.
5. **Appending to `nums` while iterating over `nums.size()`**: If you loop `for (int i = 0; i < nums.size(); i++) nums.push_back(nums[i]);`, `nums.size()` grows on every iteration, creating an infinite loop (and potential iterator/reference invalidation).

### One-Sentence Restatement

> Given an array `nums` of length `n`, return a new array of length `2n` consisting of two consecutive, identical copies of `nums`.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Dynamic Arrays (`std::vector<int>`)

**What it is**: C++'s standard contiguous, dynamically resizable array container.

**Mechanics**:
- `nums.size()` returns the number of elements (`n`).
- `ans.push_back(x)` appends `x` to the end of `ans`. If `ans` runs out of internal capacity, it allocates a larger memory block (typically `2x` capacity) and copies existing elements over, taking `O(1)` amortized time per append.
- `vector<int> ans(2 * n)` pre-allocates a vector of exact length `2n` (zero-initialized), allowing direct index assignment (`ans[i] = ...`) with zero reallocations.

**Example**:
```cpp
int n = 3;
vector<int> ans(2 * n); // Creates [0, 0, 0, 0, 0, 0] of size 6
ans[0] = 10;
ans[0 + n] = 10;        // Sets ans[3] = 10
```

**Why it matters here**: Understanding the difference between dynamic growth (`push_back`) and pre-sized direct indexing (`vector<int> ans(2 * n)`) is the exact distinction between the Baseline and Optimized approaches.

### 2. Fixed-Offset Index Mapping

**What it is**: Computing destination positions in an output array directly from the source index `i` and block size `n`.

**Mechanics**:
```text
Source index:         0     1     2   ...   n-1
First copy index:     0     1     2   ...   n-1      (i)
Second copy index:    n    n+1   n+2  ...  2n-1      (i + n)
```

**Why it matters here**: Because every input element `nums[i]` maps deterministically to indices `i` and `i + n`, we can populate both halves simultaneously in a single `0 .. n-1` loop.

### 3. Output Space vs. Auxiliary Space

**What it is**:
- **Output space**: Memory required to hold the return value mandated by the problem signature (`vector<int>` of size `2n`).
- **Auxiliary space**: Extra temporary working memory used by the algorithm beyond the input and required output.

**Why it matters here**: Both approaches return a vector of size `2n` (`O(n)` output space) and use only a few `int` loop variables (`O(1)` auxiliary space). Knowing this distinction prevents confusion in interviews when asked about space complexity.

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

Look at the relationship between the input array and the output array:
- The output array always has length `2n`, which is completely known before we inspect a single element.
- Every element `nums[i]` appears twice in the output: once in the first half (`0 .. n-1`) and once in the second half (`n .. 2n-1`).

### Manual Simulation & Naive Thought Process

If you had to do this by hand with a blank sheet of paper for `nums = [4, 8]`:
1. **Two-Pass Mental Model (Baseline)**: Read `[4, 8]` from left to right and write `4, 8`. Then go back to the start of `[4, 8]`, read it a second time, and write `4, 8` after what you already wrote.
   ```text
   Pass 1: append 4 -> [4], append 8 -> [4, 8]
   Pass 2: append 4 -> [4, 8, 4], append 8 -> [4, 8, 4, 8]
   ```
2. **Single-Pass Mental Model (Optimized)**: Draw `2n = 4` empty boxes first: `[ _, _, _, _ ]`. Now read each element of `nums` only once and write it into both its first-half box and its second-half box at the same time!

### Discovering the Single-Pass Optimization

Ask two questions:
1. *"Do I know the exact size of the output array upfront?"* → Yes, `2 * n`. So we can pre-size `ans` to `2 * n` and avoid any dynamic vector resizing.
2. *"When I am at index `i` of `nums`, where do both copies of `nums[i]` belong?"* → At index `i` and index `i + n`.

### Visual Trace of Direct Index Mapping (`nums = [5, 6, 7]`, `n = 3`)

```text
Pre-allocate ans of size 2 * 3 = 6:
ans = [ _, _, _, _, _, _ ]
idx:    0  1  2  3  4  5

i = 0 (nums[0] = 5): write to ans[0] and ans[0 + 3 = 3]
ans = [ 5, _, _, 5, _, _ ]

i = 1 (nums[1] = 6): write to ans[1] and ans[1 + 3 = 4]
ans = [ 5, 6, _, 5, 6, _ ]

i = 2 (nums[2] = 7): write to ans[2] and ans[2 + 3 = 5]
ans = [ 5, 6, 7, 5, 6, 7 ]
```

Notice that when `i = n - 1` (the last valid input index), the second write goes to `(n - 1) + n = 2n - 1`, which is the exact last valid index of `ans`. Every slot is written once, and each `nums[i]` is read from memory only once.

### Questions an Interviewer Expects You to Ask

1. *"Am I allowed to modify the input vector `nums` in-place, or should `nums` remain unchanged?"* → Usually leave the input unmodified and return a new vector unless the interviewer explicitly asks for in-place modification.
2. *"Does the space complexity requirement count the returned output vector?"* → Standard convention separates `O(n)` output space from `O(1)` auxiliary space.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Two-Pass Push Back (Baseline)

- **Type**: Baseline
- **Time**: `O(N)`
- **Space**: `O(1)` auxiliary, `O(N)` output
- Start with an empty result vector and iterate through `nums` twice, appending every element in order during each pass.
- 📄 [Approach 1 — Two-Pass Push Back (Baseline).md](<./approaches/Approach 1 — Two-Pass Push Back (Baseline).md>)
- 💻 [Approach 1 — Two-Pass Push Back (Baseline).cpp](<./approaches/Approach 1 — Two-Pass Push Back (Baseline).cpp>)

### Approach 2 — Single-Pass Direct Indexing (Optimized)

- **Type**: Optimized
- **Time**: `O(N)`
- **Space**: `O(1)` auxiliary, `O(N)` output
- Pre-allocate a result vector of size `2N` and set `ans[i] = ans[i + n] = nums[i]` in a single pass with zero reallocations.
- 📄 [Approach 2 — Single-Pass Direct Indexing (Optimized).md](<./approaches/Approach 2 — Single-Pass Direct Indexing (Optimized).md>)
- 💻 [Approach 2 — Single-Pass Direct Indexing (Optimized).cpp](<./approaches/Approach 2 — Single-Pass Direct Indexing (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Pre-Sized Array Construction & Fixed-Offset Index Mapping**: When building a new array of a known size where each input element maps to fixed target positions, pre-allocate the output array once and write directly to the calculated indices (`i` and `i + n`).

### 2. Mental Model

> "Whenever you see a problem asking you to repeat, tile, or rearrange an array into an output of known size, **write down the index mapping formula (`dest = f(i, n)`) and pre-allocate the result vector** instead of repeatedly appending."

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- `vector<int> ans(2 * n)` allocates `2n` elements upfront so `ans[i]` and `ans[i + n]` are valid indices immediately.
- Calling `ans[i]` on an **empty** `vector<int> ans;` (even after `ans.reserve(2 * n)`) is undefined behavior because `size()` is still `0`.
- Distinguish `O(N)` **output space** from `O(1)` **auxiliary space**.

**SHOULD UNDERSTAND**:
- Why `push_back` without `reserve` triggers `O(log N)` buffer reallocations, whereas pre-sizing allocates heap memory only once.
- Why `Ω(N)` time is a strict lower bound (you must write `2N` elements to return the answer).

**SHOULD BE ABLE TO RE-DERIVE**:
- If asked to concatenate `k` copies of `nums`, pre-allocate `k * n` elements and write `nums[i]` to `ans[i + c * n]` for `0 <= c < k`.

### 4. Previously Seen Patterns (Cross-Reference)

In **Problem 01 — Two Sum**, **Problem 02 — Container With Most Water**, and **Problem 03 — Longest Palindromic Substring**, you used 0-based array indexing to inspect relationships between elements. Here, you use 0-based index arithmetic (`i` and `i + n`) for **direct constructive mapping** into a pre-sized output array — a foundational building block for circular arrays (where concatenating an array with itself `nums + nums` is a classic trick to flatten wrap-around subarrays!).

### 5. Related LeetCode Problems

| Problem | Why Related |
|:--------|:------------|
| [LC 1920 — Build Array from Permutation](https://leetcode.com/problems/build-array-from-permutation/) | Direct index mapping where `ans[i] = nums[nums[i]]` on a pre-sized array |
| [LC 1470 — Shuffle the Array](https://leetcode.com/problems/shuffle-the-array/) | Maps first half `nums[i]` and second half `nums[i + n]` to interleaved output indices `2*i` and `2*i + 1` |
| [LC 1480 — Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/) | Single-pass array construction and prefix state propagation |
| [LC 503 — Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) | Uses the exact conceptual `nums + nums` (`2n` length, `i + n` / `i % n`) trick to handle a circular array |

### 6. Interview Questions

1. *"Both approaches are `O(N)` time and `O(N)` space. Why is Approach 2 considered better in C++?"* → Approach 2 performs a single heap allocation (`2 * n` ints), reads `nums` once (better cache locality), and never checks capacity or reallocates during the loop.
2. *"What is the difference between `ans.reserve(2 * n)` and `vector<int> ans(2 * n)`?"* → `reserve(2 * n)` allocates raw capacity while keeping `size() == 0` (must still use `push_back`), whereas `ans(2 * n)` sets `size() == 2 * n` and zero-initializes elements (allowing `ans[i] = ...`).
3. *"Where does concatenating an array with itself show up in harder interview problems?"* → Circular array problems! Doubling an array (`ans[i] = ans[i + n] = nums[i]`) turns any wrap-around circular subarray of length `<= n` into a standard contiguous subarray.

### 7. Leftover Important Details

- If you modify `nums` in-place via `nums.insert(nums.end(), nums.begin(), nums.end())`, be careful: in older C++ or naive implementations, inserting a range from a vector into itself can invalidate iterators if reallocation happens mid-insert (`std::vector::insert` handles self-range safely in modern standard libraries only when reserving first or via internal buffer handling, so pre-allocating `ans(2 * n)` is always cleaner and safer).

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
