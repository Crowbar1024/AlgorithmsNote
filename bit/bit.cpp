#include <myheader.h>


// medium 416 一堆数，是否可以将其分为两堆数，使和相同，01背包最先想到
// 因为每个元素<=100，数组大小<=200，最大的v是1e4，可以拿空间换时间。
// 用一个布尔数组统计所有序列的和，即bitset[i]代表序列和为i是否可以得到
bool canPartition(vector<int>& nums) {
    bitset<10001> bits(1);
    int sum = accumulate(nums.begin(), nums.end(), 0);
    for (int n : nums) bits |= bits << n;  // 特别NB的写法，生成nums前n个数的任意组合的和
    return !(sum & 1) && bits[sum >> 1];
}

// Bloom过滤器
// 数据结构是一个m长度的bit数组，可以用任意基本类型数组去定位每个位置
// 就是用k个哈希函数分别独立去处理一个字符串并%m，得到的k个位置置1
// n为要存的数据个数，p为预期的查询失败概率
// 要来一个数据，如果k个位置都为1，说明被定位到
// 只肯杀错三千，不会放过一个，所以错误情况是把一些正确的也定位到了黑名单中
// m = -(n*lnp)/(ln2*ln2)  向上取整
// k = ln2*m/n  向上取整
// p_true = (1-e^(-n*k/m))^k < p
// 如果是100亿的数据，存url，假设64字节的长度
// 若要100正确，内存空间要640GB去存
// 用Bloom过滤器，假设0.01%的失误率，m为2000亿bit，只要23GB的内存空间



// 287 medium 数组长度为n+1，是由[1,n]中的数组成（可以不用完），其中一个数字重复了多次，找到这个重复的数字
// 显然有位运算解法，具有最少的空间复杂度O1
// 因为这个数组的性质，1 2 3 3 4 5 (1 2 3 4 5)
// x^x = 0   0^x = x
// 最后得到的就是x
int findDuplicate(vector<int>& nums) {
    int res = 0, n = nums.size()-1;
    for (int i = 1; i <= n; ++i) res ^= i;
    for (int x : nums) res ^= x;
    return res;
}