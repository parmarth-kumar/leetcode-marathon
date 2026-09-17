Problem      : Longest Palindromic Substring
LeetCode     : https://leetcode.com/problems/longest-palindromic-substring/
Topic        : String, Two Pointers, Dynamic Programming
Difficulty   : Medium
Google-Tagged: Yes
Phase        : 1 — Foundation
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given a string `s`. Your goal is to find and return the **longest continuous stretch of characters** (substring) inside `s` that reads **the exact same forward and backward** (a palindrome).

If there are multiple palindromic substrings tied for the maximum length, returning **any one** of them is valid.

### Input & Output

- **Input**: `string s` — a non-empty string consisting of only digits and English letters (lowercase and/or uppercase).
- **Output**: `string` — the longest palindromic substring within `s`.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `1 <= s.length <= 1000` | String is never empty under standard LeetCode constraints (at least 1 character exists). |
| `s` consists of only digits and English letters | Standard ASCII characters (`'0'-'9'`, `'a'-'z'`, `'A'-'Z'`). Case-sensitive comparison (`'A' != 'a'`). |
| Max length `N = 1000` | `O(N^2)` (~`10^6` operations) passes effortlessly; `O(N^3)` (~`1.6 * 10^8` operations) risks Time Limit Exceeded (TLE). |

**CPU intuition**: A modern judge executes roughly `10^8` basic operations per second.
- **`O(N^3)` Brute Force**: Checking all `N(N+1)/2 ≈ 5 * 10^5` substrings with an `O(N)` palindrome check takes `~1.6 * 10^8` character comparisons in the worst case — right on the edge of TLE.
- **`O(N^2)` Expand Around Center / 2D DP**: Around `10^6` operations for `N = 1000`, executing in under 10 milliseconds.
- **`O(N)` Manacher's Algorithm**: Around `2000` operations, executing in under 1 millisecond (useful if `N <= 10^5`, though `O(N^2)` with `O(1)` space is the primary interview expectation for `N <= 1000`).

### Terminology

- **Palindrome**: A sequence of characters that reads identically forward and backward (e.g., `"racecar"`, `"noon"`, `"a"`). Every single character is trivially a palindrome of length 1.
- **Substring**: A **contiguous** (unbroken) block of characters within a string, with zero gaps or skipped characters.
- **Subsequence**: Characters chosen in relative order, allowing gaps/skips (e.g., `"ace"` is a subsequence of `"abcde"`, but **not** a substring).
- **Center of Symmetry**: The midpoint of a palindrome across which the left half mirrors the right half. It sits either directly **on a character** (for odd-length palindromes like `"aba"`) or **between two adjacent characters** (for even-length palindromes like `"abba"`).

### Worked Examples

**Example 1** — Odd-length palindromes (`s = "babad"`):
```text
Index:  0   1   2   3   4
Char:   b   a   b   a   d

- Length 1 substrings: "b", "a", "b", "a", "d" → all valid palindromes (best length = 1)
- Length 2 substrings: "ba", "ab", "ba", "ad"  → none match
- Length 3 substrings:
    s[0..2] = "bab" → reverse is "bab" ✓ (Palindrome, length = 3)
    s[1..3] = "aba" → reverse is "aba" ✓ (Palindrome, length = 3)
    s[2..4] = "bad" → reverse is "dab" ✗
- Length 4 & 5 substrings: "baba", "abad", "babad" → none match

Output: "bab" (or "aba" — both have maximum length 3)
```

**Example 2** — Even-length palindrome (`s = "cbbd"`):
```text
Index:  0   1   2   3
Char:   c   b   b   d

- Length 1: "c", "b", "b", "d" (length 1)
- Length 2:
    s[0..1] = "cb" ✗
    s[1..2] = "bb" ✓ (Palindrome, length = 2)
    s[2..3] = "bd" ✗
- Length 3 & 4: "cbb", "bbd", "cbbd" ✗

Output: "bb" (length 2)
```

**Example 3** — Entire string is a palindrome (`s = "racecar"`):
```text
Index:  0   1   2   3   4   5   6
Char:   r   a   c   e   c   a   r
                    ^
              center (index 3)

s[2] == s[4] ('c' == 'c') ✓
s[1] == s[5] ('a' == 'a') ✓
s[0] == s[6] ('r' == 'r') ✓

Output: "racecar" (length 7)
```

