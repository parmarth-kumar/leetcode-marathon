# 🎯 DSA Mastery — Student Reference & Philosophy

> **Goal:** Google SDE Fresher | **Language:** C++ | **Student:** Parmarth | **Setup:** Solo Track Practice Workspace

---

## 👤 Student Profile

- **Parmarth** — Ambitious learner mastering DSA from the ground up
- Starting DSA with a rigorous, first-principles mindset
- Learning concepts and patterns **by doing problems**
- Target: **Google SDE (Fresher)** from college
- Language: **C++ (consistent throughout)**
- Needs: Deep conceptual intuition, granular step-by-step traces, mental models, and structured deliberate practice

---

## 🧠 Mentor Philosophy

The AI mentor operates as a combination of:

- A patient teacher who never assumes prior knowledge
- A Google interviewer who knows exactly what they test and how they evaluate
- A competitive programmer who knows every optimization, invariant, and pattern

### Core Optimization Pipeline

```text
UNDERSTANDING
    ↓
REASONING
    ↓
PATTERN RECOGNITION
    ↓
APPROACH SELECTION
    ↓
IMPLEMENTATION
    ↓
INTERVIEW TRANSFER
```

The goal is **transferable algorithmic thinking** — solving new, unseen problems independently. Not memorizing solutions.

---

## 📁 Problem Folder Architecture

Every newly generated problem follows a modular, anti-spoiler structure:

```text
{sequence}_{problem_name}_{leetcode_number}/
├── before_starting.md          ← Pre-solution learning document (5 layers)
├── test_harness.cpp            ← Empty Solution + test cases (write your code here)
└── approaches/
    ├── Approach 1 — <Name> (<Type>).md   ← Deep 10-section breakdown
    ├── Approach 1 — <Name> (<Type>).cpp  ← Compilable reference implementation
    └── ...
```

### How To Use It (Your Workflow)

```text
Step 1: Open before_starting.md
        Read Layers 1 & 2 (problem + prerequisites)
        ↓
Step 2: STOP at the checkpoint
        Do NOT scroll past the 🛑 barrier
        ↓
Step 3: Open test_harness.cpp
        Write your solution in the empty Solution class
        Compile and run → get instant pass/fail on edge cases
        ↓
Step 4: If stuck → reveal Layer 3 in before_starting.md (reasoning hints)
        Still stuck → reveal Layer 4 (approach names only, no code)
        ↓
Step 5: After solving (or giving up) → open approaches/ to compare
        Read the Approach .md for the 10-section deep dive
        ↓
Step 6: Fill in the Self-Assessment at the bottom of before_starting.md
```

---

## 🗺️ DSA Roadmap

| Phase                                     | Topics                                                                                                 |
| :---------------------------------------- | :----------------------------------------------------------------------------------------------------- |
| **Phase 1 — Foundation**                  | Arrays & Strings, Basic Math for DSA, Recursion                                                        |
| **Phase 2 — Core Data Structures**        | Hashing (`unordered_map`, `unordered_set`), Two Pointers & Sliding Window, Stack & Queue, Linked Lists |
| **Phase 3 — Intermediate**                | Binary Search, Trees & BST, Heaps / Priority Queues, Backtracking                                      |
| **Phase 4 — Advanced (Google Territory)** | Graphs (BFS, DFS, Dijkstra, Union-Find), Dynamic Programming, Tries, Segment Trees / BIT               |
| **Phase 5 — CP & Interview Polish**       | Greedy Algorithms, Bit Manipulation, Mock Interview Simulations                                        |

---

## 🔍 Code Review Protocol

After writing your solution, instead of immediately opening `approaches/`, ask the agent:

> **"review my-solution.cpp"** (or whatever you named your file)

The agent will:

1. **NOT** rewrite your code or show you the optimal solution
2. Point out potential bugs, edge cases you missed, and style issues
3. Ask you the follow-up questions a Google interviewer would ask:
   - "What's the time complexity? Can you prove it?"
   - "What's the auxiliary space vs output space?"
   - "What happens if the input is empty/maximally large?"
   - "Can you do better?"
4. Only after you've addressed the feedback, suggest comparing with `approaches/`

This simulates the back-and-forth of a real Google interview — you defend your solution before seeing the "model answer."

---

## 📝 Self-Assessment Guide

At the bottom of every `before_starting.md`, you'll find a checklist. **Fill it in honestly after every problem:**

| Status                            | What It Means                                    | Action                                        |
| :-------------------------------- | :----------------------------------------------- | :-------------------------------------------- |
| ✅ Solved optimally without hints | You own this pattern                             | Move on; revisit in 2 weeks                   |
| 🟡 Needed Layer 3 hints           | Close — you needed a nudge                       | Redo a similar problem within 3 days          |
| 🟠 Needed Approach files          | You understood the solution but couldn't find it | Study the approach .md deeply, redo in 1 week |
| 🔴 Could not solve independently  | This pattern needs focused work                  | Solve 2–3 related problems immediately        |

The `README.md` tracker can aggregate these across problems so you know which patterns are weak before mock interviews.

---

## 🏷️ Session Tag Format

Used at the start of every `before_starting.md`:

```text
Problem      : [Name]
LeetCode     : [URL]
Topic        : [Array / Graph / DP / etc.]
Difficulty   : Easy / Medium / Hard
Google-Tagged: Yes / No
Phase        : [1-5]
Track        : parmarth-leetcode
```

---

## 📐 Rule Source

All AI generation rules (file structure, content specs, layer definitions, approach classification) are defined in a single authoritative file:

> **[`.agents/rules/dsa-mentor.md`](./.agents/rules/dsa-mentor.md)**

`AGENTS.md` is a router that points there. This file (`master.md`) is for human reference only.

---

## 🎯 End Goal

Every session builds engineers who can walk into a Google interview, read a new problem, and know where to start — not from memory, but from structured algorithmic thinking.

Last Updated: 2026-09-29 | Language: C++ | Target: Google SDE Fresher | Student: Parmarth
