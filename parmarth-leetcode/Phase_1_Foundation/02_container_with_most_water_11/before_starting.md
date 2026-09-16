Problem      : Container With Most Water
LeetCode     : https://leetcode.com/problems/container-with-most-water/
Topic        : Array, Two Pointers, Greedy
Difficulty   : Medium
Google-Tagged: No
Phase        : 1 — Foundation
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the **most water**. Return the **maximum amount of water** a container can store.

Notice that you may not slant the container, and the intermediate lines between your chosen two walls do **not** block water or take up volume.

```text
  Height
    8 |     |                   |
    7 |     |                   |       |
    6 |     |   |               |       |
    5 |     |   |       |       |       |
    4 |     |   |       |   |   |       |
    3 |     |   |       |   |   |   |   |
    2 |     |   |   |   |   |   |   |   |
    1 | |   |   |   |   |   |   |   |   |
    0 +-+---+---+---+---+---+---+---+---+-- x-axis
        0   1   2   3   4   5   6   7   8   (index)
```

For any two chosen indices `left` and `right` (`left < right`), the container's water level is capped by the **shorter** of the two walls, and its base is the horizontal distance between them:

$$\text{area} = (\text{right} - \text{left}) \times \min(\text{height}[\text{left}], \text{height}[\text{right}])$$

### Input & Output

- **Input**: `vector<int>& height` — an array of `n` non-negative integers representing wall heights at positions `0, 1, ..., n - 1`.
- **Output**: A single `int` — the maximum water area formed by any pair of indices `(left, right)` with `left < right`.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `2 <= height.length <= 10^5` | Always at least one valid pair of walls (`n >= 2`). At `n = 10^5`, an $O(N^2)$ solution performs $\approx 5 \times 10^9$ pairs, which will **Time Limit Exceeded (TLE)**. We need $O(N)$ or $O(N \log N)$. |
| `0 <= height[i] <= 10^4` | Wall heights can be `0` (holding `0` water). Maximum possible area is $(10^5 - 1) \times 10^4 \approx 10^9$, which fits safely inside a signed 32-bit `int` (max $\approx 2.14 \times 10^9$). |

**CPU intuition**: A modern CPU executes roughly $10^8$ simple operations per second. With $N = 10^5$, checking all $\frac{N(N-1)}{2} \approx 5 \times 10^9$ pairs takes ~50 seconds — far above LeetCode's ~1–2 second limit. We must find a way to skip pairs that cannot possibly be optimal.

### Terminology

- **Width**: The horizontal distance between two lines at indices `left` and `right`, equal to `right - left`.
- **Limiting Height (Bottleneck)**: The smaller of the two wall heights, `min(height[left], height[right])`. Water spills over the shorter wall, so the taller wall's excess height contributes nothing.
- **Container Area**: `width * limiting_height`.
- **Greedy Choice**: Making a locally optimal decision at each step (discarding the shorter wall) that is mathematically guaranteed never to discard the global optimum.

### Worked Examples

**Example 1** — Standard LeetCode case:
```text
height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
indices:  0  1  2  3  4  5  6  7  8

Pick left = 1 (height 8) and right = 8 (height 7):
  width          = 8 - 1 = 7
  limitingHeight = min(8, 7) = 7
  area           = 7 * 7 = 49

No other pair produces a larger product.
Output: 49
```

**Example 2** — Minimum length (`n = 2`):
```text
height = [1, 1]
indices:  0  1

Only one pair exists: left = 0, right = 1
  width          = 1 - 0 = 1
  limitingHeight = min(1, 1) = 1
  area           = 1 * 1 = 1

Output: 1
```

**Example 3** — Wide & short vs. Narrow & tall:
```text
height = [1, 2, 100, 100, 2, 1]
indices:  0  1   2    3   4  5

Pair (0, 5): width = 5, height = min(1, 1) = 1     → area = 5
Pair (1, 4): width = 3, height = min(2, 2) = 2     → area = 6
Pair (2, 3): width = 1, height = min(100, 100) = 100 → area = 100

Here the narrowest pair (indices 2 and 3) wins because its height dominates.
Output: 100
```

