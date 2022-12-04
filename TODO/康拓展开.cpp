//-----------------------------------【program description】---------------------------------
//  source：网易校招
//	2018/8/12	Create by Howie Yao
/*  description：
	全排列；
	1.输入一个数列，输出它是这个数列的集合的第几个全排列
	2.输入k，输出第k个全排列；
	涉及知识：康托展开和康托逆展开。
	康托展开是一个全排列到一个自然数的双射，常用于构建哈希表时的空间压缩。 
	康托展开的实质是计算当前排列在所有由小到大全排列中的顺序，因此是可逆的。
*/
//-------------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
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
const int INF = 0x3f3f3f3f;
typedef long long ll;
const int maxn = 1e5+5;
const int MOD = 1e9 + 7;

ll fac[10];

void calFac(string s) {
	int len = s.length();
	fill(fac, fac + len, 1);
	for (int i = 1; i < len; i++) {
		fac[i] = fac[i - 1] * i;
	}
}

ll cantor(string s) {
	int len = s.length();
	ll res = 0;
	for (int i = 0; i < len; i++) {
		int smallerNum = 0;
		for (int j = i + 1; j < len; j++) {
			if (s[j] < s[i]) {
				smallerNum += 1;
			}
		}
		res += smallerNum * fac[len - i - 1];
	}
	return res;
}

string decantor(string s, ll k) {
	string res;
	sort(s.begin(), s.end());
	int len = s.length();
	for (int i = len - 1; i >= 1; i--) {
		ll n = k / fac[i];
		res += s[n];
		s.erase(n, 1);
		k %= fac[i];
	}
	res += s[0];
	return res;
}

int main() {
	/*string s = "357412968";
	calFac(s);
	printf("序列 ");
	cout << s;
	printf(" 是全排列的第%lld组\n", cantor(s) + 1);*/

	string s = "12345";
	ll	x = 62;
	calFac(s);
	printf("序列 ");
	cout << s;
	printf(" 的第%lld组是 ", x - 1);
	cout << decantor(s, x - 1);
	return 0;
}
