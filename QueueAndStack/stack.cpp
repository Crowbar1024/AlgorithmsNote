#include <myheader.h>

// easy 155 最小栈，故名意思，可以返回栈中最小的元素
// 核心思路，两个栈，一个正常，一个只存放最小值。比如，存3 4 2 3
// [3               [3
// [3 4             [3 3
// [3 4 2           [3 3 2
// [3 4 2 3         [3 3 2 2
class MinStack {
private:
    stack<int> st, minSt;
public:
    MinStack() {}
    void push(int val) {
        st.push(val);
        if (minSt.empty() || val < minSt.top()) {
            minSt.push(val);
        } else {
            minSt.push(minSt.top());
        }
    }
    void pop() {
        if (st.empty()) return;
        st.pop();
        minSt.pop();
    }
    int top() { return st.top(); }
    int getMin() { return minSt.top(); }
};

// PAT 1051 [1:n]按次序压入栈，m为栈的大小，v为出栈的顺序，判断v是否正确
// 模拟每个出栈元素的出栈顺序
bool PopSequence(int n, int m, vector<int>& v) {
    stack<int> s;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        s.push(i+1);
        if (s.size() > m) {
            break;
        }
        while (!s.empty() && s.top() == v[cur]) {
            s.pop();
            ++cur;
        }
    }
    if (cur == n) {
        return true;
    } else {
        return false;
    }
}

// hard 反转栈，只能使用递归，inplace操作。
// 比如[1,2,3，先需要返回1，并且要保留[2,3的栈的结构
// 最后要把1压入栈，那么递归函数在弹出栈底和压栈之间
void reverseStack(stack<int>& s) {
    if (s.empty()) return;
    int bottom = getStackBottom(s);
    reverseStack(s);
    s.push(bottom);
}
// 简单来说，就是先不断弹出栈顶，然后不断压入栈，那么递归函数的位置就很清楚了，在弹出和压入之间
// 且返回的是相同的一个数，即栈底。
int getStackBottom(stack<int>& s) {
    int x = s.top();
    s.pop();
    if (s.empty()) {
        return x;    
    }
    int bottom = getStackBottom(s);
    s.push(x);
    return bottom;
}