**Example 4** — Zero-height walls included:
```text
height = [0, 5, 0, 4, 0]
indices:  0  1  2  3  4

Any pair using index 0, 2, or 4 has min height = 0 → area = 0.
Pair (1, 3): width = 3 - 1 = 2, height = min(5, 4) = 4 → area = 8.

Output: 8
```

### Common Beginner Traps

1. **Using `max` instead of `min` for water height**: Water cannot float above the shorter wall. Always use `min(height[left], height[right])`.
2. **Off-by-one width (`right - left + 1`)**: We are measuring distance between thin vertical lines at coordinates `left` and `right`, not counting array elements. Distance between index `1` and index `8` is `8 - 1 = 7`.
3. **Moving the taller pointer in the two-pointer approach**: Keeping the shorter wall while shrinking width guarantees the new area is strictly bounded by the old area.
4. **Confusing with Trapping Rain Water (LeetCode #42)**: In LC #11, intermediate bars do not block water or displace volume — you simply pick two lines and ignore everything else.

### One-Sentence Restatement

> Choose two indices `left < right` in the `height` array to maximize `(right - left) * min(height[left], height[right])`.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Array Indices as 1D Coordinates

**What it is**: Each array index `i` represents the x-coordinate of a vertical line, and `height[i]` represents its y-coordinate (height).

**Mechanics**:
- The distance between line `i` and line `j` (`i < j`) is `j - i`.
- Accessing the height of either line is $O(1)$ via `height[i]` and `height[j]`.

**Why it matters here**: The area depends simultaneously on **indices** (`right - left`) and **values** (`height[left]`, `height[right]`), which means **sorting the array would destroy the x-coordinates** and invalidate the widths.

### 2. `std::min` and `std::max` (`<algorithm>`)

**What it is**: Standard library functions that return the smaller or larger of two comparable values in $O(1)$ time.

**Mechanics**:
```cpp
int waterHeight = min(height[left], height[right]);
bestArea = max(bestArea, width * waterHeight);
```

**Why it matters here**: The water level is a bottleneck function (`min`), while our overall goal is an optimization function (`max`).

### 3. Opposite-End Two Pointers

**What it is**: Placing one pointer at the start of the array (`left = 0`) and another at the end (`right = n - 1`), then moving one pointer inward per step until `left == right`.

**Mechanics**:
```cpp
int left = 0, right = n - 1;
while (left < right) {
    // Evaluate pair (left, right)
    if (shouldMoveLeft) left++;
    else right--;
}
```

**Why it matters here**: Starting at `(0, n - 1)` begins with the **maximum possible width**. Every inward step decreases width by `1`, reducing an $O(N^2)$ search space to $N - 1$ steps ($O(N)$ time).

### 4. Greedy Elimination (Safe Discard)

**What it is**: Proving that a particular candidate can never be part of a strictly better solution than what we have already seen, allowing us to discard all remaining pairs involving that candidate without checking them.

**Why it matters here**: When `height[left] <= height[right]`, `left` is already paired with the **farthest possible wall** (`right`) that is at least as tall as `left`. Pairing `left` with any closer wall `right' < right` can only have a smaller width and a limiting height $\le \text{height}[\text{left}]$. Thus, `left` has achieved its maximum possible potential and can be safely discarded (`left++`).

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

Every container is defined by a pair of indices `(left, right)` with `0 <= left < right < n`. Its area is the product of two competing quantities:
1. **Width**: `right - left` (determined purely by how far apart the indices are).
2. **Height**: `min(height[left], height[right])` (determined by the **shorter** of the two lines).

### Step-by-Step Reasoning

**Step 1 — The Naive Thought Process ($O(N^2)$)**:
If we have no special insight, we can check every possible pair `(left, right)` using two nested loops, compute `(right - left) * min(height[left], height[right])`, and track the maximum.
- Why isn't this enough? For $N = 10^5$, there are $\frac{10^5 \times 99999}{2} \approx 5 \times 10^9$ pairs. We need to eliminate entire groups of pairs at once.

**Step 2 — Start at Maximum Width**:
What if we start with the widest possible container: `left = 0` and `right = n - 1`?
- Width starts at its absolute maximum (`n - 1`).
- As we move either pointer inward, **width strictly decreases** at every step.
- Since width is shrinking, the **only** way a narrower container can beat our current area is if its **limiting height increases**.

**Step 3 — Socratic Question: Which Pointer Should Move?**
Suppose we are at `(left, right)` and `height[left] < height[right]`.
- What is the limiting height right now? `height[left]`.
- **What happens if we keep `left` and move `right` inward to `right'`?**
  - New width: `right' - left < right - left` (strictly smaller).
  - New height: `min(height[left], height[right']) <= height[left]` (cannot exceed `height[left]`, even if `height[right']` is a million!).
  - Conclusion: Every pair `(left, right')` for `left < right' < right` has **strictly smaller width** AND **less-than-or-equal height**. None of them can beat `(left, right)`!
- Therefore, index `left` can never form a better container with any remaining line. We can safely discard `left` (`left++`), eliminating `right - left - 1` pairs in $O(1)$ time!
- By symmetry, if `height[right] < height[left]`, we discard `right` (`right--`).
- If `height[left] == height[right]`, neither wall can beat the current area while keeping the other wall, so moving **either** pointer inward (`left++` or `right--`) is safe.

### Visual Trace (Example 1)

```text
height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
indices:  0  1  2  3  4  5  6  7  8

Step | L | R | h[L] | h[R] | width | minH | area | best | Action & Reason
-----|--:|--:|-----:|-----:|------:|-----:|-----:|-----:|:-------------------------------
  1  | 0 | 8 |   1  |   7  |   8   |   1  |   8  |   8  | h[0]=1 < h[8]=7  → L++ (discard 0)
  2  | 1 | 8 |   8  |   7  |   7   |   7  |  49  |  49  | h[1]=8 > h[8]=7  → R-- (discard 8)
  3  | 1 | 7 |   8  |   3  |   6   |   3  |  18  |  49  | h[1]=8 > h[7]=3  → R-- (discard 7)
  4  | 1 | 6 |   8  |   8  |   5   |   8  |  40  |  49  | h[1]=8 == h[6]=8 → L++ (discard 1)
  5  | 2 | 6 |   6  |   8  |   4   |   6  |  24  |  49  | h[2]=6 < h[6]=8  → L++ (discard 2)
  6  | 3 | 6 |   2  |   8  |   3   |   2  |   6  |  49  | h[3]=2 < h[6]=8  → L++ (discard 3)
  7  | 4 | 6 |   5  |   8  |   2   |   5  |  10  |  49  | h[4]=5 < h[6]=8  → L++ (discard 4)
  8  | 5 | 6 |   4  |   8  |   1   |   4  |   4  |  49  | h[5]=4 < h[6]=8  → L++ (L==R, stop)

Final Answer: 49
```

### Questions an Interviewer Expects You to Ask

1. *"Can wall heights be zero?"* → Yes (`0 <= height[i] <= 10^4`). Formula handles `0` naturally.
2. *"Do lines between the two chosen walls block water or displace volume?"* → No, lines have zero thickness and do not block water.
3. *"Could the maximum area overflow a 32-bit signed integer?"* → With `n <= 10^5` and `height[i] <= 10^4`, max area is $\approx 10^9 < 2^{31} - 1$, so `int` is safe. (If heights were up to $10^5$, we would need `long long`).

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — All Pairs Enumeration (Brute Force)

- **Type**: Brute Force
- **Time**: $O(N^2)$
- **Space**: $O(1)$ output, $O(1)$ auxiliary
- Check every possible pair of walls `(left, right)` using nested loops and return the maximum area found.
- 📄 [Approach 1 — All Pairs Enumeration (Brute Force).md](<./approaches/Approach 1 — All Pairs Enumeration (Brute Force).md>)
- 💻 [Approach 1 — All Pairs Enumeration (Brute Force).cpp](<./approaches/Approach 1 — All Pairs Enumeration (Brute Force).cpp>)

### Approach 2 — Two Pointers Greedy (Optimized)

- **Type**: Optimized
- **Time**: $O(N)$
- **Space**: $O(1)$ output, $O(1)$ auxiliary
- Start pointers at opposite ends `(0, n - 1)` for maximum width, and at each step greedily move the shorter wall inward to search for a taller bottleneck.
- 📄 [Approach 2 — Two Pointers Greedy (Optimized).md](<./approaches/Approach 2 — Two Pointers Greedy (Optimized).md>)
- 💻 [Approach 2 — Two Pointers Greedy (Optimized).cpp](<./approaches/Approach 2 — Two Pointers Greedy (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Opposite-End Two Pointers with Greedy Elimination**: Start at the extremes of the array where one factor (width) is maximized, and advance the pointer that acts as the bottleneck (`min(height[left], height[right])`), eliminating $O(N)$ suboptimal pairs per step.

### 2. Mental Model

> "Whenever you need to choose two indices `(i, j)` to maximize a product of distance `(j - i)` and a bottleneck `min(A[i], A[j])`, start at maximum distance `(0, n - 1)` and always discard the smaller endpoint."

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- Area formula: `(right - left) * min(height[left], height[right])`.
- Always move the pointer pointing to the **shorter** wall inward.

**SHOULD UNDERSTAND**:
- Why sorting the array is illegal here (indices represent physical x-coordinates).
- Why moving the taller pointer is always suboptimal (width shrinks AND limiting height cannot increase).
- Why moving either pointer when `height[left] == height[right]` is completely safe.

**SHOULD BE ABLE TO RE-DERIVE**:
- The formal proof by contradiction that no optimal pair `(i*, j*)` is ever skipped by the two-pointer trajectory.

### 4. Previously Seen Patterns (Cross-Reference)

In **Problem 01 — Two Sum (`01_two_sum_1`)**, you also had to select a pair of indices `(i, j)` from an array where the brute-force approach checked all $\frac{N(N-1)}{2}$ pairs in $O(N^2)$ time.
- **The difference**: In *Two Sum*, we were looking for an exact equality `nums[i] + nums[j] == target` with no monotonic relationship on unsorted indices, so we used a **Hash Map** ($O(N)$ auxiliary space) to look up complements in $O(1)$. Here in *Container With Most Water*, we are maximizing an inequality/product `(right - left) * min(height[left], height[right])` where the outer boundaries naturally dominate narrower pairs for the shorter wall. This allows **Opposite-End Two Pointers** to achieve $O(N)$ time in **$O(1)$ auxiliary space** without any hash map or sorting!

### 5. Related LeetCode Problems

| Problem | Why Related |
|:--------|:------------|
| [LC 167 — Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Classic opposite-end two-pointer elimination where the sum is either too small (`left++`) or too large (`right--`). |
| [LC 15 — 3Sum](https://leetcode.com/problems/3sum/) | Fixes one element and uses opposite-end two pointers on the remaining sorted suffix. |
| [LC 42 — Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) | The direct sibling problem: instead of picking 2 walls and ignoring the middle, every bar traps water above it based on `min(maxLeft, maxRight)`. |
| [LC 84 — Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | Maximizes `width * height`, where height is limited by the *shortest bar in the entire range* `[left..right]` (solved via monotonic stack). |

### 6. Interview Questions

1. *"Prove that your greedy two-pointer algorithm never misses the optimal pair `(i*, j*)`."* → Without loss of generality, suppose `left` reaches `i*` before `right` reaches `j*` (so `right > j*`). The only way our algorithm moves `left` past `i*` is if `height[i*] <= height[right]`. Creative punchline: if `height[i*] <= height[right]`, then the container `(i*, right)` has width `right - i* > j* - i*` and height `height[i*] >= min(height[i*], height[j*])`, meaning `(i*, right)` already had an area at least as large as `(i*, j*)`!
2. *"What happens when `height[left] == height[right]`? Should you move `left`, `right`, or both?"* → Moving either one (or even both simultaneously) is valid because neither `left` nor `right` can form a strictly larger container with any interior wall while the other stays fixed.
3. *"How does this problem differ from Trapping Rain Water (LC #42)?"* → Here, walls have zero width and water is a single rectangle between two chosen lines. In LC #42, bars have width 1 and water is summed column-by-column across all indices.

### 7. Leftover Important Details

- **Tie-breaking (`<=` vs `<`)**: Whether you write `if (height[left] <= height[right]) left++;` or `<` makes no difference to correctness.
- **Integer Overflow in Follow-ups**: Always check the maximum possible product `(N - 1) * max(height[i])`. Under LeetCode constraints ($10^5 \times 10^4 = 10^9$), `int` suffices; if an interviewer raises `height[i]` to $10^9$, cast `width` to `long long`.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