**Example 4** — Long even-length palindrome embedded inside (`s = "forgeeksskeegfor"`):
```text
Indices: 0 1 2 [3 4 5 6 7 | 8 9 10 11 12] 13 14 15
Chars:   f o r [g e e k s | s k  e  e  g]  f  o  r
                          ^
                center between 7 and 8

Expanding outward from (7, 8):
  's' == 's', 'k' == 'k', 'e' == 'e', 'e' == 'e', 'g' == 'g' ✓
  Next step: s[2] = 'r' vs s[13] = 'f' ✗ (Mismatch!)

Output: "geeksskeeg" (indices 3..12, length 10)
```

### Common Beginner Traps

1. **Confusing Substring with Subsequence**: If you skip characters to form a palindrome, you are solving *Longest Palindromic Subsequence* (LC 516), which requires 2D Dynamic Programming. Here, characters must be strictly contiguous.
2. **The "Reverse + Longest Common Substring" Fallacy**: Reversing `s` into `s_rev` and finding the Longest Common Substring fails when a non-palindromic substring appears reversed elsewhere in `s`. For example, in `s = "abacdfgdcaba"`, `s_rev = "abacdgfdcaba"`, the longest common substring is `"abacd"` (length 5), which is **not** a palindrome!
3. **Forgetting Even-Length Palindromes**: Expanding only around single characters `s[i]` finds `"aba"` but misses `"abba"` or `"bb"` in `"cbbd"` because even-length palindromes have their center *between* `s[i]` and `s[i+1]`.
4. **Calling `s.substr()` Inside Inner Loops**: `s.substr(pos, len)` allocates and copies a new string in `O(len)` time. Calling it inside an `O(N^2)` loop silently inflates time and memory. Instead, track integer indices `(start, maxLen)` and call `s.substr(start, maxLen)` **once** at the very end.

### One-Sentence Restatement

> Find the longest contiguous block of characters in `s` that mirrors perfectly across its center of symmetry.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. `std::string` Indexing & `.substr(pos, count)`

**What it is**: Zero-indexed random access to characters and extracting a contiguous slice of a C++ string.

**Mechanics**:
- `s[i]` accesses the character at index `i` in `O(1)` time (`0 <= i < s.length()`).
- `s.substr(start, length)` returns a new `string` starting at index `start` containing `length` characters (Notice the second argument is **length**, not the end index!).

**Example**:
```cpp
string s = "babad";
// Extract substring from index 1 of length 3 ("aba"):
string sub = s.substr(1, 3); // "aba"
```

**Why it matters here**: During the search, we represent any candidate substring using only its `(start, maxLen)` integers in `O(1)` space, and construct the result string once at the end via `s.substr(start, maxLen)`.

### 2. Two Pointers (Inward vs. Outward Movement)

**What it is**: Using two index variables (`left` and `right`) that move in coordinated steps across a sequence.

**Mechanics**:
- **Inward convergence**: Start `left` at the start of a range and `right` at the end; move `left++` and `right--` while characters match (used to verify if a fixed substring `s[i..j]` is a palindrome).
- **Outward expansion**: Start `left` and `right` at a center point; move `left--` and `right++` while `left >= 0`, `right < n`, and `s[left] == s[right]`.

**Example**:
```cpp
// Expanding outward from center:
while (left >= 0 && right < n && s[left] == s[right]) {
    left--;
    right++;
}
```

**Why it matters here**: Switching from inward verification (`O(N^3)`) to outward expansion (`O(N^2)`) is the core algorithmic breakthrough of this problem.

### 3. Bilateral Symmetry & The `2N - 1` Centers Property

**What it is**: Every palindrome is symmetric around a unique midpoint.

**Mechanics**:
In a string of length `N`, where can a palindrome's center lie?
1. **On a character** (`left = i, right = i`): Produces **odd-length** palindromes (`1, 3, 5, ...`). There are `N` such centers.
2. **Between two adjacent characters** (`left = i, right = i + 1`): Produces **even-length** palindromes (`2, 4, 6, ...`). There are `N - 1` such centers.

Total possible centers = `N + (N - 1) = 2N - 1`.

**Example** (`s = "cbbd"`, `N = 4`):
```text
Odd centers  (4): (0,0)='c', (1,1)='b', (2,2)='b', (3,3)='d'
Even centers (3): (0,1)="cb", (1,2)="bb", (2,3)="bd"
Total = 7 centers.
```

