# Approach 1 — Merge and Pick (Brute Force)

## 1. Core Idea

Merge the two sorted arrays into a single sorted array using the two-pointer merge technique, then directly access the median element(s) by index.

## 2. Why It Works

Since both arrays are already sorted, merging them produces a complete sorted sequence. The median is simply the middle element(s) of this sequence. This is the most direct translation of the problem statement into code.

## 3. How To Think About It

1. "I need the median of the combined data."
2. "If I had one sorted array, I'd just index into the middle."
3. "I can create that single sorted array by merging — same as the merge step in merge sort."
4. "Two pointers, compare heads, pick the smaller, advance that pointer."
5. "Once merged, median = middle element (odd) or average of two middles (even)."

## 4. Visual Trace

```
nums1 = [1, 3]    nums2 = [2]

Merge step by step:
  i=0, j=0: nums1[0]=1 ≤ nums2[0]=2 → pick 1,  merged=[1],       i=1
  i=1, j=0: nums1[1]=3 > nums2[0]=2  → pick 2,  merged=[1,2],     j=1
  j exhausted → append remaining: merged=[1,2,3]

total = 3 (odd)
median = merged[3/2] = merged[1] = 2.0 ✓
```

```
nums1 = [1, 2]    nums2 = [3, 4]

Merge:
  i=0, j=0: 1 ≤ 3 → pick 1, i=1
  i=1, j=0: 2 ≤ 3 → pick 2, i=2
  i exhausted → append remaining: merged=[1,2,3,4]

total = 4 (even)
median = (merged[1] + merged[2]) / 2.0 = (2 + 3) / 2.0 = 2.5 ✓
```

## 5. Algorithm / Pseudocode

```
function findMedianSortedArrays(nums1, nums2):
    merged = []
    i, j = 0, 0

    // Two-pointer merge
    while i < len(nums1) AND j < len(nums2):
        if nums1[i] <= nums2[j]:
            merged.append(nums1[i]); i++
        else:
            merged.append(nums2[j]); j++

    // Append remaining
    while i < len(nums1): merged.append(nums1[i]); i++
    while j < len(nums2): merged.append(nums2[j]); j++

    total = len(merged)
    if total is odd:
        return merged[total / 2]
    else:
        return (merged[total/2 - 1] + merged[total/2]) / 2.0
```

## 6. Complexity

### Time

- **Claim**: O(m + n)
- **Proof**: The merge loop processes each element exactly once. Each of the `m` elements of `nums1` and `n` elements of `nums2` is compared at most once and appended once. The median lookup is O(1) index access. Total: O(m + n).
- **Note**: This does NOT meet the problem's O(log(m+n)) requirement, but is a valid starting point in an interview.

### Space

- **Output space**: O(m + n) — the merged array.
- **Auxiliary space**: O(1) — only index variables beyond the merged array.
- **Interviewer note**: "Can you avoid creating the merged array entirely?" → Yes, see Approach 2.

## 7. C++ Mechanics

- `vector::reserve(m + n)`: Pre-allocates capacity to avoid repeated reallocations during `push_back`. Without it, the vector may reallocate O(log(m+n)) times.
- `/ 2.0`: Forces floating-point division. Using `/ 2` with int operands would truncate.
- `vector<int>& nums1`: Pass by reference to avoid copying the input arrays.

## 8. Edge Cases

| Case | Handling |
|:-----|:---------|
| `nums1` empty | Merge loop skips it; all elements come from `nums2` |
| `nums2` empty | Merge loop skips it; all elements come from `nums1` |
| Both single-element | `merged` has 2 elements; even-case formula applies |
| Identical elements | Merge picks from either; median is that repeated value |
| Negative numbers | No special handling needed; comparison works the same |

## 9. Common Mistakes

1. **Integer division for median**: `(a + b) / 2` truncates when `a` and `b` are ints. Use `/ 2.0`.
2. **Off-by-one median index**: `merged[total/2]` is correct for odd. For even, it's `merged[total/2 - 1]` and `merged[total/2]`.
3. **Forgetting to handle remaining elements**: After the main merge loop, one array may still have unprocessed elements.

## 10. When To Prefer This Approach

- As a **first answer** in an interview to show correctness before optimizing.
- When constraints are small enough that O(m+n) is acceptable.
- When you need to verify the output of the optimized binary search approach during debugging.
- **Not suitable** when the interviewer explicitly requires O(log(m+n)).
