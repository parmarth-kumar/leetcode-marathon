#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* temp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(temp);
        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);

    Solution sol;
    TreeNode* inverted = sol.invertTree(root);
    assert(inverted->left->val == 7);
    assert(inverted->right->val == 2);
    cout << "All LC 226 tests passed!" << endl;
    return 0;
}
