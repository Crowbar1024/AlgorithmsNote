#include <myheader.h>




// 51 hard N皇后
// 给你一个 N×N 的棋盘，让你放置 N 个皇后，使得它们不能互相攻击（皇后可以攻击同一行、同一列、左上左下右上右下四个方向的任意单位）。
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> snap(n, string(n,'.'));
    dfs(snap, n, 0, res);
    return res;
}
void dfs(vector<string>& snap, int n, int pos, vector<vector<string>>& res) {
    if (pos == n) {
        res.push_back(snap);
        return;
    }
    // 每行就是决策树的一层
    for (int i = 0; i < n; i++) {
        if (isValid(pos, i, n, snap)) {
            snap[pos][i] = 'Q';
            dfs(snap, n, pos+1, res);
            snap[pos][i] = '.';
        }
    }
}
// 不需要测试同行的，因为每次在第pos层只选择一个
// 检测顺序都是从上到下，左上和右上
bool isValid(int row, int col, int n, vector<string>& snap) {
    for (int i = 0; i < row; i++) {
        if (snap[i][col] == 'Q') {
            return false;
        }
    }
    for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++) {
        if (snap[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
        if (snap[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}




// 332 hard 一组pair，每组类似["JFK", "LGA"]，是src和dst的关系，出发点是"JFK"
// 存在多条路径，但取字典序最小的那条（就是dst小的那个）
// 如果用map<string,string>来统计路径，无法回避某个key对应多个value的情况
// 所以增加一个维度，使用map<string,map<string,int>>，最后一个int是到dst的次数
class Solution {
public:
unordered_map<string, map<string, int>> myMap;  // 要求dst有序
vector<string> res;
vector<string> findItinerary(vector<vector<string>>& tickets) {
    for (auto &ticket : tickets) {
        myMap[ticket[0]][ticket[1]] += 1;  // 到dst的路径+1
    }
    res.emplace_back("JFK");
    dfs(tickets);
    return res;
}
// 由于最终只有一条路径是对的，没有必要遍历完，所以用bool保证中途是对的话，直接不跑了
bool dfs(vector<vector<string>>& tickets) {
    if (res.size() == tickets.size()+1) return true;
    // 遍历res末尾元素可以到达的dst
    // key不能改，而且是引用。没有const就不能引用，得是复制
    for (pair<const string, int> &dst : myMap[res.back()]) {
    // for (auto &dst : myMap[res.back()]) {  // 也行
        if (dst.second) {
            res.emplace_back(dst.first);
            dst.second -= 1;
            if (dfs(tickets)) return true;
            dst.second += 1;
            res.pop_back();
        }
    }
    return false;  // 中间发小找不到dst的会跑到这一步
}
};


// 37 hard 解数独 保证只有唯一解
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
       dfs(board);
    }
    bool dfs(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') continue;
                for (char k = '1'; k <= '9'; ++k) {
                    if (isValid(board, i, j, k)) {
                        board[i][j] = k;
                        if (dfs(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    bool isValid(vector<vector<char>>& board, int row, int col, char val) {
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == val) return false;
        }
        for (int j = 0; j < 9; ++j) {
            if (board[row][j] == val) return false;
        }
        int r = (row/3)*3, c = (col/3)*3;
        for (int i = r; i < r+3; ++i) {
            for (int j = c; j < c+3; ++j) {
                if (board[i][j] == val) return false;
            }
        }
        return true;
    }
};