//-----------------------------------【程序说明】----------------------------------------------
//  问题来源：CF 787A
//	2018年6月14日	Create by Howie Yao
/*  描述：
	求使 ax+b = cy+d 的最小整数x;
	采用扩欧：
	其实，扩欧说白了，就是求出AX+BY=GCD(A,B)的一组解;
	接下来就是一个推论:
		Ax0+By0 = Ax1+By1 = GCD(A,B) = g;
		那么得:
		A/g*(x1-x0) = B/g*(y0-y1)
		因为g是A,B的最小公因数;
		所以A/g与B/g互素;
		所以x1-x0是B/g的最小整数倍;
		那么易证：
		x1 = x0+k*B/g
		y1 = y0+k*A/g
	这样就可以从扩欧的一个解中推出其他所有解
	以上。
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

using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
const int maxn=1e2+5;
const int MOD=1e9+7;

typedef long long LL;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
	if (!b) {
		d = a，x = 1，y = 0;
		return;
	}
	exgcd(b, a%b, d, y, x);
	y -= a/b*x;
}

int main() {
	int a,b,c,d,x,y,gcd,C;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	exgcd(a,b,gcd,x,y);
	C = d-b;
	if(C%gcd) printf("-1");
	else {
		x *= (d-b)/gcd;  // 恢复成题设的方程
		int n = c/gcd;  // 上面提到的B/g，现在要不断的得到其他的解
		x = (x%n+n) % n;
		// because y<0
		while ((C-a*x)/b > 0) x += n;
		printf("%d\n",a*x+b);
	}
	return 0;
}
