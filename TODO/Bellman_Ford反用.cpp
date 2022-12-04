//-----------------------------------[Program Explantion]------------------------------------
//  Problem Source:
//	2018/5/31	Create by Howie Yao
/*  Description:
	有多种汇币，汇币之间可以交换，这需要手续费，当你用100A币交换B币时，A到B的汇率是29.75，手续费是0.39;
	那么你可以得到(100 - 0.39) * 29.75 = 2963.3975 B币。问s币的金额经过交换最终得到的s币金额数能否增加;
	
	本题是“求最大路径”，之所以被归类为“求最小路径”是因为本题题恰恰与bellman-Ford算法的松弛条件相反，
	求的是能无限松弛的最大正权路径，但是依然能够利用bellman-Ford的思想去解题。
	因此初始化d(S)=V   而源点到其他店的距离（权值）初始化为无穷小（0）
	当s到其他某点的距离能不断变大时，说明存在最大路径

 
*/
//-------------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <functional>
#include <ctime>

using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int MOD=1e9+7;
const int maxn=1e4+5;

const int N=500;

struct Edge {
	int u,v;
	double rate, cost;
}edge[N];
double dis[110];
int n,orign,nodenum,C;
double v;		//orign:拥有的货币, v:拥有的货币价值, nodenum:多少个货点 , C:把货点双向拆成2条线 

bool Bellman_Ford() {
	memset(dis,0,sizeof(dis));  // 这里与bellman的目的刚好相反。初始化为源点到各点距离无穷小  
	dis[orign]=v;   //即bellman本用于找负环，求最小路径，本题是利用同样的思想找正环，求最大路径  
	for(int i=1;i<=n-1;i++) {
		bool flag=false;
		for(int j=0;j<C;j++) {
			int a=edge[j].u, b=edge[j].v;
			double r=edge[j].rate, c=edge[j].cost;
			if(dis[b] < (dis[a]-c)*r) {		//只要有一次是赚的，我就兑换 
				dis[b] = (dis[a]-c)*r;
				flag=true;
			}
		}
		if(!flag) break;		//有一种货币不赚，我就退出来 
	}
	for(int i=0;i<C;i++) {
		int a=edge[i].u, b=edge[i].v;
		double r=edge[i].rate, c=edge[i].cost;
		if(dis[b] < (dis[a]-c)*r) return true;  //只要存在正环就行了
	}
	return false;
}

int main() {
	while(~scanf("%d%d%d%lf",&n,&nodenum,&orign,&v)) {
		C=0;
		int a,b;
		for(int i=0;i<nodenum;i++) {
			//一个“兑换点”就是图上两种货币之间的一个兑换环
			double Rab,Cab,Rba,Cba;
			scanf("%d%d%lf%lf%lf%lf",&a,&b,&Rab,&Cab,&Rba,&Cba);
			edge[C].u=a;
			edge[C].v=b;
			edge[C].rate=Rab;
			edge[C++].cost=Cab;
			edge[C].u=b;
			edge[C].v=a;
			edge[C].rate=Rba;
			edge[C++].cost=Cba;
		}
		if(Bellman_Ford()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
