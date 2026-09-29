Problem      : Add Two Numbers
LeetCode     : https://leetcode.com/problems/add-two-numbers/
Topic        : Linked List, Math, Recursion
Difficulty   : Medium
Google-Tagged: Yes
Phase        : 2 — Core Data Structures
Track        : parmarth-leetcode

---

## 🧩 Layer 1 — Problem Deconstruction

### Problem Statement (Plain English)

You are given **two non-empty singly-linked lists** representing two non-negative integers.
- The digits are stored in **reverse order**, meaning the `1`'s digit (least significant digit) is at the head of each list.
- Each node contains a **single base-10 digit** (`0` to `9`).
- Neither number contains any leading zeros, except the number `0` itself.

Your task is to **add the two numbers** and return the sum as a **newly constructed linked list**, also in reverse order.

### Input & Output

- **Input**:
  - `ListNode* l1`: Head of the first non-empty linked list (each node value in `[0, 9]`).
  - `ListNode* l2`: Head of the second non-empty linked list (each node value in `[0, 9]`).
- **Output**:
  - `ListNode*`: Head of the linked list representing the sum in reverse digit order.

### Constraints & Their Implications

| Constraint | Implication |
|:---|:---|
| `1 <= length(l1), length(l2) <= 100` | Neither list is empty. However, a 100-node list represents a **100-digit integer** — far beyond any built-in C++ integer type! |
| `0 <= Node.val <= 9` | Every node holds strictly one decimal digit. The maximum possible sum at any single position is `9 + 9 + 1 (carry) = 19`, so `carry` is always `0` or `1`. |
| No leading zeros (except `0` itself) | Input lists are canonical (e.g., `0` is `[0]`, never `[0, 0]`). Your output must also not introduce spurious trailing zero nodes. |

**CPU & Data-Type Intuition**:
- **Time**: With at most `100` nodes per list, even a multi-pass `O(max(M, N))` algorithm executes in `< 1000` CPU operations — well within the `~10^8` operations/second budget.
- **Integer Overflow (Critical!)**: Standard C++ primitive types cannot hold 100-digit numbers:
  - `int` maxes out at `~2.14 × 10^9` (~10 digits)
  - `unsigned long long` maxes out at `~1.84 × 10^19` (~19 digits)
  - `__int128` maxes out at `~3.40 × 10^38` (~39 digits)
  - Therefore, **converting the linked lists to integers, adding them, and converting back will fatally overflow**. You must simulate addition digit-by-digit.

### Terminology

- **Singly-Linked List (`ListNode`)**: A chain of heap-allocated nodes where each node stores a value (`val`) and a pointer (`next`) to the following node (or `nullptr` at the end).
- **Reverse Order (Least-Significant-Digit First)**: For the number `342`, the ones digit `2` comes first, followed by the tens digit `4`, and the hundreds digit `3`: `2 -> 4 -> 3`.
- **Carry**: When the sum of digits in a column is `10` or greater, the tens part (`sum / 10`, which is `1`) is carried over and added to the next higher positional column.
- **Leading Zero**: A `0` at the most significant digit of a multi-digit number (e.g., `0342`). Because our lists are stored in reverse order, a leading zero in the number would appear as a **trailing `0` node at the tail** of the linked list.

### Worked Examples

**Example 1** — Equal lengths with an internal carry (`342 + 465 = 807`):
```text
l1:  2 -> 4 -> 3       (represents 342)
l2:  5 -> 6 -> 4       (represents 465)

Paper Addition (right-to-left)   Linked List Addition (left-to-right)
    Carry:   1  0                    Col 0 (1s) : 2 + 5 + 0 = 7  -> digit 7, carry 0
             3  4  2                 Col 1 (10s): 4 + 6 + 0 = 10 -> digit 0, carry 1
           + 4  6  5                 Col 2 (100s): 3 + 4 + 1 = 8 -> digit 8, carry 0
           ---------
             8  0  7             Output: 7 -> 0 -> 8  (represents 807)
```

**Example 2** — Both inputs are zero (`0 + 0 = 0`):
```text
l1:  0                 (represents 0)
l2:  0                 (represents 0)

Col 0 (1s): 0 + 0 + 0 = 0 -> digit 0, carry 0
Output: 0
```

