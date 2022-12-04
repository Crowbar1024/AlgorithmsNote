#include <myheader.h>


// 658 medium 升序，找到k个与x最接近的数字，如果距离相同，小的优先，返回这k个数字
// 我的做法：很笨的利用lower_bound，然后用while去做
// while的思路就是我当前窗口的左值如果距离比它自己右滑后窗口右值的距离大，才能右移
// 实际上我已经解决了最困难的一步，就是滑动窗口的移动判断
// 所以这个问题就转换成了找窗口的左值，直接用二分去搜索它就完了
// 至于边界问题，已经有一定经验了，根据缩减情况，肯定是l<r，返回l，不需要进一步分析
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int l = 0, r = arr.size() - k;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (x - arr[mid] > arr[mid + k] - x) l = mid + 1;
        else r = mid;
    }
    return vector<int>(arr.begin() + l, arr.begin() + l + k);
}



// 300 medium 最长严格上升非连续子序列的长度
// 有DP解法
// 核心：建立一个升序数组，每次把新的数放到大于等于这个数的位置上
// 为什么可以这样做需要证明
// 为了要求严格上升，要使用lower_bound
// 如果要找非降序的话，就用upper_bound
// 注意这种二分的解法是找不到路径的，DP可以找到路径，虽然这样时间复杂度就上去了
int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i != nums.size(); i++) {
        auto it = lower_bound(res.begin(), res.end(), nums[i]);
        if (it == res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}
// DP解法O(n^2)
// 以i结尾的最长上升非连续子序列 dp[i] = max(dp[j]+1,dp[i]) for all nums[j] < nums[i]


// 287 medium 数组长度为n+1，是由[1,n]中的数组成（可以不用完），其中一个数字重复了多次，找到这个重复的数字
// 由于不一定用到了所有的n，不能用求和的形式去做
// 这是一道经典数组题，而且给出了[1,n]这个取值范围，那么试试二分，用[l,r]不断缩小的方法去找目标
// 有了mid，可以数出所有小于等于m的数，显然如果数量比mid大，那么目标在[l,mid]
// 否则，目标显然在[mid+1,r]
// 根据这个缩放条件，利用经验自然是l<r && return l
// 时间复杂度nlogn
int findDuplicate(vector<int>& nums) {
    int l = 1, r = nums.size() - 1;    // [1,n]
    while (l < r) {
        int mid = l + (r - l) / 2, cnt = 0;
        for (int x : nums) cnt += x <= mid;
        if (cnt > mid) r = mid;
        else l = mid + 1;
    }
    return l;
}
// 还可以用离散数学去做，他的时间复杂度是On，简单来说就是利用链表去检查环的起点的思想，可见142







 
// 154 hard 数组形式同153，即前进升序数组，分A,B段，A的都比B大，但是元素可以重复。用二分找最小值，
// 核心思想：不断更新[l,r]的取值范围，可以通过mid和任意一边界进行对比来缩短范围，这里选择r，所nums[r]要取得到
// 注意找到的并不一定是B的头
int findMin(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    if (nums[l] < nums[r]) return nums[0];
    while (l < r) {
        int mid = l + ((r - l) >> 1);
        if (nums[mid] < nums[r]) r = mid;  // 这种情况和153不变，mid有可能是要找的值
        else if (nums[mid] > nums[r]) l = mid + 1;  // 这种情况和153要区分，153直接else，因为==情况在153不可能存在
        // 相等时有两种情况：
        // 1: 445('1'11)2 
        // 2: 3(3334'3'3)3
        // 即mid有可能出现在B的头的左边和右边，似乎难以倍速的缩放范围
        // 所以可以考虑常量级别的缩小[l,r]
        else r--;  // 同时，由于这个写法，最后返回的l并不一定是B的头
        // 因为如果是11131，第一次r--，就抛弃了B的头的情况
    }
    return nums[l];
}

// 4 hard 两者都是可能有重复的升序数组，找到两者拼在一起的中位数，要求时间复杂度Olog(n+m)
// 为了避免奇偶导致的各种边界问题，将数组各个数之间加入'#'（如果为空，就只有一个'#'）
// 这样总共有2(m+n)+2个数，总的个数是偶数
// 设置一个划线将两个数组给自一分为二，将划线定义为'#'，这样两边各有（m+n）个数（包括#）
// 根据中位数的性质，有：
// (i) # (2m-i) 括号是每段的长度，这样i的取值范围[0,2m]
// (j) # (2n-j)
// 根据中位数的性质：i+j = 2m+2n-i-j --> j = m+n-i 为了避免j是负数，由i的取值范围得n>=m
// 显然结果是要找到满足中位数性质（l1 <= r2 && l2 <= r1）的i，那么就要对扩容后的nums1进行[0,2m]的二分
// 所以真正的时间复杂度为Olog(2*min(m,n))
// 如果遍历到取nums1前c1个数时，那么此时划线的左边界为l1 = nums1[(c1-1)/2]
// 划线的右边界r1 = nums1[c1/2]。同理l2,r2
// 根据这个定义条件会有一点点问题，举个例子：#1#3#4#7#，取前奇数个，势必会不符合定义，似乎是违法的
// 但仔细想，如果取前5个数，这样左右边界都是4，相当于把4这个数复制了一份
// 经过检测，j会根据m+n的奇偶是偶奇，响应的左右数的个数还是相同的，所以这样做没有半点问题
// 同样，这里的缩放情况是+1 -1，与通常情况不同，所以要分析一下：
// 还是最普通的l<r，举个例子，最后一次[4,5]，无论变成[4,4]还是[5,5]都要计算出res，所以是l<=r
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    if (m > n) return findMedianSortedArrays(nums2, nums1);
    int lo = 0, hi = 2*m;
    double res;
    while (lo <= hi) {    // 因为返回的值关于lo,hi有进一步计算，所以要算=的情况
        int i = lo + (hi - lo) / 2;
        int j = m + n - i;
        int l1 = (i == 0) ? INT_MIN : nums1[(i-1)/2];
        int l2 = (j == 0) ? INT_MIN : nums2[(j-1)/2];
        int r1 = (i == 2*m) ? INT_MAX : nums1[i/2];
        int r2 = (j == 2*n) ? INT_MAX : nums2[j/2];
        if (l1 > r2) hi = i - 1;
        else if (l2 > r1) lo = i + 1;
        else {
            res = (min(r1, r2) + max(l1, l2)) / 2.0;
            break;
        }
    }
    return res;
}


