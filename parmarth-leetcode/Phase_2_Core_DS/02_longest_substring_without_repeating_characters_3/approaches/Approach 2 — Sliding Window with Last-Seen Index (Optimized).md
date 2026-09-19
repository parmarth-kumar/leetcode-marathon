# Approach 2 — Sliding Window with Last-Seen Index (Optimized)

## 1. Core Idea

Maintain a dynamic sliding window `s[left..right]` containing only unique characters, alongside a direct-access lookup table `lastSeen[128]` storing the most recent index of each ASCII character. As `right` advances through the string, if `s[right]` has been seen before, jump `left` directly to `max(left, lastSeen[s[right]] + 1)`, update `lastSeen[s[right]] = right`, and update `maxLen = max(maxLen, right - left + 1)`.

## 2. Why It Works

**Loop Invariant**: At the end of every iteration `right`, `left` is the **smallest** valid starting index such that the substring `s[left..right]` contains zero duplicate characters.

- **Base case (`right = 0`)**: `left = 0`, and `s[0..0]` has length 1 with no duplicates.
- **Inductive step**: Suppose `s[left..right-1]` is the longest duplicate-free window ending at `right - 1`. When we append `ch = s[right]`:
  1. The *only* character capable of introducing a duplicate into `s[left..right]` is `ch` itself.
  2. If `lastSeen[ch] < left` (or `-1`), then `ch` does not appear inside `s[left..right-1]`. Thus `s[left..right]` is still duplicate-free, and `left` does not need to move.
  3. If `lastSeen[ch] >= left`, then `ch` appears at index `p = lastSeen[ch]` inside our current window. Any window ending at `right` that starts at or before `p` will contain two copies of `ch` (at `p` and `right`). Therefore, the earliest valid start index for a window ending at `right` is `p + 1`.
  4. Both cases are captured by `left = max(left, lastSeen[ch] + 1)`.

Because we compute the longest valid window ending at *every* possible `right` ($0 \le \text{right} < N$), taking the maximum over all `right` is guaranteed to find the global longest substring without repeating characters.

## 3. How To Think About It

1. *"In Approach 1, when `s[i..j]` failed because `s[j]` duplicated `s[p]` ($i \le p < j$), why was incrementing `i` one by one wasteful?"*
2. *"Every start index from `i` through `p` still includes both `s[p]` and `s[j]`. And once we jump start to `p + 1`, we already know `s[p+1..j-1]` has no duplicates!"*
3. *"So `right` never needs to move backward, and `left` can jump directly to `lastSeen[s[right]] + 1`."*
4. *"Wait — what if `lastSeen[s[right]]` is from way back before `left` (like the second `'a'` in `"abba"`)? `left` must never move backward! Guard the jump with `left = max(left, lastSeen[ch] + 1)`."*

## 4. Visual Trace

### Trace 1 — Standard Input (`s = "abcabcbb"`)

```text
Indices:  0  1  2  3  4  5  6  7
Chars:    a  b  c  a  b  c  b  b

right = 0 ('a'): lastSeen['a']=-1 → left=0, window=[a]       (0..0), len=1, maxLen=1, lastSeen['a']=0
right = 1 ('b'): lastSeen['b']=-1 → left=0, window=[a b]     (0..1), len=2, maxLen=2, lastSeen['b']=1
right = 2 ('c'): lastSeen['c']=-1 → left=0, window=[a b c]   (0..2), len=3, maxLen=3, lastSeen['c']=2
right = 3 ('a'): lastSeen['a']=0  → left=max(0, 0+1)=1,
                                    window=[b c a]           (1..3), len=3, maxLen=3, lastSeen['a']=3
right = 4 ('b'): lastSeen['b']=1  → left=max(1, 1+1)=2,
                                    window=[c a b]           (2..4), len=3, maxLen=3, lastSeen['b']=4
right = 5 ('c'): lastSeen['c']=2  → left=max(2, 2+1)=3,
                                    window=[a b c]           (3..5), len=3, maxLen=3, lastSeen['c']=5
right = 6 ('b'): lastSeen['b']=4  → left=max(3, 4+1)=5,
                                    window=[c b]             (5..6), len=2, maxLen=3, lastSeen['b']=6
right = 7 ('b'): lastSeen['b']=6  → left=max(5, 6+1)=7,
                                    window=[b]               (7..7), len=1, maxLen=3, lastSeen['b']=7

Result: maxLen = 3
```

### Trace 2 — The `"abba"` Pointer Regression Guard

```text
Indices:  0  1  2  3
Chars:    a  b  b  a

right = 0 ('a'): lastSeen['a']=-1 → left=0, window="a"  (0..0), len=1, maxLen=1, lastSeen['a']=0
right = 1 ('b'): lastSeen['b']=-1 → left=0, window="ab" (0..1), len=2, maxLen=2, lastSeen['b']=1
right = 2 ('b'): lastSeen['b']=1  → left=max(0, 1+1)=2,
                                    window="b"          (2..2), len=1, maxLen=2, lastSeen['b']=2
right = 3 ('a'): lastSeen['a']=0  → left=max(2, 0+1)=2  (GUARDED! Does NOT regress to 1)
                                    window="ba"         (2..3), len=2, maxLen=2, lastSeen['a']=3

Result: maxLen = 2
```

