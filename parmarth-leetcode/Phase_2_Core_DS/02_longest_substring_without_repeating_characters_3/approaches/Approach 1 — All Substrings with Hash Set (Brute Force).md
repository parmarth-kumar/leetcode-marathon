# Approach 1 — All Substrings with Hash Set (Brute Force)

## 1. Core Idea

For every possible starting index `i` in `s`, expand the ending index `j` from `i` rightward one character at a time while maintaining a lookup set (`visited[128]`) of characters seen in `s[i..j]`. Update the maximum length as long as characters remain unique, and break out of the inner loop the moment the first duplicate is encountered.

## 2. Why It Works

Every contiguous substring has a unique start index `i` and end index `j` ($0 \le i \le j < N$). By testing all valid start indices `i` and extending `j` until a duplicate appears, we are guaranteed to inspect the longest duplicate-free substring starting at every possible index `i`. Furthermore, breaking on the first duplicate at `j` is completely safe because if `s[i..j]` already contains a duplicate pair, any longer substring `s[i..k]` ($k > j$) starting at the same `i` will still contain that duplicate pair.

## 3. How To Think About It

1. *"What is the most direct way to find the longest valid substring?"* → Check all substrings.
2. *"A pure $O(N^3)$ loop generates every `s[i..j]` and rescans `k` from `i` to `j` to check uniqueness. Where is the wasted work?"*
3. *"When I extend `s[i..j-1]` to `s[i..j]`, I already verified `s[i..j-1]` had all unique characters! I only need to check whether the single new character `s[j]` has already appeared since `i`."*
4. *"If I maintain a `visited` set for the current `i`, checking and inserting `s[j]` takes $O(1)$ time, and I can stop extending `j` immediately when `visited[s[j]]` is true."*

## 4. Visual Trace

Tracing `s = "pwwkew"`:

```text
Indices:  0  1  2  3  4  5
Chars:    p  w  w  k  e  w

i = 0 ('p'):
  j = 0 ('p'): visited = {'p'}           → unique, len = 1, maxLen = 1
  j = 1 ('w'): visited = {'p', 'w'}      → unique, len = 2, maxLen = 2
  j = 2 ('w'): 'w' already in visited!   → BREAK inner loop

i = 1 ('w'):
  j = 1 ('w'): visited = {'w'}           → unique, len = 1, maxLen = 2
  j = 2 ('w'): 'w' already in visited!   → BREAK inner loop

i = 2 ('w'):
  j = 2 ('w'): visited = {'w'}           → unique, len = 1, maxLen = 2
  j = 3 ('k'): visited = {'w', 'k'}      → unique, len = 2, maxLen = 2
  j = 4 ('e'): visited = {'w', 'k', 'e'} → unique, len = 3, maxLen = 3
  j = 5 ('w'): 'w' already in visited!   → BREAK inner loop

i = 3 ('k'):
  j = 3..5 ("kew"): all unique           → len = 3, maxLen = 3

i = 4 ('e'):
  j = 4..5 ("ew"):  all unique           → len = 2, maxLen = 3

i = 5 ('w'):
  j = 5..5 ("w"):   all unique           → len = 1, maxLen = 3

Final Result: maxLen = 3
```

## 5. Algorithm / Pseudocode

```text
function lengthOfLongestSubstring(s):
    n = s.length()
    maxLen = 0

    for i = 0 to n - 1:
        visited[128] = {false}   // reset seen set for start index i

        for j = i to n - 1:
            ch = unsigned_char(s[j])
            if visited[ch] is true:
                break            // s[i..j] has a duplicate; larger j will too

            visited[ch] = true
            maxLen = max(maxLen, j - i + 1)

    return maxLen
```

## 6. Complexity

### Time

