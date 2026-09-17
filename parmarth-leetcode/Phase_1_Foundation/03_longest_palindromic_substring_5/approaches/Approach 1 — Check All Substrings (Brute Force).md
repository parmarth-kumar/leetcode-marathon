# Approach 1 — Check All Substrings (Brute Force)

## 1. Core Idea

Enumerate every possible substring `s[i..j]` that is strictly longer than the best palindrome found so far, and verify whether `s[i..j]` is a palindrome using an inward two-pointer check. Track the `(startIdx, maxLen)` of the longest valid substring and extract it once at the end.

## 2. Why It Works

A longest palindromic substring must have some start index `i` (`0 <= i < N`) and some end index `j` (`i <= j < N`). By exhaustively testing all candidate pairs `(i, j)` and verifying symmetry directly (`s[left] == s[right]` as `left` moves right and `right` moves left), we are guaranteed to inspect the optimal substring.

Furthermore, because any single character `s[0..0]` is already a valid palindrome of length `1`, we can initialize `maxLen = 1` and start our inner loop at `j = i + maxLen`. This structural pruning skips all substrings of length `<= maxLen`, ensuring that every palindrome we find is strictly longer than our previous best.

## 3. How To Think About It

1. *"What is the simplest way to find the longest palindromic substring?"* → Test all substrings and keep the longest one that is a palindrome.
2. *"How do I represent a substring without copying characters?"* → By its inclusive index bounds `[i, j]`.
3. *"How do I check if `s[i..j]` is a palindrome in `O(1)` extra space?"* → Place `left = i` and `right = j`, compare `s[left] == s[right]`, and move both pointers inward until `left >= right`.
4. *"Do I really need to check substrings that are shorter than or equal to `maxLen`?"* → No! Starting `j` at `i + maxLen` guarantees `j - i + 1 > maxLen`, so any palindrome found automatically improves our answer.

## 4. Visual Trace

```text
Input: s = "babad" (N = 5)
Initial state: startIdx = 0, maxLen = 1 (representing "b")

i = 0 (j starts at 0 + 1 = 1):
  j = 1: s[0..1] = "ba"
         isPalindrome("babad", 0, 1): s[0]('b') != s[1]('a') → false
  j = 2: s[0..2] = "bab"
         isPalindrome("babad", 0, 2): s[0]('b') == s[2]('b') ✓, left=1 >= right=1 → true!
         Update: maxLen = 2 - 0 + 1 = 3, startIdx = 0 ("bab")
  j = 3: s[0..3] = "baba"
         isPalindrome("babad", 0, 3): s[0]('b') != s[3]('a') → false
  j = 4: s[0..4] = "babad"
         isPalindrome("babad", 0, 4): s[0]('b') != s[4]('d') → false

i = 1 (j starts at 1 + maxLen = 1 + 3 = 4):
  Notice j = 1, 2, 3 (including s[1..3] = "aba" of length 3) are skipped
  because they cannot beat maxLen = 3!
  j = 4: s[1..4] = "abad"
         isPalindrome("babad", 1, 4): s[1]('a') != s[4]('d') → false

i = 2 (j starts at 2 + 3 = 5 >= N → inner loop does not run)
i = 3 (j starts at 3 + 3 = 6 >= N → inner loop does not run)
i = 4 (j starts at 4 + 3 = 7 >= N → inner loop does not run)

Return s.substr(0, 3) → "bab" ✓
```

## 5. Algorithm / Pseudocode

```text
function isPalindrome(s, left, right):
    while left < right:
        if s[left] != s[right]:
            return false
        left++
        right--
    return true

function longestPalindrome(s):
    n = length(s)
    if n <= 1:
        return s

    startIdx = 0
    maxLen = 1

    for i from 0 to n - 1:
        // Only check substrings strictly longer than maxLen
        for j from (i + maxLen) to n - 1:
            if isPalindrome(s, i, j):
                maxLen = j - i + 1
                startIdx = i

    return s.substr(startIdx, maxLen)
```