**Why it matters here**: Since there are only `2N - 1` possible centers in the entire string, we can exhaustively expand around every single one of them in `O(N^2)` total time.

### 4. Pointer Overshoot & Substring Length Math

**What it is**: Determining the exact boundaries and length of a valid range after a `while` loop terminates.

**Mechanics**:
- For an inclusive range `[L, R]`, the number of elements is `R - L + 1`.
- When an outward expansion loop `while (left >= 0 && right < n && s[left] == s[right]) { left--; right++; }` stops, `left` and `right` have stepped **one position too far** on both sides.
- Therefore, the last valid matching indices are `left + 1` and `right - 1`, and the valid length is `(right - 1) - (left + 1) + 1 = right - left - 1`.

**Why it matters here**: Off-by-one errors in pointer recovery are the #1 bug in palindrome expansion code.

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

Every single character in `s` is already a palindrome of length 1. So `maxLen` is at least `1` (for `N >= 1`). To find a longer palindrome, we need a substring whose characters mirror each other across its midpoint.

### Step-by-Step Reasoning

**Step 1 — The Naive / Direct Thought Process**:
What is the most direct way to guarantee we find the longest palindromic substring?
- Enumerate every possible start index `i` (`0 <= i < N`) and end index `j` (`i <= j < N`).
- For each pair `(i, j)`, check if `s[i..j]` is a palindrome by comparing `s[left]` and `s[right]` moving inward from `(i, j)`.
- Notice a free structural pruning: if we already found a palindrome of length `maxLen`, we never need to check any `j < i + maxLen`!
- **Why is this still slow?** There are `O(N^2)` substrings and each check takes up to `O(N)` time → `O(N^3)` worst-case time.

**Step 2 — Spot the Redundant Work**:
Watch what happens when Brute Force checks substrings of `"ababa"`:
```text
Check s[1..3] = "bab"   → compares s[1] ('b') == s[3] ('b') ✓ (Palindrome!)
Check s[0..4] = "ababa" → compares s[0] ('a') == s[4] ('a') ✓
                        → compares s[1] ('b') == s[3] ('b') ✓  <-- DUPLICATE WORK!
```
Why did we re-verify that `"bab"` is a palindrome when checking `"ababa"`?
Because checking **from the outside inward** forgets whether the inner core was already a palindrome!

**Step 3 — Flip the Direction (Inside Outward)**:
What if we invert the direction and grow palindromes **from the center outward**?
- Start at a center (e.g., index `2`, `'b'` in `"ababa"`).
- Step 1 outward: compare `s[1]` and `s[3]` (`'b' == 'b'`) → `"bab"` is a palindrome!
- Step 2 outward: compare `s[0]` and `s[4]` (`'a' == 'a'`) → `"ababa"` is a palindrome!
- If at any step `s[left] != s[right]`, we **stop immediately** — no larger substring centered at this point can ever be a palindrome!

**Step 4 — Account for Both Odd and Even Centers**:
For each index `i` from `0` to `N - 1`, we launch two expansions:
1. Odd-length expansion anchored at `(left = i, right = i)`.
2. Even-length expansion anchored at `(left = i, right = i + 1)`.

### Visual Trace

**Trace 1: `s = "babad"` (`N = 5`, `2N - 1 = 9` centers)**

