#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) l = mid + 1;
            else r = mid - 1;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    assert(sol.search(nums, 9) == 4);
    assert(sol.search(nums, 2) == -1);
    cout << "All LC 704 tests passed!" << endl;
    return 0;
}
