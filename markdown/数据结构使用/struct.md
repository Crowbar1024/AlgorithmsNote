### struct 赋值
```c++
struct point {
    int x;
    int y;
    point(int _x, int _y) : x(_x), y(_y) {}
};
for (int n : v) {
    point tmp = {1, n}; r.push_back(tmp);
    r.push_back((point){1,n});
    r.push_back(point{1,n});
    r.push_back({1,n});  // 我一般用这种
}
```

### vector初始化
```c++
struct myMatrix {
    vector<int> mat;
    myMatrix() : mat(vector<int>(4,0)) {}
};
```