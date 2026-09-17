# Approach 2 — Expand Around Center (Optimized)

## 1. Core Idea

Every palindrome mirrors around its center. Instead of enumerating `O(N^2)` start/end pairs and checking inward, iterate through all `2N - 1` possible palindrome centers (`N` single-character centers for odd-length palindromes and `N - 1` between-character centers for even-length palindromes) and expand two pointers (`left`, `right`) outward while `s[left] == s[right]`. Track the `(start, maxLen)` of the longest valid window in `O(1)` auxiliary space.

## 2. Why It Works

A substring `s[L..R]` (with length `>= 3`) is a palindrome if and only if:
1. Its outer characters match (`s[L] == s[R]`), **and**
2. Its inner core `s[L+1..R-1]` is already a palindrome.

When we expand outward from a fixed center:
- Every step `left--, right++` builds directly on top of an inner substring that we **just proved** is a palindrome in the previous step.
- Thus, extending a known palindrome by 2 characters requires **only 1 character comparison** (`s[left] == s[right]`), completely eliminating the `O(N)` re-verification work of Brute Force.
- Furthermore, the moment `s[left] != s[right]`, **no larger substring** sharing that exact center can ever be a palindrome, so we can immediately stop expanding from that center.

## 3. How To Think About It

1. *"Why was Brute Force `O(N^3)`?"* → Because checking `"ababa"` re-verified `"bab"` from scratch.
2. *"How can I reuse the fact that `"bab"` is already a palindrome?"* → Start at the center `'b'` and grow outward: `'b'` → `"bab"` → `"ababa"`.
3. *"Where can the center of a palindrome be?"* → Either **on** a character `i` (odd length, like `"aba"`) or **between** two characters `i` and `i + 1` (even length, like `"abba"`).
4. *"How do I write one helper function for both cases?"* → Pass `(left, right)` into `expandAroundCenter(s, left, right)`. Pass `(i, i)` for odd centers and `(i, i + 1)` for even centers!
5. *"What are the exact bounds when the `while` loop stops?"* → The loop stops right after `left` and `right` step one index too far (mismatch or out-of-bounds). So the valid palindrome spans `[left + 1, right - 1]`, with length `(right - 1) - (left + 1) + 1 = right - left - 1`.

## 4. Visual Trace

```text
Trace 1: Odd-length expansion on s = "babad" at i = 1 (center 'a')
Index:    0     1     2     3     4
Chars:    b     a     b     a     d

Call expandAroundCenter(s, left = 1, right = 1):
  - Step 1: left=1, right=1 → s[1]('a') == s[1]('a') ✓ → left=0, right=2
  - Step 2: left=0, right=2 → s[0]('b') == s[2]('b') ✓ → left=-1, right=3
  - Step 3: left=-1 < 0 → loop terminates!

Overshoot recovery:
  validStart = left + 1  = -1 + 1 = 0
  validEnd   = right - 1 =  3 - 1 = 2
  length     = validEnd - validStart + 1 = 3 ("bab") ✓
```

```text
Trace 2: Even-length expansion on s = "cbbd" at i = 1 (center between index 1 and 2)
Index:    0     1     2     3
Chars:    c     b     b     d

Call expandAroundCenter(s, left = 1, right = 2):
  - Step 1: left=1, right=2 → s[1]('b') == s[2]('b') ✓ → left=0, right=3
  - Step 2: left=0, right=3 → s[0]('c') != s[3]('d') ✗ → loop terminates!

Overshoot recovery:
  validStart = left + 1  = 0 + 1 = 1
  validEnd   = right - 1 = 3 - 1 = 2
  length     = validEnd - validStart + 1 = 2 ("bb") ✓
```

## 5. Algorithm / Pseudocode

```text
function expandAroundCenter(s, left, right):
    n = length(s)
    while left >= 0 AND right < n AND s[left] == s[right]:
        left--
        right++
    // Recover last valid matching bounds after 1-step overshoot
    return pair {left + 1, right - 1}

function longestPalindrome(s):
    n = length(s)
    if n <= 1:
        return s

    start = 0
    maxLen = 1

    for i from 0 to n - 1:
        // 1. Odd-length palindromes centered at s[i]
        {l1, r1} = expandAroundCenter(s, i, i)
        if (r1 - l1 + 1) > maxLen:
            maxLen = r1 - l1 + 1
            start = l1

        // 2. Even-length palindromes centered between s[i] and s[i + 1]
        {l2, r2} = expandAroundCenter(s, i, i + 1)
        if (r2 - l2 + 1) > maxLen:
            maxLen = r2 - l2 + 1
            start = l2

    return s.substr(start, maxLen)
```

