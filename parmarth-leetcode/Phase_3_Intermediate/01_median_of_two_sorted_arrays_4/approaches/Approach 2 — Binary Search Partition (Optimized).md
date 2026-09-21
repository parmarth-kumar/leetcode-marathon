# Approach 2 — Binary Search Partition

**Problem:** Median of Two Sorted Arrays  
**Goal:** Find the median in `O(log(min(m,n)))` time without merging the arrays.

---

# 1. The Problem We Are Actually Solving

We have two individually sorted arrays:

```text
nums1 = [1, 3, 8, 9]
nums2 = [2, 4, 5, 7, 10]
```

If we merged them:

```text
[1, 2, 3, 4, 5, 7, 8, 9, 10]
```

the median would be:

```text
5
```

But the problem requires:

```text
O(log(m+n))
```

so we cannot simply merge the arrays.

The key realization is:

> **We don't actually need the merged array. We only need to find where the LEFT half and RIGHT half should be separated.**

---

# 2. The Most Important Mental Model

Imagine the merged array:

```text
[1, 2, 3, 4, 5 | 7, 8, 9, 10]
                ↑
            partition
```

We want:

```text
LEFT  = first half
RIGHT = second half
```

For an odd number of total elements, LEFT gets one extra element.

For example, with 9 elements:

```text
LEFT  = 5 elements
RIGHT = 4 elements
```

The important point is:

> **We do NOT actually construct this merged array.**

We only figure out where the partition would have to be.

---

# 3. Split BOTH Arrays

Suppose:

```text
nums1 = [1, 3, 8, 9]
nums2 = [2, 4, 5, 7, 10]
```

We can imagine placing a partition inside each array:

```text
nums1 = [1, 3 | 8, 9]

nums2 = [2, 4, 5 | 7, 10]
```

Together:

```text
LEFT:
nums1 → [1, 3]
nums2 → [2, 4, 5]

RIGHT:
nums1 → [8, 9]
nums2 → [7, 10]
```

Therefore:

```text
LEFT contains 2 + 3 = 5 elements
RIGHT contains 2 + 2 = 4 elements
```

Exactly what we need.

---

# 4. What Is `i`?

This is the most important variable.

`i` means:

> **How many elements are we taking from `nums1` into the LEFT half?**

For:

```text
nums1 = [1, 3, 8, 9]
```

possible partition positions are:

```text
i = 0

| 1 3 8 9
```

```text
i = 1

1 | 3 8 9
```

```text
i = 2

1 3 | 8 9
```

```text
i = 3

1 3 8 | 9
```

```text
i = 4

1 3 8 9 |
```

Therefore:

```text
i ∈ [0, m]
```

where `m = nums1.size()`.

We are NOT searching for the median value directly.

We are searching for:

> **the correct partition position `i`.**

---

# 5. What Is `j`?

Suppose the total number of elements is:

```text
m + n = 9
```

Then:

```text
half = (9 + 1) / 2
     = 5
```

So LEFT must contain exactly 5 elements.

If:

```text
i = 2
```

then we already took 2 elements from `nums1`.

Therefore we MUST take:

```text
j = 5 - 2
  = 3
```

from `nums2`.

So:

```text
i + j = half
```

and therefore:

```text
j = half - i
```

This is why we only binary-search one variable.

> **Once `i` is chosen, `j` is automatically determined.**

---

# 6. What Are We Binary Searching?

This is NOT normal binary search for a target element.

Normal binary search asks:

```text
Is target smaller than mid?
Is target larger than mid?
```

Here we ask:

```text
Is the partition too far LEFT?
Is the partition too far RIGHT?
```

Possible partition positions:

```text
0 1 2 3 4
```

Binary search might try:

```text
i = 2
```

instead of checking:

```text
0 → 1 → 2 → 3 → 4
```

If `i = 2` is wrong, we determine WHY it is wrong.

That tells us which half of the possible partition positions can be eliminated.

---

# 7. The Four Boundary Values

Suppose:

```text
nums1 = [1, 3 | 8, 9]
nums2 = [2, 4, 5 | 7, 10]
```

We only care about the elements immediately next to each partition.

```text
nums1 = [1, 3 | 8, 9]
             ↑   ↑
            L1   R1
```

Therefore:

```text
L1 = 3
R1 = 8
```

And:

