#include <myheader.h>

// minimum spanning tree

// 1-Kruskal
// 将所有边的按权重从小到大排序。
// 从小到大遍历这些边。当遍历边<u,v>时,如果u和v属于两棵规模小的最小生成树，则将u与v链接起来，合并成一个规模大的最小生成树。
// 总费用加上<u,v>的费用。
// 最小生成树用并查集表示。


// 1584 medium
// 给了一堆点，问这些点组成的最小生成树的边长的和，边长是曼哈顿距离
// kruskal解法
// 步骤简单如下：
// 1 将所有可能的边放入一个小顶堆，按照边的长度
// 2 每次取出堆头，即最短的边，然后利用并查集检测顶点是否之间被访问过
// 3 如果没有被访问过，即有个顶点的父节点就是自己，然后让它加入并查集，然后让并查集的父节点对应的元素数量+1
// 可以发现kruskal的顺序就是最下生成树的生成过程
struct edge {
    int len;
    int x;
    int y;
    bool operator<(const edge& x) const{
        return len > x.len;
    }
};
// 使用一个数组来保存并查集，十分巧妙
// 因为并查集只有两个节点间的合并，所以可以用第一个节点当做头结点，保存数量信息，后者保存前者的节点编号
int find(vector<int>& ufs, int i) {
    if (ufs[i] < 0) return i;
    else return ufs[i] = find(ufs, ufs[i]);
}
int minCostConnectPoints(vector<vector<int>>& points) {
    vector<edge> v;
    int n = points.size();
    vector<int> ufs(n, -1);
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {  // 这样遍历是n(n-1)/2，与所有边的数量相等
            v.push_back({abs(points[i][0]-points[j][0])+abs(points[i][1]-points[j][1]), i, j});
        }
    }
    priority_queue<edge> pq(v.begin(), v.end());
    int res = 0;
    while (!pq.empty()) {
        int nlen = pq.top().len, nx = pq.top().x, ny = pq.top().y;
        pq.pop();
        int root1 = find(ufs, nx);
        int root2 = find(ufs, ny);
        if (root1 != root2) {  // 并查集合并
            res += nlen;
            ufs[root1] += ufs[root2];  // 集合的数量增加
            ufs[root2] = root1;  // 后者挂在前者上
            if (ufs[root1] == -n) break; // 集合已经包含了n个节点
        }
    }
    return res;
}
// Prims解法
// 1 随机挑一个初始点当做初始点集合A
// 2 寻找边集中与集合A最近的点，加入点集，边集加入这条边
// 3 继续挑选与这个集合有连接的还没被访问的点……
// 在这道题中就是把步骤2改改，把所有未访问过的点放到小顶堆中，找到其中边最小的点
// 然后从中把
// 由于需要找到边集中与集合A最近的点，所以之前的边与每次找到的v的距离需要保留在堆中
// 这样有两种情况，即新的点到上一个点的距离是否位于堆顶
// 1如果位于，如果元素唯一，最简单，直接用；如果相等，要考虑是否被访问过
// 2不是，比如 ab-100 ac-1 bc-2
// c作为初始点，下一个点是a，然后把与a相连的点放入堆中发现，堆顶是bc-2，即是之前剩下的b
// 当然堆顶的点被访问过，自然不能用
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    priority_queue<pair<int,int>> pq;
    int res = 0;
    int v = 0;  // initial point
    vector<bool> isVisited(n);
    for (int i = 1; i < n; ++i) {
        isVisited[v] = true;
        for (int j = 0; j < n; ++j) {
            if (!isVisited[j]) {
                int len = abs(points[j][0]-points[v][0]) + abs(points[j][1]-points[v][1]);
                pq.push({-len, j});  // 取负数是因为默认大顶堆
            }
        }
        while (isVisited[pq.top().second]) pq.pop();
        res -= pq.top().first;
        v = pq.top().second;
        pq.pop();
    }
    return res;
}
// 这种解法运用到了堆，因为会把所有边都统计，所以时间复杂度为n^2 * 2logn，前者为边数，后者为堆的运算一次的复杂度
// 由于会计算到全部边，所以改进的方法是用一个n维的数组去统计最短距离
// minDist[j]是当前节点j到点集A的最短距离
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    int res = 0;
    vector<int> minDist(n, INT_MAX);
    int v = 0;  // initial point
    for (int i = 1; i < n; ++i) {
        minDist[v] = INT_MAX-1;  // 需要与之不同，因为需要让未访问过的和已经访问并确定值的区别开
        int adjCur = v;
        for (int j = 0; j < n; ++j) {
            if (minDist[j] != INT_MAX-1) {  // 依然是未被访问过的含义
                int len = abs(points[j][0]-points[v][0]) + abs(points[j][1]-points[v][1]);
                minDist[j] = min(minDist[j], len);  // 每次更新节点与集合A的最短距离
                adjCur = minDist[j] < minDist[adjCur] ? j : adjCur;  // 更新出所有点中与当前节点最近的那个
            }
        }
        res += minDist[adjCur];
        v = adjCur;
    }
    return res;
}