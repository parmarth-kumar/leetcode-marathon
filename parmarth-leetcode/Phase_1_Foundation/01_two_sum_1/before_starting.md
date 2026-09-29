Problem      : Two Sum
LeetCode     : https://leetcode.com/problems/two-sum/
Topic        : Array / Hash Table
Difficulty   : Easy
Google-Tagged: Yes
Phase        : 1 — Foundation
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given an array of integers `nums` and a single integer `target`. Your job is to find **two distinct positions (indices)** `i` and `j` in the array such that the numbers at those positions add up to `target` (`nums[i] + nums[j] == target`), and return those two indices.

You are guaranteed that **exactly one valid answer exists**, and you may **not** use the same array element twice (`i != j`). You may return the two indices in any order.

### Input & Output

- **Input**:
  - `vector<int>& nums` — an unsorted array of integers (can contain negative numbers, zeros, and duplicates).
  - `int target` — the target sum to achieve.
- **Output**:
  - `vector<int>` of length 2 containing `[i, j]` where `0 <= i < j < nums.size()` and `nums[i] + nums[j] == target`.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `2 <= nums.length <= 10^4` | Array always has at least 2 elements. At `N = 10^4`, `N^2 = 10^8` operations — right on the ~1 second CPU boundary, hinting that an `O(N)` solution is strongly preferred in interviews. |
| `-10^9 <= nums[i] <= 10^9` | Elements can be negative, zero, or large positive numbers. You cannot assume all numbers are positive or smaller than `target`. |
| `-10^9 <= target <= 10^9` | `nums[i] + nums[j]` or `target - nums[i]` could reach `±2 * 10^9`, which fits right inside a signed 32-bit `int` (`[-2,147,483,648, 2,147,483,647]`). |
| **Only one valid answer exists** | No need to handle "no solution" or tie-breaking between multiple valid pairs. |
| **Cannot use same element twice** | `i != j` strictly. Even if `2 * nums[i] == target`, index `i` cannot pair with itself. |

**CPU intuition**: A modern CPU executes roughly `10^8` simple operations per second. With `N <= 10^4`, an `O(N^2)` nested loop performs up to `N(N-1)/2 ≈ 5 × 10^7` comparisons — it passes on LeetCode, but in a Google interview you will immediately be asked: *"Can you do this in `O(N)` time?"*

### Terminology

- **Index (Position)**: The 0-based location of an element in the array (`0, 1, 2, ...`), **not** the element's value.
- **Complement**: For a given number `x` and a target sum `target`, its **complement** is `target - x` — the exact missing partner needed so that `x + complement == target`.
- **Distinct Indices (`i != j`)**: Two separate positions in the array. They may hold the *same numeric value* (e.g., `nums = [3, 3]`), as long as their array indices are different (`0` and `1`).

### Worked Examples

**Example 1** — Standard positive values:
```
nums   = [2, 7, 11, 15]
target = 9

Index:    0   1   2   3
Value:  [ 2,  7, 11, 15 ]
          ^   ^
          2 + 7 = 9 == target ✓

Output: [0, 1]
```

**Example 2** — Unsorted array where the pair is not at index 0:
```
nums   = [3, 2, 4]
target = 6

Check pairs:
  (index 0, index 1) → 3 + 2 = 5 != 6 ✗
  (index 0, index 2) → 3 + 4 = 7 != 6 ✗
  (index 1, index 2) → 2 + 4 = 6 == 6 ✓

Output: [1, 2]
(Note: We cannot use index 0 twice even though 3 + 3 = 6!)
```

**Example 3** — Duplicate values at different indices:
```
nums   = [3, 3]
target = 6

Index:    0   1
Value:  [ 3,  3 ]
          ^   ^
          3 + 3 = 6 == target ✓ (indices 0 and 1 are distinct)

Output: [0, 1]
```

**Example 4** — Negative numbers:
```
nums   = [-1, -2, -3, -4, -5]
target = -8

Index:     0   1   2   3   4
Value:  [ -1, -2, -3, -4, -5 ]
                   ^       ^
                  -3 + (-5) = -8 == target ✓

Output: [2, 4]
```