## 6. Complexity

### Time

- **Claim**: `O(N^3)` worst-case time.
- **Proof**:
  - There are `N(N - 1) / 2 = O(N^2)` pairs of indices `(i, j)` with `i < j`.
  - For a pair `(i, j)` of length `L = j - i + 1`, `isPalindrome(s, i, j)` performs up to `L / 2` character comparisons.
  - Summing across all `(i, j)` pairs in the worst case (e.g., `"aaaa...ab..."` or strings with long matching prefixes/suffixes that fail near the center):
    $$\sum_{i=0}^{N-1} \sum_{j=i+1}^{N-1} \frac{j - i + 1}{2} = \frac{N(N+1)(N+2)}{12} = \Theta(N^3)$$
- **Lower bound**: Reading every character of the input requires at least `Ω(N)` time.

### Space

- **Output space**: `O(N)` — `s.substr(startIdx, maxLen)` allocates the returned palindrome string of length up to `N`.
- **Auxiliary space**: `O(1)` — only four integer variables (`startIdx`, `maxLen`, `i`, `j`) and two loop pointers (`left`, `right`) are used; `s` is passed by `const string&` to `isPalindrome`.
- **Interviewer note**: Never call `s.substr(i, j - i + 1)` inside `isPalindrome` or inside the `(i, j)` loop — doing so allocates `O(N^2)` temporary strings on the heap. Always pass index bounds `(i, j)` on the original string reference.

## 7. C++ Mechanics

- **`const string& s` parameter in helper**: Passing `s` by `const` reference avoids copying the entire string on every `isPalindrome` call (`O(1)` pass-by-reference vs. `O(N)` pass-by-value).
- **Structural Pruning (`j = i + maxLen`)**: By starting `j` at `i + maxLen`, the candidate length is `(i + maxLen) - i + 1 = maxLen + 1`. We never need an `if (j - i + 1 > maxLen)` check inside the loop because it is guaranteed by the loop initializer.
- **`s.substr(startIdx, maxLen)`**: Called once at the end of `longestPalindrome`.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| Single character (`"a"`) | Early return `if (n <= 1) return s;` returns `"a"` immediately. |
| No palindrome longer than 1 (`"abcde"`) | `isPalindrome` returns `false` for all `j >= i + 1`; defaults `startIdx = 0, maxLen = 1` return `"a"`. |
| Entire string is a palindrome (`"racecar"`) | Found at `i = 0, j = n - 1`, setting `maxLen = n`; subsequent `i` iterations immediately skip the inner loop since `i + maxLen >= n`. |
| All identical characters (`"aaaa"`) | `i = 0` updates `maxLen` up to `n` on the first outer iteration; remaining `i > 0` iterations do zero inner loop work due to `j = i + maxLen` pruning. |

## 9. Common Mistakes

1. **Passing `string s` by value to `isPalindrome`**: Copies `N` characters on every single `(i, j)` check, turning even fast mismatches into `O(N)` memory allocations and causing immediate TLE.
2. **Constructing `s.substr()` and calling `std::reverse()` to check palindromes**: Allocates two heap strings per `(i, j)` pair instead of using two integer pointers `left` and `right` in `O(1)` space.
3. **Confusing the second argument of `s.substr(pos, count)`**: Passing the end index `j` instead of the length `maxLen` produces the wrong slice whenever `startIdx > 0`.

## 10. When To Prefer This Approach

- **As a 60-second baseline in an interview**: State this `O(N^3)` approach verbally first so the interviewer sees you can decompose the problem cleanly, then immediately point out the redundant inner checks (`s[i+1..j-1]`) to motivate **Approach 2 (Expand Around Center)**.
- **For small inputs (`N <= 100`) or unit-test oracle verification**: Simple to write and verify against more complex algorithms.