**Example 3** — Unequal lengths + lingering final carry (`99 + 1 = 100`):
```text
l1:  9 -> 9            (represents 99)
l2:  1                 (represents 1)

Col 0 (1s)  : 9 + 1 + 0 = 10 -> digit 0, carry 1
Col 1 (10s) : 9 + 0 + 1 = 10 -> digit 0, carry 1   (l2 ended, treat missing digit as 0)
Col 2 (100s): 0 + 0 + 1 = 1  -> digit 1, carry 0   (both ended, but carry=1 creates a new node!)

Output: 0 -> 0 -> 1   (represents 100)
```

**Example 4** — Long cascading carry across unequal lengths (`9999999 + 9999 = 10009998`):
```text
l1:  9 -> 9 -> 9 -> 9 -> 9 -> 9 -> 9   (7 nodes)
l2:  9 -> 9 -> 9 -> 9                  (4 nodes)

Col 0: 9 + 9 + 0 = 18 -> digit 8, carry 1
Col 1: 9 + 9 + 1 = 19 -> digit 9, carry 1
Col 2: 9 + 9 + 1 = 19 -> digit 9, carry 1
Col 3: 9 + 9 + 1 = 19 -> digit 9, carry 1
Col 4: 9 + 0 + 1 = 10 -> digit 0, carry 1
Col 5: 9 + 0 + 1 = 10 -> digit 0, carry 1
Col 6: 9 + 0 + 1 = 10 -> digit 0, carry 1
Col 7: 0 + 0 + 1 = 1  -> digit 1, carry 0

Output: 8 -> 9 -> 9 -> 9 -> 0 -> 0 -> 0 -> 1  (8 nodes)
```

### Common Beginner Traps

1. **The Integer Overflow Trap (Fatal)**: Converting `l1` and `l2` into `long long`, adding them, and building a list from the sum. LeetCode includes test cases with 30–100 nodes that immediately overflow 64-bit integers.
2. **Reversing the Input Lists Unnecessarily**: Beginners see "stored in reverse order" and instinctively reverse the lists first. **Do not reverse them!** Elementary addition starts at the ones place, and reverse order puts the ones place right at the head of both lists.
3. **Forgetting the Final Carry (Most Common Bug)**: When adding `99 + 1`, both `l1` and `l2` become `nullptr` after two steps, but `carry = 1` is still waiting. Stopping when `l1 == nullptr && l2 == nullptr` drops the most significant digit (`1`), returning `0 -> 0` instead of `0 -> 0 -> 1`.
4. **Null-Pointer Dereference on Unequal Lengths**: Accessing `l1->val` or `l1->next` after the shorter list has already reached `nullptr`.
5. **Losing the Head of the Result List**: Using a single pointer `curr` to allocate nodes (`curr = curr->next`) without keeping a fixed pointer anchored to the start of the result list.

### One-Sentence Restatement

> Simulate grade-school column addition from left to right across two reverse-ordered linked lists, treating missing nodes in a shorter list as `0` and propagating the `carry` until both lists and the carry are exhausted.

---

## 📚 Layer 2 — Concepts & Prerequisites

### 1. Singly-Linked List & Pointer Traversal (`ListNode`)

**What it is**: A dynamic data structure where elements (`ListNode` structs) are allocated separately in memory and connected via pointers.

**Mechanics**:
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```
- Access the current node's value with `curr->val`.
- Advance to the next node with `curr = curr->next`.
- A pointer with value `nullptr` indicates the end of the list.

**Why it matters here**: Both inputs and the required output are singly-linked lists accessed exclusively through `ListNode*` pointers.

### 2. Grade-School Column Addition (Digit & Carry Math)

**What it is**: The arithmetic rule for adding two single-digit numbers plus an incoming carry at a given positional column in base 10.

**Mechanics**:
Given `val1 ∈ [0, 9]`, `val2 ∈ [0, 9]`, and `carry ∈ {0, 1}`:
```cpp
int sum = val1 + val2 + carry;
int new_digit = sum % 10;  // Remainder stays in the current column (0..9)
int new_carry = sum / 10;  // Quotient carries over to the next column (0 or 1)
```

**Example**:
```text
val1 = 9, val2 = 9, carry = 1
sum = 19  -->  new_digit = 19 % 10 = 9,  new_carry = 19 / 10 = 1
```

**Why it matters here**: Every node in the output list is computed using `sum % 10`, and `sum / 10` is passed to the next iteration.

### 3. The Sentinel (Dummy Head) Node Pattern

**What it is**: A temporary placeholder node created before the start of a new linked list so that every real node—including the very first one—can be appended uniformly via `tail->next`.

**Mechanics**:
Without a dummy head, you must branch on every iteration to check if `head == nullptr`:
```cpp
// Without dummy head (verbose and error-prone):
if (head == nullptr) { head = new ListNode(d); tail = head; }
else                 { tail->next = new ListNode(d); tail = tail->next; }
```
With a stack-allocated or heap-allocated dummy head:
```cpp
ListNode dummy(0);          // Stack sentinel (auto-cleaned on return)
ListNode* tail = &dummy;