### Common Beginner Traps

1. **Returning values instead of indices**: Returning `{2, 7}` instead of `{0, 1}`. The problem asks for **positions**.
2. **Using the same element twice (`i == j`)**: In `nums = [3, 2, 4], target = 6`, checking `nums[0] + nums[0] = 3 + 3 = 6` and returning `{0, 0}` is invalid.
3. **Assuming the array is sorted**: `nums` is **not** sorted, and sorting it directly destroys the original indices unless you store `{value, original_index}` pairs.
4. **Skipping negative numbers**: Assuming `nums[i] > target` means `nums[i]` can't be part of the answer. With negative numbers (e.g., `nums = [10, -4], target = 6`), a number larger than `target` *can* be part of the answer.

### One-Sentence Restatement

> Find the two distinct 0-based indices `i` and `j` in an unsorted array `nums` whose values sum to `target`.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. 0-Based Array Indexing & `std::vector`

**What it is**: Dynamic arrays in C++ (`vector<int>`) store elements contiguously from index `0` to `nums.size() - 1`.

**Minimum mechanics**:
```cpp
vector<int> nums = {2, 7, 11, 15};
int n = nums.size(); // 4
int first = nums[0]; // 2
return {0, 1};       // Brace-enclosed initializer list returns a 2-element vector<int>
```

**Why it matters here**: We must iterate with an index variable `i` so we always know the position of each number, and return two indices using `{i, j}`.

### 2. Exhaustive Pair Enumeration (Nested Loops)

**What it is**: Checking every unique pair of indices `(i, j)` with `0 <= i < j < n`.

**Minimum mechanics**:
```cpp
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        // (i, j) visits every unique pair of distinct indices exactly once
    }
}
```

**Why it matters here**: Starting `j` at `i + 1` guarantees two things automatically: we never pair an element with itself (`i != j`), and we never check both `(i, j)` and `(j, i)`.

### 3. Hash Map (`std::unordered_map`)

**What it is**: A key-value data structure backed by a hash table that supports **O(1) average-time** insertion and key lookup. Think of it like a locker room where each locker number (`key`) maps directly to what is stored inside (`value`) without scanning every locker.

**Minimum mechanics**:
```cpp
#include <unordered_map>
unordered_map<int, int> seen; // maps: number_value -> array_index

seen[2] = 0;                  // store key = 2 with value = index 0
if (seen.count(2)) {          // returns 1 if key 2 exists, 0 otherwise — O(1) avg
    int idx = seen[2];        // retrieves value 0 — O(1) avg
}
```

**Why it matters here**: Instead of scanning the array in `O(N)` to check if `target - nums[i]` exists, storing previously seen numbers in an `unordered_map<int, int>` lets us answer *"Has `target - nums[i]` appeared earlier, and at what index?"* in **O(1) average time**.

---

> 🛑 **STOP HERE AND ATTEMPT THE PROBLEM FIRST.**
>
> Open `test_harness.cpp`, write your solution inside the empty `Solution` class, compile, and test it against the provided edge cases.
>
> Only open the sections below if you are stuck or want to compare after solving.

---

<details>
<summary>🔍 Layer 3 — How To Think Through The Problem (click to reveal)</summary>

### Step 1 — What Should You Notice First?

The equation `nums[i] + nums[j] == target` has **two unknowns** (`nums[i]` and `nums[j]`).
Whenever an equation has two unknowns and you fix one of them (`nums[i]`), the other unknown is **completely determined**:
```
nums[j] = target - nums[i]
```
This value `target - nums[i]` is the **complement** of `nums[i]`.

### Step 2 — The Naive / Direct Thought Process

If you pick the first number `nums[i]`, how do you find if `target - nums[i]` exists in the rest of the array?
Scan every index `j > i` and check if `nums[i] + nums[j] == target`.

```
nums = [3, 2, 4], target = 6

i = 0 (nums[0] = 3): need 6 - 3 = 3
  scan j = 1 (nums[1] = 2) → no
  scan j = 2 (nums[2] = 4) → no

i = 1 (nums[1] = 2): need 6 - 2 = 4
  scan j = 2 (nums[2] = 4) → YES! return [1, 2]
```

