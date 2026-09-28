#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = 1e9;
        int maxProfit = 0;
        for (int p : prices) {
            minPrice = min(minPrice, p);
            maxProfit = max(maxProfit, p - minPrice);
        }
        return maxProfit;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {7, 1, 5, 3, 6, 4};
    assert(sol.maxProfit(p1) == 5);
    vector<int> p2 = {7, 6, 4, 3, 1};
    assert(sol.maxProfit(p2) == 0);
    cout << "All LC 121 tests passed!" << endl;
    return 0;
}
