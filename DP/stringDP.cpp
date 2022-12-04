#include <myheader.h>




// 1143 两个字符串最长公共子序列（可以不连续）
// 经典的DP，定义dp[i][j]为text1前i个和text2前j个的最长公共子序列长度
// 注意不要定义成以i，j结尾的最长公共子序列长度，这样难以确定返回值，除非说了是连续的公共子串
// 初始化：dp[0][j]=0，dp[i][0]=0，最后返回dp[m][n]
// 显然当text1[i]==text2[j]时：dp[i][j] = dp[i-1][j-1] + 1
// 否则：dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// 根据状态转移方程，上边，左边，左上各一个，要求返回右下角
// 所以迭代顺序为：从上往下，从左往右
// 进行状态压缩，上边用上一个大循环dp[j]，左边用这次循环dp[j-1]
// 左上用一个临时变量prev存储
int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size(), n2 = text2.size();
    vector<int> dp(n2+1, 0);
    for (int i = 1; i <= n1; i++) {
        int prev = 0;  // dp[i-1][0] 第1列的左上
        dp[0] = 0;  // dp[i][0] 第1列左边
        for (int j = 1; j <= n2; j++) {
            int tmp = dp[j];  // 在下一次中会变成相对应的左上
            if (text1[i-1] == text2[j-1]) dp[j] = prev + 1;
            else dp[j] = max(dp[j], dp[j-1]);
            prev = tmp;  // 成了下面遍历的前一次遍历的左上
        }
    }
    return dp[n2];
}
// 上面一问的结果的路径
// 思路完全一样，按照上面的代码定义dp[i][j]为最长的相同子序列的string
string longestCommonSubsequencePath(string text1, string text2) {
    int n1 = text1.size(), n2 = text2.size();
    vector<string> dp(n2+1, "");
    for (int i = 1; i <= n1; i++) {
        string prev = "";
        dp[0] = "";
        for (int j = 1; j <= n2; j++) {
            string tmp = dp[j];
            if (text1[i-1] == text2[j-1]) dp[j] = prev + text1[i-1];
            else dp[j] = dp[j].size() > dp[j-1].size() ? dp[j] : dp[j-1];
            prev = tmp;
        }
    }
    return dp[n2];
}


// 字符串s由左括号和右括号组成，()(())这种就是正确的序列，求正确序列的最大长度
// 典型的用下标i结尾做DP的例子，假设dp[i]表示以i结尾的正确序列的长度
// ()(()())
// 01234567
// 02002048
// 当遍历到下标7时，如果为右括号，那么得找到那个与其匹配的左括号
// 找到之后，就是7前面的正确序列长度加上左括号左边的正确序列的长度
// 值得注意的就是下标的越界问题
int maxBracketLength(string s) {
    int n = s.size();
    vector<int> dp(n,0);
    int res = 0;
    for (int i=1; i<s.size(); ++i) {
        if (s[i] == ')') {
            int pre = i-1-dp[i-1];  // 找到那个与s[i]相匹配的左括号
            if (pre && s[pre] == '(') {
                dp[i] = dp[i-1] + 2 + (pre>0 ? dp[pre-1] : 0);
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}





// 72 hard 两个字符串之间通过最少多少次增删改可以相同
// 这道题的难点是想到用DP去做
// 想到之后，理所当然，dp[i][j]表示以i和j结尾的字符串通过的最少次增删改的次数
// 那么初始情况：dp[0][j]=j, dp[i][0]=i 最后返回dp[l1][l2]
// 如果word1[i]=word[j] 显然dp[i][j]=dp[i-1][j-1]
// 如果是不相等的情况，因为要最少，那么迭代的状态肯定是上一个再+1
// 上个状态有dp[i-1][j-1]和dp[i-1][j],dp[i][j-1]
// 前者很好考虑，让word1[i]变成word2[j]就可以了
// 但后者可以是把word1[i]删掉，再通过dp[i-1][j]。综上，只需要选择其中最小的一种就行了
int minDistance(string word1, string word2) {
    int l1 = word1.size(), l2 = word2.size();
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
    for (int i=0; i<=l1; i++) {
        dp[i][0] = i;
    }
    for (int j=0; j<=l2; j++) {
        dp[0][j] = j;
    }
    for (int i=1; i<=l1; i++) {
        for (int j=1; j<=l2; j++) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1])) + 1;
            }
        }
    }
    return dp[l1][l2];
}
// 上一道的题的压缩
// 根据转移方程式，当前的点是通过上面一个，左边一个，左上方一个得到
// 显然上面一个，用外循环的上一次得到的dp[j]，左边一个，用这次循环的上一个dp[j-1]
// 那么左上就需要一个临时变量去记录：
// 每次在j的循环里面保存一个dp[j]，这个dp[j]显然是上一行的dp[i-1][j]
// 在更新完这一行的dp[i][j]后，这个记录相对于下一次就变成了dp[i-1][j-1]
// 同时，每次需要重新更新dp[0]和重置左上的数dp[0][0]
int minDistance(string word1, string word2) {
    int l1 = word1.size(), l2 = word2.size();
    vector<int> dp(l2+1, 0);
    for (int j=1; j<=l2; j++) {
        dp[j] = j;
    }
    for (int i=1; i<=l1; i++) {
        int prev = dp[0];
        dp[0] = i;    // dp[0]是dp[i][0]
        for (int j=1; j<=l2; j++) {
            int tmp = dp[j];
            if (word1[i-1] == word2[j-1]) {
                dp[j] = prev;
            } else {
                dp[j] = min(prev, min(dp[j],dp[j-1])) + 1;
            }
            prev = tmp;
        }
    }
    return dp[l2];
}

