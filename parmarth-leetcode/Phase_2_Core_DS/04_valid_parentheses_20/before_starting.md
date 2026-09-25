# 20. Valid Parentheses

## Intuition & Problem Analysis
Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

### Rules of Validity:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

### Key Observation:
The most recently opened bracket must be the first one closed. This Last-In-First-Out (LIFO) property is the textbook use case for a Stack.