// 887 hard K个蛋，N层楼，问测试多少次找到使鸡蛋恰好破的楼层
// 经典的鸡蛋问题，基本做法是用递归，思路就是自顶向下，这样会搜索所有的情况
// 引入二分的思想，定义dp[i][j]:测试i次，有j个蛋可以确定的最大楼层高度
// 如果鸡蛋破了，可以测试dp[i-1][j-1]，即dp[i-1][j-1]以下的楼层（包括）
// 没破，可以测试dp[i-1][j]，即dp[i-1][j]往上的楼层（不包括）
// 综上：dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + 1)
// 最后的dp[i][K]会等于N，返回最后的i
// 状态压缩，上边的直接用外循环的上一个dp[j]，左上的直接用外循环的上一个dp[j-1]
// 由于左上的选择，这里要反向遍历
// 这道题也包含二分的思想，时间复杂度O(KlogN)
// 所以这道题的核心就是让dp的计算结果当成是二分的对象，比较考智商的题目
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

// 410 hard 把非负的数组分成m个连续字串，选择“m个字串中最大的字串和”最小的情况，返回这个最大值
// 和719很像，已知字串和的取值范围，那么显然可以采用二分法，这里二分这个最大字串和的值
// 那么结果就是当二分到某个值，找出能恰好小于等于这个值的字串的个数是m时，那么这个值就是要找的
// splitArrayHelp: 查看当前被二分的最大和是否能满足条件
// 返回true，有2种情况：
// 1：恰好有m个连续子串的最大和都小于等于target，target有可能取大也有可能恰好
// 2：不到m个就已经取满了所有满足条件的连续子串，显然target取大了
// 返回false，说明target小了
// 根据缩放的经验，这里l<r return l
int splitArray(vector<int>& nums, int m) {
    int r = accumulate(nums.begin(), nums.end(), 0);
    int l = *max_element(nums.begin(), nums.end());
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (splitArrayHelp(mid, nums, m)) r = mid;
        else l = mid + 1;
    }
    return l;
}
bool splitArrayHelp(int target, vector<int>& nums, int m) {
    int cnt = 1, total = 0;    // BUG1: cnt要初始化为1
    for (int n : nums) {
        total += n;
        if (total > target) {
            total = n;
            cnt++;
        }
        if (cnt > m) return false;
    }
    return true;
}


// 354 hard
// 矩阵覆盖问题，不可以旋转
// 先排序后二分，复杂度O(nlogn)
// 需要注意的是排序要让第一维相同的，第二维从高到低，否则后面使用lowerbound会增加无效的矩形
// 下面是除了写lambda的另一种方法
static bool comp(vector<int>&a, vector<int>&b){
    return a[0]<b[0] || (a[0]==b[0] && a[1]>b[1]);
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(), [](const auto& x, const auto& y){ return x[0] < y[0] ||
        (x[0] == y[0] && x[1] > y[1]); });  // 注意写在sort里面时不需要捕获
    vector<int> d2;
    for (int i=0; i<envelopes.size(); ++i) {
        int y = envelopes[i][1];
        auto pos = lower_bound(d2.begin(), d2.end(), y);
        if (pos == d2.end()) {
            d2.emplace_back(y);
        } else {
            *pos = y;
        }
    }
    return d2.size();
}