## 6. Complexity

### Time

- **Claim**: `O(N^2)` worst-case time (`O(N)` best-case time when all characters are distinct).
- **Proof**:
  - The outer loop runs `N` times (`i = 0` to `N - 1`), invoking `expandAroundCenter` twice per iteration (`2N` calls total; the last even call `(N-1, N)` immediately exits in `O(1)`).
  - For a center at index `i`, the pointer `left` starts at `i` and decrements at most `i + 1` times before `left < 0`, while `right` starts at `i` (or `i + 1`) and increments at most `N - i` times before `right == N`.
  - Thus, a single expansion performs at most `min(i + 1, N - i) <= N / 2` character comparisons.
  - Summing across all `2N - 1` centers in the worst case (`s = "aaaa...a"`):
    $$\text{Total Comparisons} \le 2 \sum_{i=0}^{N-1} \min(i + 1, N - i) \approx 2 \cdot 2 \sum_{k=1}^{N/2} k = 4 \cdot \frac{(N/2)(N/2 + 1)}{2} \approx \frac{N^2}{2} = \Theta(N^2)$$
- **Lower bound**: Any algorithm must inspect every character at least once → `Ω(N)`. (Manacher's Algorithm achieves the `Θ(N)` theoretical lower bound at the cost of `O(N)` extra space).

### Space

- **Output space**: `O(N)` — the returned `std::string` of length `maxLen <= N`.
- **Auxiliary space**: `O(1)` — only integer index variables (`start`, `maxLen`, `i`, `left`, `right`, `l1`, `r1`, `l2`, `r2`) live on the stack.
- **Interviewer note**: Compared to 2D Dynamic Programming (`O(N^2)` time and `O(N^2)` auxiliary space for the boolean `dp[N][N]` table), Expand Around Center achieves the same `O(N^2)` time while reducing auxiliary memory from `O(N^2)` to `O(1)`.

## 7. C++ Mechanics

- **Returning `pair<int, int>` + C++17 Structured Bindings (`auto [l1, r1]`)**: Returning `{left + 1, right - 1}` directly from `expandAroundCenter` avoids error-prone index math like `start = i - (len - 1) / 2` in the caller. Note that when no even-length palindrome exists at `(i, i + 1)`, the loop does zero iterations and returns `{i + 1, i}`, which naturally has length `i - (i + 1) + 1 = 0`.
- **Short-Circuit Evaluation in `while` Condition**: In `left >= 0 && right < n && s[left] == s[right]`, C++ evaluates `&&` left-to-right and stops as soon as a condition is `false`. Putting the bounds checks `left >= 0 && right < n` **before** `s[left] == s[right]` prevents out-of-bounds memory access.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Single character (`"a"`) | Handled by `if (n <= 1) return s;` (or `expandAroundCenter(s, 0, 0)` returning `{0, 0}`). |
| Two identical characters (`"aa"`) | At `i = 0`, even expansion `(0, 1)` matches `s[0] == s[1]` and returns `{0, 1}` of length `2`. |
| Two different characters (`"ac"`) | Odd expansion at `i = 0` gives `{0, 0}` (length 1); even expansion at `(0, 1)` immediately fails and returns `{1, 0}` (length 0). Returns `"a"`. |
| Even center at `i = n - 1` | `expandAroundCenter(s, n - 1, n)` checks `right < n` (`n < n` is `false`), exits immediately without reading `s[n]`, and returns `{n, n - 1}` (length 0). |
| All identical characters (`"aaaaaa"`) | Reaches the maximum valid expansion at the midpoint center, returning the full string. |

## 9. Common Mistakes

1. **Checking `s[left] == s[right]` before `left >= 0 && right < n`**: Causes an out-of-bounds read (`s[-1]` or `s[n]`), triggering AddressSanitizer / undefined behavior on LeetCode.
2. **Returning `{left, right}` instead of `{left + 1, right - 1}`**: Forgets that the `while` loop decrements `left` and increments `right` one final time *before* the termination check fails.
3. **Only expanding around `(i, i)`**: Misses all even-length palindromes like `"cbbd"` → `"bb"` or `"forgeeksskeegfor"` → `"geeksskeeg"`.

## 10. When To Prefer This Approach

- **Primary interview solution for LeetCode #5 and #647**: Cleanest to implement under interview time pressure, bug-free when returning `{left + 1, right - 1}`, and optimal in auxiliary space (`O(1)`).
- **Whenever `N <= 5000` and `O(1)` memory is valued**: Outperforms 2D DP in both runtime constants (no heap allocation, sequential cache access) and memory footprint.