tail->next = new ListNode(d);
tail = tail->next;

return dummy.next;          // Real head starts right after dummy
```

**Why it matters here**: Eliminates special-case logic for initializing the head of the sum list.

### 4. Safe Null-Pointer Substitution (Ternary Guard)

**What it is**: Replacing a missing node's value with an identity element (`0` for addition) when one list is shorter than the other.

**Mechanics**:
```cpp
int val1 = (l1 != nullptr) ? l1->val : 0;
int val2 = (l2 != nullptr) ? l2->val : 0;
if (l1 != nullptr) l1 = l1->next;
if (l2 != nullptr) l2 = l2->next;
```

**Why it matters here**: Allows a single unified loop to handle both lists even after one list reaches `nullptr`, instead of writing three separate loops.

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

When we add two numbers on paper (say `342 + 465`), which digits do we add first?
We always start at the **rightmost digit (the ones place)**: `2 + 5 = 7`, then move to the tens place `4 + 6 = 10`, and finally the hundreds place `3 + 4 + 1 = 8`.

Look at how the linked lists are given:
```text
l1: 2 -> 4 -> 3
l2: 5 -> 6 -> 4
```
The heads of `l1` and `l2` **already point to the ones place**! Moving forward (`->next`) moves from ones → tens → hundreds, which is the exact order in which carries propagate.

### Step-by-Step Reasoning

**Step 1 — Rule out integer conversion**:
Can we convert `l1` to an integer `342`, `l2` to `465`, compute `342 + 465 = 807`, and unpack the digits?
No — the constraints allow up to `100` nodes (`10^100 - 1`), which overflows `int` (10 digits) and `long long` (19 digits).

**Step 2 — The Naive / Direct Thought Process (Vector Extraction)**:
If we aren't yet comfortable manipulating linked-list pointers while doing arithmetic, we can decouple the problem into three stages:
1. Traverse `l1` and `l2` to copy their digits into `vector<int> v1` and `vector<int> v2`.
2. Add `v1` and `v2` element-by-element using a `carry` variable, pushing each `sum % 10` into `vector<int> res`.
3. Loop over `res` and build the output linked list.

This works and avoids overflow, but it uses `O(M + N)` extra memory for the vectors and makes 3 separate passes.

**Step 3 — Discovering the Single-Pass Optimization**:
Look closely at Step 2 above: at index `i`, we only ever read `v1[i]` and `v2[i]` once, and immediately produce one output digit `sum % 10`.
Why copy `l1->val` and `l2->val` into vectors first when we can read `l1->val` and `l2->val` directly from the nodes, allocate the output node `new ListNode(sum % 10)` immediately, and advance the pointers?

**Step 4 — Handling Unequal Lengths & Termination**:
What if `l1` has 2 nodes and `l2` has 1 node (like `99 + 1`)?
- Instead of stopping when the shorter list ends, we treat a `nullptr` list as contributing `0` to the sum.
- When are we truly done? Only when **all three** sources of value are exhausted:
  1. `l1 == nullptr` (no digits left in `l1`)
  2. `l2 == nullptr` (no digits left in `l2`)
  3. `carry == 0` (no carry waiting to create a new most-significant digit)

Therefore, our loop condition is:
```text
while (l1 != nullptr || l2 != nullptr || carry != 0)
```

### Visual Trace (`l1 = [9, 9]`, `l2 = [1]`)

```text
Initial State:
  l1   : [9] -> [9] -> nullptr
  l2   : [1] -> nullptr
  dummy: [0] -> nullptr
  tail : points to dummy
  carry: 0

--- Iteration 1 (1s place) ---
  val1 = 9, val2 = 1, carry = 0
  sum  = 9 + 1 + 0 = 10
  digit = 10 % 10 = 0,  new carry = 10 / 10 = 1
  Append [0] to tail:
    dummy: [0] -> [0] -> nullptr
                   ^
                  tail
  Advance l1 to second [9], l2 to nullptr

--- Iteration 2 (10s place) ---
  val1 = 9, val2 = 0 (l2 is nullptr), carry = 1
  sum  = 9 + 0 + 1 = 10
  digit = 10 % 10 = 0,  new carry = 10 / 10 = 1
  Append [0] to tail:
    dummy: [0] -> [0] -> [0] -> nullptr
                          ^
                         tail
  Advance l1 to nullptr, l2 stays nullptr

