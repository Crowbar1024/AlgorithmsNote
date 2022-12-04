#ifndef MYHEADERH
#define MYHEADERH


#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <string>
#include <functional>
#include <atomic>
#include <sstream>
#include <numeric>
#include <climits>
#include <ctime>
#include <type_traits>

using namespace std;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif