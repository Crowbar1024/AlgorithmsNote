#include <myheader.h>


// 307的树状数组解法 给你一个数组 nums，请你完成两类查询。
// 其中一类查询要求更新 nums 下标对应的值
// 另一类查询要求返回 nums 中 [left, right] 的元素之和
// 举个例子，14个节点
//    1     2    3     4    5     6    7     8    9     10     11     12     13       14
// [1,1] [1,2]      [1,4]                 [1,8]
//            [3,3]      [5,5] [5,6]           [9,9] [9,10]        [9,12]
//                                  [7,7]                  [11,11]       [13,13] [13,14]
// 可见，每往下一层，就见缝插针，插的大小是2的幂，插不下就停止
// 这样比如要求[1,13]的求和
// 13 = 8 + 4 + 1
// [1,13] = [1,8] + [9,12] + [13,13]
// 反过来可以理解，先从节点13开始，再加上节点12，再加上节点8
// 即 1101->1100->1000
// 其实就是不断将当前数字的最后一个1翻转为0的过程
// 注意，树状数组也是下标从1开始，和线段树一样。所以查询要相应做调整。
// 查询和更新的时间复杂度和线段树一致，都是O(logn)
class NumArray {
private:
    vector<int> bia;  // binary index array
    vector<int> arr;  // original array 是必要的，因为更新只给了下标
    int n;

    // 获得x的最后一位1
    int lowbit(int x) { 
        return x & (-x);
    }

    // 单例更新，比如nums[5]+2
    // 更新的节点是index不断加上末尾1的节点，与查询正好相反，挺神奇的
    // 5 = 0101
    // 6 = 0110
    // 8 = 1000
    void addBIA(int index, int increment) {
        for (int i = index; i <= n; i += lowbit(i)) {
            bia[i] += increment;
        }
    }

    // [1,index]的总和
    int queryBIA(int index) {
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i)) res += bia[i];
        return res;
    }

public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        arr = nums;
        bia.resize(n+1);
        for (int i = 1; i <= n; ++i) {
            addBIA(i, nums[i-1]);
        }
    }

    // 下标从0开始
    void update(int index, int val) {
        int increment = val - arr[index];
        addBIA(index+1, increment);
        arr[index] = val;  // 别忘记原始数组要保留变化
    }

    // 下标从0开始
    int sumRange(int left, int right) {
        ++left; ++right;
        int res = queryBIA(right) - queryBIA(left-1);
        return res;
    }
};


// 315 hard 一个数组，计算每个元素的右边小于其的元素个数
// 离散化+二分
// nums 3 9 5 2 6 1 3 经过sort unique
// a    1 2 3 5 6 9   初始化count
// cnt  0 0 0 0 0 0   然后从尾巴开始遍历原始数组
// cnt  0 0 1 0 0 0   3的数量+1
// res  0 0 0 0 0 0 0 cnt中3的左边前缀和为0
// cnt  1 0 1 0 0 0   1的数量+1
// res  0 0 0 0 0 0 0 cnt中1的左边前缀和为0
// 右边和左边其实没有区别，每次更新cnt，其实就是更新nums右边的频率
// 可以发现，这道题成了一道动态维护前缀和的题目，cnt就是树状数组
// 然后每次从nums尾巴遍历时，需要找到其在cnt数组的下标
// 这个可以用辅助数组或者每次用二分查询
class Solution {
private:
    vector<int> cnt;  // count
    vector<int> arr;  // sort and unique the orignal nums
    int n;  // arr size

    int lowbit(int x) { 
        return x & (-x);
    }

    void discretization(vector<int>& nums) {
        arr = nums;
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
    }

    void Init(vector<int>& nums) {
        discretization(nums);
        n = arr.size();
        cnt.resize(n+1, 0);
    }

    void addBIA(int index, int increment) {
        for (int i = index; i <= n; i += lowbit(i)) {
            cnt[i] += increment;
        }
    }