| Center `i` | Type | Initial `(L, R)` | Outward Comparisons | Final Valid `[L+1, R-1]` | Palindrome | Length | Best So Far |
|:---:|:---:|:---:|:---|:---:|:---:|:---:|:---:|
| `0` | Odd | `(0, 0)` | `s[0]==s[0]` ✓ → `L=-1, R=1` (bounds) | `[0, 0]` | `"b"` | 1 | `"b"` (1) |
| `0` | Even | `(0, 1)` | `s[0]!=s[1]` (`'b'!='a'`) ✗ | — | — | 0 | `"b"` (1) |
| `1` | Odd | `(1, 1)` | `s[1]==s[1]` ✓ → `s[0]==s[2]` (`'b'=='b'`) ✓ → `L=-1, R=3` | `[0, 2]` | `"bab"` | **3** | `"bab"` (3) |
| `1` | Even | `(1, 2)` | `s[1]!=s[2]` (`'a'!='b'`) ✗ | — | — | 0 | `"bab"` (3) |
| `2` | Odd | `(2, 2)` | `s[2]==s[2]` ✓ → `s[1]==s[3]` (`'a'=='a'`) ✓ → `s[0]!=s[4]` (`'b'!='d'`) ✗ | `[1, 3]` | `"aba"` | 3 | `"bab"` (3, tie) |
| `2` | Even | `(2, 3)` | `s[2]!=s[3]` (`'b'!='a'`) ✗ | — | — | 0 | `"bab"` (3) |
| `3` | Odd | `(3, 3)` | `s[3]==s[3]` ✓ → `s[2]!=s[4]` (`'b'!='d'`) ✗ | `[3, 3]` | `"a"` | 1 | `"bab"` (3) |
| `3` | Even | `(3, 4)` | `s[3]!=s[4]` (`'a'!='d'`) ✗ | — | — | 0 | `"bab"` (3) |
| `4` | Odd | `(4, 4)` | `s[4]==s[4]` ✓ → `L=3, R=5` (bounds) | `[4, 4]` | `"d"` | 1 | `"bab"` (3) |

**Trace 2: `s = "cbbd"` (Catching the Even Center at `i = 1`)**
```text
Index:  0   1   2   3
Char:   c   b   b   d

At i = 1:
  Odd expansion  (1, 1): s[1]==s[1] ✓, next s[0]!=s[2] ('c'!='b') ✗ → "b" (len 1)
  Even expansion (1, 2): s[1]==s[2] ('b'=='b') ✓ → L=0, R=3
                         s[0]!=s[3] ('c'!='d') ✗ → stops!
                         Valid range = [L+1, R-1] = [1, 2] → "bb" (len 2) ✓
```

### Questions an Interviewer Expects You to Ask

1. *"If there are multiple longest palindromic substrings of the same maximum length, does it matter which one I return?"* → No, any one of them is acceptable.
2. *"Is character comparison case-sensitive, and can the string contain non-alphanumeric characters?"* → Case-sensitive (`'a' != 'A'`), and only alphanumeric characters appear.
3. *"Do you prefer optimizing for `O(1)` auxiliary space (`O(N^2)` Expand Around Center) or strict `O(N)` time (`O(N)` space Manacher's Algorithm)?"* → Almost always `O(N^2)` time with `O(1)` auxiliary space in a 45-minute interview, with a brief verbal explanation of Manacher's if asked.

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Check All Substrings (Brute Force)

- **Type**: Brute Force
- **Time**: `O(N^3)`
- **Space**: `O(N)` output, `O(1)` auxiliary
- Enumerate all `(i, j)` substring boundaries (pruning substrings shorter than `maxLen`) and verify each candidate with an inward two-pointer check.
- 📄 [Approach 1 — Check All Substrings (Brute Force).md](<./approaches/Approach 1 — Check All Substrings (Brute Force).md>)
- 💻 [Approach 1 — Check All Substrings (Brute Force).cpp](<./approaches/Approach 1 — Check All Substrings (Brute Force).cpp>)

### Approach 2 — Expand Around Center (Optimized)

