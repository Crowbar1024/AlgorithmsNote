#include <myheader.h>

// 455 easy g是孩子的胃口，s是饼干的尺寸，只有一块饼干大小大于孩子的胃口，这个孩子才会满足
// 求最多可以给几个孩子满足
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int res = 0;
    for (int i = 0, j = 0; i < g.size() && j < s.size(); ++i, ++j) {
        while (j < s.size() && s[j] < g[i]) ++j;
        if (j == s.size()) break;
        ++res;
    }
    return res;
}
// 优化，既然都排序了，可以发现res压根是没必要的，就是i
// 一个for循环里既然可以if，那就省去了while多写一次判断
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0;
    for (int j = 0; j < s.size(); ++j) {
        if (i < g.size() && s[j] >= g[i]) ++i;
    }
    return i;
}



// 376 medium 摆动序列（一大一小变化的序列，只有两个不同值的序列也算）
// 给定一个整数序列，返回作为摆动序列的最长子序列的长度。
// 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。
// 一眼DP，但似乎有点麻烦，发现有另外的思路，即每次只删除单调的点
// 即{1,2,3,4,5,2}中删除2,3,4；{1,2,2,4,2}中删除2,2
// 这意味着需要 curDiff 和 preDiff 异号，就可以保证了
// 所以为了避免{2,5} {5,2}这种只有两个点的情况，默认第一个点double，直接删除第一个点，保留第0个点
// 所以贪心实际上是找策略
int wiggleMaxLength(vector<int>& nums) {
    int curDiff = 0, preDiff = 0;  // 当前节点与前一个节点的差，和前一个差
    int res = 1;  // 第一个点默认是峰
    for (int i = 1; i < nums.size(); ++i) {
        curDiff = nums[i] - nums[i-1];
        if ((curDiff > 0 && preDiff <= 0) || (curDiff < 0 && preDiff >= 0)) {
            ++res;
            preDiff = curDiff;
        }
    }
    return res;
}


// 53 medium 著名的最大子数组和
// DP是最容易想到的，dp[i] = max(nums[i], dp[i-1]+nums[i])
// 但这里要考虑贪心策略，即一种方法不需要借助额外的数组，本质上就是dp的压缩
// 其实这也可以解读，dp就是以i作为结尾的数组的和，是动态变化的，res就是统计其中最大的
int maxSubArray(vector<int>& nums) {
    int dp = 0, res = INT_MIN;
    for (int i = 0; i < nums.size(); ++i) {
        dp = max(nums[i], dp+nums[i]);
        res = max(dp, res);
    }
    return res;
}

// 121 easy prices表示股票每天价格。选择某一天买，并选择在未来卖（一共一次），算你所能获取的最大利润。
// 如果你不能获取任何利润，返回0 
// 贪心很简单，一个统计最小，一个统计结果就行了
int maxProfit(vector<int>& prices) {
    int minprice = INT_MAX, res = 0;
    for (int i = 0; i < prices.size(); ++i) {
        minprice = min(minprice, prices[i]);
        res = max(res, prices[i]-minprice);
    }
    return res;
}
// 122 medium 股票价格，每天只能买/卖一支股票，计算最大利润
// 比作山峰，就是所有严格递增段的高度差
int maxProfit(vector<int>& prices) {
    int res = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i-1]) {
            res += prices[i] - prices[i-1];
        }
    }
    return res;
}

// 714 medium 122+手续费
// 依然需要严格递增的高度差，如果中间有相同值，不能买卖，这样浪费了手续费
// 贪心策略：每次能赚钱就买，然后更新左边界
int maxProfit(vector<int>& prices, int fee) {
    int res = 0;
    int l = prices[0];
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] > l+fee) {  // 可以买，但为了节省手续费，期望后面遇到更大的
            res += prices[i]-l-fee;  // 先买了
            l = prices[i]-fee;  // 遇到更大的，可以把手续费补上，一定会越来越大
        } else if (prices[i] >= l && prices[i] <= l+fee) {  // 不卖
            continue;
        } else {  // 直接更新最小值
            l = prices[i];
        }
    }
    return res;
}