### Step 3 — Spot the Repeated Work (How Optimization Is Discovered)

Ask yourself the two golden optimization questions:
1. **"What am I doing repeatedly?"**
   For every index `i`, I am linearly scanning the array to ask: *"Does `target - nums[i]` exist, and at what index?"*
2. **"Which data structure answers 'Does key X exist, and what value is associated with it?' in O(1) time?"**
   A **Hash Map** (`unordered_map<int, int>`) where `Key = number` and `Value = index`.

### Step 4 — One-Pass Simulation with a Memory Table

Instead of looking *ahead* with a second loop, look *behind* in a hash map of numbers you have already visited:

```
nums = [2, 7, 11, 15], target = 9
seen = {} (empty hash map)

Step i = 0:
  Current number = nums[0] = 2
  Complement needed = 9 - 2 = 7
  Is 7 in `seen`? NO.
  Record current number in `seen`: seen = { 2 : 0 }

Step i = 1:
  Current number = nums[1] = 7
  Complement needed = 9 - 7 = 2
  Is 2 in `seen`? YES! seen[2] is 0.
  We found our pair! Return [seen[2], 1] → [0, 1] ✓
```

### Step 5 — Crucial Subtlety: Check BEFORE Inserting

What happens when the answer uses two identical numbers at different indices, such as `nums = [3, 3], target = 6`?

```
nums = [3, 3], target = 6

i = 0 (nums[0] = 3):
  Complement = 6 - 3 = 3
  1. Check `seen` FIRST: Is 3 in `seen`? NO (`seen` is empty).
  2. Insert AFTER checking: `seen[3] = 0`.

i = 1 (nums[1] = 3):
  Complement = 6 - 3 = 3
  1. Check `seen` FIRST: Is 3 in `seen`? YES! at index 0.
  2. Return [0, 1] ✓
```
If you inserted `seen[nums[i]] = i` *before* checking for `complement`, then at `i = 0` you would match `3` with itself and return `[0, 0]`. Always **check first, insert second**.

### Questions an Interviewer Expects You to Ask

1. *"Is the input array sorted?"* → No.
2. *"Can there be duplicate elements in the array?"* → Yes (e.g., `[3, 3]`).
3. *"Is there always a valid answer, or should I handle the no-solution case?"* → Exactly one valid answer is guaranteed.
4. *"Can numbers be negative or zero?"* → Yes, `-10^9 <= nums[i] <= 10^9`.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Nested Loops (Brute Force)

- **Type**: Brute Force
- **Time**: O(N²)
- **Space**: O(1) auxiliary, O(1) output
- Check every unique pair of indices `(i, j)` with `j > i` until finding the pair that sums to `target`.
- 📄 [Approach 1 — Nested Loops (Brute Force).md](<./approaches/Approach 1 — Nested Loops (Brute Force).md>)
- 💻 [Approach 1 — Nested Loops (Brute Force).cpp](<./approaches/Approach 1 — Nested Loops (Brute Force).cpp>)

### Approach 2 — One-Pass Hash Map (Optimized)

