#include <myheader.h>

// 96 medium 给定一个整数n，求以1 ... n为节点组成的二叉搜索树有多少种？
// 这种题目只能找找规律
// n=1 1
// n=2 2
// n=3 2+1+2
// 即当n=i时，选一个j当root，那么它的左子树的数量就是dp[j-1]，右子树的数量就是dp[i-j]
// 显然dp[0] = 1
int numTrees(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] += dp[j-1]*dp[i-j];
        }
    }
    return dp[n];
}

