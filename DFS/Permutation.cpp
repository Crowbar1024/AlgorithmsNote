#include <myheader.h>

// 组合问题的特点
// 同一层的决策树的节点可选择数量一样
// 体现：for的个数本质上是当前节点的儿子个数
// 而组合的dfs基本传进去的是pos+1，这意味着每个儿子的儿子数量一样

// DFS是符合字典序的，所以也可以输出结果的排名

// 46 medium 全排列
// 有swap的写法
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        dfs(nums, 0, res);
        return res;
    }
    void dfs(vector<int>& nums, int pos, vector<vector<int>>& res) {
        if (pos == nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = pos; i < nums.size(); i++) {
            swap(nums[i], nums[pos]);
            dfs(nums, pos+1, res);  // 遍历当前决策树节点的子树
            swap(nums[i], nums[pos]);
        }
    }
};
// 没有swap的写法
class Solution {
public:
    vector<int> snap;
    vector<int> used;
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        used.resize(nums.size(), false);
        dfs(nums);
        return res;
    }
    void dfs(vector<int>& nums) {
        if (snap.size() == nums.size()) {
            res.push_back(snap);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (!used[i]) {
                snap.emplace_back(nums[i]);
                used[i] = true;
                dfs(nums);
                used[i] = false;
                snap.pop_back();
            }
            
        }
    }
};

// 47 medium 46进阶 给定一个可包含重复数字的序列，按任意顺序返回所有不重复的全排列。
// 因为加入了重复的思考，这里抛弃使用交换去获得新数组的方式
// 那么问题就变得更简单了一点，比如{1,1,2}的2当了第一层的第三个节点时
// 可以发现，它的儿子节点需要从第一个节点获得，所以每层的pos其实都是0
class Solution {
    public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> snap;
        vector<bool> used(nums.size(), false);
        dfs(used, nums, snap, res);
        return res;
    }
    void dfs(vector<bool> &used, vector<int>& nums, vector<int> &snap, vector<vector<int>>& res) {
        if (snap.size() == nums.size()) {
            res.push_back(snap);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            if (!used[i]) {
                snap.emplace_back(nums[i]);
                used[i] = true;
                dfs(used, nums, snap, res);
                snap.pop_back();
                used[i] = false;
            }

        }
    }
};