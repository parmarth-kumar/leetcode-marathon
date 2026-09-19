// ============================================================
// Approach 2 — Sliding Window with Last-Seen Index
// Type      : Optimized
// Time      : O(N)
// Space     : O(min(N, Sigma)) auxiliary (O(1) for 128 ASCII), O(1) output
// ============================================================

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = static_cast<int>(s.length());

        // Direct-access table storing the most recent 0-based index of each ASCII character.
        // Initialized to -1 to indicate the character has not yet been seen.
        vector<int> lastSeen(128, -1);

        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < n; ++right) {
            unsigned char ch = static_cast<unsigned char>(s[right]);

            // If 'ch' appeared previously, jump 'left' past its previous occurrence.
            // max() ensures 'left' never moves backward if lastSeen[ch] < left (e.g., "abba").
            if (lastSeen[ch] != -1) {
                left = max(left, lastSeen[ch] + 1);
            }

            lastSeen[ch] = right;
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

int main() {
    Solution sol;

    // Test 1: Standard repeating triplets ("abc")
    assert(sol.lengthOfLongestSubstring("abcabcbb") == 3);

    // Test 2: All identical characters ("b")
    assert(sol.lengthOfLongestSubstring("bbbbb") == 1);

    // Test 3: Middle answer + subsequence trap ("wke")
    assert(sol.lengthOfLongestSubstring("pwwkew") == 3);

    // Test 4: Empty string
    assert(sol.lengthOfLongestSubstring("") == 0);

    // Test 5: Single space character
    assert(sol.lengthOfLongestSubstring(" ") == 1);

    // Test 6: Pointer regression trap ("ab" or "ba")
    assert(sol.lengthOfLongestSubstring("abba") == 2);

    // Test 7: Separated duplicate ("vdf")
    assert(sol.lengthOfLongestSubstring("dvdf") == 3);

    // Test 8: Interleaved duplicates ("mzuxt")
    assert(sol.lengthOfLongestSubstring("tmmzuxt") == 5);

    cout << "All tests passed!" << endl;
    return 0;
}
