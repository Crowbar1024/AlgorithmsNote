#include <myheader.h>


// easy 350 找到两个数组中所有重合的数字，结果可以重复。用map去统计。
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> m;
    for (auto n : nums1) m[n]++;
    vector<int> res;
    for (auto n : nums2) {
        if (m.count(n) && m[n] > 0) {
            m[n]--;
            res.push_back(n);
        }
    }
    return res;
}
// easy 349 如果结果要求不重复即unique，就用set统计

// 1346 easy 查看数组是否存在2倍关系的数，时间要求On
// 正常思路是存进set找，但两个0也算，所以得用map
bool checkIfExist(vector<int>& arr) {
    unordered_map<int, int> s;
    for (int n : arr) s[n]++;
    for (int n : arr)  {
        if (n && s.find(n*2) != s.end()) return true;
        else if (!n && s[0] > 1) return true;
    }
    return false;
}

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
        int64_t numsi_64 = static_cast<int64_t>(nums[i]);
        int64_t t_64 = static_cast<int64_t>(t);
        auto x = s.lower_bound(numsi_64 - t_64);
        if (x != s.end() && *x <= t_64 + numsi_64) return true;
        s.insert(nums[i]);
        if (s.size() > k) s.erase(nums[i-k]);
    }
    return false;
}


// 560 nums不是有序且有负数，求所有的字串之和为k的连续子串的个数
// 找字串和，一般都和前缀和有关，假设[i,j]为符合题意的子串，则 preSum[i]-preSum[j-1]=k
// 所以第一种方法就是前缀和+暴力搜索i和j O(n^2)
// 可以发现，preSum[i]-k=preSum[j-1]，可以利用空间换时间的思路
// 如果用一个map<preSum[i], times>去记录每个前缀和出现的次数，
// 对于每一个preSum[i]，如果前面有多个符合题意的preSum[j-1]，cnt就可以加上这个数量
// 所以只需要一次遍历
// 前缀和+哈希表
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;  // 前缀和为0的次数只有一次，就是preSum的下标为0时
    int preSum = 0, res = 0;
    for (int& num : nums) {
        preSum += num;
        if (mp.find(preSum-k) != mp.end()) {
            res += mp[preSum-k];
        }
        mp[preSum] += 1;
    }
    return res;
}


// 49 medium strs中包含若干个字符串，其中某些的字母种类和对应的个数相同，一组称为anagram，将其组起来
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
// 哈希表，核心是如何识别每组的字母，显然需要一个键值
// 1 一个最简单的思路就是map<string, vector<string>>，键值就是排好序的string
// 2 用26个字母对应的个数组成的数组，但这样键值就是一个数组，C++对于这种情况需要写一个对于数组的哈希函数，过于复杂
// 3 使用质数去设计键值，26个字母对应的质数，每个单次的字母的质数的一定不会重复，但有可能会溢出，取模有概率会碰撞
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> m;
    vector<vector<string>> res;
    for (string& str : strs) {
        string key = str;
        sort(key.begin(), key.end());
        m[key].emplace_back(str);
    }
    for (auto it = m.begin(); it != m.end(); ++it) {
        res.emplace_back(it->second);
    }
    return res;
}

// 438 medium s中包括p的anagram，返回起始下标
// s = "cbaebabacd", p = "abc"  ----> [0,6]
// 我一开始的思路就是遍历匹配，显然每次都要排序，不够简单
// 然后发现可以利用滑动窗口
vector<int> findAnagrams(string s, string p) {
    int l = 0, r = 0, len = p.size();
    unordered_map<char,int> pm;
    for (char ch = 'a'; ch <= 'z'; ++ch) pm[ch] = 0;
    for (char ch : p) pm[ch] += 1;
    unordered_map<char,int> wd;
    vector<int> res;
    while (r < s.size()) {
        wd[s[r]] += 1;
        // 只要wd多了，就可以l前移
        while (wd[s[r]] > pm[s[r]]) {
            wd[s[l]] -= 1;
            ++l;
        }
        if (r-l+1 == len) {
            res.emplace_back(l);
        }
        ++r;
    }
    return res;
}