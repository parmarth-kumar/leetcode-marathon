// ============================================================
// Approach 1 — Check All Substrings
// Type      : Brute Force
// Time      : O(N^3)
// Space     : O(1) auxiliary, O(N) output
// ============================================================

#include <string>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
private:
    // Pass by const reference so we inspect characters in-place in O(1) auxiliary space
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    string longestPalindrome(string s) {
        int n = static_cast<int>(s.length());
        if (n <= 1) return s;

        int startIdx = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            // Structural pruning: start j at (i + maxLen) so we only test
            // substrings strictly longer than our current best (length >= maxLen + 1)
            for (int j = i + maxLen; j < n; j++) {
                if (isPalindrome(s, i, j)) {
                    maxLen = j - i + 1;
                    startIdx = i;
                }
            }
        }

        // Allocate the result substring only once at the end
        return s.substr(startIdx, maxLen);
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
