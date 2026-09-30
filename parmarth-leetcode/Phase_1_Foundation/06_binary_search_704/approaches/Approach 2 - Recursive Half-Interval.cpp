#include <vector>
using namespace std;

class SolutionRecursive {
private:
    int helper(const vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) return helper(nums, target, mid + 1, right);
        return helper(nums, target, left, mid - 1);
    }
public:
    int search(vector<int>& nums, int target) {
        return helper(nums, target, 0, nums.size() - 1);
    }
};
