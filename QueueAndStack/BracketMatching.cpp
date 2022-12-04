#include <myheader.h>

// easy JD2018春招03 括号匹配问题
// 像这些是对的：
// ()()()
// ((()))()
// 现在给出一个字符串，如果最多只能交换其中的一组数据，swap(i,j)，能否使字符串正确
// 思路就是用栈遍历这个字符串，观察栈里最后剩下的括号情况
bool judgeBySwapOnce(string s) {
    int len = s.size();
    if (len & 1) {
        return false;	
    }
    stack<char> sk;
    for (char ch : s) {
        if (sk.empty()) {
            sk.push(ch);
        } else if (sk.top() == '(' && ch == ')') {
            sk.pop();
        } else {
            sk.push(ch);
        }
    }
    if (sk.empty()) {
        return true;
    } else if (sk.size() != 2) {
        return false;
    } else {  // 只有)(这种情况可以交换成功
        char ch1 = sk.top();
        sk.pop();
        if (ch1 == '(' && sk.top() == ')') {
            return true;
        } else {
            return false;
        }
    }
}

// easy 20 类似JD2018春招03，只需要判断是否有效就行，并且有3种括号(){}[]
// 因为只要判断有效，所以可以在循环中直接返回。
// 并且由于栈的性质，遇到一个)，如果栈顶是(，说明之间可能存在一大堆别的已经弹出了
// 所以可以直接压([{，遇到对应的右括号时如果不对，就直接报错就行
// 为了代码的简单，可以用哈希表。由于需要通过右括号找左括号，哈希表设计注意一下。
// 为什么用哈希表？因为想判断ch是否是三个左括号之一
bool isValid(string s) {
    int len = s.size();
    if (len & 1) {
        return false;	
    }
    unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
    };
    stack<char> sk;
    for (char ch : s) {
        if (!pairs.count(ch)) {  // 左括号直接压
            sk.push(ch);
        } else {
            if (sk.empty() || sk.top() != pairs[ch]) {
                return false;
            }
            sk.pop();
        }
    }
    return sk.empty();
}

// 1003 medium ""-"abc"-"aabcbc"...
// 可以从任意地方插入新的"abc"，判断s是否是这样产生的
// 和两个括号的匹配思路完全相同，右括号碰到左括号消掉。那么c碰到ab也能消掉，同理abcd。
bool isValid(string s) {
    stack<char> sk;
    for (char ch : s) {
        if (ch == 'a' || ch == 'b') {
            sk.push(ch);
        } else {
            if (sk.size() < 2 || sk.top() != 'b') {
                return false;
            }
            sk.pop();
            if (sk.top() != 'a') {
                return false;
            }
            sk.pop();
        }
    }
    return sk.empty();
}


// 1190 medium 将()中的字符串翻转，并在输出中删除括号。
// 如输入为 (uoy(love)i)，输出为iloveyou
// 每次记录左括号(的位置，每次遇到右括号就在res上翻转，相当于从左到右模拟一遍
string reverseParentheses(string s){
    stack<int> leftP;
    string res = "";  // 最后输出的字符串
    for(char ch : s) {
        if (ch == '(') {  // 记录当前为止前面的字母数量，用来充当翻转操作的位置起始点
            leftP.push(res.size());
        } else if (ch == ')') {
            int l = leftP.top();  // 获取当前(X)中X前的字母数量
            leftP.pop();
            reverse(res.begin()+l, res.end());  // 翻转当前(X)中的X
        } else {
            res += ch;
        }
    }
    return res;
}
// 时间复杂度O(n^2)。难以接受。如果统计每个左括号和右括号之间的引用关系，会不会只需要遍历一次就行了？
// 如(uoy(love)i)，{0,11}和{4,9}，当遍历到第一个左括号时，res跳跃到11，然后逆向遍历字符；
// 同理在遇到其他括号，就需要遍历方向反转
string reverseParentheses(string s) {
    vector<int> partner(s.size());
    stack<int> idx;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            idx.emplace(i);
        } else if (s[i] == ')') {
            int j = idx.top(); idx.pop();
            partner[i] = j;
            partner[j] = i;
        }
    }
    string res = "";
    int cur = 0, dir = 1;
    while (cur < s.size()) {
        if (s[cur] == '(' || s[cur] == ')') {
            cur = partner[cur];
            dir = -dir;
        } else {
            res += s[cur];
        }
        cur += dir;
    }
    return res;
}