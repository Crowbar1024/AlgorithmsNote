#include <myheader.h>


// 前缀树有多种应用，最多是在查找某个字符串数组中是否存在某个字符串或者字符串的前缀
// 实现方法有多种
// 这里写了一种最常见的方法，即把node和tree分开

// medium 208
class TrieNode {
public:
    TrieNode* children[26];  // 26char
    bool isEnd;
    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
        // memset(children, 0, sizeof(children));  // 也可以，我觉得不太安全
    }
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear(root);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* cur = root;
        for (char ch : word) {
            int id = ch - 'a';
            if (cur->children[id] == nullptr) {
                cur->children[id] = new TrieNode();
            }
            cur = cur->children[id];
        }
        cur->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* cur = find(word);
        return cur != nullptr && cur->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* cur = find(prefix);
        return cur != nullptr;
    }

private:
    TrieNode* root;
    TrieNode* find(string word) {  // search和startsWith太像了，所以使用一个辅助函数
        TrieNode* cur = root;
        for (char ch : word) {
            int id = ch - 'a';
            if (cur->children[id] == nullptr) {
                return nullptr;
            }
            cur = cur->children[id];
        }
        return cur;
    }
    void clear(TrieNode *cur) {  // 确保删除干净
        for(int i = 0; i < 26; i++){
            if (cur->next[i] != nullptr){
                clear(cur->next[i]);
            }
        }
        delete cur;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


/* 
    如果node不分开，全部写在一起，会有以下变化
    私有变量的改变，当然可以写进创构
    Trie* next[26] = {};
    bool isword = false;
    新建的改变
    Trie* node = this;
    node->next[ch] = new Trie();
*/

/*
    如果不用数组用map，并且写在一起
    map<char, Trie*> next = {};
    bool isword = false;
    if (!node->next.count(ch)) { node->next[ch] = new Trie(); }
    node = node->next[ch];
    其实也没多少改变
*/