- **Claim**: $O(N^2)$ worst-case time (more precisely, $O(N \cdot \min(N, \Sigma))$ where $\Sigma$ is the alphabet size).
- **Proof**:
  - The outer loop runs $N$ times (for $i = 0, 1, \dots, N-1$).
  - For each $i$, the inner loop increments $j$ until either $j$ reaches $N-1$ or `s[j]` duplicates a previous character.
  - Over a general alphabet where all $N$ characters can be distinct, the inner loop runs $N - i$ iterations for each $i$, performing $O(1)$ work per iteration:
    $$\sum_{i=0}^{N-1} (N - i) = \frac{N(N + 1)}{2} = O(N^2)$$
  - *(Pigeonhole Note)*: When the character set $\Sigma$ is fixed (e.g., $\Sigma = 128$ ASCII), the inner loop can execute at most $\Sigma + 1 = 129$ iterations before the Pigeonhole Principle guarantees a duplicate character and triggers `break`. Still, for general $\Sigma$, the paradigm is quadratic $O(N^2)$ (and unpruned substring verification without `break` is $O(N^3)$).
- **Lower bound**: $\Omega(N)$, since every character in the input string must be inspected at least once to know whether it extends the longest unique substring.

### Space

- **Output space**: $O(1)$ — returns a single `int`.
- **Auxiliary space**: $O(\min(N, \Sigma))$ — the lookup structure stores at most $\min(N, \Sigma)$ distinct characters at any time. Using `bool visited[128]` for ASCII takes $128\text{ bytes} = O(1)$ fixed stack space.
- **Interviewer note**: If implemented with `std::unordered_set<char>`, auxiliary space is still $O(\min(N, \Sigma))$, but heap allocations and hashing make it significantly slower than `bool visited[128]`.

## 7. C++ Mechanics

- **`bool visited[128] = {false};`**: Zero-initializes all 128 booleans on the stack in a single fast memory operation (`memset`/register zeroing) at the start of each outer loop iteration.
- **`static_cast<unsigned char>(s[j])`**: Standard `char` in C++ is signed on most x86/ARM compilers (`-128` to `127`). Casting to `unsigned char` ensures values are in `[0, 255]`, preventing negative array indices.
- **`std::max(maxLen, j - i + 1)`**: Requires `<algorithm>`. Both arguments must have matching integer types (`int`).

## 8. Edge Cases

| Case | Input | How Approach 1 Handles It |
|:-----|:------|:--------------------------|
| Empty string | `""` | `n = 0`; outer loop `i < 0` never executes; returns `maxLen = 0`. |
| Single character | `" "` or `"z"` | `i = 0, j = 0` runs once; `maxLen` becomes `0 - 0 + 1 = 1`. |
| All identical | `"bbbbb"` | For every `i`, `j = i` succeeds (`len = 1`) and `j = i + 1` immediately hits `visited['b'] == true` and breaks. Returns `1`. |
| All unique | `"abcdef"` | Inner loop runs all the way to `n - 1` for every `i`. `i = 0, j = 5` records `6`. |
| Non-letter ASCII | `"a b!a"` | `visited` has size `128`, safely indexing `' '` (32) and `'!'` (33). |

## 9. Common Mistakes

1. **Forgetting to reset `visited` inside the outer loop**: Declaring `visited` outside the `for (int i ...)` loop without clearing it causes characters from `i = 0` to falsely block `i = 1`.
2. **Continuing instead of `break` on duplicate**: Writing `if (visited[ch]) continue;` skips duplicate characters and computes the length of a *subsequence* instead of a *substring*.
3. **Using `j - i` instead of `j - i + 1`**: Off-by-one error that undercounts every substring length by `1`.

## 10. When To Prefer This Approach

- **In an interview**: State this approach verbally in 30 seconds as your baseline ($O(N^2)$ with early exit) to demonstrate structured thinking, then immediately point out the redundancy (re-scanning `s[i+1..j-1]`) to motivate Approach 2 (Sliding Window).
- **For small inputs or sanity-checking**: Useful as a reference oracle in stress tests against the $O(N)$ sliding window implementation.
