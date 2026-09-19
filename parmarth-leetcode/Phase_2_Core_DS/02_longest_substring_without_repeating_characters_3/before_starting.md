Problem      : Longest Substring Without Repeating Characters
LeetCode     : https://leetcode.com/problems/longest-substring-without-repeating-characters/
Topic        : Hash Table, String, Sliding Window
Difficulty   : Medium
Google-Tagged: Yes
Phase        : 2 — Core Data Structures
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given a string `s` consisting of English letters, digits, symbols, and spaces. Find the **length of the longest contiguous slice (substring)** inside `s` that contains **no duplicate characters** (every character in the slice appears at most once).

You only need to return the **maximum integer length**, not the substring itself (though returning the actual substring is a classic Google follow-up).

### Input & Output

- **Input**: `string s` — a sequence of ASCII characters (`0 <= s.length() <= 5 * 10^4`).
- **Output**: `int` — the maximum length of any contiguous substring of `s` with all unique characters.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `0 <= s.length <= 5 * 10^4` | **Empty string `""` is valid input!** Must return `0` without crashing on index `0`. |
| `N = 50,000` | $O(N^3)$ ($\approx 2 \times 10^{13}$ ops) and $O(N^2)$ ($\approx 1.25 \times 10^9$ ops) will **Time Limit Exceeded (TLE)**. We need an $O(N)$ algorithm. |
| `s` consists of English letters, digits, symbols, and spaces | Not just `'a'`–`'z'`! Cannot use a 26-element array with `ch - 'a'`. All characters fit in standard 7-bit ASCII (`0` to `127`), so a 128-element direct lookup array works in $O(1)$ space. |

**CPU intuition ($\approx 10^8$ ops/sec)**:

| Algorithm Class | Operations Formula ($N = 5 \times 10^4$) | Rough Ops Count | Verdict |
|:---|:---|:---|:---|
| **$O(N^3)$ Pure Naive** | $\frac{N^3}{6}$ | $\approx 2.08 \times 10^{13}$ ops | ❌ Severe TLE |
| **$O(N^2)$ Substring Expansion** | $\frac{N(N+1)}{2}$ | $\approx 1.25 \times 10^9$ ops | ❌ TLE ($\approx 12\text{ s}$) |
| **$O(N)$ Sliding Window** | $N$ to $2N$ | $\le 10^5$ ops | ✅ Optimal ($0\text{--}2\text{ ms}$) |

### Terminology

- **String**: A sequence of characters stored in contiguous memory (e.g., `"abcabcbb"`).
- **Substring (Contiguous)**: A continuous slice `s[i..j]` with **no skipped characters**. In `"pwwkew"`, `"wke"` is a substring.
- **Subsequence (Non-contiguous allowed)**: Obtained by deleting zero or more characters without changing the order of the remaining characters. In `"pwwkew"`, `"pwke"` is a subsequence, **not** a substring.
- **Without Repeating Characters**: Every character inside `s[i..j]` has frequency `1`.
- **Window `[left..right]`**: A contiguous range of indices from `left` to `right` inclusive, whose length is `right - left + 1`.

### Worked Examples

**Example 1** — Standard recurring cycles (`s = "abcabcbb"`):
```text
Indices:  0  1  2  3  4  5  6  7
Chars:    a  b  c  a  b  c  b  b

- s[0..2] = "abc"  → all unique, length = 3
- s[0..3] = "abca" → duplicate 'a'! Drop s[0] → s[1..3] = "bca" (length = 3)
- s[1..4] = "bcab" → duplicate 'b'! Drop s[1] → s[2..4] = "cab" (length = 3)
- s[2..5] = "cabc" → duplicate 'c'! Drop s[2] → s[3..5] = "abc" (length = 3)
- s[3..6] = "abcb" → duplicate 'b'! Drop s[3..4] → s[5..6] = "cb" (length = 2)
- s[5..7] = "cbb"  → duplicate 'b'! Drop s[5..6] → s[7..7] = "b"  (length = 1)

Maximum length = 3 ("abc", "bca", or "cab")
```

