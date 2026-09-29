# 🎯 LeetCode & DSA Mastery — Parmarth's Track

> **Target:** Google SDE Fresher | **Language:** C++ | **Engineer:** Parmarth | **Approach:** Deep Concept & Pattern Building

This repository tracks a structured journey from foundational problem solving to advanced Data Structures, Algorithms, and Competitive Programming in **C++**.

Maintained by **Parmarth**, focusing on deep conceptual problem solving, problem depth, and learning materials.

---

## 📁 Workspace Directory

- **[`parmarth-leetcode/`](./parmarth-leetcode/)** — Parmarth's track

---

## 🗺️ Roadmap & Phases

The track contains five phase directories:

- **Phase 1: Foundation** — Arrays & Strings, Basic Math, Recursion
- **Phase 2: Core Data Structures** — Hashing, Two Pointers, Sliding Window, Stacks & Queues, Linked Lists
- **Phase 3: Intermediate** — Binary Search, Trees & BST, Heaps, Backtracking
- **Phase 4: Advanced** — Graphs, Dynamic Programming, Tries, Segment Trees
- **Phase 5: CP & Interview Polish** — Greedy, Bit Manipulation, Mock Simulations

---

## 📁 Problem Folder Architecture

Every newly generated problem follows this structure:

```text
{sequence}_{problem_name}_{leetcode_number}/
├── before_starting.md          ← 5-layer pre-solution guide (anti-spoiler design)
├── test_harness.cpp            ← Empty Solution + assert tests (write your code here)
└── approaches/
    ├── Approach 1 — <Name> (<Type>).md   ← 10-section deep dive
    ├── Approach 1 — <Name> (<Type>).cpp  ← Compilable reference implementation
    └── ...
```

See [`master.md`](./master.md) for the complete workflow guide.

---

## 📊 Solved Problems Tracker

### Phase 1: Foundation

|  #  | Problem                                                                                              | Topic                       | Difficulty | Google Tagged |                                     Folder                                       |
| :-: | ---------------------------------------------------------------------------------------------------- | --------------------------- | :--------: | :-----------: | :------------------------------------------------------------------------------: |
| 01  | [Two Sum (LC 1)](https://leetcode.com/problems/two-sum/)                                             | Array / Hash Table          |    Easy    |    ⭐ Yes     |            [📂](./parmarth-leetcode/Phase_1_Foundation/01_two_sum_1/)            |
| 02  | [Container With Most Water (LC 11)](https://leetcode.com/problems/container-with-most-water/)        | Array, Two Pointers, Greedy |   Medium   |      No       |  [📂](./parmarth-leetcode/Phase_1_Foundation/02_container_with_most_water_11/)   |
| 03  | [Longest Palindromic Substring (LC 5)](https://leetcode.com/problems/longest-palindromic-substring/) | String, Two Pointers, DP    |   Medium   |    ⭐ Yes     | [📂](./parmarth-leetcode/Phase_1_Foundation/03_longest_palindromic_substring_5/) |
| 04  | [Concatenation of Array (LC 1929)](https://leetcode.com/problems/concatenation-of-array/)            | Array, Simulation           |    Easy    |      No       |   [📂](./parmarth-leetcode/Phase_1_Foundation/04_concatenation_of_array_1929/)   |

### Phase 2: Core Data Structures

|  #  | Problem                                                                                                                                | Topic                              | Difficulty | Google Tagged |                                            Folder                                              |
| :-: | -------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------- | :--------: | :-----------: | :--------------------------------------------------------------------------------------------: |
| 01  | [Add Two Numbers (LC 2)](https://leetcode.com/problems/add-two-numbers/)                                                               | Linked List, Math                  |   Medium   |    ⭐ Yes     |                [📂](./parmarth-leetcode/Phase_2_Core_DS/01_add_two_numbers_2/)                 |
| 02  | [Longest Substring Without Repeating Characters (LC 3)](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Hash Table, String, Sliding Window |   Medium   |    ⭐ Yes     | [📂](./parmarth-leetcode/Phase_2_Core_DS/02_longest_substring_without_repeating_characters_3/) |
| 03  | [3Sum (LC 15)](https://leetcode.com/problems/3sum/)                                                                                    | Array, Two Pointers, Sorting       |   Medium   |    ⭐ Yes     |                     [📂](./parmarth-leetcode/Phase_2_Core_DS/03_3sum_15/)                      |

### Phase 3: Intermediate

|  #  | Problem                                                                                          | Topic                                    | Difficulty | Google Tagged |                                     Folder                                       |
| :-: | ------------------------------------------------------------------------------------------------ | ---------------------------------------- | :--------: | :-----------: | :------------------------------------------------------------------------------: |
| 01  | [Median of Two Sorted Arrays (LC 4)](https://leetcode.com/problems/median-of-two-sorted-arrays/) | Array, Binary Search, Divide and Conquer |    Hard    |    ⭐ Yes     | [📂](./parmarth-leetcode/Phase_3_Intermediate/01_median_of_two_sorted_arrays_4/) |

---

## 🛠️ Repository Standards & References

- **AI Generation Rules (Single Source of Truth):** [`.agents/rules/dsa-mentor.md`](./.agents/rules/dsa-mentor.md)
- **Student Reference & Philosophy:** [`master.md`](./master.md)
- **Agent Router:** [`AGENTS.md`](./AGENTS.md)
- **Shared C++ Types:** [`include/leetcode_types.h`](./include/leetcode_types.h)
