#include <vector>
#include <iostream>
using namespace std;

class solution{
public:
    vector<int> getConcatenation(vector<int>& nums){
        int n = nums.size();
        vector<int> ans(2*n);

        for(int i=0; i<n; i++){
            ans[i] = nums[i];
            ans[i+n] = nums[i];
        }
        return ans;

    };

};

int main(){

    vector<int> nums = {1,2,3};
    solution sol;
    vector<int> ans = sol.getConcatenation(nums);
    cout << "{";
    for (int x: ans) {
        cout << x << " " ;
       
    }
    cout << "}" << endl;
    

    return 0;
}