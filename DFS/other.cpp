#include <myheader.h>


// 滑雪，只能从高到低，上下左右。现在给了场地每个节点的高度maze，问最长可以滑的距离是多少
int skiing(vector<vector<int>> maze) {
    int width = maze.size(), length = maze[0].size();
    vector<vector<int>> longestDis(width, vector<int>(length, 0));
    int res = 0;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < length; ++j) {
            res = max(res, dfs(maze, longestDis, i, j));  // 这一步挺妙的
        }
    }
    return res+1;  // 注意本身位置没统计，需加一
}
const vector<vector<int>> dir{{1,0},{0,1},{-1,0},{0,-1}};
// 显然这里选择列表就是四个方向，由于不需要路径记录，可以用一个数组存储每个节点作为起点的滑雪长度
int dfs(vector<vector<int>>& maze, vector<vector<int>>& longestDis, int row, int col) {
    if (longestDis[row][col] > 0) return longestDis[row][col];
    for (int i = 0; i < 4; i++) {
        int nextR = row + dir[i][0];
        int nextL = col + dir[i][1];
        if (nextR >= 0 && nextR < maze.size() && nextL >= 0 && nextL < maze[0].size()) {
            if (maze[row][col] > maze[nextR][nextL]) {
                longestDis[row][col] = max(longestDis[row][col], dfs(maze, longestDis, nextR, nextL)+1);
            }
        }
    }
    return longestDis[row][col];
}


// 1306 medium 依旧是跳跃问题，45 55的变体
// arr非负，即有可能存在若干个0的数，arr[i]说明当前可以跳的位置{i-arr[i],i+arr[i]}
// 给一个起始点，判断是否可以到达任意是0的位置，不能跳出边界。
// 明显的DFS
bool canReach(vector<int>& arr, int start) {
    if (arr[start] == 0) return true;
    return dfs(arr, start);
}
// 选择列表有2，向前向后
// 同时，为了避免重复访问（这题特殊之处），将边界条件设置成重复就终止
bool dfs(vector<int>& arr, int pos) {
    if (arr[pos] < 0) return false;
    arr[pos] = -arr[pos];  // 这个节点访问过了
    bool res = (arr[pos] == 0);
    for (int i = 0; i < 2; i++) {
        int newPos = pos + (2*i-1)*arr[pos];
        if (newPos >= 0 && newPos < arr.size()) {
            res = res || dfs(arr, newPos);  // 注意这里不需要做把选择列表取出和送回
            // 因为这道题没有路径之说，只需要遍历完所有节点就行，所以时间复杂度为On
        }
    }
    return res;
}

// 美团笔试21/5/9 1
// 一个二维数组，从(0,0)到右下角，有多条路径(x,y)->(u,v)的长度，问最短的路径长度是多少
// 为了简单起见，要求x<=u,y<=v
// 长度和宽度上限都是500
// 这道题先入为主使用dijkstra这种算法，但一思考，总结点数为25000，On^2算法肯定挂
// 一看条件，其实简单的DFS就可以解决，因为根据条件，可以理解为一棵树向右下角生成
void dfs(vector<vector<int>>& path, vector<vector<int>>& pathDis, int pos, vector<int>& dis) {
    for (int i = 0; i < path[pos].size(); ++i) {
        int x = path[pos][i];
        dis[x] = min(dis[x], dis[pos]+pathDis[pos][i]);
        dfs(path, pathDis, x, dis);
    }
}
int findMinLength(vector<pair<int,int>> p1, vector<pair<int,int>> p2, vector<int> k, int n, int m) {
    int t = n*m, q = p1.size();
    vector<vector<int>> path(t), pathDis(t);
    for (int i = 0; i < q; ++i) {
        int a1 = (p1[i].first-1)*m + p1[i].second-1;
        int a2 = (p2[i].first-1)*m + p2[i].second-1;
        path[a1].push_back(a2);
        pathDis[a1].push_back(k[i]);
    }
    vector<int> dis(t, INF);
    dis[0] = 0;
    dfs(path, pathDis, 0, dis);
    return dis[t-1]==INF ? -1 : dis[t-1];
}

// HDU 1007
// 平面内的点与点之间的最小距离
// dfs核心：比较两个子区域的最小距离和会跨中心的最小距离
// 也有点二分的意思
struct point {
	double x;
	double y;
};
double minDis(vector<point>& v) {
    sort(v.begin(), v.end(), [](point& a, point& b){ return a.x<b.x; });
    double res = find(0, v.size()-1, v);
    return res/2;
}
double dist(int a, int b, vector<point>& v) {
	return sqrt((v[a].x-v[b].x)*(v[a].x-v[b].x) + (v[a].y-v[b].y)*(v[a].y-v[b].y));
}
double find(int l, int r, vector<point>& v) {
	if (l+1 == r) return dist(l, r, v);
	else if (l+2 == r) return min(dist(l,l+1,v), min(dist(l,r,v),dist(l+1,r,v)));
	int mid = (l+r) >> 1;
	double d = min(find(l, mid, v), find(mid+1, r, v));
	// 保存有可能属于最小距离的点
    vector<int> cc;
	int cnt = 0;
	for (int i=l; i<=r; i++)
		if (v[mid].x-d <= v[i].x && v[i].x <= v[mid].x+d )  // |v[i].x-v[mid].x|<=d
            cc.emplace_back(i);
    int cnt = cc.size();
	sort(cc.begin(), cc.end(), [v](int a, int b){ return v[a].y<v[b].y; });
	for (int i=0; i<cnt-1; i++) {
		for (int j=i+1; j<cnt; j++) {
			if (v[cc[j]].y-v[cc[i]].y >= d) break;
			d = min(d, dist(cc[i], cc[j], v));
		}
	}
	return d;
}