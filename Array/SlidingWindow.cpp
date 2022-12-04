#include <myheader.h>


// 我认为滑动窗口一般分为多类
// 场景A 左右向中间靠拢，这种一般是有序数组
// 场景B 左右同时从头开始，一般非有序
// 当数组中存在负数时，滑动窗口就失灵了，因为窗口边框前进和后退不知道和究竟是变大还是变小


// 一串数，问有多少三元组可以组成三角形
// 技巧是，排序后，如果[l,r]满足条件，那么[l,r-1]的最短边都满足
int triangleCount(vector<int> nums) {
	int cnt = 0;
	sort(nums.begin(), nums.end());
	// i为最大边，l为最小边，r为中间边
	// 固定i，找[l,r]的组合
	for (int i=nums.size()-1; i>1; --i) {
		int l = 0, r = i-1;
		while (l < r) {
			if (nums[l]+nums[r] > nums[i]) {
				cnt += r-l;  // 三条边：[l:r-1], r, i
				r--;
			} else {
				l++;
			}
		}
	}
	return cnt;
}

// 209 medium nums全为正，找到最短的连续子串的和满足恰好大于等于target
int minSubArrayLen(int target, vector<int>& nums) {
    int l = 0, r = 0, len = INT_MAX, sum = 0;
    while (l <= r && r < nums.size()) {
        sum += nums[r];
        while (sum >= target) {
            len = min(len, r-l+1);
            sum -= nums[l++];
        }
        ++r;
    }
    return len==INT_MAX ? 0 : len;
}
// 这道题还有O(nlogn)的做法，也是我第一次想到的，算是二分法
// 用一个sum数组统计以i结尾的和，每次找sum[i]-target的最大的j
// 可以发现，这种找和的可以使用滑动窗口的前提是数组全为正，如果有负，建议使用以i结尾这种DP


// nums全为正，找到最长的连续子串的和满足恰好等于target
// 因为全为正，[l,r]初始化0，然后让r一直往右滑直到恰好大于等于target
// 因为全为正，现在要缩小，窗口的和，只能让l向前滑直到恰好小于等于target



// NC28 hard 给出两个字符串 s 和 t，要求在 s 中找出最短的包含 t 中所有字符的连续子串。（注意包含的顺序没要求）
// 数据范围：两者长度<10000，保证s和t字符串中仅包含大小写英文字母
// 要求：空间复杂度 O(n) 时间复杂度 O(n)
// 如果 s 中没有包含 t 中所有字符的子串，返回空字符串
// 满足条件的子串可能有很多，但是题目保证满足条件的最短的子串唯一。
// 根据复杂度的要求就可以排除set和map的可行性，自然就想到滑动窗口
// 由于不要求包含T的顺序，所以需要一个cnt数组去记录T所有元素的个数
// 当窗口中包含所有T元素时，对应的元素的cnt值可能小于0
string minWindow(string S, string T) {
    // A-65 a-97
    vector<int> cnt(128, 0);
    // cnt记录T中每个字符的数量
    for (auto ch : T) cnt[ch-'A'] += 1;
    // restNumT表示 T 中还未被 [l,r) 包含的元素个数
    int l = 0, r = 0, restNumT = T.size();
    int len = INT_MAX, head = 0;
    while (r < S.size()) {
        // 当前r属于T，而且份额还没用完，直接用（左闭右开）
        if (cnt[S[r]-'A'] > 0) {
            restNumT -= 1;
        }
        cnt[S[r]-'A'] -= 1;
        r += 1;
        // 表示以及全部包含全部了，开始移动l
        while (restNumT == 0) {
            if (r-l < len) {
                len = r-l;
                head = l;
            }
            // 前面的r已经走了很长的距离，导致T的所有元素都被[l,r)包括了
            // 所以自然cnt数组内所有属于T的元素的数量都小于等于0（r的移动可能接受超过T数量的元素被包含进来）
            // 所以没有出现在T中的肯定是负数
            // 如果是0，说明此时对应的字符已经到了恰好可以包含T的窗口的左边界，所以终止while循环，去更新右边界
            if (cnt[S[l]-'A'] == 0) {
                restNumT += 1;  // 接下来要向右移动l，所以会增加
            }
            cnt[S[l]-'A'] += 1;  // 接下来要向右移动l，所以l对应的会增加
            l += 1;
        }
    }
    return len == INT_MAX ? "" : S.substr(head, len);
}

