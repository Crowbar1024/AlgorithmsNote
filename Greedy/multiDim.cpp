#include <myheader.h>


/*
    多维度思考
    1 数据有2个维度，需要自定义排序：452，435，406，
    2 数据需要左右遍历2次：135
    3 数据左遍历，先进行统计信息，在左遍历一次做策略：763

*/

// 452 medium 射箭，一组{x0,x1}x轴坐标，表示一条线，最少从x轴向上射几根箭，可以戳爆所有线
// 1 对左边界排序
// [1 3]
// [ 2 4]
//     [5 6]
// 显然如果左边界大于上一个右边界，一定到了新的区域
// 如果不是，需要把当前的右边界小，
// 1.1 如果自己边界更大，结果生成一个方块的右上半部分（容易理解）
// 1.2 自己更短，意味着自己就在整个区域中，对于下一次的节点没有任何影响，所以不变
// 2 对右边界排序
// [ 2 4]
// [1     6]
//   [3 5]
// 产生新区域的依然还是同上
// 并且不出现新区域时不需要更新边界
int findMinArrowShots(vector<vector<int>>& points) {  // 版本1
    if (points.empty()) return 0;
    sort(points.begin(), points.end(), [](vector<int> &p1, vector<int> &p2) {
        return p1[0] < p2[0];
    });
    int res = 1, pos = points[0][1];
    for (const vector<int> &line : points) {
        if (line[0] > pos) {
            res += 1;
            pos = line[1];
        }
    }
    return res;
}
int findMinArrowShots(vector<vector<int>>& points) {  // 版本2
    if (points.empty()) return 0;
    sort(points.begin(), points.end(), [](vector<int> &p1, vector<int> &p2) {
        return p1[1] < p2[1];
    });
    int res = 1, pos = points[0][1];
    for (const vector<int> &line : points) {
        if (line[0] > pos) {
            res += 1;
            pos = line[1];
        }
    }
    return res;
}

// 435 medium 给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠（左右边界重合不算重叠）
// 和452很像，使用右边界排序，如果当前发生重叠，就排除当前节点
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() < 2) return 0;
    sort(intervals.begin(), intervals.end(), [](const vector<int> &p1, const vector<int> &p2) {
        return p1[1] < p2[1];
    });
    int res = 0, pos = intervals[0][1];  // pos记录上一个节点的右边界
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < pos) {
            res += 1;
        } else {
            pos = intervals[i][1];
        }
    }
    return res;
}

// 56 medium 给出一个区间的集合，请合并所有重叠的区间。（左右边界重合算重叠）
// 这次需要排序左边界了，这样[l,r]的l永远是可以保证的
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() < 2) return intervals;
    sort(intervals.begin(), intervals.end(), [](const vector<int> &p1, const vector<int> &p2) {
        if (p1[0] == p2[0]) return p1[1] < p2[1];
        return p1[0] < p2[0];
    });
    vector<vector<int>> res;
    int l = intervals[0][0], r = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] > r) {
            res.emplace_back(vector<int>{l,r});
            l = intervals[i][0];
        }
        r = max(r, intervals[i][1]);
    }
    res.emplace_back(vector<int>{l,r});  // 最后一次没有放进去
    return res;
}

// 406 medium 一堆人排队，他们只能看到前面比自己高或者和自己一样高的人数ki，同时也知道自己身高hi
// 即已知知识为 {hi, ki}。现在给出了一组 pair，但顺序不是队伍从前往后给出的，返回正确的队伍顺序。
// 如果按照身高从高到低排，ki从低到高排序。每次插进一个人，因为所有人都比自己高或者相同，所以只要插到ki就完了
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](const vector<int> &p1, const vector<int> &p2) {
        if (p1[0] == p2[0]) return p1[1] < p2[1];
        return p1[0] > p2[0];
    });
    list<vector<int>> que;
    for (const vector<int> &p : people) {
        int pos = p[1];
        auto it = que.begin();
        while (pos--) ++it;
        que.insert(it, p);
    }
    return vector<vector<int>>{que.begin(), que.end()};
}


// 135 hard 老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的ratings，预先给他们评分。
// 你需要按照以下要求，帮助老师给这些孩子分发糖果：
// 1 每个孩子至少分配到 1 个糖果；2 相邻的孩子中，评分高的孩子必须获得更多的糖果。
// 那么这样下来，老师至少需要准备多少颗糖果呢？
// 不要想太多，向前一次，向后一次
int candy(vector<int>& ratings) {
    int len = ratings.size();
    vector<int> cnt(len, 1);
    for (int i = 1; i < len; ++i) {
        if (ratings[i] > ratings[i-1]) cnt[i] = cnt[i-1] + 1;
    }
    for (int i = len-2; i >= 0; --i) {
        if (ratings[i] > ratings[i+1]) cnt[i] = max(cnt[i], cnt[i+1]+1);
    }
    return accumulate(cnt.begin(), cnt.end(), 0);
}


// 763 medium s由小写字母组成。把s划分为尽可能多的段，同一字母最多出现在一个段中。返回一个表示每个字符串片段的长度的列表。
// 首先用一个数组pos统计每个字母最远出现的位置，这意味着：i<=pos[i]
// 所以"858575878,14,...“这种情况，表示[l,r]区间的边界就是pos[8]
// 如果在找8的过程中出现比8更大的数，比如9，且还没到8时，这意味着需要更新要找的数为pos[9]
// 这是因为需要把9放到该区间，所以得找到i==pos
// 如果比8小，不能分，因为8还没找到。
vector<int> partitionLabels(string s) {
    int pos[26] = {0};
    for (int i = 0; i < s.size(); ++i) {
        pos[s[i]-'a'] = i;
    }
    vector<int> res;
    int l = 0, r = 0;
    for (int i = 0; i < s.size(); ++i) {
        r = max(r, pos[s[i]-'a']);
        if (i == r) {
            res.emplace_back(r-l+1);
            l = i + 1;
        }
    }
    return res;
}