**Example 2** — All identical characters (`s = "bbbbb"`):
```text
Indices:  0  1  2  3  4
Chars:    b  b  b  b  b

- s[0..0] = "b"  → unique, length = 1
- Any slice of length >= 2 contains at least two 'b's → invalid.

Maximum length = 1
```

**Example 3** — Answer in the middle + Subsequence trap (`s = "pwwkew"`):
```text
Indices:  0  1  2  3  4  5
Chars:    p  w  w  k  e  w

- s[0..1] = "pw"  → unique, length = 2
- Index 2 ('w') duplicates index 1 ('w'). Must start at index 2.
- s[2..4] = "wke" → unique, length = 3
- Index 5 ('w') duplicates index 2 ('w'). Must start at index 3.
- s[3..5] = "kew" → unique, length = 3

Maximum length = 3 ("wke" or "kew")
(Note: "pwke" has length 4, but it is a subsequence, NOT a substring!)
```

**Example 4** — The Pointer Regression Trap (`s = "abba"`):
```text
Indices:  0  1  2  3
Chars:    a  b  b  a

- s[0..1] = "ab" → unique, length = 2 (left = 0, right = 1)
- At right = 2 ('b'): duplicates 'b' at index 1.
  left jumps to 1 + 1 = 2. Active window: s[2..2] = "b".
- At right = 3 ('a'): 'a' was previously seen at index 0.
  TRAP: Index 0 is BEFORE our current left = 2!
  If we blindly set left = 0 + 1 = 1, the window becomes s[1..3] = "bba",
  which contains duplicate 'b's!
  Instead, left stays at 2. Active window: s[2..3] = "ba" (length = 2).

Maximum length = 2 ("ab" or "ba")
```

### Common Beginner Traps

1. **Confusing Substring with Subsequence**: Counting distinct characters across the string or skipping duplicates in-place (`"pwke"` in `"pwwkew"`). Substrings must be strictly contiguous.
2. **Pointer Regression (`"abba"` bug)**: Blindly setting `left = lastSeen[ch] + 1` when `lastSeen[ch] < left`, moving `left` backward and re-introducing old duplicates into the window.
3. **Assuming Lowercase Letters Only**: Allocating `int freq[26]` and indexing `ch - 'a'`. A space `' '` (ASCII 32) produces `32 - 97 = -65`, causing an immediate out-of-bounds memory error.
4. **Restarting from `i + 1` on Duplicate**: In `"dvdf"`, scanning from `0` hits duplicate `'d'` at index `2`. If you reset your scan cleanly instead of sliding the window, or jump to index `2` instead of `0 + 1 = 1`, you miss `"vdf"` (length 3).
5. **Off-by-One in Window Length**: The number of elements in `[left..right]` inclusive is `right - left + 1`, not `right - left`.

### One-Sentence Restatement

> Find the maximum length `right - left + 1` of any contiguous window `s[left..right]` in which every character appears at most once.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Zero-Indexed Window Length Arithmetic

- **What it is**: Computing the number of elements in a closed index interval `[left, right]`.
- **Minimum mechanics**:
  ```cpp
  int currentLength = right - left + 1;
  ```
- **Tiny example**: If `left = 2` and `right = 4`, the indices included are `2, 3, 4` — that is `4 - 2 + 1 = 3` characters.
- **Why it matters here**: Every time we expand or adjust our window, we measure its length using `right - left + 1`.

### 2. Same-Direction Two Pointers (Dynamic Sliding Window)

- **What it is**: Maintaining a contiguous subsegment `s[left..right]` where `right` expands the window one step at a time and `left` advances forward whenever the window invariant is violated.
- **Minimum mechanics**:
  ```cpp
  int left = 0;
  for (int right = 0; right < n; ++right) {
      // 1. Update state with s[right]
      // 2. Advance 'left' if window is invalid
      // 3. Record best window size: right - left + 1
  }
  ```
- **Why it matters here**: Because both `left` and `right` only move forward ($0 \to n-1$), we process the string in $O(N)$ time instead of checking all $O(N^2)$ substrings from scratch.

### 3. Direct-Access ASCII Lookup Table vs. `std::unordered_map` / `std::unordered_set`

