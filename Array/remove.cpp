#include <myheader.h>

// 27 删除数组里面所有为val的数，并返回删除后的数组长度，要求空间复杂度O1，无所谓新数组里的顺序
// 这是一种边统计边更新的操作，比较少见，但很有效
int removeElement(vector<int>& nums, int val) {
    int len = nums.size(), cnt = 0;
    for (int i = 0; i < len; i++) {
        if (nums[i] == val) cnt++;
        else nums[i - cnt] = nums[i];
    }
    nums.resize(len - cnt);
    return len - cnt;
}

// 26 27变体 unique非降序序列，并返回最后的长度
int removeDuplicates(vector<int>& nums) {
    int len = nums.size(), cnt = 0;
    for (int i = 1; i < len; i++) {
        if (nums[i] == nums[i-1]) cnt++;
        else nums[i - cnt] = nums[i];
    }
    nums.resize(len - cnt);
    return len - cnt;
}

// 283 27变体 把数组中所有的0搬到后面，剩下元素的顺序不变
void moveZeroes(vector<int>& nums) {
    int len = nums.size(), cnt = 0;
    for (int i = 1; i < len; i++) {
        if (nums[i] == 0) cnt++;
        else nums[i - cnt] = nums[i];
    }
}

// 可以发现一个共同点，都是将所需要的元素提到原数组的前头来