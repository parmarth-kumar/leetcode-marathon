# Approach 1: String Replacement (Baseline)
Repeatedly replace occurrences of `"()"`, `"{}"`, and `"[]"` with empty strings until no more replacements can be made. If the resulting string is empty, it's valid.

### Complexity:
- Time: $O(N^2)$ due to repeated substring scanning and deletions.
- Space: $O(N)$ for string copies.