--- Iteration 3 (100s place — triggered by carry == 1) ---
  val1 = 0, val2 = 0, carry = 1
  sum  = 0 + 0 + 1 = 1
  digit = 1 % 10 = 1,   new carry = 1 / 10 = 0
  Append [1] to tail:
    dummy: [0] -> [0] -> [0] -> [1] -> nullptr
                                 ^
                                tail
  l1 is nullptr, l2 is nullptr, carry is 0 -> Loop ends!

Return dummy.next  -->  [0] -> [0] -> [1]  (represents 100) ✓
```

| Step | `l1` Node | `l2` Node | Incoming `carry` | `sum = v1 + v2 + carry` | New Node (`sum % 10`) | Outgoing `carry` (`sum / 10`) | Result List (`dummy.next`) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---|
| 1 | `9` | `1` | `0` | `9 + 1 + 0 = 10` | `0` | `1` | `0` |
| 2 | `9` | `nullptr` (`0`) | `1` | `9 + 0 + 1 = 10` | `0` | `1` | `0 -> 0` |
| 3 | `nullptr` (`0`) | `nullptr` (`0`) | `1` | `0 + 0 + 1 = 1` | `1` | `0` | `0 -> 0 -> 1` |

### Questions an Interviewer Expects You to Ask

1. *"Are the digits stored in reverse order (least significant digit at the head) or forward order?"* → Reverse order (head is the 1s place).
2. *"Can either linked list be empty (`nullptr`)?"* → No, constraints guarantee at least 1 node per list, though our pointer guard naturally handles empty lists too.
3. *"Are we allowed to modify the input lists in-place, or should we allocate a new list for the result?"* → Usually allocate a new list, though in-place reuse is a common follow-up question.
4. *"Can the numbers contain leading zeros?"* → No, except the number `0` itself (`[0]`).

</details>

---

<details>
<summary>📋 Layer 4 — Approach Overview (click to reveal)</summary>

### Approach 1 — Vector Extraction and Addition (Brute Force)

- **Type**: Brute Force
- **Time**: `O(max(M, N))` (3 separate passes)
- **Space**: `O(M + N)` auxiliary (intermediate vectors), `O(max(M, N))` output
- Extract digits from both linked lists into `std::vector<int>`, simulate grade-school addition on the vectors, and construct the output linked list from the result vector.
- 📄 [Approach 1 — Vector Extraction and Addition (Brute Force).md](<./approaches/Approach 1 — Vector Extraction and Addition (Brute Force).md>)
- 💻 [Approach 1 — Vector Extraction and Addition (Brute Force).cpp](<./approaches/Approach 1 — Vector Extraction and Addition (Brute Force).cpp>)

### Approach 2 — Elementary Math with Dummy Head (Optimized)

- **Type**: Optimized
- **Time**: `O(max(M, N))` (single simultaneous pass)
- **Space**: `O(1)` auxiliary, `O(max(M, N))` output
- Traverse both linked lists simultaneously in a single pass, computing each digit and carry on-the-fly and appending directly to a dummy-headed result list with zero intermediate containers.
- 📄 [Approach 2 — Elementary Math with Dummy Head (Optimized).md](<./approaches/Approach 2 — Elementary Math with Dummy Head (Optimized).md>)
- 💻 [Approach 2 — Elementary Math with Dummy Head (Optimized).cpp](<./approaches/Approach 2 — Elementary Math with Dummy Head (Optimized).cpp>)

</details>

---

<details>
<summary>🎯 Layer 5 — What To Take Away (click to reveal)</summary>

### 1. Core Pattern

**Simultaneous Multi-List Traversal with Sentinel (Dummy) Head**: Advancing two pointers lockstep across two linked lists while using a dummy head node to build a new output list in `O(1)` auxiliary space.

### 2. Mental Model

> "Whenever you need to build a new linked list node-by-node from one or more streams, anchor the result with a **Dummy Head** (`ListNode dummy(0)`) and keep your loop running while **any input stream OR carry remains active** (`l1 || l2 || carry`)."

### 3. Memorization vs Understanding

**MUST REMEMBER**:
- The **Dummy Head idiom**: `ListNode dummy(0); ListNode* tail = &dummy; ... return dummy.next;`
- The **3-part loop condition**: `while (l1 != nullptr || l2 != nullptr || carry != 0)`
- Null-safe value extraction: `int val1 = (l1 != nullptr) ? l1->val : 0;`

**SHOULD UNDERSTAND**:
- Why converting linked lists to `int` or `long long` fails when list length reaches 20–100 nodes.
- Why reverse digit order allows single-pass left-to-right traversal (because carries propagate from least significant to most significant digit).
- Why `carry` can never exceed `1` (`9 + 9 + 1 = 19`, and `19 / 10 = 1`).

**SHOULD BE ABLE TO RE-DERIVE**:
- Base-`B` column addition formulas: `digit = sum % B` and `carry = sum / B` (works for Base 10, Base 2 in LC 67, etc.).
- How to adapt the algorithm if digits were stored in forward order (reverse lists first, or push onto stacks as in LC 445).

### 4. Previously Seen Patterns (Cross-Reference)

This is **Problem 01 of Phase 2 (Core Data Structures)** and your first Linked List problem in the curriculum. While you saw index-based array construction in **Phase 1, Problem 04 — Concatenation of Array (LC 1929)** and two-pointer traversal in **Phase 1, Problem 02 — Container With Most Water (LC 11)**, here those ideas transition from contiguous array indices (`nums[i]`) to **heap-allocated pointer chains (`curr = curr->next`)** where random access does not exist.

### 5. Related LeetCode Problems

| Problem | Why Related |
|:---|:---|
| [LC 445 — Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/) | Direct follow-up: digits are stored in **forward (most-significant-first)** order; requires stacks or list reversal. |
| [LC 415 — Add Strings](https://leetcode.com/problems/add-strings/) | Identical grade-school addition and carry loop applied to two `std::string` objects from back to front. |
| [LC 67 — Add Binary](https://leetcode.com/problems/add-binary/) | Same `i >= 0 || j >= 0 || carry` loop pattern, using base 2 (`sum % 2` and `sum / 2`) instead of base 10. |
| [LC 66 — Plus One](https://leetcode.com/problems/plus-one/) | Simplified version of carry propagation when adding `1` to a big integer represented as an array of digits. |
| [LC 21 — Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | Uses the exact same **Dummy Head + `tail` pointer** construction pattern on two linked lists. |

### 6. Interview Questions

1. **"What if the digits were stored in forward order (e.g., `3 -> 4 -> 2` for `342`)?"**
   → Carries propagate from right to left, opposite to the pointer direction. You can either (a) reverse both input lists, add them, and reverse the result (`O(1)` auxiliary space), or (b) push both lists onto two stacks so the ones digits sit on top (`O(M + N)` space, avoids modifying inputs — LC 445).
2. **"Can you solve this with strictly `O(1)` total new allocations (reusing input nodes)?"**
   → Yes, if the interviewer permits mutating `l1` and `l2`, you can overwrite `l1->val` with `sum % 10`, splice `l2`'s tail onto `l1` if `l2` is longer, and only allocate at most one `new ListNode(1)` if a final carry remains.
3. **"Why is the iterative solution preferred over a recursive implementation in C++?"**
   → A recursive implementation (`add(l1->next, l2->next, carry)`) takes `O(max(M, N))` call-stack space, whereas the iterative dummy-head approach uses `O(1)` auxiliary space.
4. **"Should `dummy` be allocated on the stack (`ListNode dummy(0);`) or on the heap (`new ListNode(0)`)?"**
   → Stack allocation (`ListNode dummy(0);`) is cleaner and faster in C++: it requires no heap allocation, cannot leak memory if an exception occurs, and automatically cleans itself up when the function returns `dummy.next`.

### 7. Leftover Important Details

- **Maximum Output Length**: Adding an `M`-digit number and an `N`-digit number produces a result with at most `max(M, N) + 1` digits (because `10^k - 1 + 10^k - 1 = 2·10^k - 2 < 10^(k+1)`).
- **Stack vs Heap Dummy Node**: If you do allocate the dummy node on the heap (`ListNode* dummy = new ListNode(0);`), always save `ListNode* result = dummy->next;` and call `delete dummy;` before returning to avoid a 1-node memory leak in interviews. Using `ListNode dummy(0);` on the stack avoids this completely.

</details>

---

## 📝 Self-Assessment (fill in after attempting)

- [ ] Solved optimally without any hints
- [ ] Solved but needed Layer 3 hints
- [ ] Solved but needed to read Approach files
- [ ] Could not solve independently
- **Time taken**: \_\_\_ minutes
- **Confidence to solve a similar problem in an interview**: Low / Medium / High
