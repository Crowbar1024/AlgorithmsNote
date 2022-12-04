vector多次动态扩容时可以用list替换。
```c++
list<vector<int>> que;
for (int &num : nums) {
    auto it = que.begin();
    for(int i = 0; i < num; ++i) ++it;
    que.insert(it, num*num);
}
return vector<int>{que.begin(), que.end()};
```