- **Type**: Optimized
- **Time**: O(N) average
- **Space**: O(N) auxiliary, O(1) output
- Iterate through the array once, checking in O(1) average time if `target - nums[i]` already exists in a hash map of `{value -> index}` before inserting `nums[i]`.
- 📄 [Approach 2 — One-Pass Hash Map (Optimized).md](<./approaches/Approach 2 — One-Pass Hash Map (Optimized).md>)
- 💻 [Approach 2 — One-Pass Hash Map (Optimized).cpp](<./approaches/Approach 2 — One-Pass Hash Map (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Complement Lookup via Hash Map (Space-Time Tradeoff)**: Trading `O(N)` auxiliary memory to replace an `O(N)` inner search loop with an `O(1)` hash table lookup, reducing overall time complexity from `O(N^2)` to `O(N)`.

### 2. Mental Model

> *"Whenever you need two elements that satisfy a pairwise equation `f(a, b) = target` in an unsorted array, rewrite it as `b = complement(target, a)` and use a Hash Map to look up `b` in `O(1)` time as you iterate."*

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- The complement relation: `complement = target - nums[i]`.
- In a one-pass hash map, **check if the complement exists BEFORE inserting the current element** so an element never matches with itself.
- Map layout: `Key = element value (nums[i])`, `Value = element index (i)`.

**SHOULD UNDERSTAND**:
- Why sorting + two pointers (`O(N log N)`) is slower than the hash map (`O(N)`) and requires extra work to preserve original indices.
- Why `unordered_map` gives `O(1)` *average* lookup (`O(N)` worst-case on hash collisions), whereas `std::map` gives `O(log N)` guaranteed via a Red-Black Tree.

**SHOULD BE ABLE TO RE-DERIVE**:
- Why duplicate numbers in `nums` never break the one-pass hash map (even if `mp[nums[i]] = i` overwrites an older index of the same value, we already checked if the second copy completed the target sum first!).

### 4. Previously Seen Patterns (Cross-Reference)

This is **Problem 01 of Phase 1** — the foundational entry point for both **Exhaustive Pair Search** and **Hash Map Complement Lookup**. You will see this exact hash-table lookup mindset reappear in `Phase_2_Core_DS/02_contains_duplicate_217` (existence check with a hash set) and across prefix-sum + hash-map problems later in the curriculum.

### 5. Related LeetCode Problems

| Problem | Why It Is Related |
|:---|:---|
| [LC 167 — Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Same problem when the input is already sorted — allows `O(N)` time with `O(1)` auxiliary space using Two Pointers. |
| [LC 15 — 3Sum](https://leetcode.com/problems/3sum/) | Extends Two Sum to three elements (`a + b + c = 0`) by fixing `a` and reducing the rest to a Two Sum problem. |
| [LC 217 — Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) | Simpler sibling of the one-pass lookup pattern: checks if `nums[i]` itself was seen before using an `unordered_set`. |
| [LC 560 — Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | Combines Prefix Sums with the exact Two Sum complement pattern (`prefix[j] - prefix[i] == k` → look up `prefix[j] - k`). |

### 6. Interview Questions

1. **"Why did you use `unordered_map` instead of `map`?"**
   → `unordered_map` uses a hash table with `O(1)` average lookup/insertion, giving `O(N)` total time. `std::map` is a balanced BST (`O(log N)` per operation), which would take `O(N log N)` total time.
2. **"What if the input array is already sorted, and memory is strictly limited to `O(1)` auxiliary space?"**
   → Use the Two Pointers technique (`left = 0, right = n - 1`), moving `left++` if the sum is too small and `right--` if the sum is too large (`O(N)` time, `O(1)` space — LC 167).
3. **"What happens if `nums` contains duplicate values that are NOT the answer, e.g., `nums = [2, 2, 7], target = 9`?"**
   → At `i = 0`, `seen[2] = 0`. At `i = 1`, `complement = 7` (not found), and `seen[2] = 1` overwrites the index to `1`. At `i = 2` (`7`), it looks up `2` and returns `[1, 2]` (or `[0, 2]`), which is still valid. And if `target = 4`, at `i = 1` it checks `seen.count(2)` *before* overwriting, immediately returning `[0, 1]`.
4. **"Could `target - nums[i]` overflow a 32-bit signed `int`?"**
   → Given `-10^9 <= nums[i], target <= 10^9`, the extreme values of `target - nums[i]` are `±2 * 10^9`, which safely fit inside a 32-bit signed `int` (`±2.14 * 10^9`). If constraints were `±2 * 10^9`, we would cast to `long long`.

### 7. Leftover Important Details

- Putting the index as the **value** (`mp[nums[i]] = i`) and the array element as the **key** feels backwards at first because arrays map `index -> value`. Remember: you always make the **key** the thing you need to **search by** (here, we search by the complement's numeric value).
- Always return `{mp[complement], i}` (earlier index first, current index second) for clean, deterministic output ordering.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
