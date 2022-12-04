struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};






// easy NC19 最大子串和
// dp[i] = max{dp[i-1]+a[i],a[i]}
// 用一个元素压缩之
int FindGreatestSumOfSubArray(vector<int> array) {
    int dp = array[0], res = dp;
    for (int i = 1; i < array.size(); ++i) {
        dp = max(dp+array[i], array[i]);
        res = max(res, dp);
    }
    return res;
}



// SCU2018校赛初赛
// 给出一串数字。问有多少串连续子段的和能被整除
// 考虑子串和subSum[l][r]=sum[r]-sum[l-1]%K==0 <=> sum[r]%K==sum[l-1]%K
// 转换为找出所有(sum[]%K)中有多少对相等的pair
ll SubstringDividedByK(vector<int> a, int k) {
    unordered_map<int, int> m;
    ll cnt = 0;
    int sum = 0;
    for (int i=0; i<a.size(); ++i) {
        sum = (sum+a[i])%k;
        // 因为sum[0]=0（这里0是哨兵，不是a的第一个数），任何一个sum=0的前缀和都可以和sum[0]组队
        if (!sum) cnt++;
        m[sum]++;
    }
    for (auto it=m.begin(); it!=m.end(); ++it) {
        int t = it->second;
        cnt += t*(t-1)/2;  //组合数C(t)(2)
    }
    return cnt;
}

