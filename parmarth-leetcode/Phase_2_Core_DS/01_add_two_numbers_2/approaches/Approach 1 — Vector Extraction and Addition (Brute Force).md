# Approach 1 — Vector Extraction and Addition (Brute Force)

## 1. Core Idea

Decouple linked-list pointer manipulation from arithmetic by extracting the digits of `l1` and `l2` into two `std::vector<int>` arrays (`digits1` and `digits2`), simulating grade-school column addition index-by-index into a third `resultDigits` vector, and finally constructing the output linked list from `resultDigits`.

## 2. Why It Works

- **Why naive integer conversion fails**: A linked list in this problem can contain up to `100` nodes (`100` decimal digits). Built-in C++ integer types overflow far below 100 digits (`int` at ~10 digits, `long long` at ~19 digits, `__int128` at ~39 digits).
- **Why vector extraction works**: By storing each digit at index `i` in a dynamic array (`digits1[i]` holds the `10^i` place), we represent an arbitrary-precision integer ("BigInt") of any length without overflow.
- Standard column-by-column addition (`sum = val1 + val2 + carry`) on the two vectors produces the exact reverse-order digits needed to build the output linked list.

## 3. How To Think About It

1. *"Converting a 100-node list into `long long` will overflow, so I must add digit-by-digit."*
2. *"Doing pointer traversal, null checks, and linked-list node allocation all at the same time feels error-prone at first. Can I turn this into an array problem?"*
3. *"Yes! First, walk `l1` and `l2` and `push_back` their values into `digits1` and `digits2`."*
4. *"Second, loop with indices `i` and `j` while `i < n1 || j < n2 || carry > 0`, pushing `sum % 10` into `resultDigits` and updating `carry = sum / 10`."*
5. *"Third, iterate over `resultDigits` and attach a `new ListNode(d)` for each digit using a dummy head."*

## 4. Visual Trace

```text
Input:
  l1 = 9 -> 9 -> nullptr   (represents 99)
  l2 = 1 -> nullptr        (represents 1)

Pass 1 — Extract Linked Lists into Vectors:
  digits1 = [9, 9]   (n1 = 2)
  digits2 = [1]      (n2 = 1)

Pass 2 — Column Addition on Vectors:
  i = 0, j = 0, carry = 0:
    val1 = digits1[0] = 9,  val2 = digits2[0] = 1
    sum  = 9 + 1 + 0 = 10   -->  resultDigits.push_back(0), carry = 1
    i = 1, j = 1

  i = 1, j = 1, carry = 1:
    val1 = digits1[1] = 9,  val2 = 0 (since j == n2)
    sum  = 9 + 0 + 1 = 10   -->  resultDigits.push_back(0), carry = 1
    i = 2, j = 1

  i = 2, j = 1, carry = 1:
    val1 = 0 (since i == n1), val2 = 0 (since j == n2)
    sum  = 0 + 0 + 1 = 1    -->  resultDigits.push_back(1), carry = 0
    i = 2, j = 1

  Loop terminates (i == n1, j == n2, carry == 0).
  resultDigits = [0, 0, 1]

Pass 3 — Build Output Linked List from resultDigits:
  dummy -> [0] -> [0] -> [1] -> nullptr
  Return dummy.next  -->  0 -> 0 -> 1 ✓
```

## 5. Algorithm / Pseudocode

```text
function addTwoNumbers(l1, l2):
    // Pass 1: Extract digits into arrays
    digits1 = [], digits2 = []
    while l1 != nullptr:
        digits1.append(l1.val)
        l1 = l1.next
    while l2 != nullptr:
        digits2.append(l2.val)
        l2 = l2.next

    // Pass 2: Simulate grade-school addition
    resultDigits = []
    i = 0, j = 0, carry = 0
    while i < len(digits1) OR j < len(digits2) OR carry > 0:
        val1 = (i < len(digits1)) ? digits1[i++] : 0
        val2 = (j < len(digits2)) ? digits2[j++] : 0
        sum = val1 + val2 + carry
        resultDigits.append(sum % 10)
        carry = sum / 10

    // Pass 3: Convert result array into linked list
    dummy = ListNode(0)
    tail = &dummy
    for d in resultDigits:
        tail.next = new ListNode(d)
        tail = tail.next

    return dummy.next
```