- **What it is**: Using a fixed-size array of length `128` (or `256`) indexed directly by a character's ASCII code instead of a heap-allocated hash table.
- **Minimum mechanics**:
  ```cpp
  vector<int> lastSeen(128, -1); // -1 means "never seen"
  unsigned char ch = static_cast<unsigned char>(s[right]);
  int prevIndex = lastSeen[ch];
  lastSeen[ch] = right;
  ```
- **Why it matters here**: Standard ASCII characters have integer codes `0` to `127`. Indexing a 128-int array (`512` bytes) lives entirely in L1 CPU cache, takes 1 CPU cycle, and avoids hash function overhead and heap allocations. Casting to `unsigned char` guards against negative indices if `char` is signed on the target platform.

---

> 🛑 **STOP HERE AND ATTEMPT THE PROBLEM FIRST.**
>
> Open `test_harness.cpp`, write your solution inside the empty `Solution` class, compile, and test it against the provided edge cases.
>
> Only open the sections below if you are stuck or want to compare after solving.

---

<details>
<summary>🔍 Layer 3 — How To Think Through The Problem (click to reveal)</summary>

### Step 1 — What Should Be Noticed First?

1. We are looking for a **contiguous** range `[i..j]` with **no duplicate characters**.
2. A substring is completely determined by its `left` (start) and `right` (end) indices.
3. With $N \le 5 \times 10^4$, there are $\frac{N(N+1)}{2} \approx 1.25 \times 10^9$ substrings. We cannot afford to inspect all of them individually.

### Step 2 — The Naive / Direct Thought Process

How would you solve this by hand before optimizing?
- Pick a starting index `i`.
- Extend the ending index `j` from `i` rightward, keeping a set of characters seen in `s[i..j]`.
- The moment `s[j]` is already in our set, **stop extending `j`!** Why? Because if `s[i..j]` already has a duplicate, then `s[i..j+1]`, `s[i..j+2]`, etc. will also contain that same duplicate.
- This early exit reduces the $O(N^3)$ check-every-substring approach to $O(N^2)$.

### Step 3 — Finding the Redundancy (Observation $\to$ Sliding Window)

Ask yourself: **When `s[i..j]` fails because `s[j]` duplicates an earlier character at index `p` (where `i <= p < j`), what happens when the outer loop increments `i`?**

```text
Index:  0  1  2  3  4  5  6  7
Chars:  a  b  c  d  e  c  f  g
        ^     ^        ^
        i    p=2      j=5 (duplicate 'c'!)
```

- At `i = 0`, we scanned `j = 0, 1, 2, 3, 4` (`"abcde"`, all unique) and hit duplicate `'c'` at `j = 5`.
- What if we try `i = 1`? The substring `s[1..5]` (`"bcdec"`) **still contains both `'c'`s** at indices `2` and `5`!
- What if we try `i = 2`? The substring `s[2..5]` (`"cdec"`) **still contains both `'c'`s**!
- The **first** starting index that eliminates the duplicate `'c'` at `p = 2` is `i = p + 1 = 3` (`"dec"`).
- Even better: we already know `s[3..4]` (`"de"`) has no duplicates because it was part of the valid window `s[0..4]`! We don't need to move `j` backward at all!

### Step 4 — Discovering the $O(1)$ Jump Rule (and the `"abba"` Guard)

Instead of shrinking `left` one step at a time with a `while` loop ($O(2N)$), what if we store the **last seen index** of each character in `lastSeen[ch]`?

When `right` encounters character `ch = s[right]`:
- If `ch` appeared previously at `lastSeen[ch]`, is it a duplicate inside our current window `s[left..right-1]`?
  - **Case A (`lastSeen[ch] >= left`)**: Yes! It is inside our current window. We must jump `left` to `lastSeen[ch] + 1`.
  - **Case B (`lastSeen[ch] < left`)**: No! That old occurrence was already excluded when `left` jumped past it earlier (like the first `'a'` in `"abba"`). `left` must remain unchanged.
- Both cases combine cleanly into a single monotonic update:
  ```text
  left = max(left, lastSeen[ch] + 1)
  ```

### Step 5 — Full Manual Trace (`s = "tmmzuxt"`)

