//-----------------------------------【程序说明】----------------------------------------------
//  问题来源：密码学求乘法逆元 
//	2018年4月23日	Create by Howie Yao
/*  描述：
	如果ax ≡1 (mod p),且gcd(a,p)=1（a与p互质），则称a关于模p的乘法逆元为x。
	求x 
	
	给出exgcd的推导
	a*x+b*y = gcd(a , b)
		    = gcd(b , a mod b)  
	        = b * x1 + (a mod b) * y1       
	        = b * x1 + (a - a / b * b) * y1   
	化简上式，得
	a*x+b*y = a * y1 + b * (x1-a/b*y1)
	
	如下的exgcd板子只是交换了x,y的顺序
	
	好了，以上就是求x,y的方法。
	
	1. 用费马小定理求乘法逆元 
	接着引入费马小定理的介绍：
	假如a是一个整数，p是一个质数，那么 
	a^p ≡a (mod p)
	如果a不是p的倍数，这个定理也可以写成
	a^(p-1) ≡1 (mod p)
	那么，以上的乘法逆元x = a^(p-2)，用快速幂可以算出即可。 (前提，a,p互质)
	
	2. 用扩欧求乘法逆元 
	因为 ax ≡1 (mod p)
	即 ax = py+1
	换一下就是：ax+py=1，
	
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
const int maxn=1e5+5;
const int MOD=1e9+7;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
	//gcd算完了 
	if (!b) {
		d = a;
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a%b, d, y, x);
	y -= a/b*x;
}

ll inv(ll a, ll p) {
    ll d, x, y;
    exgcd(a, p, d, x, y);
    //因为x可能算出来可能是负的 
    return d == 1 ? (x+p)%p : -1;
}


int main()  {
	freopen("input.txt","r",stdin);
	ll a,b,d,x,y;
	while (~scanf("%lld %lld",&a,&b)) {
//		exgcd(a,b,d,x,y);
		ll res = inv(a,b);
//		printf("%lld %lld %lld\n",d,x,y);
		printf("%lld\n",res);
	}
	return 0;
}

