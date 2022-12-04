#include <myheader.h>

// 414 easy 找数组中第3大的（要求distinct），如果没有，返回最大的
// 根据distinct的要求用set来做，一直存储前三位最大的，set的insert操作和erase操作都是对数级的
// 因为这里要利用set存放是非严格上升的特性，不适合unordered_set
// 这样每次排除一个最小的，剩下三个最大的
// 至于优先队列，当然可以对原数组做一遍unique操作再放进放出，也行。
int thirdMax(vector<int>& nums) {
    set<int> top3;
    for (int n : nums)
        if (top3.insert(n).second && top3.size() > 3) top3.erase(top3.begin());
    return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
}

// 219 easy 一个数组，是否存在下标i,j 使i,j的绝对差最大为k时，存在nums[i]==nums[j]
// 核心思想：由于仅仅是判断是否存在，所以可以从头遍历，用一个数据结构去做判断
// 显然，用一个size为k的窗口，然后每次让新的元素与这个窗口中做匹配，查看是否有值重合
// 综上，这个窗口可以用set模拟
// 有220的medium进阶
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> s;
    for (decltype(nums.size()) i = 0; i != nums.size(); ++i) {
        auto it = s.insert(nums[i]);
        if (!it.second) return true;  // 大小为k的set插入失败，说明插入的这个与前面的有相同的值
        if (s.size() > k) s.erase(nums[i-k]);
    }
    return false;
}

// 220 medium 类似219，一个数组，是否存在下标i,j 使i,j的绝对查至多为k时，存在nums[i]和nums[j]的绝对差至多是t
// 可以这么理解，有个size为k的窗口，出现新的nums[i]时，计算出nums[i]与窗口中某个数的绝对差如果小于等于t，那么返回true
// 设存在这个数x，则|x-nums[i]| <= t 则 -t + nums[i] <= x <= t + nums[i]
// 由于这里需要进行查找，不能使用哈希版本的set
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<int64_t> s;  // -2^31 <= nums[i] <= 2^31 - 1 所以加减t后可能越界
    for (decltype(nums.size()) i = 0; i != nums.size(); ++i) {
        auto x = s.lower_bound(static_cast<int64_t>(nums[i]) - static_cast<int64_t>(t));
        if (x != s.end() && *x <= static_cast<int64_t>(t) + static_cast<int64_t>(nums[i])) return true;
        s.insert(nums[i]);
        if (s.size() > k) s.erase(nums[i-k]);
    }
    return false;
}


// 贝壳21/5/8 笔试4
// 二分+前缀和+set
// 一袋水果，给了每个水果的重量。
// K次查询，每次查询给出一个s，问是否满足所有水果的重量等于s；
// 每次查询独立。
// 若不满足条件，可以从以下两个策略选择：
// 1 把所有重量超过平均数的水果扔掉；
// 2 把所有重量小于等于平均数的水果扔掉；
// 问是否可以通过执行若干次策略使条件满足。
// 这道题的难点在于k的范围<=10^5;
// 水果的数量也是这个范围
// 所以问题的关键肯定是和k的范围有关，显然不能每次查询时再遍历一遍，必挂
// 所以用一个set去直接统计可以通过这2个策略的所有水果重量，所以这点想到了二分应该也会想到，所以归在set
// 每次用二分取一段范围，其和是可以使用策略得到的数，难点是判断这段范围如果全部相等就是无法得到的
void fruitPolling(vector<int> a, vector<int> polling) {
    int n = a.size();
    vector<ll> presum(n,0);
    unordered_set<ll> weightSet;
    weightSet.insert(0);
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        presum[i] += a[i];
        presum[i] += i>0 ? presum[i-1] : 0;
    }
    pair<int,int> range(0, n-1);
    queue<pair<int,int>> q;
	q.push(range);
    while (!q.empty()) {
        range = q.front();
		q.pop();
        int l = range.first, r = range.second;
        ll sum = l>0 ? presum[r]-presum[l-1] : presum[r];
        weightSet.insert(sum);
        int avg = sum/(r-l+1);
        if (a[l]==avg && a[r]==avg) continue;  // 两种情况被排除，1 l==r; 2 相等的序列
        int pos = upper_bound(a.begin()+l, a.begin()+r, avg) - a.begin();
        q.push(pair<int,int>(l,pos-1));
        q.push(pair<int,int>(pos,r));
    }
    for (int i = 0; i < polling.size(); ++i) {
        if (weightSet.count(polling[i])) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