```text
Initial state: left = 0, maxLen = 0, lastSeen[all] = -1
Indices:       0   1   2   3   4   5   6
Characters:    t   m   m   z   u   x   t
```

| `right` | `ch = s[right]` | `lastSeen[ch]` (before) | `left` Update (`max(left, lastSeen[ch] + 1)`) | Active Window `s[left..right]` | Window Length | `maxLen` |
|:---:|:---:|:---:|:---|:---|:---:|:---:|
| `0` | `'t'` | `-1` | `0` (not seen) | `"t"` (`[0..0]`) | `1` | `1` |
| `1` | `'m'` | `-1` | `0` (not seen) | `"tm"` (`[0..1]`) | `2` | `2` |
| `2` | `'m'` | `1` | `max(0, 1 + 1) = 2` | `"m"` (`[2..2]`) | `1` | `2` |
| `3` | `'z'` | `-1` | `2` (not seen) | `"mz"` (`[2..3]`) | `2` | `2` |
| `4` | `'u'` | `-1` | `2` (not seen) | `"mzu"` (`[2..4]`) | `3` | `3` |
| `5` | `'x'` | `-1` | `2` (not seen) | `"mzux"` (`[2..5]`) | `4` | `4` |
| `6` | `'t'` | `0` | `max(2, 0 + 1) = 2` (old `'t'` at `0 < left`, ignored!) | `"mzuxt"` (`[2..6]`) | `5` | `5` |

Final Answer: **`5`** (`"mzuxt"`).

### Questions an Interviewer Expects You to Ask

1. *"What is the character set of `s`? Is it only lowercase `'a'`–`'z'`, standard ASCII (128), extended ASCII (256), or full Unicode?"* → Standard ASCII (letters, digits, symbols, spaces).
2. *"Can the input string be empty?"* → Yes, `0 <= s.length <= 5 * 10^4`; empty string should return `0`.
3. *"Do you want the length of the substring, or the substring itself?"* → Length, though it's trivial to also track `bestStart` to return the substring.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — All Substrings with Hash Set (Brute Force)

- **Type**: Brute Force
- **Time**: $O(N^2)$ (or $O(N^3)$ unpruned)
- **Space**: $O(1)$ output, $O(\min(N, \Sigma))$ auxiliary (where $\Sigma = 128$ for ASCII $\implies O(1)$)
- Fix every starting index `i` and expand `j` rightward while tracking seen characters in a direct lookup set, breaking early on the first duplicate.
- 📄 [Approach 1 — All Substrings with Hash Set (Brute Force).md](<./approaches/Approach 1 — All Substrings with Hash Set (Brute Force).md>)
- 💻 [Approach 1 — All Substrings with Hash Set (Brute Force).cpp](<./approaches/Approach 1 — All Substrings with Hash Set (Brute Force).cpp>)

### Approach 2 — Sliding Window with Last-Seen Index (Optimized)

