#include <myheader.h>

// easy 704 二分查找，找到了返回下标，试了下迭代器，和类型转换
// 使用迭代器的话需要注意区间是[l,r)
int search1(vector<int>& nums, int target) {
    auto l = nums.begin(), r = nums.end();
    auto mid = l + (r - l) / 2;
    while (l < r && *mid != target) {
        if (target < *mid) r = mid;
        else l = mid + 1;
        mid = l + (r - l) / 2;
    }
    if (mid == nums.end() || *mid != target) return -1;
    return static_cast<int>(mid - nums.begin());
}

// medium 34 非降序序列，找到target的第一个和最后一个
// 一开始想一次二分，发现很困难
vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res{-1, -1};
    auto itl = lower_bound(nums.begin(), nums.end(), target);
    auto itr = upper_bound(itl, nums.end(), target);
    if (nums.empty() || itl == nums.end() || itl == itr) return res;
    res[0] = itl - nums.begin();
    res[1] = itr - nums.begin() - 1;
    return res;
}

// 162 medium 用对数时间找到有序数组任意一个peak
// 核心思想是构建[l,r]的范围，这俩边界就大于外面的，然后不断缩小
int findPeakElement(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int midl = l + ((r - l) >> 1);
        int midr = midl + 1;
        if (nums[midl] < nums[midr]) l = midr;
        else r = midl;
    }
    return l;
}


// 33 medium 一个升序排列的数组，向前移动了一定距离（就是尾巴移到头），假定前部分为A，后部分为B，B部分全部比A小
// 元素唯一，用二分找最小值，那么这个值就是A,B两段的B头
// 注意点，开始要排除无前进的情况
// 核心思想：不断更新[l,r]的取值范围，可以通过mid和任意一边界进行对比来缩短范围
// 由于代码的缩小速度适中，一个mid,一个mid+1
// 所以考虑l<r，那么最后一次可能是[4,5]：
// 1：r=4，说明4有可能是真，此时l=4, r=4, 只能返回4（3是之前l=3+1迭代，说明3为假）
// 2：l=4+1=5，说明4为假，此时l=5，r=4，返回5
// 所以最后返回的是l
// 然后需要需要找到某个数，可以直接根据找到的B的头二分，也可以用下面的方法
int search(vector<int>& nums, int target) {
    int len = nums.size();
    int l = 0, r = len - 1;  // 按照一般情况，是左闭右开，但我设置的是与右边界对比，所以要左闭右闭
    int p;  // B的头
    if (nums[l] < nums[r]) p = 0;
    else {  // 利用153的代码
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (nums[mid] < nums[r]) r = mid;  // mid和r都在B，mid有可能是B的头
            else l = mid + 1;  // 1：mid在A，r在B，mid取不到 2：mid和r相同，此时l==r，这种情况不存在
        }
        p = l;
    }
    l = 0, r = len;  // 我比较习惯左闭右开
    while (l < r) {
        int mid = l + ((r - l) >> 1);
        int realMid = (mid + p) % len;  // 原来的mid对应的值就是nums[(i+p)&len]
        if (target < nums[realMid]) r = mid;
        else if (target > nums[realMid]) l = mid + 1;
        else return realMid;
    }
    return -1;
}

// 33 medium 同81的写法
// 思考，有多种情况：
// 1 nums[l]<=nums[mid]: l和mid只可能在同一侧(注意是<=，因为有可能l=mid)
// 所以这里要分target在mid左侧和右侧
// 注意的是，如果在左侧，必须加入target >= nums[l]的限制，因为不写有可能target出现在右侧
// 2 以上的else，那么l和mid只可能在不同侧，且nums[l]>nums[mid]
// 所以这里要分target在mid左侧和右侧
// 注意的是，如果在右侧，必须加入target <= nums[r]的限制，因为不写有可能target出现在左侧
// 同时注意写的时候判断左右的优先级，哪边好判断就先写哪边，显然2判断左边，3判断右边好做
// 最后判断条件终止的情况，由于最后是在while里面返回true，如果[4,5]找5，所以最后[5,5]还需要判断一次
// 综上是l<=r
int search3(vector<int>& nums, int target) {
    int len = nums.size();
    if (len == 0) return -1;
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (target == nums[mid]) return mid;
        if (nums[l] <= nums[mid]) {
            if (target >= nums[l] && target < nums[mid]) r = mid - 1;
            else l = mid + 1;
        } else {
            if (target > nums[mid] && target <= nums[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}

// 81 medium 同33 但可以重复
// 这道题本来想利用hard的154的思想，但154是求最小值，由于重复，返回的并不一定是B的头的位置
// 所以这道题得写比较复杂的条件判断
// 还是用一个[l,r]去维护一个包含target的范围
// 思考，有多种情况，从最极端的情况开始：
// 1 nums[l]==nums[mid]==nums[r]，那么直接常数的向内缩小
// 2 nums[l]<=nums[mid]: l和mid只可能在同一侧（如果不在同侧，只可能nums[l]==nums[mid]，但此时由于数组的性质，只可能出现1的情况）
// 所以这里要分target在mid左侧和右侧
// 注意的是，如果在左侧，必须加入target >= nums[l]的限制，因为不写有可能target出现在右侧
// 3 以上的else，那么l和mid只可能在不同侧，且nums[l]>nums[mid]
// 所以这里要分target在mid左侧和右侧
// 注意的是，如果在右侧，必须加入target <= nums[r]的限制，因为不写有可能target出现在左侧
// 同时注意写的时候判断左右的优先级，哪边好判断就先写哪边，显然2判断左边，3判断右边好做
// 最后判断条件终止的情况，由于最后是在while里面返回true，如果[4,5]找5，所以最后[5,5]还需要判断一次
// 综上是l<=r
bool search2(vector<int>& nums, int target) {
    int len = nums.size();
    if (len == 0) return false;
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (target == nums[mid]) return true;
        if (nums[l] == nums[mid] && nums[r] == nums[mid]) {
            l++;
            r--;
        } else if (nums[l] <= nums[mid]) {
            if (target >= nums[l] && target < nums[mid]) r = mid - 1;
            else l = mid + 1;
        } else {
            if (target > nums[mid] && target <= nums[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return false;
}