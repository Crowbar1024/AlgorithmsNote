# map

1.  用来存储和区别的是key,strict weak ordering criterion

2.  通过key去获取元素比unordered\_map慢，but they allow the direct iteration on subsets based on their order.

3.  内部实现 binary search trees.

4.  可以使用下标访问

同set，map是有序的。

# unordered_map

1.  看了下官网，这个容器内部使用hash的bucket，所以查找比map快，尽管通常在通过其元素子集进行范围迭代时效率较低。（毕竟map有个compare用来排列内部key ）

2.  所以前者的find时间是mapsize的对数级，后者是常数，当然，最坏的情况就是mapsize

```c++
// 初始化
map<int, string> m;  
unordered_map<int, string> m;
unordered_map<int, int> m(5); // 桶数是5

// 插入
m.insert(pair<int, string>(1, "student_one"));  
m.insert(map<int, string>::value_type (2, "student_two"));  
m[3] = "student_three"; // override is ok, 2 method above can't
m[i]++;  // if <int,int>

// 遍历
for(map<int, string>::iterator iter = m.begin(); iter != m.end(); iter++)  
    cout<<iter->first<<' '<<iter->second<<endl;    // (*it).first
for(int nindex = 1; nindex <= mapStudent.size(); nindex++)    // 由下标来遍历，带有size()
    cout<<mapStudent[nindex]<<endl;  

// 查找
iter = mapStudent.find(1);
int cnt = mapStudent.count(1);    // 无法定位数据出现位置.

// 删除
mapStudent.erase(iter);  
int n = mapStudent.erase(1);////如果要删除1，用关键字删除  如果删除了会返回1，否则返回0  
mapStudent.erase( mapStudent.begin(), mapStudent.end() );  
```

unordered\_map如何避免哈希冲突

[https://leetcode-cn.com/circle/discuss/H9EIRG/](https://leetcode-cn.com/circle/discuss/H9EIRG/ "https://leetcode-cn.com/circle/discuss/H9EIRG/")