## 5. Algorithm / Pseudocode

```text
function lengthOfLongestSubstring(s):
    n = s.length()
    lastSeen = array of 128 ints initialized to -1
    left = 0
    maxLen = 0

    for right = 0 to n - 1:
        ch = unsigned_char(s[right])

        if lastSeen[ch] != -1:
            left = max(left, lastSeen[ch] + 1)

        lastSeen[ch] = right
        maxLen = max(maxLen, right - left + 1)

    return maxLen
```

## 6. Complexity

### Time

- **Claim**: $O(N)$
- **Proof**:
  - Initialization of `lastSeen(128, -1)` takes $128 = O(1)$ operations.
  - The single `for` loop executes exactly $N$ iterations (`right = 0` to `N - 1`).
  - Inside the loop, every operation — casting `s[right]`, indexing `lastSeen[ch]`, computing `max`, assigning `lastSeen[ch] = right`, and updating `maxLen` — executes in $O(1)$ worst-case time (zero inner loops, zero hash collisions).
  - Total time is $O(128) + N \cdot O(1) = O(N)$.
- **Lower bound**: $\Omega(N)$ — any correct algorithm must examine every character in `s` at least once in the worst case (e.g., when the unique character extending the answer is at index $N - 1$). Thus $O(N)$ is asymptotically optimal.

### Space

- **Output space**: $O(1)$ — returns a single `int`.
- **Auxiliary space**: $O(\min(N, \Sigma))$ for general alphabet $\Sigma$, which simplifies to $O(\Sigma) = O(128) = O(1)$ for standard ASCII using a fixed 128-integer lookup table (`512` bytes).
- **Interviewer note**: If the interviewer asks *"What if the input is arbitrary Unicode?"*, state that replacing the fixed array with `std::unordered_map<char32_t, int>` yields $O(\min(N, \Sigma))$ auxiliary space.

## 7. C++ Mechanics

- **`vector<int> lastSeen(128, -1)` (or `int lastSeen[128]`)**: Maps each ASCII code `[0..127]` to its last index. Using `-1` as the sentinel for "not yet seen" works cleanly because valid string indices are $\ge 0$.
- **Branchless observation**: Even without `if (lastSeen[ch] != -1)`, the expression `left = max(left, lastSeen[ch] + 1)` is still correct when `lastSeen[ch] == -1`, because `-1 + 1 = 0` and `left >= 0` always holds! Keeping the `if` makes the intent explicit for readers.
- **`static_cast<unsigned char>(s[right])`**: Prevents Undefined Behavior from negative array indexing if `char` is signed on the host compiler.

## 8. Edge Cases

| Case | Input | How Approach 2 Handles It |
|:-----|:------|:--------------------------|
| Empty string | `""` | Loop `0 < 0` does not run; returns `maxLen = 0`. |
| Single character | `" "` | `right = 0`: `left = 0`, `maxLen = max(0, 0 - 0 + 1) = 1`. |
| All identical | `"bbbbb"` | Every step `right >= 1` jumps `left` to `right`; window length is always `right - right + 1 = 1`. |
| Pointer regression | `"abba"` | At `right = 3` (`'a'`), `lastSeen['a'] = 0`, `left = 2`. `max(2, 0 + 1)` keeps `left = 2`. |
| Separated duplicate | `"dvdf"` | At `right = 2` (`'d'`), `lastSeen['d'] = 0`, `left` jumps to `1` (`'v'`). At `right = 3` (`'f'`), window `[1..3]` (`"vdf"`) gives `3`. |
| Symbols & spaces | `"!@# !@#"` | Indexed directly by ASCII codes (`32`, `33`, `64`, `35`); returns `4`. |

## 9. Common Mistakes

1. **Omitting `max` in `left = lastSeen[ch] + 1`**: Causes `left` to move backward when a character's previous occurrence lies to the left of `left` (fails on `"abba"` and `"tmmzuxt"`).
2. **Updating `lastSeen[ch] = right` BEFORE updating `left`**: If you overwrite `lastSeen[ch]` with `right` first, then `lastSeen[ch] + 1` becomes `right + 1`, collapsing the window to length `0` on every duplicate!
3. **Sizing the array to `26` instead of `128`**: Crashes immediately on inputs containing spaces (`" "`), digits (`"123"`), or uppercase letters (`"AbC"`).

## 10. When To Prefer This Approach

- **Always in coding interviews and production**: It achieves the theoretical $\Omega(N)$ time lower bound in a single pass with $O(1)$ L1-cache-friendly auxiliary space and minimal code.
- **When jumping is cleaner than step-by-step shrinking**: Because our validity condition only depends on the *most recent index* of each character (rather than aggregate counts of $K$ characters), jumping `left` in $O(1)$ is strictly cleaner and faster than a `while` loop that increments `left` one by one.
