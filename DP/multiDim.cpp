#include <myheader.h>


/*
    多维度，不是指状态压缩前的多维度，类似背包，而是另一个维度一般表示状态

*/


// 122 medium 股票价格，每天只能买/卖一支股票，计算最大利润
// 贪心法也很快，但考虑DP，得加入现在有没有持有股票这一维度
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i]);
    }
    return dp[n-1][0];  // 最后肯定不持有股票
}
// 可以压缩，不写了