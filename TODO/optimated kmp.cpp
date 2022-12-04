//-----------------------------------[Program Explantion]------------------------------------
//  Problem Source:
//	2018/5/26	Create by Howie Yao
/*  Description:
    optimated kmp
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
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn=1e2+5;
const int MOD=1e9+7;

int next[maxn];

// after optimation, avoid p[i]=p[next[i]]
void getNext(char p[]) {
    int len = strlen(p);
    next[0] = -1;
    int k=-1,i=0;  // k is first index of prefix, i is first index of postfix
    while (i<len-1) {
        if (k==-1 || p[k]==p[i]) {
            k++;
            i++;
            if (p[i] != p[k]) next[i] = k;
            else next[i] = next[k];  // vital! avoid the problem above!
        }
        else k = next[k];
    }
}


int kmp(char s[], char p[]) {
    getNext(p);
	int i=0, j=0;
	int slen=strlen(s), plen=strlen(p);
	while (i<slen && j<plen) {
        if (j==-1 || s[i]==p[j]) {
            i++;
            j++;
        } else j = next[j];
	}
	return j==plen ? i-j : -1;
}

int main() {
    freopen("input.txt","r",stdin);
    char s[20],p[20];
    scanf("%s %s",s,p);
//    printf("%s\n%s",s,p);
    printf("%d",kmp(s,p));
	return 0;
}
