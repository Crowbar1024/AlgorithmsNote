#include <myheader.h>

// hard 一个由数组组成的环，如果数i和j之间有比两端小的数，可以视为i和j可以互相看见
// 相邻一定可以互相看见，求环上可以互相看见的对数
// 一个神奇的点：如果没有重复的数，环的长度为n，那么对数为2n-3
// 选择最高和次高两个点，其他任意一点，必然可以找到顺时针和逆时针恰好大于它的数，2(n-2)
// 然后此高和最高一定可以互相看见，1
// 然后是一般情况，根据上述的情况可以发现，其实是找每个元素左右恰好比它大的数的个数
// 使用单调栈
// 比如 5 2 2 2 3 4 1 2
// 单调栈的意思就是只能压入不大于栈顶的数，否则两者都要弹出
// 这里 5-2*3，压入3
// 那么2的右边恰好比他高的数是3，3个2之间两两互相看见，C(n)(2)，n是栈顶元素的个数
// 然后加上2n，因为每个2的左右恰好比其大的数是3和5
// 5-4-1，压入2，弹出 1 2
// 5-4，4的右边没有比他大的数，左边有恰好比他大的数（它下面），弹出，+1
// 5，5的右边没有，左边也没有
// 所以要选最大的数当栈底，不然万一一个小的数当栈底弹出了，不知道有没有左边比它大的数
// 还有一种情况：5*m-4*n-3k（都>1），弹出k个3，此时还剩5和4，说明3的左右有5和4，得+2k
// 5m-4n，弹出4，实际上4的两边都有5，+2n
int communications(vector<int> a) {
    if (a.empty() || a.size() < 2) return 0;
    int n = a.size();
    int maxIndex = 0;
    for (int i=1; i<n; ++i) {
        maxIndex = a[i]>a[maxIndex] ? i : maxIndex;
    }
    int maxValue = a[maxIndex];
    int index = (maxIndex+1)%n;
    stack<pair<int,int>> s;
    s.push({maxValue, 1});
    int res = 0;
    while (index != maxIndex) {
        int newValue = a[index];
        while (s.top().first < newValue) {  // 把小于新的数的全部弹出
            int times = s.top().second;
            s.pop();
            res += times*(times-1)/2 + times*2;
        }
        if (s.top().first == newValue) {
            s.top().second += 1;
        } else {
            s.push({newValue, 1});
        }
        index = (index+1)%n;
    }
    while (!s.empty()) {  // 此时是从大到小的单调栈
        int times = s.top().second;
        s.pop();
        res += times*(times-1)/2;  // 内部
        if (!s.empty()) {
            res += times;
            if (s.size() > 1) {
                res += times;
            } else {
                res += s.top().second>1 ? times : 0;
            }
        }
    }
    return res;
}
