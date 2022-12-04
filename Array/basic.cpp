#include <myheader.h>


// 88 easy 合并两个有序数组，合并在第一个数组上面
// 给定的m并不是第一个数组的真实长度，所以不需要多创建空间
// 唯一的难点就在于是从末尾开始合并，由于nums1有多余的空间
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (!n) return;
    int i = m - 1, j = n - 1, k = n + m - 1;
    for ( ; i >= 0 && j >= 0; k--) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
    }
    if (i < 0) {
        for ( ; k >= 0; k--, j--) {
            nums1[k] = nums2[j];
        }
    }
}
// 可以思考什么情况下是从头开始合并的情况，链表是这样的


// 1299 easy 让数组每个数变成这个数的右边的所有数中最大的数，不包括自己
vector<int> replaceElements(vector<int>& arr) {
    int maxRight = -1;
    for (int i = arr.size() - 1; i >= 0; i--) {
        arr[i] = max(maxRight, exchange(arr[i], maxRight));
    }
    return arr;
}


// 字符串最小表示法
// 返回开头节点
// 双指针法，l和r分别指向可能为最小表示法的节点
// k表示相等substring的长度
// 6223724[2]23
int MinimumRepresentation(string s) {
    int i = 0, j = 1, k = 0, len = s.size();
    while (i < len && j < len && k < len) {
        int d = s[(i+k)%len] - s[(j+k)%len];
        if (d == 0) k++;
        else {
            if (d < 0) j += k+1;  // 因为此时[j+1,j+k]都不可能成为最小表示法的头
            else i += k+1;
            k = 0;
            if (i == j) ++j;
        }
    }
    return min(i, j);
}



// PAT 1045 Favorite Color Stripe 
// 给出颜色总数n，一组数a，一组数b，a是喜欢的颜色序列，b是一块布的颜色序列
// 颜色序列为[1:n]，a的长度小于200，b的长度小于10000
// 现在需要剪裁b，让剪裁后再拼起来的布的颜色序列满足a，可以缺少部分颜色，也可以重复相同的颜色，返回最长的长度
// 比如a是 5 2 3 1   b是 4 5 5 3 1 1 5   最长的长度就是 5 5 3 1 1 的长度5
// 这道题的其实隐含了一个条件，就是a是unique的，大大简化了题目难度
// 只需要记录a每个颜色出现的位置，然后记录b中出现在a的所有元素，然后统计最长的非严格递增序列的长度就行
// 注意用upper_bound


// 554 medium 一张海报，每行填充了不同长度的线条，从上到下划一刀，最少可以经过几条线条
// 最少经过几条线条，可以理解为最多经过几个线条间的裂缝
// 设置一个hashmap：edge，edge[i]储存了从第一行到最后一行，列为edge[i]的这个位置的裂缝数
// 所以需要从头遍历到尾，只有经过裂缝时才更新，得到edge
// 而这个问题的答案肯定也经过裂缝，所以可以在更新时得到解
int leastBricks(vector<vector<int>>& wall) {
    int rowNum = wall.size();
    int width = accumulate(wall[0].begin(), wall[0].end(), 0);
    if (width == 1) return rowNum;
    unordered_map<int, int> edge;
    int res = rowNum;
    for (auto row : wall) {
        for (int i = 0, curWid = 0; i < row.size()-1; ++i) {  // 注意裂缝数为线条数-1
            curWid += row[i];
            ++edge[curWid];
            res = min(res, rowNum - edge[curWid]);
        }
    }
    return res;
}

// 无规律，找出右值-左值最大的情况，返回这个值
// 要求只遍历一遍
// 关键在于，4....2...7，类似这种，只要最小值更新后，后面的值的差一定比未更新前大
int maxProfit(vector<int>& prices) {
    int minN = prices[0], res = 0;
    for (int i = 1; i < prices.size(); ++i) {
        res = max(res, prices[i]-minN);
        if (prices[i] < minN) minN = prices[i];
    }
    return res;
}
