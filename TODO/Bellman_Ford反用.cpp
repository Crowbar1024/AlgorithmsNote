//-----------------------------------[Program Explantion]------------------------------------
//  Problem Source:
//	2018/5/31	Create by Howie Yao
/*  Description:
	�ж��ֻ�ң����֮����Խ���������Ҫ�����ѣ�������100A�ҽ���B��ʱ��A��B�Ļ�����29.75����������0.39;
	��ô����Եõ�(100 - 0.39) * 29.75 = 2963.3975 B�ҡ���s�ҵĽ����������յõ���s�ҽ�����ܷ�����;
	
	�����ǡ������·������֮���Ա�����Ϊ������С·��������Ϊ������ǡǡ��bellman-Ford�㷨���ɳ������෴��
	������������ɳڵ������Ȩ·����������Ȼ�ܹ�����bellman-Ford��˼��ȥ���⡣
	��˳�ʼ��d(S)=V   ��Դ�㵽������ľ��루Ȩֵ����ʼ��Ϊ����С��0��
	��s������ĳ��ľ����ܲ��ϱ��ʱ��˵���������·��

 
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
double v;		//orign:ӵ�еĻ���, v:ӵ�еĻ��Ҽ�ֵ, nodenum:���ٸ����� , C:�ѻ���˫����2���� 

bool Bellman_Ford() {
	memset(dis,0,sizeof(dis));  // ������bellman��Ŀ�ĸպ��෴����ʼ��ΪԴ�㵽�����������С  
	dis[orign]=v;   //��bellman�������Ҹ���������С·��������������ͬ����˼���������������·��  
	for(int i=1;i<=n-1;i++) {
		bool flag=false;
		for(int j=0;j<C;j++) {
			int a=edge[j].u, b=edge[j].v;
			double r=edge[j].rate, c=edge[j].cost;
			if(dis[b] < (dis[a]-c)*r) {		//ֻҪ��һ����׬�ģ��ҾͶһ� 
				dis[b] = (dis[a]-c)*r;
				flag=true;
			}
		}
		if(!flag) break;		//��һ�ֻ��Ҳ�׬���Ҿ��˳��� 
	}
	for(int i=0;i<C;i++) {
		int a=edge[i].u, b=edge[i].v;
		double r=edge[i].rate, c=edge[i].cost;
		if(dis[b] < (dis[a]-c)*r) return true;  //ֻҪ��������������
	}
	return false;
}

int main() {
	while(~scanf("%d%d%d%lf",&n,&nodenum,&orign,&v)) {
		C=0;
		int a,b;
		for(int i=0;i<nodenum;i++) {
			//һ�����һ��㡱����ͼ�����ֻ���֮���һ���һ���
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
