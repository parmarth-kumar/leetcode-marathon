# Approach 2 — One-Pass Hash Map (Optimized)

## 1. Core Idea

Scan the array in a single left-to-right pass while maintaining an `unordered_map<int, int>` that maps each previously seen number (`nums[j]`) to its index (`j`). For each element `nums[i]`, compute its required complement `target - nums[i]` and check in $O(1)$ average time if that complement is already in the map. If it is, return `{seen[complement], i}`; otherwise, insert `seen[nums[i]] = i` and continue.

## 2. Why It Works

Any valid pair of indices `(j, i)` has one smaller index `j` and one larger index `i` (`j < i`). When our loop reaches the second element of the pair at index `i`, the first element at index `j` (`j < i`) has **already been visited and stored** in the hash map! Because `nums[j] + nums[i] == target` is equivalent to `nums[j] == target - nums[i]`, looking up `complement = target - nums[i]` in the hash map of already-visited elements is guaranteed to find `j` as soon as we reach `i`.

Furthermore, because we check the hash map **before** inserting `nums[i]`, the map at step `i` only contains elements from indices `0 .. i - 1`, making it impossible to match index `i` with itself.

## 3. How To Think About It

1. *"In Approach 1, for every element `nums[i]`, the inner loop spent $O(N)$ time searching for `target - nums[i]`."*
2. *"I want to replace that $O(N)$ linear search with an $O(1)$ lookup."*
3. *"What am I searching for? A **number** (`target - nums[i]`). What do I need back when I find it? Its **index**."*
4. *"So I need a dictionary where `Key = number` and `Value = index`: `unordered_map<int, int> seen`."*
5. *"Do I need two passes (one to fill the map, one to query)? No! If a pair `(j, i)` with `j < i` exists, I don't need to find it when I'm at `j` — I will find it when I reach `i` and look back at `j`."*

## 4. Visual Trace

**Trace 1**: `nums = [2, 7, 11, 15], target = 9`
```
Initial state: seen = {}

Step i = 0 (nums[0] = 2):
  complement = 9 - 2 = 7
  Is 7 in seen? NO.
  Insert nums[0] -> 0:  seen = { 2 : 0 }

Step i = 1 (nums[1] = 7):
  complement = 9 - 7 = 2
  Is 2 in seen? YES! (seen[2] == 0)
  Return {seen[2], 1} = {0, 1}  ✓
```

**Trace 2 (Duplicate-Value Edge Case)**: `nums = [3, 3], target = 6`
```
Initial state: seen = {}

Step i = 0 (nums[0] = 3):
  complement = 6 - 3 = 3
  1. Check FIRST: Is 3 in seen? NO (seen is empty).
  2. Insert AFTER: seen[3] = 0  →  seen = { 3 : 0 }

Step i = 1 (nums[1] = 3):
  complement = 6 - 3 = 3
  1. Check FIRST: Is 3 in seen? YES! (seen[3] == 0)
  2. Return {0, 1}  ✓  (Distinct indices 0 and 1!)
```

## 5. Algorithm / Pseudocode

```text
function twoSum(nums, target):
    seen = empty hash map { number -> index }

    for i from 0 to length(nums) - 1:
        complement = target - nums[i]
        if complement exists in seen:
            return [seen[complement], i]
        seen[nums[i]] = i

    return []
```

## 6. Complexity

### Time

- **Claim**: $O(N)$ average-case, $O(N^2)$ pathological worst-case (under adversarial hash collisions).
- **Proof**:
  - The loop runs at most $N$ iterations (`i = 0 .. N - 1`).
  - Inside each iteration, we perform:
    1. One subtraction (`target - nums[i]`): $O(1)$.
    2. One hash table lookup (`seen.find(complement)` or `seen.count(complement)`): $O(1)$ average time.
    3. At most one hash table insertion (`seen[nums[i]] = i`): $O(1)$ amortized average time.
  - Summing $O(1)$ work over at most $N$ iterations yields $N \times O(1) = O(N)$ average time.
- **Lower bound**: $\Omega(N)$ — in the worst case, any deterministic algorithm must inspect at least $N - 1$ elements of the unsorted input array before discovering which pair sums to `target`. Thus $O(N)$ is asymptotically time-optimal.

### Space

- **Output space**: $O(1)$ — a 2-element `vector<int>` (`{seen[complement], i}`).
- **Auxiliary space**: $O(N)$ — in the worst case (when the valid pair involves the last element `nums[N - 1]`), the `unordered_map` stores $N - 1$ key-value pairs (`{nums[i], i}`).
- **Interviewer note**: Explicitly frame this as a **Space-Time Tradeoff**: we spend $O(N)$ extra memory to buy a speedup from $O(N^2)$ down to $O(N)$ time.

## 7. C++ Mechanics

- **`unordered_map::find(key)` vs `unordered_map::count(key)` + `operator[]`**:
  - Using `auto it = seen.find(complement); if (it != seen.end()) return {it->second, i};` performs **only one** hash lookup when the complement is found (`it->second` directly accesses the value).
  - Using `if (seen.count(complement)) return {seen[complement], i};` is also $O(1)$ and very readable, though it hashes `complement` twice on the final winning step.
- **Never use `if (seen[complement])` to test existence**: In C++, `seen[key]` **inserts `key` with default value `0`** if `key` does not exist! Not only does this pollute the map with fake keys, it also fails completely when the valid index is `0` (since `0` evaluates to `false` in a boolean check!). Always use `seen.find(key) != seen.end()` or `seen.count(key)`.

## 8. Edge Cases

| Case | Input | How One-Pass Hash Map Handles It |
|:---|:---|:---|
| Duplicate values forming the answer | `nums = [3, 3], target = 6` | At `i = 0`, `3` is inserted after the check fails. At `i = 1`, `seen` already has `3 -> 0`, so it checks before overwriting and returns `{0, 1}`. |
| Duplicate values NOT forming the answer | `nums = [2, 2, 7], target = 9` | At `i = 0`, `seen[2] = 0`. At `i = 1`, `complement = 7` is not in `seen`, and `seen[2] = 1` overwrites the index. Since only one valid answer exists, if `2 + 2` was not the answer, at most one `2` is needed later. |
| First element at index `0` is part of the answer | `nums = [2, 7, 11, 15], target = 9` | Because we use `.find()` / `.count()` instead of `if (seen[complement])`, index `0` is properly detected and returned. |
| Negative numbers and zero | `nums = [-3, 4, 3, 90], target = 0` | `std::hash<int>` hashes negative numbers and `0` identically to positive integers. |

## 9. Common Mistakes

1. **Inserting into the map BEFORE checking for the complement**:
   ```cpp
   seen[nums[i]] = i;                 // BUG: inserted too early!
   if (seen.count(target - nums[i]))  // Matches nums[i] with itself if 2 * nums[i] == target!
   ```
   Always **check first, insert second**.
2. **Using `if (seen[complement])` to check if a key exists**: As noted in Section 7, `operator[]` mutates the map by inserting missing keys with value `0`, and treats valid index `0` as `false`.
3. **Swapping Key and Value (`seen[i] = nums[i]`)**: If you make the index the key, you cannot look up by value in $O(1)$ time. Always set `Key = nums[i]`, `Value = i`.

## 10. When To Prefer This Approach

- **Default optimal interview solution for unsorted Two Sum**: Whenever the input array is unsorted and $O(N)$ auxiliary space is acceptable, this is the gold-standard $O(N)$ time solution expected at Google and other top-tier interviews.
- **Streaming data**: Because it is a one-pass algorithm, it works even if elements arrive one by one in a stream.