    int queryBIA(int index) {
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i)) res += cnt[i];
        return res;
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
        Init(nums);
        vector<int> res(nums.size(), 0);
        for (int i = nums.size()-1; i >= 0; --i) {
            // 由于nums[i]一定存在arr中，所以查找下标用lower_bound就行了
            int index = lower_bound(arr.begin(), arr.end(), nums[i]) - arr.begin() + 1;  // 从1开始
            res[i] = queryBIA(index-1);  // index左边
            addBIA(index, 1);
        }
        return res;
    }
};
// 这道题是逆序对数目的进阶版


// 493 上面题目的进阶，和逆序对类似，只不过是统计自己比右边的数的2倍还大的个数
// 离散化+map/set
// 即a[i]>a[j]*2, i < j
// 只要把lower_bound那里改一下，因为统计的是前缀和
// 比如 1 0 1 0 0 0 来了个6
// 按照之前的思路，要加上[1,5]的前缀和，按照这里的题意，只需要统计[1,2]就行了
// 即找到最后一个小于等于2的数，但这个数不一定存在arr中
// 这题使用另一种离散化方法，即用map存
class Solution {
private:
    vector<int> cnt;
    set<int> s;
    int n;  // set size
    map<int,int> m;

    int lowbit(int x) { 
        return x & (-x);
    }

    // nums 1 4 9 4 1
    // set  1 4 9
    // map  1-1 4-2 9-3
    // 这样用map[nums[i]]就能得到其树状数组中的下标
    void discretization(vector<int>& nums) {
        s.insert(nums.begin(), nums.end());
        int i = 0;  
        for (int num : s) {
            m[num] = ++i;
        }
    }

    void Init(vector<int>& nums) {
        discretization(nums);
        n = s.size();
        cnt.resize(n+1, 0);
    }

    void addBIA(int index, int increment) {
        for (int i = index; i <= n; i += lowbit(i)) {
            cnt[i] += increment;
        }
    }

    int queryBIA(int index) {
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i)) res += cnt[i];
        return res;
    }


public:
    int reversePairs(vector<int>& nums) {
        Init(nums);
        int res = 0;
        for (int i = nums.size()-1; i >= 0; --i) {
            int index = m[nums[i]];
            // 1 9 4 9 1
            // 9的tmp为5
            // 大于等于5是9，退一个是4
            // 5 5
            // tmp为3，大于等于3是5，是头，不能加
            // -5 -3
            // -5tmp为-2，大于等于-2是-5，退一个是-3
            // 所以，正数和负数的一半再退一个得分开讨论
            // 尽量使用lower，不要用upper
            int tmp = ((long long)nums[i] + 1) / 2;
            if (nums[i] < 0) {
                tmp = nums[i] / 2;
            }
            auto it = s.lower_bound(tmp);
            if (it != s.begin()) {
                it--;
                res += queryBIA(m[*it]);
            }
            addBIA(index, 1);
        }
        return res;
    }
};

// 295 hard 两种操作，一个往数组中添加元素，一个求数组的中位数
// 元素大小限制[-10^5,10^5]，保证求中位数时数组中有元素，大概5*10^4次操作
// 离散化
// 中位数，也可以理解找到第mid小的数
// 如果离散化，每个元素的值作为下标，值就是其个数，那么query操作就能找到前k小的数
// 树状数组大小 n 为2*10^5，更新和求和都是 logn ，经过 5*10^4 不会超时
class MedianFinder {
private:
    vector<int> cnt;  // BIA
    const int maxn = 2e5+10;
    int n;

    int lowbit(int x) { 
        return x & (-x);
    }

    void addBIA(int index, int increment) {
        for (int i = index; i <= maxn; i += lowbit(i)) {
            cnt[i] += increment;
        }
    }