```text
nums2 = [2, 4, 5 | 7, 10]
                 ↑   ↑
                L2   R2
```

Therefore:

```text
L2 = 5
R2 = 7
```

In code:

```cpp
maxL1 = largest element on LEFT of nums1
minR1 = smallest element on RIGHT of nums1

maxL2 = largest element on LEFT of nums2
minR2 = smallest element on RIGHT of nums2
```

---

# 8. Why Only Four Values?

Each individual array is already sorted.

Therefore:

```text
nums1 LEFT  = [1, 3]
```

has largest element:

```text
3
```

and:

```text
nums1 RIGHT = [8, 9]
```

has smallest element:

```text
8
```

The same applies to `nums2`.

So the only possible problem between LEFT and RIGHT can occur at the boundaries.

We only need to check:

```text
L1 <= R2
L2 <= R1
```

---

# 9. What Does a Correct Partition Mean?

The fundamental requirement is:

```text
EVERY element on LEFT <= EVERY element on RIGHT
```

Since each individual array is already sorted, this reduces to:

```text
L1 <= R2
```

and:

```text
L2 <= R1
```

If both are true:

```text
L1 <= R2 ✓
L2 <= R1 ✓
```

then the partition is correct.

Another equivalent way to think about it:

```text
largest element on LEFT
        <=
smallest element on RIGHT
```

That is:

```text
max(L1, L2) <= min(R1, R2)
```

So if:

```text
x = max(L1, L2)
y = min(R1, R2)
```

then:

```text
x <= y
```

means:

> **Correct partition.**

---

# 10. What If the Partition Is Wrong?

This is where binary search becomes useful.

There are TWO possible ways the partition can be wrong.

---

## Case A — We Took Too Many From `nums1`

Suppose:

```text
L1 > R2
```

Example:

```text
nums1 = [1, 3, 8 | 9]
                 ↑
                L1 = 8

nums2 = [2, 4 | 5, 7, 10]
             ↑
            R2 = 5
```

We get:

```text
8 > 5
```

That means LEFT contains:

```text
8
```

while RIGHT contains:

```text
5
```

This cannot be correct.

Why does this mean `i` is too large?

Because `L1` came from the LEFT side of `nums1`.

We put too many `nums1` elements into LEFT.

Therefore:

```text
Need FEWER nums1 elements on LEFT
```

So move the partition in `nums1` LEFT:

```text
i ←
```

In binary search:

```cpp
high = i - 1;
```

We eliminate the current `i` and everything larger.

---

# 11. Case B — We Took Too Few From `nums1`

Suppose:

```text
L2 > R1
```

Example:

```text
nums1 = [1, 3 | 8, 9]
             ↑
            R1 = 8

nums2 = [2, 4, 5 | 7, 10]
                 ↑
                L2 = 5
```

Actually this example is valid because:

```text
5 <= 8
```

So use a clearer example:

```text
nums1 = [1, 2 | 3, 4]

nums2 = [5, 6, 7 | 8, 9]
```

Here:

```text
L2 = 7
R1 = 3
```

Therefore:

```text
7 > 3
```

LEFT contains `7`, while RIGHT contains `3`.

The problem is that we took too FEW elements from `nums1`.

We need:

```text
MORE nums1 elements on LEFT
```

Therefore move the partition RIGHT:

```text
i →
```

In binary search:

```cpp
low = i + 1;
```

---

# 12. The Binary Search Decision Tree

Memorize this:

```text
                    Check partition
                           |
                           v
              L1 <= R2 AND L2 <= R1 ?
                    /              \
                  YES               NO
                   |                 |
                   v                 v
              CORRECT          Which crossing?
                   |             /          \
                   |         L1 > R2       L2 > R1
                   |            |              |
                   |            v              v
                   |       Too many        Too few
                   |       from nums1      from nums1
                   |            |              |
                   |            v              v
                   |          i ←            i →
                   |       high = i-1      low = i+1
                   |
                   v
                 Median
```

The critical rule is:

```text
L1 > R2
    ↓
i too large
    ↓
move i LEFT
```

while:

```text
L2 > R1
    ↓
i too small
    ↓
move i RIGHT
```

---

# 13. Why `x > y` Alone Is Not Enough

You can calculate:

```text
x = max(L1, L2)
y = min(R1, R2)
```

If:

```text
x <= y
```

the partition is correct.

But if:

