# Approach 2 — Elementary Math with Dummy Head (Optimized)

## 1. Core Idea

Traverse `l1` and `l2` simultaneously in a **single pass** from head to tail, simulating grade-school column addition on-the-fly (`sum = val1 + val2 + carry`) and appending each resulting digit (`sum % 10`) directly to a dummy-headed output list using `O(1)` auxiliary space.

## 2. Why It Works

1. **Reverse Order Aligns with Carry Propagation**: Because the head of each list holds the `1`'s place (`10^0`), the second node holds the `10`'s place (`10^1`), and so on, walking forward (`->next`) visits digits in the exact order required by elementary addition.
2. **Identity Substitution for Unequal Lengths**: Once the shorter list reaches `nullptr`, its missing higher-order digits are mathematically `0` (e.g., `99 + 1` is `99 + 01`). Replacing a `nullptr` node's value with `0` lets a single unified loop process both lists to completion.
3. **Carry Invariant**: Since `0 <= val1, val2 <= 9` and `carry ∈ {0, 1}`, the column sum satisfies `0 <= sum <= 19`. Thus `sum % 10` is always a valid single digit `[0, 9]` and `sum / 10` is always `0` or `1`.

## 3. How To Think About It

1. *"In Approach 1, I copied `l1` and `l2` into vectors just to read them from left to right. Why not read `l1->val` and `l2->val` directly?"*
2. *"I need to build a new linked list as I go. To avoid `if (head == nullptr)` on every step, I'll anchor the result with a stack-allocated `ListNode dummy(0)` and maintain a `tail` pointer."*
3. *"At each step, if `l1` is not null, grab `l1->val` and advance `l1`; otherwise use `0`. Do the same for `l2`."*
4. *"Compute `sum = val1 + val2 + carry`, attach `new ListNode(sum % 10)` to `tail->next`, advance `tail`, and update `carry = sum / 10`."*
5. *"Keep looping as long as `l1 != nullptr || l2 != nullptr || carry != 0` so neither a longer list nor a final carry is left behind."*

## 4. Visual Trace

```text
Input:
  l1: 2 -> 4 -> 3 -> nullptr   (represents 342)
  l2: 5 -> 6 -> 4 -> nullptr   (represents 465)

Setup:
  dummy: [0] -> nullptr
  tail : &dummy
  carry: 0

--- Iteration 1 (1s place) ---
  l1 points to [2], l2 points to [5], carry = 0
  sum   = 2 + 5 + 0 = 7
  carry = 7 / 10 = 0
  tail->next = new ListNode(7 % 10 = 7)
  tail moves to [7]
  l1 moves to [4], l2 moves to [6]
  List so far: dummy -> [7] -> nullptr

--- Iteration 2 (10s place) ---
  l1 points to [4], l2 points to [6], carry = 0
  sum   = 4 + 6 + 0 = 10
  carry = 10 / 10 = 1
  tail->next = new ListNode(10 % 10 = 0)
  tail moves to [0]
  l1 moves to [3], l2 moves to [4]
  List so far: dummy -> [7] -> [0] -> nullptr

--- Iteration 3 (100s place) ---
  l1 points to [3], l2 points to [4], carry = 1
  sum   = 3 + 4 + 1 = 8
  carry = 8 / 10 = 0
  tail->next = new ListNode(8 % 10 = 8)
  tail moves to [8]
  l1 moves to nullptr, l2 moves to nullptr
  List so far: dummy -> [7] -> [0] -> [8] -> nullptr

--- Loop Check ---
  l1 == nullptr, l2 == nullptr, carry == 0  -->  Terminate!

Return dummy.next  -->  [7] -> [0] -> [8]  (represents 807) ✓
```

## 5. Algorithm / Pseudocode

```text
function addTwoNumbers(l1, l2):
    dummy = ListNode(0)
    tail = &dummy
    carry = 0

    while l1 != nullptr OR l2 != nullptr OR carry != 0:
        val1 = (l1 != nullptr) ? l1.val : 0
        val2 = (l2 != nullptr) ? l2.val : 0

        sum = val1 + val2 + carry
        carry = sum / 10

        tail.next = new ListNode(sum % 10)
        tail = tail.next

        if l1 != nullptr: l1 = l1.next
        if l2 != nullptr: l2 = l2.next

    return dummy.next
```