// 904 medium 场景B
// 正数串 [3,3,3,1,2,1,1,2,3,3,4] ，求只包含两种数字的最长连续子串的长度，这里是len[1,2,1,1,2] = 5
// [l,r]是符合题意的子串，肯定每次都是r向右扩张，当[l,r]中数字种类恰好超过2时，让l前进到恰好又满足2的位置
// 所以需要借助哈希表统计每种数的个数
int totalFruit(vector<int>& fruits) {
    unordered_map<int,int> cnt;
    int l = 0, r = 0, len = fruits.size();
    int res = 0;
    while (r < len) {
        // 可以直接放，因为map可以统计size
        cnt[fruits[r]] += 1;
        while (cnt.size() > 2) {
            cnt[fruits[l]] -= 1;
            if (cnt[fruits[l]] == 0) {
                cnt.erase(fruits[l]);
            }
            ++l;
        }
        res = max(res, r-l+1);
        ++r;
    }
    return res;
}

// 76 hard 
// 字符串s、字符串t。返回s中涵盖t所有字符的最小子串。如果s中不存在涵盖t所有字符的子串，则返回空字符串 
// s = "ADOBECODEBANC", t = "ABC" 输出 "BANC"
// 和904类似，但最大滑窗是在迭代右移右边界的过程中更新结果（904是左边界向右走完后才更新），
// 而最小滑窗是在迭代右移左边界的过程中更新结果
string minWindow(string s, string t) {
    unordered_map<char,int> cnt;
    for (char ch : t) {
        cnt[ch] += 1;
    }
    int tsum = t.size();
    int l = 0, r = 0, len = s.size();
    int res = len+1;  // len显然是错的
    string strRes = "";
    while (r < len) {
        if (cnt.count(s[r]) > 0) {
            // 只有该元素少才能变tsum
            if (cnt[s[r]] > 0) {
                tsum -= 1;
            }
            cnt[s[r]] -= 1;  // 该值是可能为负的
        }
        while (tsum == 0) {
            if (res >= r-l+1) {
                res = r-l+1;
                strRes = s.substr(l, res);
            }
            if (cnt.count(s[l])) {
                if (cnt[s[l]] == 0) {
                    tsum += 1;
                }
                cnt[s[l]] += 1;
            }
            ++l;
        }
        ++r;
    }
    return strRes;
}

// 1004 medium 一串01序列，k为最大翻转数，问通过最多k次翻转，最长的1子串长度为多少
// 根据904和76，这就是求一串01子串中，0有k个，这个子串的最长长度
int longestOnes(vector<int>& nums, int k) {
    int l = 0, r = 0, res = 0, len = nums.size();
    int cnt = 0;  // [l,r]中0的个数
    while (r < len) {
        if (nums[r] == 0) {
            cnt += 1;
        }
        // 这个循环条件需要小心，只有>k时才需要调整l
        while (cnt > k) {
            if (nums[l] == 0) {
                cnt -= 1;
            }
            ++l;
        }
        res = max(res, r-l+1);
        ++r;
    }
    return res;
}


// 3 medium 返回s没有重复字符的最长连续字串 "pwwkew"->"wke" 3
// 这道题有个点需要注意，就是开始不能直接把r插进去
int lengthOfLongestSubstring(string s) {
    int l = 0, r = 0, len = s.size();
    int res = 0;
    unordered_set<char> us;
    while (r < len) {
        while (us.count(s[r]) > 0) {
            us.erase(s[l]);
            ++l;
        }
        res = max(res, r-l+1);
        us.insert(s[r]);
        ++r;
    }
    return res;
}
// 缺点：每次左指针右移一位，移除set的一个字符，还要好多次循环才能到达上一次出现s[r]的后一个位置
// 不如直接用map记下每个字符的索引，直接进行跳转
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> idx;
    int l = 0, r = 0, len = s.size();
    int res = 0;
    while (r < len) {
        if (idx.count(s[r]) > 0) {
            l = max(l, idx[s[r]]+1);
        }
        res = max(res, r-l+1);
        idx[s[r]] = r;
        ++r;
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
        // 只要wd多了，或者pm[s[r]]==0，就可以l前移
        // 第二种情况会让l==r
        // 并且为了应对pm[s[r]]==0，需要做map的初始化
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