## 6. Complexity

### Time

- **Claim**: `O(max(M, N))`, where `M` and `N` are the lengths of `l1` and `l2`.
- **Proof**:
  - **Pass 1 (Extraction)**: Traverses `l1` (`M` steps) and `l2` (`N` steps), calling `push_back` in `O(1)` amortized time per element → `O(M + N)`.
  - **Pass 2 (Vector Addition)**: Runs at most `max(M, N) + 1` iterations (each iteration does `O(1)` arithmetic and `O(1)` amortized `push_back`) → `O(max(M, N))`.
  - **Pass 3 (List Construction)**: Allocates at most `max(M, N) + 1` nodes in `O(1)` per node → `O(max(M, N))`.
  - Summing all three passes: `O(M + N) + O(max(M, N)) + O(max(M, N)) = O(max(M, N))`.
- **Lower bound**: `Ω(max(M, N))`, because every node of the longer input list must be inspected at least once to determine the sum.

### Space

- **Output space**: `O(max(M, N))` — the newly allocated linked list contains `max(M, N)` or `max(M, N) + 1` nodes.
- **Auxiliary space**: `O(M + N)` — `digits1` stores `M` ints, `digits2` stores `N` ints, and `resultDigits` stores up to `max(M, N) + 1` ints on the heap.
- **Interviewer note**: While `O(max(M, N))` time is asymptotically optimal, an interviewer will immediately ask: *"Why store all digits in three `std::vector` buffers when the input linked lists are already in least-significant-digit-first order?"* Eliminating those vectors reduces auxiliary space from `O(M + N)` to `O(1)` (Approach 2).

## 7. C++ Mechanics

- **Amortized `std::vector::push_back`**: Appending `k` elements to an empty `vector<int>` doubles capacity geometrically (`1, 2, 4, 8, ...`), costing `< 2k` element copies total (`O(1)` amortized per element).
- **`static_cast<int>(digits1.size())`**: `vector::size()` returns `size_t` (unsigned). Casting to `int` avoids signed/unsigned comparison warnings (`-Wsign-compare` under `-Wall -Werror`) when comparing with `int i`.
- **Stack Sentinel (`ListNode dummy(0)`)**: Declaring `dummy` as a local stack variable rather than `new ListNode(0)` avoids an extra heap allocation and guarantees automatic cleanup on return.

## 8. Edge Cases

| Case | How This Approach Handles It |
|:---|:---|
| **100-digit lists** | Stored as 100 elements in `vector<int>` — zero risk of integer overflow |
| **Unequal lengths (`[9, 9]` + `[1]`)** | `i < n1` and `j < n2` bounds checks supply `0` after the shorter vector ends |
| **Final carry (`[5]` + `[5]`)** | Loop guard includes `|| carry > 0`, appending the trailing `1` to `resultDigits` |
| **Both inputs `[0]`** | `digits1 = [0]`, `digits2 = [0]` → `resultDigits = [0]` → single node `0` |

## 9. Common Mistakes

1. **Attempting `long long` conversion instead of vector extraction**: Fails on LeetCode's 30–100 node test cases due to 64-bit integer overflow.
2. **Omitting `|| carry > 0` in Pass 2**: Drops the most significant digit whenever the final column produces a carry (e.g., `99 + 1` outputs `0 -> 0` instead of `0 -> 0 -> 1`).
3. **Signed/unsigned mismatch**: Comparing `int i` with `digits1.size()` (`size_t`) triggers compiler warnings under `-Wall -Werror`.

## 10. When To Prefer This Approach

- As a **stepping-stone mental model** if you want to verify your digit-addition logic on arrays before fusing it with pointer traversal.
- Related array/stack extraction is actually required in **LC 445 (Add Two Numbers II)** when digits are given in *forward* order and you are not allowed to reverse the input lists.
- For **LC 2 (Add Two Numbers)** where digits are already reversed, **prefer Approach 2** in an interview to achieve `O(1)` auxiliary space in a single pass.
