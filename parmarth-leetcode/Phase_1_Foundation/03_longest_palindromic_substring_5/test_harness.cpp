// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <string>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        // YOUR CODE HERE
        (void)s;
        return "";
    }
};

int main() {
    Solution sol;

    // Test 1: LeetCode Example 1 — odd-length palindrome in the middle ("bab" or "aba")
    {
        string res = sol.longestPalindrome("babad");
        assert(res == "bab" || res == "aba");
    }

    // Test 2: LeetCode Example 2 — even-length palindrome in the middle
    {
        assert(sol.longestPalindrome("cbbd") == "bb");
    }

    // Test 3: Single character string (minimum constraint length)
    {
        assert(sol.longestPalindrome("a") == "a");
    }

    // Test 4: Two different characters — any single character is a valid length-1 palindrome
    {
        string res = sol.longestPalindrome("ac");
        assert(res == "a" || res == "c");
    }

    // Test 5: Entire string is an odd-length palindrome
    {
        assert(sol.longestPalindrome("racecar") == "racecar");
    }

    // Test 6: All identical characters (even length)
    {
        assert(sol.longestPalindrome("aaaa") == "aaaa");
    }

    // Test 7: Long even-length palindrome embedded inside non-palindromic prefix/suffix
    {
        assert(sol.longestPalindrome("forgeeksskeegfor") == "geeksskeeg");
    }

    // Test 8: Trap input for "reverse + longest common substring" fallacy
    {
        string res = sol.longestPalindrome("abacdfgdcaba");
        assert(res == "aba");
    }

    cout << "All tests passed!" << endl;
    return 0;
}
