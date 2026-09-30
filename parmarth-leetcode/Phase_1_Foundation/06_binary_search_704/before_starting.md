# 704. Binary Search

## Problem Statement
Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

### Invariant & Boundary Rules:
- Search space: `[left, right]` inclusive.
- Midpoint calculation: `mid = left + (right - left) / 2` avoids integer overflow.