- **Type**: Optimized
- **Time**: `O(N^2)`
- **Space**: `O(N)` output, `O(1)` auxiliary
- Expand two pointers outward from all `2N - 1` possible palindrome centers (`N` single-character odd centers and `N - 1` between-character even centers) and track the longest valid window.
- 📄 [Approach 2 — Expand Around Center (Optimized).md](<./approaches/Approach 2 — Expand Around Center (Optimized).md>)
- 💻 [Approach 2 — Expand Around Center (Optimized).cpp](<./approaches/Approach 2 — Expand Around Center (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Two Pointers — Outward Center Expansion**: Exploiting bilateral symmetry by anchoring two pointers at each of the `2N - 1` potential centers and expanding outward while characters match.

### 2. Mental Model

> "Whenever a problem asks to find or count **palindromic substrings** (contiguous), think **2N - 1 centers + outward two-pointer expansion** to achieve `O(N^2)` time in `O(1)` auxiliary space."

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- A string of length `N` has `2N - 1` palindrome centers: `(i, i)` for odd length and `(i, i + 1)` for even length.
- Outward expansion loop condition: `while (left >= 0 && right < n && s[left] == s[right])`.
- When the loop terminates, `left` and `right` have overshot by 1: valid start is `left + 1`, valid end is `right - 1`, and valid length is `right - left - 1`.
- Track `(start, maxLen)` as integers and call `s.substr(start, maxLen)` only once at the end.

**SHOULD UNDERSTAND**:
- Why inward checking (`O(N^3)`) repeats work while outward expansion (`O(N^2)`) reuses the already-verified inner palindrome on every step.
- Why Expand Around Center (`O(1)` auxiliary space) is preferred in interviews over 2D Dynamic Programming (`O(N^2)` auxiliary space for `dp[i][j]`), even though both run in `O(N^2)` time.
- Why **substrings** allow center expansion (contiguous), whereas **subsequences** (LC 516) require 2D Interval DP (since characters can be skipped).

**SHOULD BE ABLE TO RE-DERIVE**:
- Recovering `start = i - (len - 1) / 2` from the center index `i` and length `len` if your helper returns `int` length instead of a `{left + 1, right - 1}` pair.
- How Manacher's Algorithm unifies odd and even centers by inserting `#` separators (`"aba"` → `"^#a#b#a#$"`) and reuses mirror radii across the rightmost palindrome boundary to reach `O(N)` time.

### 4. Previously Seen Patterns (Cross-Reference)

You saw the **Two Pointers** pattern in **Problem 02 — Container With Most Water (LC 11)**.
- In **Container With Most Water**, the two pointers started at the **outer edges** (`left = 0`, `right = n - 1`) and converged **inward** (`left++` or `right--`). We also use that exact inward convergence inside `isPalindrome(s, i, j)` in Approach 1.
- The key difference in **Longest Palindromic Substring (Approach 2)** is that we invert the pointer direction: we place `left` and `right` at a **center** (`(i, i)` or `(i, i + 1)`) and expand **outward** (`left--`, `right++`) to grow symmetric substrings in `O(1)` auxiliary space.

### 5. Related LeetCode Problems

| Problem | Why Related |
|:--------|:------------|
| [LC 647 — Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) | Uses the exact same `2N - 1` center expansion! Instead of tracking `maxLen`, increment a counter every time `s[left] == s[right]`. |
| [LC 516 — Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) | The subsequence counterpart (gaps allowed). Contrasts when Center Expansion works (contiguous) vs. when 2D Interval DP is mandatory. |
| [LC 125 — Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) | Foundational inward two-pointer palindrome check with alphanumeric filtering. |
| [LC 131 — Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) | Combines backtracking with precomputed palindrome substring checks. |
| [LC 214 — Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) | Hard follow-up requiring the longest palindromic prefix starting at index 0 (via KMP prefix table or rolling hash). |

### 6. Interview Questions

1. *"Why use Expand Around Center instead of 2D Dynamic Programming?"* → Both run in `O(N^2)` time, but 2D DP allocates an `N × N` boolean table (`O(N^2)` auxiliary space, ~1 MB for `N = 1000`) with worse cache locality, whereas Expand Around Center uses `O(1)` auxiliary space.
2. *"Why does reversing the string and finding the Longest Common Substring fail?"* → Because a non-palindromic substring (like `"abacd"` in `"abacdfgdcaba"`) can appear reversed at another position in the string. You would have to additionally verify that the matched indices map to the exact same region in `s`.
3. *"What is the worst-case input for Expand Around Center, and what is the best-case input?"* → Worst case is all identical characters (e.g., `"aaaa...a"`), where every center expands all the way to the nearest boundary (`~N^2 / 2` comparisons). Best case is a string with all distinct characters (e.g., `"abcdef..."`), where every center mismatches in `1` step (`O(N)` comparisons).
4. *"Can you solve this in `O(N)` time?"* → Yes, using Manacher's Algorithm, which inserts `#` between characters so all palindromes become odd-length and reuses previously computed palindrome radii mirrored across the current rightmost palindrome's center.

### 7. Leftover Important Details

- **2D DP State Transition (Good to know for discussions)**: If asked how DP solves this, `dp[i][j] = (s[i] == s[j]) && (j - i <= 2 || dp[i + 1][j - 1])`, iterating over increasing substring lengths `L = 1..N`.
- **Manacher's Algorithm in Interviews**: No interviewer expects you to write Manacher's from scratch in 20 minutes unless it is a specialized CP role, but being able to explain the `#` separator trick and mirror-radius reuse in 60 seconds is a strong senior signal.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