// 45 medium 跳跃游戏 给你一个非负整数数组 nums，你最初位于数组的第一个位置。
// 数组中的每个元素代表你在该位置可以跳跃的最大长度。你的目标是使用最少的跳跃次数到达数组的最后一个位置。
// 假设你总是可以到达数组的最后一个位置。
// 策略：第一次就跳到可以跳到的最远距离，然后每次跳到当前节点最远的距离
// 然后每次记录每个数组位置最远的距离，如果某个位置已经到终点了，而这个位置一定是cur或者cur以前的节点
// 由于cur每次都是最远，所以当出现这种情况时，再跳一次的总步数就是结果。
int jump(vector<int>& nums) {
    int up = 0;  // 每个节点最远到达的距离
    int cur = 0;  // 跳到的位置
    int res = 0;
    for (int i = 0; i < nums.size()-1; i++) {
        up = max(up, i+nums[i]);
        if (up >= nums.size()-1) {
            return ++res;
        }
        if (cur == i) {
            cur = up;
            res++;
        }
    }
    return res;
}
// 55 medium 同45，判断你是否能够到达最后一个位置。
// 达不到只有一种情况，就是困在0处且最远也只能到这儿了。将上面的改一下，为：
// if (cur == i) {
//     if (nums[cur] == 0 && cur == up) return false;
//     cur = up;
// }
// 不过也可以不用这种思路，只要判断中途能不能到达最后一个节点就行，最后返回false，傻瓜版
// 显然傻瓜版如果false需要跑完一整段，时间效率低，但节省了2个常量。
bool canJump(vector<int>& nums) {
    int up = 0;
    for (int i = 0; i < nums.size()-1; ++i) {
        up = max(up, nums[i]+i);
        if (up >= nums.size()-1) return true;
    }
    return false;
}

// 1005 easy  给定一个整数数组，翻转若干个数 K 次（可以相同的数多次翻转）。返回数组可能的最大和。
// 先排序，分情况，若是k大于负数的个数，全部用于翻转最小的正数；否则直接用完
int largestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end(), [](const int &x, const int &y) {
        return abs(x) > abs(y);
    });
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (k > 0 && nums[i] < 0) {
            res += -nums[i];
            --k;
        } else res += nums[i];
    }
    if (k & 1) res -= 2*abs(nums.back());
    return res;
}


// 134 medium 加油站问题，环形的加油站每个站可以加的油是gas[i]，走到下一站消耗是cost[i]
// 问题保证只有一个站点可以走完整条环形道路，问是哪个节点
// 这道题简化后，发现gas-cost这个数组，有正有负，找到一个索引，不断累加，过程中不能出现负数
// 如果必有解的话，这个解肯定出现在sum为负数的下一个
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	int sum = 0, n = gas.size();
	for (int i = 0; i < n; ++i) {
		sum += gas[i] - cost[i];
	}
	if (sum < 0) return -1;
	int start = 0;
	sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += gas[i] - cost[i];
		if (sum < 0) {
			sum = 0;
			start = i + 1;
		}
	}
	return start == n ? 0: start;
}


// 860 easy 每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，一次购买一杯，然后向你付 5 美元、10 美元或 20 美元。
// 你必须给每个顾客正确找零，注意，一开始你手头没有任何零钱。
// 判断能否给每位顾客正确找零
bool lemonadeChange(vector<int>& bills) {
    int d5 = 0, d10 = 0;  // 不需要统计20块的，因为找不出去
    for (int bill : bills) {
        if (bill == 5) d5++;
        else if (bill == 10) {
            if (d5) d5--, d10++;
            else return false;
        } else {
            if (d10 && d5) d10--, d5--;
            else if (d10 && !d5) return false;
            else if (!d10 && d5 >= 3) d5 -= 3;
            else return false;
        }
    }
    return true;
}


// 738 medium 给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增。
// 肯定是从后向前遍历，332->329->299，每次出现s[i-1]>s[i]，就让前者-1，后者变9
// 但如果是100，100->100->090，所以一旦出现了9，后面都是9，不能边-1边变9
int monotoneIncreasingDigits(int n) {
    string s = to_string(n);
    int pos;  // 9开始的位置
    for (int i = s.size()-1; i > 0; --i) {
        if (s[i-1] > s[i]) {
            s[i-1] -= 1;
            pos = i;
        }
    }
    for (int i = pos; i < s.size(); ++i) s[i] = '9';
    return stoi(s);
}