```text
x > y
```

you know only:

> The partition is wrong.

You still need to determine WHICH crossing caused the problem.

Check:

```text
L1 > R2
```

or:

```text
L2 > R1
```

That tells you the direction of binary search.

Therefore:

```text
x > y
```

is the **validity test**, but:

```text
L1 > R2
```

or:

```text
L2 > R1
```

is the **binary-search direction test**.

---

# 14. Complete Example

```text
nums1 = [1, 5, 9]
nums2 = [2, 6, 10]
```

Total:

```text
3 + 3 = 6
```

Therefore:

```text
half = (6 + 1) / 2
     = 3
```

Possible `i`:

```text
0 1 2 3
```

Start:

```text
low = 0
high = 3
```

---

## Iteration 1

```text
i = (0 + 3) / 2
  = 1
```

Therefore:

```text
j = 3 - 1
  = 2
```

Partitions:

```text
nums1 = [1 | 5, 9]
nums2 = [2, 6 | 10]
```

Boundary values:

```text
L1 = 1
R1 = 5

L2 = 6
R2 = 10
```

Check:

```text
L1 <= R2
1 <= 10 ✓

L2 <= R1
6 <= 5 ✗
```

Therefore:

```text
L2 > R1
```

We took too few from `nums1`.

Move RIGHT:

```text
low = i + 1
    = 2
```

---

## Iteration 2

```text
i = (2 + 3) / 2
  = 2
```

Then:

```text
j = 3 - 2
  = 1
```

Partitions:

```text
nums1 = [1, 5 | 9]
nums2 = [2 | 6, 10]
```

Boundary values:

```text
L1 = 5
R1 = 9

L2 = 2
R2 = 6
```

Check:

```text
5 <= 6 ✓
2 <= 9 ✓
```

Correct partition found.

Total is even, so:

```text
largest LEFT  = max(5,2) = 5
smallest RIGHT = min(9,6) = 6

median = (5 + 6) / 2
       = 5.5
```

---

# 15. Why We Don't Merge or Sort

This is a common misunderstanding.

We never create:

```text
[1,2,3,4,5,6,...]
```

We never sort the LEFT side.

We already know:

```text
nums1 is sorted
nums2 is sorted
```

Once the partition is correct:

```text
nums1 = [1,5 | 9]
nums2 = [2 | 6,10]
```

the largest LEFT element is simply:

```text
max(5,2)
```

and the smallest RIGHT element is:

```text
min(9,6)
```

That's enough to calculate the median.

---

# 16. Why Search the Smaller Array?

We always want:

```cpp
nums1 = smaller array
```

because we binary-search its partition.

If:

```text
m = 5
n = 1,000,000
```

we search:

```text
0 ... 5
```

instead of:

```text
0 ... 1,000,000
```

Therefore:

```text
Time = O(log(min(m,n)))
```

---

# 17. Sentinel Values

Sometimes the partition is at the extreme end.

Example:

```text
nums1 = [1,2,3]
```

If:

```text
i = 0
```

then nums1 has nothing on LEFT.

There is no real `L1`.

We use:

```cpp
INT_MIN
```

to represent:

```text
L1 = -∞
```

Similarly, if:

```text
i = m
```

then nums1 has nothing on RIGHT.

We use:

```cpp
INT_MAX
```

to represent:

```text
R1 = +∞
```

So:

```cpp
maxL1 = (i == 0) ? INT_MIN : nums1[i - 1];

minR1 = (i == m) ? INT_MAX : nums1[i];
```

This lets the same comparison logic work even at the boundaries.

---

# 18. Why `high = m`, Not `m - 1`?

Because `i` represents a **partition position**, not an element index.

If:

```text
nums1 = [1,2,3]
```

then:

```text
i = 3
```

is completely valid:

```text
[1,2,3 | ]
```

All 3 elements are on LEFT.

Therefore:

```cpp
high = m;
```

not:

```cpp
high = m - 1;
```

---

# 19. Code-to-Concept Mapping

When reading the code, translate the variables mentally like this:

| Code    | Meaning                                   |
| ------- | ----------------------------------------- |
| `i`     | Number of `nums1` elements on LEFT        |
| `j`     | Number of `nums2` elements on LEFT        |
| `half`  | Total number of elements required on LEFT |
| `maxL1` | Largest `nums1` element on LEFT           |
| `minR1` | Smallest `nums1` element on RIGHT         |
| `maxL2` | Largest `nums2` element on LEFT           |
| `minR2` | Smallest `nums2` element on RIGHT         |
| `low`   | Smallest possible `i`                     |
| `high`  | Largest possible `i`                      |

