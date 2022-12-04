#include <myheader.h>

// 并查集
// 支持两种集合操作
// 1 A和B是否是在一个集合
// 2 A和B合并

// 547 medium 给了一个n*n的矩阵，m[i][j]为1表示i和j相连（m[i][i]当然为1），求连通图的数量
// DFS和BFS当然能做，这里使用UFS试试
class sUFS {
private:
    // ufs[i]<0说明i是集合的头头，其绝对值为集合元素的数量
    vector<int> ufs;
public:
    void init(int n) {
        // 一开始所有自己的头头就是自己
        ufs.resize(n, -1);
    }
    // 查询i的集合的头头，是正数
    int find(int i) {
        if (ufs[i] < 0) return i;
        else return ufs[i] = find(ufs[i]);
    }
    // 让nx和ny是一个集合
    void unit(int nx, int ny) {
        int root1 = find(nx);
        int root2 = find(ny);
        if (root1 != root2) {
            ufs[root1] += ufs[root2];  // 集合的数量增加
            ufs[root2] = root1;  // 后者挂在前者上
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), res = 0;
        init(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) {
                    unit(i, j);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (find(i) == i) {
                ++res;
            }
        }
        return res;
    }
};
