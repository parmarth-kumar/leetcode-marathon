#include <vector>
#include <algorithm>
using namespace std;

class SolutionOptimized {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = 1e9;
        int maxProf = 0;
        for (int price : prices) {
            minPrice = min(minPrice, price);
            maxProf = max(maxProf, price - minPrice);
        }
        return maxProf;
    }
};