    int queryBIA(int index) {
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i)) res += cnt[i];
        return res;
    }

    int getKthMinNum(int k) {
        // 左闭右开
        int l = 1, r = maxn;
        // 由于原始数组会很稀疏
        // 1000001110000(mid)0000100
        // 如果queryBIA(mid)处就是k，但最后要给一个值，显然还要往前推，所以要让开的有边界取mid
        while (l < r) {
            int mid = l + (r-l)/2;
            int tmp = queryBIA(mid);
            if (tmp < k) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }

public:
    MedianFinder() {
        n = 0;
        cnt.resize(maxn, 0);
    }
    
    // -100000+100001=1
    void addNum(int num) {
        num += 100001;
        addBIA(num, 1);
        n++;
    }
    
    // 假设 n 是奇数，要找到第 (n+1)/ 2 小的数
    // 假设 n 是偶数，要找到第 n/2 和 (n/2)+1 小的数
    // 综上，找到第 (n+1)/2 小的数，然后判断奇偶
    double findMedian() {
        int res1 = getKthMinNum((n+1)/2)-100001;
        if (n&1) return res1;
        int res2 = getKthMinNum((n+1)/2+1)-100001;
        return (res1+res2)*0.5;  // 注意转换，/2就错了
    }
};



// SCU校赛 求n个正整数组成的序列中，严格上升子序列的个数
// 比如 1 4 1000 1000 1001 中 
// 每个元素算一个 5；两个一组 4+3+2 = 9；三个一组 3+2+2 = 7；四个一组 2；一共23
// 因为结果过大，对MOD=1e9+7取模
// 第一步没得说，排序+离散化
// 1 4 1000 1001
// 用BIA去存放严格上升子序列的个数，因为这符合结合律（加法的和也是）
// query(pos)就是求前pos个dv的数组成的序列中的严格上升子序列的个数
// 假设遍历到了第2个1000，找到1000在dv中的位置是第3个
// m=queryBIA(3-1)是找到以前2个数组成的序列中的严格上升子序列的个数，有 1 4，4这么2个
// 那么每次往树状数组中添加一个数，那么以1000结尾的序列个数有m+1个（1 4 1000, 4 1000, 1000）
// 所以要在第 3 位上加上 m+1
// 想一想，离散化计数前缀和，每次都是add(newN, 1)，即出现次数+1
// 基础的add(pos, inc)，即这个位置上的数本身加变量inc
// 那么根据用BIA去存放严格上升子序列的个数，也要加上增加的严格上升子序列的个数
// 这道题和求右边大于自己的数很像，因为遍历的顺序，让dv对应的树状数组每次的更新都有效
class StrictlyIncreasingSubsequence {
private:
    vector<int> cnt;  // BIA
    vector<int> dv;  // vector nums after discretization
    int n;
    const int MOD=1e9+7;

    void discretization(vector<int>& nums) {
        dv = nums;
        sort(dv.begin(), dv.end());
        dv.erase(unique(dv.begin(), dv.end()), dv.end());
        n = dv.size();
        cnt.resize(n+1, 0);
    }

    int lowbit(int x) { 
        return x & (-x);
    }

    void addBIA(int index, int increment) {
        for (int i = index; i <= n; i += lowbit(i)) {
            cnt[i] = (cnt[i]+increment)%MOD;
        }
    }

    int queryBIA(int index) {
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i)) res = (res+cnt[i])%MOD;
        return res;
    }
public:
    int getNumber(vector<int>& nums) {
        discretization(nums);
        for (int num : nums) {
			int pos = lower_bound(dv.begin(), dv.end(), num) - dv.begin() + 1;
			addBIA(pos, queryBIA(pos-1)+1);
		}
		return queryBIA(n);
    }
};
// 这道题有多种变体，现在要求返回的结果长度至少为2，且不能重复
// 只要做简单的改进
// 比如上一道题有2个1000，当遍历到了第2个1000时
// 首先得到前面2个数组成的严格上升子序列个数m，m+1就是加上1000后新的个数
// 然后不能add这个数了，因为前面有了1000，所以需要减掉前面增加的个数，操作如下
// addBIA(pos, m+1-last[pos]);
// last[pos] = m+1;
// 这样保证多个1000只在第一个1000有效
// 注意不能用if省略，因为当前循环内的m+1不一定等于last[pos]
// 最后query[n]-n保证只出现长度大于1的