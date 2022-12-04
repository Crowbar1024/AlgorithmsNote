#include <myheader.h>

// PAT 1013 n个节点[1:n]，边ptp，删除一个节点，临边消失。
// 问至少要添加多少条边才能让图重新变为连通图
// 知识：当n个互相分立的连通分量需要变为连通图的时候，只需要添加n-1个路线，成为连通图
// 所以这道题就是求去除了某个节点之后图所拥有的连通分量数
class BattleOverCities {
private:
    int n;
    vector<vector<int>> path;  // 邻接矩阵
    vector<int> visit;
    void Init(int cityNum, vector<vector<int>>& ctc) {
        n = cityNum;
        path.resize(n+1, vector<int>(n+1, 0));
        for (int i = 0; i < ctc.size(); ++i) {
            int c1 = ctc[i][0], c2 = ctc[i][1];
            path[c1][c2] = path[c2][c1] = 1;
        }
        visit.resize(n+1, 0);
    }
    void dfs(int x) {
        visit[x] = 1;
        for (int i = 1; i <= n; i++) {
            if (!visit[i] && path[i][x]) dfs(i);
        }
    }
public:
    int addEdgeNum(int cityNum, int destroyCity, vector<vector<int>> ctc) {
        Init(cityNum, ctc);
        int cnt = 0;
        visit[destroyCity] = 1;
        for (int i = 1; i <= n; i++) {
            if (!visit[i]) {
                dfs(i);
                cnt++;
            }
        }
        return cnt;
    }
};


// PAT 1091 给定一个三维数组box，0表示正常1表示有肿瘤，肿瘤块的大小大于等于t才算作是肿瘤，求肿瘤的总体积
// 三维连通图
// 由于没有边的约束，只给了点的信息，即涉及到走来走去，bfs更好，并且可以在一个循环中得到一个联通图的节点数量
// 并且为了不建立visit，使用消元法，而消元的前提就是没有边
class BattleOverCities {
private:
    const vector<vector<int>> dir{{1,0,0},{0,1,0},{0,0,1},{-1,0,0},{0,-1,0},{0,0,-1}};
    struct Node {
        int x, y, z;
    };
    vector<vector<vector<int>>> box;
    int n,m,l;  // 长宽高
    int t;
    int tNum, tSize;
    void init(vector<vector<vector<int>>>& organ, int tumourSize) {
        t = tumourSize;
        n = organ.size();
        m = organ[0].size();
        l = organ[0][0].size();
        box = organ;
        tNum = tSize = 0;
    }
    void bfs(int x, int y, int z) {
        int cnt = 1;
        queue<Node> q;
        box[x][y][z] = 0;
        q.push({x,y,z});
        while (!q.empty()) {
            auto tmp = q.front();
            for (int i = 0; i<6; i++) {
                int nx = tmp.x + dir[i][0];
                int ny = tmp.y + dir[i][1];
                int nz = tmp.z + dir[i][2];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && nz >= 0 && nz < l && box[nx][ny][nz]) {
                    cnt++;
                    box[nx][ny][nz] = 0;
                    q.push({nx, ny, nz});
                }
            }
            q.pop();
        }
        if (cnt >= t) tSize += cnt;
    }
public:
    vector<int> getTumourSize(vector<vector<vector<int>>>& organ, int tumourSize) {
        init(organ, tumourSize);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < l; k++) {
                    if (box[i][j][k]) {
                        bfs(i,j,k);
                        tNum++;
                    }
                }
            }
        }
        return vector<int>{tNum, tSize};
    }
};


// PAT 1021 给出n个结点（1~n）之间的n-1条边，保证能生成一棵树（即保证无环）
// 返回能构成最深的树的高度时，树的根结点。如果有多个，按照节点序号从小到大输出。
// 由于点比边多，邻接矩阵不合适，故使用邻接表
// 经过一次DFS后，从任意一点出发所能找到的，是从该点出发的最长边的末尾
// 若是完全平方树，且该点就是头节点，那么互为镜像的叶子节点都是所求，若不是，一般只能找到一侧的点
// 所以需要从那些点再次出发，第二次DFS后，最长边的末尾就是另一侧
// 这两个结点集合的并集就是所求。
// 考察：邻接表+DFS+树
class BattleOverCities {
private:
    int n;
    vector<vector<int>> adjList;  // 邻接表 adjacency list
    vector<int> visit;
    int maxLen;
    vector<int> endList;  // 从某一点出发能找到的最长边的尾端点的序列
    set<int> headSet;
    void Init(int N, vector<vector<int>>& ptpList) {
        n = N;
        for (int i = 0; i < n-1; ++i) {
            int c1 = ptpList[i][0], c2 = ptpList[i][1];
            adjList[c1].push_back(c2);
            adjList[c2].push_back(c1);
        }
        visit.resize(n+1, 0);
        maxLen = 0;
    }
    void dfs(int cur, int curLen) {
        if (curLen > maxLen) {
            maxLen = curLen;
            endList.clear();
            endList.push_back(cur);
        } else if (curLen == maxLen) {
            endList.push_back(cur);
        }
        visit[cur] = 1;
        for (int i = 0; i <= adjList[cur].size(); i++) {
            if (!adjList[cur][i]) {
                dfs(adjList[cur][i], curLen+1);
            }
        }
    }
public:
    vector<int> DeepestRoot(int N, vector<vector<int>> ptpList) {
        Init(N, ptpList);
        int tmp;
        for (int i = 1; i <= n; i++) {
            if (!visit[i]) {
                dfs(i, 1);
            }
            if (i == 1) {
                tmp = endList[0];
                headSet.insert(endList.begin(), endList.end());
            }
        }
        fill(visit.begin(), visit.end(), 0);
        dfs(tmp, 1);
        headSet.insert(endList.begin(), endList.end());
        return vector<int>{headSet.begin(), headSet.end()};
    }
};
