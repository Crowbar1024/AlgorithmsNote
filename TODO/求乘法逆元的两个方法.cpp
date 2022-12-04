//-----------------------------------������˵����----------------------------------------------
//  ������Դ������ѧ��˷���Ԫ 
//	2018��4��23��	Create by Howie Yao
/*  ������
	���ax ��1 (mod p),��gcd(a,p)=1��a��p���ʣ������a����ģp�ĳ˷���ԪΪx��
	��x 
	
	����exgcd���Ƶ�
	a*x+b*y = gcd(a , b)
		    = gcd(b , a mod b)  
	        = b * x1 + (a mod b) * y1       
	        = b * x1 + (a - a / b * b) * y1   
	������ʽ����
	a*x+b*y = a * y1 + b * (x1-a/b*y1)
	
	���µ�exgcd����ֻ�ǽ�����x,y��˳��
	
	���ˣ����Ͼ�����x,y�ķ�����
	
	1. �÷���С������˷���Ԫ 
	�����������С����Ľ��ܣ�
	����a��һ��������p��һ����������ô 
	a^p ��a (mod p)
	���a����p�ı������������Ҳ����д��
	a^(p-1) ��1 (mod p)
	��ô�����ϵĳ˷���Ԫx = a^(p-2)���ÿ����ݿ���������ɡ� (ǰ�ᣬa,p����)
	
	2. ����ŷ��˷���Ԫ 
	��Ϊ ax ��1 (mod p)
	�� ax = py+1
	��һ�¾��ǣ�ax+py=1��
	
	���ϡ�
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
	//gcd������ 
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
    //��Ϊx��������������Ǹ��� 
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

