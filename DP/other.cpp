#include <myheader.h>




// 877 一堆不同重量的石头，总重量是奇数，每次只能拿两侧的石头，我先挑，请问我的石头能否最重
// 如果石头堆数是偶数，我可以一直拿到奇数或者一直拿到偶数编号的石头。但奇偶拿到的石头数量不等，肯定赢
// 这道题的难点在于想到用DP。所以我觉得应该配得上hard
// 定义dp[i][j]为某人能从[i,...,j]石头堆里能拿到的超过他对手石头的最大重量，是个差值
// 如果我先拿，就是我超过我对手的最大重量；如果对手先拿，就是对手超过我的最大重量
// 返回值：dp[0][n-1]，因为我先拿，那么只要判断这个数是正就可以判断我赢
// 初始化，dp[i][i]=piles[i]
// 那么根据题意，状态转移方程如下所示：
// dp[i][j] = max(piles[i]-(dp[i+1][j], piles[j]-dp[i][j-1])
// 可以见由下边，左边各一个生成，并且上半部分，所以迭代顺序：从下往上，从左向右
// 所以进行状态压缩的话，下边的是上一轮的大循环的dp[j]，左边的是这一轮循环的dp[j-1]
// 由于压缩后，反正y=-x轴这条线都取不到，所以直接拿pile去初始化dp，这样还省去了对边界的每次更新重写（其实一般的题目也不会）
bool stoneGame(vector<int>& piles) {
    int n = piles.size();
    if (piles.size()&1 == 0) return true;
    vector<int> dp = piles;    // base case dp[i][i]=piles[i]
    for (int i=n-2; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            dp[j] = max(piles[i]-dp[j], piles[j]-dp[j-1]);
        }
    }
    return dp[n-1] > 0;
}
// 一样，现在返回优胜者的石头重量，下面是傻瓜版
int stoneGame(vector<int>& piles) {
    if (piles.empty()) return 0;
    int sum = accumulate(piles.begin(), piles.end(), 0);
    int firstTakePrice = firstTake(piles, 0, piles.size()-1);
    return max(firstTakePrice, sum-firstTakePrice);
}
int firstTake(vector<int>& piles, int i, int j) {
    if (i == j) return piles[i];
    return max(piles[i]+secondTake(piles,i+1,j), piles[j]+secondTake(piles,i,j-1));
}
int secondTake(vector<int>& piles, int i, int j) {
    if (i == j) return 0;  // 剩下的唯一一个被拿走了
    // 由于是后发，拿走谁取决于先发者，他拿完了，我就成了先发者
    // 由于双方都是理性个体，先发者肯定让后发者先发取最下的数
    return min(firstTake(piles,i+1,j), firstTake(piles,i,j-1));
}
// 将上述的方法化简，由于递归过程中会重复调用，使用两张二维表将firstTake和secondTake给存放
// 显然最后需要的是这两张表右上角的值，且对角线的值就是i==j的情况
// 由递归可见，每张表的每个节点都是由下方和左方的值递推而来
// 所以遍历的顺序就是从左往右，从下到上
int stoneGame(vector<int>& piles) {
    if (piles.empty()) return 0;
    int sum = accumulate(piles.begin(), piles.end(), 0);
    int firstTakePrice = firstTake(piles, 0, piles.size()-1);
    return max(firstTakePrice, sum-firstTakePrice);
}
// 对傻瓜版化简，只需要一个递归函数
int firstTake(vector<int>& piles, int i, int j) {
    if (i == j) return piles[i];
    else if (i+1 == j) return max(piles[i],piles[j]);
    // 一样的思路，下一次我先发的其实是上一次的后发，双方都是理性个体，所以第二次先发拿到的要取最小
    return max(piles[i] + min(firstTake(piles,i+2,j),firstTake(piles,i+1,j-1)),
            piles[j] + min(firstTake(piles,i,j-2),firstTake(piles,i+1,j-1)));
}
// 然后对其进行列表化，顺序是斜的，左上到右下（因为一个节点由左下三个点得到）



// 887 hard K个蛋，N层楼，问测试多少次找到使鸡蛋恰好破的楼层
// 经典的鸡蛋问题，基本做法是用递归，思路就是自顶向下，这样会搜索所有的情况
// 引入二分的思想，定义dp[i][j]:测试i次，有j个蛋可以确定的最大楼层高度
// 如果鸡蛋破了，可以测试dp[i-1][j-1]，即dp[i-1][j-1]以下的楼层（包括）。
// 没破，可以测试dp[i-1][j]，即dp[i-1][j]往上的楼层（不包括）
// 综上：dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + 1)
// 最后的dp[i][K]会等于N，返回最后的i
// 状态压缩，上边的直接用外循环的上一个dp[j]，左上的直接用外循环的上一个dp[j-1]
// 由于左上的选择，这里要反向遍历
// 这道题也包含二分的思想，时间复杂度O(KlogN)
// 所以这道题的核心就是让dp的计算结果当成是二分的对象，比较考智商的题目
// 解决它的一个思考突破口就是如果鸡蛋没破，这层楼及以上都可以看成是新的一栋楼
int superEggDrop(int K, int N) {
    vector<int> dp(K+1, 0);
    int i = 0;
    for (; dp[K] < N; i++) {
        for (int j = K; j > 0; j--) {
            dp[j] = dp[j] + dp[j-1] + 1;
        }
    }
    return i;
}