- **Type**: Optimized
- **Time**: $O(N)$
- **Space**: $O(1)$ output, $O(\min(N, \Sigma))$ auxiliary (where $\Sigma = 128$ for ASCII $\implies O(1)$)
- Maintain a monotonic sliding window `[left..right]` and a `lastSeen` index table to jump `left` directly past any duplicate in $O(1)$ time per character.
- 📄 [Approach 2 — Sliding Window with Last-Seen Index (Optimized).md](<./approaches/Approach 2 — Sliding Window with Last-Seen Index (Optimized).md>)
- 💻 [Approach 2 — Sliding Window with Last-Seen Index (Optimized).cpp](<./approaches/Approach 2 — Sliding Window with Last-Seen Index (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Dynamic Sliding Window with Last-Seen Index Table**: Maintain a contiguous window `[left, right]` that satisfies an invariant (all unique characters). Expand `right` every step, and restore the invariant in $O(1)$ by jumping `left` forward using a direct-access hash table of last-seen positions.

### 2. Mental Model

> **"Whenever you see a problem asking for the longest or shortest CONTIGUOUS subarray/substring satisfying a monotonicity property (like 'no duplicates' or 'at most $K$ distinct'), think Dynamic Sliding Window (`[left, right]`)."**

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- Window length formula: `right - left + 1`
- Monotonic left-pointer jump: `left = max(left, lastSeen[ch] + 1)`
- Array sizing for character sets: `128` for standard ASCII, `256` for extended byte values, `26` only when guaranteed lowercase `'a'`–`'z'`
- Casting `static_cast<unsigned char>(s[right])` before array indexing in C++

**SHOULD UNDERSTAND**:
- Why `left` must never move backward (the `"abba"` counterexample)
- Why Sliding Window only applies when the validity condition is **monotonic** with respect to window expansion/contraction
- Why a fixed 128-element array (`512` bytes in L1 cache) beats `std::unordered_map<char, int>` in practice by a large constant factor

**SHOULD BE ABLE TO RE-DERIVE**:
- The two-pointer shrinking variant (`while (inWindow[ch]) { inWindow[s[left++]] = false; }`) when the problem tracks frequencies instead of jump indices
- Returning the actual longest substring by recording `bestStart = left` whenever `right - left + 1 > maxLen`

### 4. Previously Seen Patterns (Cross-Reference)

- **Hash Table (`value -> index` mapping)**: You saw this exact idea in **Phase 1, Problem 01 — Two Sum (LC #1)**, where we stored each number's index in a hash table to look up complements in $O(1)$ time. Here, we store each character's most recent index (`lastSeen[ch] = right`) so we can detect duplicates inside `[left..right]` and jump `left` in $O(1)$ time.
- **Two Pointers**: You saw **Opposite-Direction Two Pointers** in **Phase 1, Problem 02 — Container With Most Water (LC #11)**, where `left` (`0`) and `right` (`n - 1`) moved inward toward each other. Here, we use **Same-Direction Two Pointers (Sliding Window)**, where both `left` and `right` start at `0` and move monotonically left-to-right.

### 5. Related LeetCode Problems

| Problem | Why Related |
|:--------|:------------|
| [LC 159 — Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/) | Direct generalization: sliding window shrinks when distinct count in frequency map exceeds `2`. |
| [LC 340 — Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/) | Generalizes LC #3 and LC #159 to `K` distinct characters using a sliding window + frequency map. |
| [LC 424 — Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | Sliding window over strings tracking character frequencies to keep replacements $\le K$. |
| [LC 76 — Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | Classic Hard sliding window: expand `right` to satisfy target counts, shrink `left` to minimize length. |
| [LC 1004 — Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) | Same dynamic sliding window skeleton applied to binary arrays with at most `K` zeroes. |

### 6. Interview Questions

1. *"Why do you need `max(left, lastSeen[ch] + 1)` instead of just `left = lastSeen[ch] + 1`?"* → Because `lastSeen[ch]` might point to an index strictly less than `left` (outside the current window), as in `"abba"` when seeing the second `'a'`. Moving `left` backward would include previously expelled duplicates (`"bb"`).
2. *"What is the space complexity in terms of $N$ and the alphabet size $\Sigma$?"* → $O(\min(N, \Sigma))$ auxiliary space. With a direct array of size $\Sigma = 128$, it is $O(\Sigma) = O(1)$.
3. *"What if the input string contains arbitrary Unicode code points (UTF-32)?"* → $\Sigma$ can be up to $1.1 \times 10^6$, so a fixed 128-array won't suffice; we would use `std::unordered_map<char32_t, int>`, giving $O(\min(N, \Sigma))$ auxiliary space.
4. *"How would you modify your code to return the actual longest substring rather than just its length?"* → Track `bestStart = 0`. Whenever `right - left + 1 > maxLen`, update `maxLen = right - left + 1` and `bestStart = left`. Return `s.substr(bestStart, maxLen)`.

### 7. Leftover Important Details

- Initializing `lastSeen` to `-1` lets us avoid an `if (lastSeen[ch] != -1)` branch if we want: when `lastSeen[ch] == -1`, `lastSeen[ch] + 1` evaluates to `0`, and since `left >= 0`, `max(left, 0)` is always `left`! Keeping the `if` or omitting it are both $O(1)$ and completely valid.
- In C++, `char` may be signed (`-128` to `127`) depending on the compiler/architecture. Always cast `static_cast<unsigned char>(s[right])` before indexing a raw array.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
