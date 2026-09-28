#include <vector>
#include <algorithm>
using namespace std;

class SolutionBrute {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int maxProf = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                maxProf = max(maxProf, prices[j] - prices[i]);
            }
        }
        return maxProf;
    }
};