// 85 hard 01图中全是1组成的最大矩阵面积
// 这道题最大的难点在于想到用DP去处理
// 创新点是三个DP数组
// height[i][j]：第i行第j列若为1，往上的连续1的数量，就是以当前点的高度为高度的矩阵高度
// leftmost[i][j]，以height[i][j]为高度的矩阵的左边界
// rightmost[i][j]，以height[i][j]为高度的矩阵的右边界
// 这样以height[i][j]为高度的矩阵的面积 = (rightmost[i][j]-leftmost[i][j]+1)*height[i][j]
// 状态压缩，从上到下遍历，leftmost必须从左往右，rightmost必须从右往左
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int n = matrix.size(), m = matrix[0].size();
    vector<int> leftmost(m, 0);
    vector<int> rightmost(m, m-1);
    vector<int> height(m, 0);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int tmp = m-1;  // 记录第i行从右往左遍历时的每一个从0变过来的1的位置
        for (int j = m-1; j >= 0; --j) {
            if (matrix[i][j] == '1') {
                rightmost[j] = min(rightmost[j], tmp);  // 记录高度为weight[j]的矩形的右边
            } else {
                tmp = j-1;
                rightmost[j] = m-1;
            }
        }
        tmp = 0;
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == '1') {
                height[j] += 1;
                leftmost[j] = max(leftmost[j], tmp);
                res = max(res, (rightmost[j]-leftmost[j]+1)*height[j]);
            } else {
                height[j] = 0;
                tmp = j+1;
                leftmost[j] = 0;
            }
        }
    }
    return res;
}

// poj 1037
// n个木棒，长度为[1:n]，构成一高一低的栅栏（前两个既可以上升也可以下降），问按照字典序的第k个序列
// up[i][j]，长度为j的栅栏，头为i，且一开始是升序的长度
// down[i][j]，长度为j的栅栏，头为i，且一开始是降序的长度
// 根据定义有：down[i][j] = \sum_{k=1}^{k=i-1}up[k][j-1]
// 类似可以得到up[i][j]，但为了计算简单，可以发现，up[i][j]=down[j-i+1][j] 可以理解为Cni=Cn(n-i)，即对称
vector<int> DecorativeFence(int n, int k) {
    vector<vector<int>> up(n+1, vector<int>(n+1, 0));
    vector<vector<int>> down(n+1, vector<int>(n+1, 0));
	up[1][1] = down[1][1] = 1;
	for(int j=2; j<=n; ++j) {
		for(int i=1; i<=j; ++i) {
            // down[i][j] = \sum_{k=1}^{k=i-1}up[k][j-1]
            // 则 down[i][j]-down[i-1][j] = up[i-1][j-1]
			down[i][j] = down[i-1][j] + up[i-1][j-1];
		}
        for(int i=1; i<=j; ++i) {
			up[i][j] = down[j-i+1][j];
		}
	}
    vector<int> res;
    // 现在up[i][n],down[i][n]储存了所有的情况，k肯定是位于其中的一个区间，即通过不断减，k<=up/down[i][n]其中的某个数
    int flag, v = 0;
    vector<int> s(n);
	for(int i=1; i<=n; ++i) s[i]=i;  // 用来储存每个数
	for(int j=n; j>=0; --j) {
		if (j==n) {
			for (int i=1; i<=n; i++) {  
				if (k<=down[i][j]) {  // up[i][n]的字典序在down[i][n]之后
					v = i;  // k位于开头为v的降序情况组合中
                    flag=0;
                    break;
				}
				k -= down[i][j];
				if (k<=up[i][j]) {
					v = i;
                    flag = 1;
                    break;
				}
				k -= up[i][j];
			}
		} else {
			if (flag) {
				for (int i=v; i<=j; ++i) {
					if (k<=down[i][j]) {
						v=i;
                        break;
					}
					k -= down[i][j];
				}
			} else {
				for (int i=1; i<v; ++i) {
					if (k<=up[i][j]) {
						v = i;
                        break;
					}
					k -= up[i][j];
				}
			}
			flag ^= 1;
		}
		res.emplace_back(s[v]);
        // 因为我每次取的v其实只是剩下的一堆数的编号，比如剩下41，是在down[i][2]中取
		for(int i=v; i<j; ++i) s[i] = s[i+1];  // 删除s[v]
	}
}

  