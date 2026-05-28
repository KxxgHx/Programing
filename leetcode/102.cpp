#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(vector<int>& nums) {
    if (nums.empty() || nums[0] == -1)
        return nullptr;

    TreeNode* root = new TreeNode(nums[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nums.size()) {
        TreeNode* node = q.front();
        q.pop();

        if (i < nums.size() && nums[i] != -1) {
            node->left = new TreeNode(nums[i]);
            q.push(node->left);
        }
        i++;

        if (i < nums.size() && nums[i] != -1) {
            node->right = new TreeNode(nums[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);

                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }

            result.push_back(level);
        }

        return result;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> nums(n + 1);
    for (int i = 0; i < n; i++) cin >> nums[i];

    TreeNode* root = buildTree(nums);

    Solution sol;
    vector<vector<int>> result = sol.levelOrder(root);

    for (auto &level : result) {
        cout << "[";
        for (int i = 0; i < level.size(); i++)
        {
            cout << level[i];
            if (i < (int)level.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }

    return 0;
}