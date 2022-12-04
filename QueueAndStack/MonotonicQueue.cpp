#include <myheader.h>

// hard 239 有一个大小为k的滑动窗口从数组nums的最左侧移动到数组的最右侧。
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。返回每次滑动窗口中的最大值。
// 我一开始想用一个pair去储存滑动窗口中的最大值，但显然如果这个数没了，又需要得到次大值。
// 所以需要一个有序的数据结构去存储滑动窗口的pair，第一个想到的是优先队列。O(nlogn)
// 这里使用单调队列。存的{i,nums[i]}和{j,nums[j]}要求i<j且nums[i]>nums[j]，所以存的是下标
// 所以新人会挤掉前面比它小的，排到大哥后面。这样只要查看大哥在不在就行。O(n)，更好。
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    for (int i = 0; i < k; ++i) {
        while (!dq.empty() && nums[i] >= nums[dq.back()]) {
            dq.pop_back();
        }
        dq.emplace_back(i);
    }
    vector<int> res{nums[dq.front()]};
    for (int i = k; i < nums.size(); ++i) {
        while (!dq.empty() && nums[i] >= nums[dq.back()]) {
            dq.pop_back();
        }
        dq.emplace_back(i);
        if (dq.front() <= i-k) {
            dq.pop_front();
        }
        res.emplace_back(nums[dq.front()]);
    }
    return res;
}