## 6. Complexity

### Time

- **Claim**: `O(max(M, N))`, where `M` and `N` are the number of nodes in `l1` and `l2`.
- **Proof**:
  - Each iteration of the `while` loop advances `l1` (if non-null) and `l2` (if non-null) by one node.
  - After `max(M, N)` iterations, both `l1` and `l2` are `nullptr`.
  - If `carry == 1` at that point, one additional iteration runs (`0 + 0 + 1 = 1`), setting `carry = 0` and terminating.
  - Inside the loop, every operation (ternary check, addition, `% 10`, `/ 10`, `new ListNode`, pointer assignment) executes in `O(1)` time.
  - Total iterations: at most `max(M, N) + 1` → `O(max(M, N))`.
- **Lower bound**: `Ω(max(M, N))`, since every node in both lists can affect the output and must be read at least once. Thus `O(max(M, N))` is asymptotically optimal.

### Space

- **Output space**: `O(max(M, N))` — allocates `max(M, N)` or `max(M, N) + 1` `ListNode` objects for the returned sum list.
- **Auxiliary space**: `O(1)` — uses only a stack-allocated sentinel `dummy`, one pointer `tail`, and integer variables (`carry`, `val1`, `val2`, `sum`).
- **Interviewer note**: When an interviewer asks for the space complexity, explicitly state: *"Output space is `O(max(M, N))` for the required result list, and auxiliary space is `O(1)` because we allocate no extra buffers or recursion frames."*

## 7. C++ Mechanics

- **Stack-Allocated Dummy Node (`ListNode dummy(0);`)**:
  Instead of `ListNode* dummy = new ListNode(0);` (which requires a heap allocation and an explicit `delete dummy;` before returning), creating `ListNode dummy(0);` on the stack is faster, leak-proof, and automatically destroyed when `addTwoNumbers` returns `dummy.next`.
- **Pointer-to-Stack-Object (`ListNode* tail = &dummy;`)**:
  `tail` starts by pointing to `dummy` on the stack. On the first iteration, `tail->next` sets `dummy.next` to the first heap-allocated node, and `tail = tail->next` moves `tail` onto the heap chain.
- **Null-Safe Pointer Advancement**:
  Always guard `if (l1 != nullptr) l1 = l1->next;` — advancing an already-null pointer causes an immediate segmentation fault (`SIGSEGV`).

## 8. Edge Cases

| Case | How This Approach Handles It |
|:---|:---|
| **Unequal list lengths (`[9, 9]` + `[1]`)** | Shorter list becomes `nullptr` early and contributes `0` on remaining iterations |
| **Final carry after both lists end (`[5]` + `[5]`)** | `carry != 0` keeps the loop alive for one final iteration to allocate node `[1]` |
| **Cascading carries (`[9,9,9,9,9,9,9]` + `[9,9,9,9]`)** | `carry = 1` propagates cleanly across all 7 columns and spawns an 8th node `[1]` |
| **Both lists are `[0]`** | Runs 1 iteration: `sum = 0`, allocates `[0]`, `carry = 0`, loop ends |

## 9. Common Mistakes

1. **Writing `while (l1 != nullptr && l2 != nullptr)`**: Terminates as soon as the shorter list ends, ignoring the rest of the longer list.
2. **Writing `while (l1 != nullptr || l2 != nullptr)` (forgetting `|| carry != 0`)**: Fails on inputs like `99 + 1 = 100` or `5 + 5 = 10` where a carry outlives both lists.
3. **Advancing `l1 = l1->next` unconditionally**: Causes a null-pointer dereference (`SIGSEGV`) as soon as one list is shorter than the other.
4. **Returning `&dummy` or `dummy` instead of `dummy.next`**: Includes the fake leading `0` sentinel node in the output (and returning `&dummy` returns a dangling stack pointer!).

## 10. When To Prefer This Approach

- **Always** in interviews and production for **LC 2 — Add Two Numbers**.
- It is optimal in both time (`O(max(M, N))` single pass) and auxiliary space (`O(1)`), and demonstrates idiomatic C++ linked-list manipulation using a stack-allocated dummy head.
