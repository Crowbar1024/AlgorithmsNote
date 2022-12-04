#include <myheader.h>

// 70 easy 爬楼梯。需要n阶（>0）才能到达楼顶。
// 每次可以爬1或2个台阶。有多少种不同的方法可以爬到楼顶
// dp[i] = dp[i-1]+dp[i-2]
// dp[1] = 1; dp[2] = 2;
// 所以本质还是斐波那契数列509，可以用快速幂
int climbStairs(int n) {
    int dp1 = 1, dp2 = 1;
    while (--n) {
        dp2 = exchange(dp1, dp1+dp2);
    }
    return dp1;
}
// 这道题变一下，每次最多可以跳m层，那么跳到楼顶一共有多少种跳法？同完全背包的377，排列数统计

// 746 easy cost为楼梯每个阶梯对应的体力花费（>=0）
// 一旦支付了相应的体力值，可以选择向上爬一个阶梯或者爬两个阶梯。找出达到楼层顶部（不是cost末尾）的最低花费。
// 在开始时，你可以选择从下标为0或1的元素作为初始阶梯。
// dp[i] = min(dp[i-2]+cost[i-2],dp[i-1]+cost[i-1])
// dp[0] = 0; dp[1] = 0;  状态压缩为两个变量
int minCostClimbingStairs(vector<int>& cost) {
    int dp1 = 0, dp2 = 0;
    for (int i = 2; i <= cost.size(); ++i) {  // 不是末尾，所以取等号
        dp1 = exchange(dp2, min(dp1+cost[i-2], dp2+cost[i-1]));
    }
    return dp2;
}

// 62 medium 一个机器人位于一个mxn网格的左上角，每次只能向下或者向右移动一步。
// 试图达到网格的右下角，问总共有多少条不同的路径？
// dp[i][j] = dp[i-1][j]+dp[i][j-1] 显然可以压缩
// dp[i][0] = dp[0][j] = 1;
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] += dp[j-1];
        }
    }
    return dp[n-1];
}
// 还有组合思想的解法，不如DP

// 63 medium 62的基础上加了阻碍，1表示阻碍
// 正常DP为
// if (obstacleGrid[i][j] == 1) {
//     dp[i][j] = 0;
// } else {
//     if (obstacleGrid[i-1][j] == 1) {
//         dp[i][j] = dp[i][j-1];  // 都是1也成立
//     } else if (obstacleGrid[i][j-1] == 1) {
//         dp[i][j] = dp[i-1][j];
//     } else {
//         dp[i][j] = dp[i-1][j]+dp[i][j-1];
//     }
// }
// 可以发现，不管前面和上面有没有，都可以使用dp[i][j] = dp[i-1][j]+dp[i][j-1]，因为阻碍的都是0
// 也可以状态压缩，麻烦一点，需要考虑第一行和第一列
// 第一行，遇到阻碍，后面的都是0
// 第一列的考虑比较多，因为本来就是dp[0]，一个参数：
// 1 obstacleGrid[i][0] == 1，自然为0
// 2 不是0，那么dp[i][0]=dp[i-1][0]，不需要变
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<int> dp(n, 0);
    dp[0] = 1;
    for (int j = 1; j < n; ++j) {
        if (obstacleGrid[0][j] != 1) {
            dp[j] = 1;
        } else break;
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[i][j] == 1) {
                dp[j] = 0;
            } else if (j != 0) {
                dp[j] += dp[j-1];
            }
        }
    }
    return dp[n-1];
}

// 198 medium 偷东西，相邻元素之间不能偷，问最大偷多少
// dp[i] 表示到第i个元素为止，偷的钱
// dp[i] = max(dp[i-1], dp[i-2]+nums[i])
// 可以压缩
int rob(vector<int>& nums) {
    if (nums.size() < 2) return nums[0];
    int dp1 = nums[0];  // dp[i-2]
    int dp2 = max(nums[0], nums[1]);  // dp[i-1]
    for (int i = 2; i < nums.size(); ++i) {
        dp1 = exchange(dp2, max(dp2, dp1+nums[i]));
    }
    return dp2;
}
// 213 medium 198变成环了
// 要么从0开始，默认末尾n-2，要么从1开始，默认末尾n-1
int rob(vector<int>& nums) {
    if (nums.size() < 2) return nums[0];
    int dp1 = nums[0];
    int dp2 = max(nums[0], nums[1]);
    if (nums.size() == 2) return dp2;
    for (int i = 2; i < nums.size()-1; ++i) {
        dp1 = exchange(dp2, max(dp2, dp1+nums[i]));
    }
    int res = dp2;
    dp1 = nums[1];
    dp2 = max(nums[1], nums[2]);
    for (int i = 3; i < nums.size(); ++i) {
        dp1 = exchange(dp2, max(dp2, dp1+nums[i]));
    }
    res = max(res, dp2);
    return res;
}
// 337 medium 变成树了，相邻节点不能偷 树形DP
// 后序遍历，统计每个节点偷和不偷的钱
int rob(TreeNode* root) {
    pair<int,int> res = robTree(root);
    return max(res.first, res.second);
}
pair<int,int> robTree(TreeNode* cur) {
    if (!cur) return {0,0};
    pair<int,int> lsum = robTree(cur->left);
    pair<int,int> rsum = robTree(cur->right);
    int doRob = cur->val + lsum.second + rsum.second;
    int notRob = max(lsum.first,lsum.second) + max(rsum.first,rsum.second);
    return {doRob, notRob};
}