Most importantly:

```text
i + j = half
```

and:

```text
maxL1 <= minR2
maxL2 <= minR1
```

---

# 20. Pseudocode

```text
function findMedian(nums1, nums2):

    if nums1 is larger:
        swap nums1 and nums2

    m = size(nums1)
    n = size(nums2)

    low = 0
    high = m

    half = (m + n + 1) / 2

    while low <= high:

        i = (low + high) / 2
        j = half - i

        maxL1 = largest value on nums1 LEFT
        minR1 = smallest value on nums1 RIGHT

        maxL2 = largest value on nums2 LEFT
        minR2 = smallest value on nums2 RIGHT

        if maxL1 <= minR2 AND maxL2 <= minR1:

            if total is odd:
                return max(maxL1, maxL2)

            return (
                max(maxL1, maxL2)
                +
                min(minR1, minR2)
            ) / 2.0

        else if maxL1 > minR2:

            i is too large
            high = i - 1

        else:

            i is too small
            low = i + 1
```

---

# 21. Complexity

### Time

```text
O(log(min(m,n)))
```

We binary-search only the smaller array.

There are `m + 1` possible partition positions when `m` is the smaller size, and each iteration performs only constant-time work.

### Auxiliary Space

```text
O(1)
```

Only a fixed number of variables are used.

The recursive swap call adds only constant stack depth.

---

# 22. Common Mistakes

### Mistake 1 — Thinking `i` is an element index

Wrong:

```text
i = "the element we are searching for"
```

Correct:

```text
i = "number of nums1 elements placed on LEFT"
```

---

### Mistake 2 — Searching `i` and `j` independently

Wrong:

```text
search i
search j
```

Correct:

```text
i = binary-search variable
j = half - i
```

---

### Mistake 3 — Thinking `x > y` directly tells the direction

Wrong:

```text
x > y → i++
```

or:

```text
x > y → i--
```

Correct:

```text
x = max(L1,L2)
y = min(R1,R2)

x <= y → correct

x > y → partition wrong

Then determine why:

L1 > R2 → i too large → move LEFT

L2 > R1 → i too small → move RIGHT
```

---

### Mistake 4 — Merging the arrays

The whole point of this approach is:

```text
DO NOT MERGE
DO NOT SORT
```

We only locate the correct partition.

---

### Mistake 5 — Using `(m+n)/2`

Use:

```cpp
half = (m + n + 1) / 2;
```

The `+1` makes the LEFT side contain the extra element when the total is odd.

That makes:

```text
odd → median = largest LEFT
```

---

### Mistake 6 — Using `0` as a boundary sentinel

Never do:

```cpp
maxL1 = 0;
```

because arrays may contain:

```text
negative values
```

or:

```text
0
```

Use:

```cpp
INT_MIN
INT_MAX
```

---

### Mistake 7 — Using `high = m - 1`

Wrong because:

```text
i = m
```

is a valid partition:

```text
[entire nums1 | empty]
```

Use:

```cpp
high = m;
```

---

# 23. The Final Mental Model

Before writing the code, think:

```text
1. I need to split the combined sorted data into LEFT and RIGHT.

2. LEFT must contain half of all elements.

3. I will decide how many elements come from nums1.
   That number is i.

4. Once i is known:
   j = half - i.

5. Now I have two partitions:

   nums1: [ LEFT | RIGHT ]
   nums2: [ LEFT | RIGHT ]

6. I only need four boundary values:

   L1, R1, L2, R2.

7. Correct partition:

   L1 <= R2
   L2 <= R1

8. If L1 > R2:
   too many from nums1.
   Move i LEFT.

9. Otherwise:
   L2 > R1.
   Too few from nums1.
   Move i RIGHT.

10. Once correct:
    odd  → max(L1,L2)
    even → (max(L1,L2) + min(R1,R2)) / 2.
```

## One sentence to remember

> **Binary search the number of elements taken from the smaller array into LEFT; let the other array automatically fill the remaining LEFT positions, then use the four boundary values to decide whether the partition is correct or which direction to move.**

That is the entire algorithm.
