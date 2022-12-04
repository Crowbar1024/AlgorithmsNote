#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <functional>
#include <atomic>
#include <sstream>
#include <unordered_set>
#include <numeric>

using namespace std;

/*
    1   3   
    1   3 5 
    1 2 3 5 6 7
    head节点，val为1，vector的长度是3，v[i]表示第i个level对应的下一个节点
*/



class Skiplist {
public:
    struct ListNode {
        int val;
        vector<ListNode*> next;
        ListNode(int val_, int level) : val(val_), next(level) {}
    };

    Skiplist() {
        head = new ListNode(0, MAXLEVEL);
    }
    
    // 在curLevel这一层找到恰好比target小的节点
    ListNode* findPre(ListNode* node, int curlevel, int target) {
        while (node->next[curlevel] != nullptr && node->next[curlevel]->val < target) {
            node = node->next[curlevel];
        }
        return node;
    }

    bool search(int target) {
        ListNode *cur = head;
        // 从最上面那个level开始搜索
        for (int i = height-1; i >= 0; --i) {
            cur = findPre(cur, i, target);
            if (cur->next[i] != nullptr && cur->next[i]->val == target) {
                return true;
            }
        }
        return false;
    }
    

    void add(int num) {
        int level = generateRand();
        ListNode *cur = head;
        ListNode* node = new ListNode(num, level);
        for (int i = height-1; i >= 0; --i) {
            cur = findPre(cur, i, num);
            if (i < level) {
                if (cur->next[i] == nullptr) {
                    cur->next[i] = node;
                } else {
                    ListNode* tmp = cur->next[i];
                    cur->next[i] = node;
                    node->next[i] = tmp;
                }
            }
        }
        // 比如level = 4，表示3级索引，此时height = 3
        if (level > height) {
            for (int i = height; i < level; ++i) {
                head->next[i] = node;
            }
            height = level;
        }
    }
    
    bool erase(int num) {
        ListNode *cur = head;
        ListNode* node = nullptr;
        bool flag = false;
        for (int i = height-1; i >= 0; --i) {
            cur = findPre(cur, i, num);
            if (cur->next[i] != nullptr && cur->next[i]->val == num) {
                if (node == nullptr) node = cur->next[i];
                flag = true;
                cur->next[i] = cur->next[i]->next[i];
                continue;
            }
        }
        delete node;
        return flag;
    }



private:
    const int MAXLEVEL = 32;
    const int P = 0.25;
    int height = 1;  // 表示当前只有一层
    ListNode *head;

    /*
        返回 1 表示当前插入的该元素不需要建索引，只需要存储数据到原始链表即可（概率 1/2）
        返回 2 表示当前插入的该元素需要建一级索引（概率 1/4）
        返回 3 表示当前插入的该元素需要建二级索引（概率 1/8）
        以此类推
    */
    int generateRand() {
        int level = 1;
        while (rand() < P && level < MAXLEVEL) {
            ++level;
        }
        return level;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */