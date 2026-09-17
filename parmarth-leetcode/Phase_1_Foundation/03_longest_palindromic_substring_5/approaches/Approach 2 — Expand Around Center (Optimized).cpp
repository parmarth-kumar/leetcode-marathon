// ============================================================
// Approach 2 — Expand Around Center
// Type      : Optimized
// Time      : O(N^2)
// Space     : O(1) auxiliary, O(N) output
// ============================================================

#include <string>
#include <utility>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
private:
    // Expands outward from [left, right] while characters match and returns
    // the inclusive {start, end} indices of the longest palindrome for this center.
    pair<int, int> expandAroundCenter(const string& s, int left, int right) {
        int n = static_cast<int>(s.length());
        while (left >= 0 && right < n && s[left] == s[right]) {
            left--;
            right++;
        }
        // When the loop exits, left and right have overshot the valid palindrome by 1 step
        return {left + 1, right - 1};
    }

public:
    string longestPalindrome(string s) {
        int n = static_cast<int>(s.length());
        if (n <= 1) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            // Case 1: Odd-length palindrome centered on s[i]
            auto [l1, r1] = expandAroundCenter(s, i, i);
            if (r1 - l1 + 1 > maxLen) {
                maxLen = r1 - l1 + 1;
                start = l1;
            }

            // Case 2: Even-length palindrome centered between s[i] and s[i + 1]
            auto [l2, r2] = expandAroundCenter(s, i, i + 1);
            if (r2 - l2 + 1 > maxLen) {
                maxLen = r2 - l2 + 1;
                start = l2;
            }
        }

        // Construct the final substring once in O(maxLen) output space
        return s.substr(start, maxLen);
    }
};

int main() {
    Solution sol;

    // Test 1: Odd-length palindrome in the middle
    {
        string res = sol.longestPalindrome("babad");
        assert(res == "bab" || res == "aba");
    }

    // Test 2: Even-length palindrome in the middle
    {
        assert(sol.longestPalindrome("cbbd") == "bb");
    }

    // Test 3: Single character
    {
        assert(sol.longestPalindrome("a") == "a");
    }

    // Test 4: Two distinct characters
    {
        string res = sol.longestPalindrome("ac");
        assert(res == "a" || res == "c");
    }

    // Test 5: Full string palindrome
    {
        assert(sol.longestPalindrome("racecar") == "racecar");
    }

    // Test 6: All identical characters
    {
        assert(sol.longestPalindrome("aaaa") == "aaaa");
    }

    // Test 7: Embedded long even-length palindrome
    {
        assert(sol.longestPalindrome("forgeeksskeegfor") == "geeksskeeg");
    }

    // Test 8: Reverse-LCS trap input
    {
        assert(sol.longestPalindrome("abacdfgdcaba") == "aba");
    }

    cout << "All tests passed!" << endl;
    return 0;
}
