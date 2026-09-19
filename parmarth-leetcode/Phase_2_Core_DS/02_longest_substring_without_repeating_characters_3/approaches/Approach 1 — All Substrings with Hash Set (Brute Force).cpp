// ============================================================
// Approach 1 — All Substrings with Hash Set
// Type      : Brute Force
// Time      : O(N^2)
// Space     : O(min(N, Sigma)) auxiliary (O(1) for 128 ASCII), O(1) output
// ============================================================

#include <string>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = static_cast<int>(s.length());
        int maxLen = 0;

        // Try every possible starting index i
        for (int i = 0; i < n; ++i) {
            // Direct-access set tracking characters seen in s[i..j]
            bool visited[128] = {false};

            for (int j = i; j < n; ++j) {
                unsigned char ch = static_cast<unsigned char>(s[j]);

                // If s[j] already appeared in s[i..j-1], extending j further
                // from this start index i can never be valid.
                if (visited[ch]) {
                    break;
                }

                visited[ch] = true;
                maxLen = max(maxLen, j - i + 1);
            }
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