// m*n的矩阵，从左上角走到右下角有多少种方法，只能向右向下
// 显然 dp[i][j]=dp[i-1][j]+dp[i][j-1]
// 初始化 dp[i][1]=dp[1][j]=1
// 左边+上边，得到右下角
// 遍历顺序选择：从上到下，从左到右
// 上边的压缩dp[j]，左边dp[j-1]
int uniquePaths(int m, int n) {
    vector<int> dp(n+1);
    dp[1] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <=n; ++j) {
            dp[j] = dp[j-1] + dp[j];
        }
    }
    return dp[n];
}
// 因为只能向右走或者向下走，所以从一共需要的步数中挑出n-1个向下走，剩下的m-1个就是向右走
// 其实就是从（m-1+n-1）里挑选（n-1）或者（m-1）个，是一个组合问题


// 10 hard 正则表达式 s是字符串，p是模式，查看是否匹配成功
// '.'可以匹配任意单个字符(不能为空字符)，'*'可以让前面的字符出现0或者任意次(所以不可能出现在第一个)
// 比如aa,a*aa返回true，ab,.*返回true
// 一看就要用DP来做，而且dp的对象显而易见，dp[i][j]定义为前i个和前j个是否匹配
// 结果返回dp[n1][n2]，初始化：dp[i][0]=false，dp[0][0]=true
// 当p[j-1]!='*': dp[i][j] = dp[i-1][j-1] && (s[i-1]==p[j-1] || p[j-1]=='.')
// 当p[j-1]=='*': 有两种情况，第1种让前面的字符不出现，第2种至少出现一次
// 则第一种情况:dp[i][j] = dp[i][j-2]
// 第二种情况：dp[i][j] = dp[i-1][j] && (s[i-1]==p[j-2] || p[j-2]=='.')
// 这里注意是dp[i-1][j]，因为x*已经定了，如果s[i-2]也是x，那么dp[i-1][j]也是true；如果s往前找x没有了，就会出现上面的第1种情况
// 考虑状态压缩，图全部，返回右上角，迭代顺序与左边，左上角，左边的左边得到
// 显然，左边和左边的左边由这次循环的dp[j-1]和dp[j-2]得到。
// 左上角由一个临时变量prev存储
// 综上，从上往下，从左往右迭代
bool isMatch(string s, string p) {
    int n1 = s.size(), n2 = p.size();
    vector<bool> dp(n2+1, false);
    for (int i = 0; i <= n1; i++) {
        bool prev = dp[0];
        dp[0] = (i == 0);  // dp[0][0] = true;
        for (int j = 1; j <= n2; j++) {
            bool tmp = dp[j];
            if (p[j-1] != '*')
                dp[j] = i && prev && (s[i-1] == p[j-1] || p[j-1] == '.');
            else
                dp[j] = dp[j-2] || (i && dp[j] && (s[i-1] == p[j-2] || p[j-2] == '.'));  // 根据定义p[0]!='*'
            prev = tmp;
        }
    }
    return dp[n2];
}

// 1092 hard 最短的公共Supersequence（子序列的反义词）
// 比如ab,bc的结果就是abc
// 这道题的思路就是利用LCS，最长公共子序列，不过这里要得到它，即需要知道DP的路径
string shortestCommonSupersequence(string &str1, string &str2) {
    string lcs = longestCommonSubsequence(str1, str2);
    string res = "";
    int i = 0, j = 0;
    for (auto c = lcs.begin(); c != lcs.end(); c++, i++, j++) {
        while (*c != str1[i]) res += str1[i++];
        while (*c != str2[j]) res += str2[j++];
        res += *c;
    }
    return res + str1.substr(i) + str2.substr(j);
}
string longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size(), n2 = text2.size();
    vector<string> dp(n2+1, "");
    for (int i = 1; i <= n1; i++) {
        string prev = "";
        dp[0] = "";
        for (int j = 1; j <= n2; j++) {
            string tmp = dp[j];
            if (text1[i-1] == text2[j-1]) dp[j] = prev + text1[i-1];
            else dp[j] = dp[j].size() > dp[j-1].size() ? dp[j] : dp[j-1];
            prev = tmp;
        }
    }
    return dp[n2];
}