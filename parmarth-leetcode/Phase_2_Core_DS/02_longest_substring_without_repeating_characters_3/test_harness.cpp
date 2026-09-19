// test_harness.cpp — Write your solution here, then compile and run.
// DO NOT look at approaches/ until all tests pass or you are truly stuck.

#include <string>
#include <cassert>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // YOUR CODE HERE
        return 0;
    }
};

int main() {
    Solution sol;

    // Test 1: Standard case with repeating triplets ("abc")
    assert(sol.lengthOfLongestSubstring("abcabcbb") == 3);

    // Test 2: All identical characters ("b")
    assert(sol.lengthOfLongestSubstring("bbbbb") == 1);

    // Test 3: Answer in the middle + subsequence trap ("wke" or "kew")
    assert(sol.lengthOfLongestSubstring("pwwkew") == 3);

    // Test 4: Empty string boundary case (s.length() == 0)
    assert(sol.lengthOfLongestSubstring("") == 0);

    // Test 5: Single space character (non-letter ASCII)
    assert(sol.lengthOfLongestSubstring(" ") == 1);

    // Test 6: Pointer regression trap — old duplicate outside current window ("ab" or "ba")
    assert(sol.lengthOfLongestSubstring("abba") == 2);

    // Test 7: Non-adjacent duplicate where restarting from scratch fails ("vdf")
    assert(sol.lengthOfLongestSubstring("dvdf") == 3);

    // Test 8: Interleaved duplicates + trailing unique stretch ("mzuxt")
    assert(sol.lengthOfLongestSubstring("tmmzuxt") == 5);

    cout << "All tests passed!" << endl;
    return 0;
}
