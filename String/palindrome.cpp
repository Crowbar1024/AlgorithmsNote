#include <myheader.h>


// 647 计算回文子串的个数（我总结出了规律，串连续，序列可以不连续）
// 解决这道题可以用统计回文中心的方法去做，有多少个中心，就有多少个回文字串，那么这个方法就应该归在string里
// 那么这个方法的注意点就是要注意中心点可以是两个，所以遍历时需要遍历两个，一个s[i]，另一个s[i],s[i+1]
// 然后写个中心进行向外拓展的辅助统计函数就OK了，每拓展成功一次，子串个数++
int countSubstrings(string s) {
    int n = s.size(), cnt = 0;
    for (int i=0; i<n; i++) {
        cnt += extractPalindrome(s, i, i);
        cnt += extractPalindrome(s, i, i+1);
    }
    return cnt;
}
int extractPalindrome(string s, int left, int right) {
    int n = s.size();
    int cnt = 0;
    while (left>=0 && right<n && s[left]==s[right]) {
        left--;
        right++;
        cnt++;
    }
    return cnt;
}
// DP解法
// 如果用DP来做，我一开始想用dp[i][j]表示s[i...j]中的回文子串个数
// 如果这样想的话，如果s[i]==s[j]，dp[i][j]无法给出更新，因为这是不连续的字串，dp[i][j]无法与dp[i+1][j-1]建立关系
// 如果一定要用DP来做，dp[i][j]可以定义为s[i...j]是否为回文子串，这样状态转移就可以从dp[i+1][j-1]更新
// 这样可以统计dp[i][j]为true的个数，这样需要最终跑到右上角dp[0][n-1]
// 这样dp[i][j] = (s[i]==s[j]) && (j-i<3 || dp[i+1][j-1])
// 由左下方的一个得到，位于右上半部分，所以从下往上，从左到右迭代



// 516 最长回文子序列（可以不连续）
// 看到最长这名字，思考DP的可行性
// 定义dp[i][j]为s[i...j]包含的最长回文子序列长度，返回dp[0][n-1]
// 如果是最长回文子串的话，这种DP方法就是错的
// 初始化：dp[i][i]=1
// 显然当s[i]==s[j]时，dp[i][j] = dp[i+1][j-1]+2
// 否则：dp[i][j] = max(dp[i+1][j],dp[i][j-1])
// 画出状态转移图，返回右上角，由左下角，下边，左边各一个得到，所有情况在右上半部分
// 所以迭代顺序，从下往上，从左向右
// 状态压缩，下边由上一轮大循环的dp[j]，左边由这次循环的dp[j-1]
// 左下角由一个临时变量存储
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<int> dp(n, 1);
    for (int i=n-2; i>=0; i--) {
        int prev = 0;
        // dp[i] = 1;  // 可以省略，反正没有被更新
        for (int j = i+1; j < n; j++) {
            int tmp = dp[j];
            if (s[i] == s[j]) {
                dp[j] = prev + 2;
            } else {
                dp[j] = max(dp[j-1], dp[j]);
            }
            prev = tmp;
        }
    }
    return dp[n-1];
}
// 有道序号为5的最长回文子串，感觉应该分到array中，没啥技巧
// 基本都是遍历过去，每个节点向外检测，或者2个节点的向外检测




// 234 easy 判断一个链表是否是回文串
// 判断回文的递归解
// 用check把p递归到末尾，然后一层层往栈顶上走
// 本来是把第一个参数设置为外部的一个变量，但这样写更cool
// 因为递归调用了n次，所以空间复杂度是On
bool isPalindrome(ListNode* head) {
    return check(head, head);
}
bool check(ListNode*& head, ListNode* p) {
    if(!p) return true;
    bool isPal = check(head, p->next);
    if(!isPal || head->val != p->val) return false;
    head = head->next;  // 因为传进来的head是指针的引用，这是自上而下的更新
    return isPal;
}
// 非递归解法涉及到翻转，所以不贴在这里


// 最长回文子串，要求时间On
// 马拉车算法
// 核心思想
//  c a b b a b
// #c#a#b#b#a#b#  $是边界
// r为当前回文子串最右边的边界下标，s为对应的回文子串的中心，数组p记录新字符串每个下标的回文半径（不算自己）
// i是当前遍历的新字符串下标，利用i在[s,p]内回文的性质，通过i在s的对面镜像的回文直径来得到自己的p[i]
int manacher(string a) {
    string newA = "#";
	for (int i = 0; i < a.size(); i++) {
        // newA += a[i] + "#";  // 注意这种会产生乱码
        newA += a[i];
        newA += "#";
	}
    int r = 0, s = 0, n = newA.size();
	vector<int> p(n, 0);
	for (int i = 0; i < n; ++i) {
        int i_mirror = 2*s - i;
        // i_mirror ... s ... i ... r
        if (r > i) {
            p[i] = min(p[i_mirror], r-i);  // i+p[i]不能超过r
        } else {
            p[i] = 0;
        }
        // 中心扩展法，注意一定要有下标约束
		while (i-p[i]-1 >= 0 && newA[i+p[i]+1] == newA[i-p[i]-1]) {
            ++p[i];
        }
		// 更新s和r
		if (i + p[i] > r) {
			r = i + p[i];
			s = i;
		}
	}
    int maxL = 0, center = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] > maxL) {
            maxL = p[i];
            center = i;
        }
    }
    // return (maxL-center)/2;  // 返回最长回文子串的左边界下标
    return maxL;
}
