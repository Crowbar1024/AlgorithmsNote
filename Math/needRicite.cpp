#include <myheader.h>


// 62 medium 一个机器人位于一个mxn网格的左上角，每次只能向下或者向右移动一步。
// 试图达到网格的右下角，问总共有多少条不同的路径？
// 显然可以用组合思想求解，起点和终点定了，那么一共走了m+n-2步，然后从中选择m-1步是向下的
// 利用杨辉三角，C_n^m=C_(n-1)^(m-1)+C_(n-1)^(m)
// 1
// 1 1
// 1 2 1
// 1 3 3 1
// 1 4 6 4 1
// 每行都是对称的，所以可以只迭代一半
// 但这里只要求一次，所以这里每一行只迭代到m，注释的部分是全部迭代了
// 也可以发现，若是仅仅求一次组合数的话，还不如用DP
int uniquePaths(int m, int n) {
    n = m+n-2, m = m-1;
    m = min(m,n-m);
    // vector<vector<int>> c(n+1, vector<int>(n/2+1, 1));
    vector<vector<int>> c(n+1, vector<int>(m+1, 1));
    for (int i = 2; i <= n; ++i) {
        // for (int j = 1; j <= i/2; ++j) {
        for (int j = 1; j <= m; ++j) {
            // 偶数行有奇数个值，中间值是有效的
            // 奇数行有偶数个，所以只赋值前一半
            // 这样偶数行的中间值无法让奇数行中间两个赋值，所以double一下
            if (!(i&1) && j == i/2) {
                c[i][j] = c[i-1][j-1] * 2;
            } else {
                c[i][j] = c[i-1][j-1] + c[i-1][j];
            }
        }
    }
    return c[n][m];
}




// 素数筛选
void primeTransform(int a, int b) {
    const int n = 1e4+5;
    bitset<n> isPrime("11");
    isPrime.flip();
	for(int i=2;i<=maxn;i++) {
		if(isPrime[i]) {
			for(int j=i<<1; j<=maxn; j+=i) isPrime[j] = 0;
		}
	}    
}

// NC132/139 约瑟夫环
// 有n个人，从第一个人开始数，数到第q个人，让他挂掉，然后接着接龙，看谁活到最后
// 算法来源，具体数学中，数学归纳法
// 这个版本是序号从0开始，所以如果从1开始，只需要+1
int JosephRing(int n, int q) {
    int rescurID = 0;
	for (int i=2; i<=n; ++i) {
        rescurID = (rescurID+q)%i;
    }
    return rescurID;
}

// 给出一个多边形的全部顶点，判断(ax,bx)这个点是否唉多边形内部
// 需要注意的是，给定的其实是多边形的顺时针的边（因为单纯给出顶点，可以有多个形状不同的多边形）
// 采用射线法，往右的射线与多边形的边的交点的个数，若为奇，在内部，否则不在
// 这种方法在经过多边形的拐点时失效
// 2 连线角之和为360，当不为凸时，有些位置失效
// 我自己的想法是由于拐点的存在，判断这两条边是否一上一下，是的话算交点（本质上这样就是一条边）
struct edge {
    pair<double,double> p1;
    pair<double,double> p2;
};
bool isPoiWithinPoly(pair<double,double> p, vector<edge>& e) {
    int intersection = 0;
    for (int i = 0; i < e.size(); ++i) {
        edge tmp = e[i];
        if (tmp.p1.first > tmp.p2.first) {  // 这是下面判断边交点的前提
            pair<double,double> tmpPoint = tmp.p1;
            tmp.p1 = tmp.p2;
            tmp.p2 = tmpPoint;
        }
        if (isRayIntersectsSegment(p, e, i)) ++intersection;
    }
    return intersection&1 ? true : false;
}
bool isRayIntersectsSegment(pair<double,double> x, vector<edge>& e, int i) {
    pair<double,double> a = e[i].p1;
    pair<double,double> b = e[i].p2;
    if (a.second==b.second)  // 与射线平行或者重合
        return false;
    if (a.second>x.second && b.second>x.second)  // 在射线上边
        return false;
    if (a.second<x.second && b.second<x.second) // 在射线下边
        return false;
    if (a.second == x.second && b.second != x.second) {
        if ((e[i-1].p1.second-x.second)*(a.second-x.second) < 0)  // 上下两边
            return true;
        else return false;
    }
    if (a.second == x.second && b.second != b.second) {
        i = i > 0 ? i : e.size();
        if ((e[(i-1)%e.size()].p1.second-x.second)*(a.second-x.second) < 0)  // 上下两边
            return true;
        else return false;  //  不需要检测b.second == x.second，上一个循环已经测试过了
    }
    if (b.second==x.second && a.second>x.second)  // 交点为a
        return false;
    if (b.first<x.first && b.second<x.second)  // 在射线左边
        return false;
    double xseg = a.first-(a.first-b.first)*(b.second-x.second)/(b.second-a.second);  // 交点
    if (xseg<x.first)  // 交点在射线起点的左侧
        return false;
    return true;
}