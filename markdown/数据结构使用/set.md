# set

# set

1.  容器，内部排序，元素唯一。由于这个性质，set可以视为unique后的优先队列

2.  内部实现时，里面的元素是常量，所以不能修改，但可以添加或者删除

3.  排序方法：strict weak ordering criterion 默认是非降序

4.  通过key去获取元素比unordered\_set慢，but they allow the direct iteration on subsets based on their order.

5.  内部实现 binary search trees.

# unordered\_set

1.  容器，元素唯一。元素的值同时也是唯一标识元素的键。

2.  内部实现时，里面的元素是常量，所以不能修改，但可以添加或者删除

3.  没有特别的排序方式，根据hash值进行bucket排序，所以对unordered\_set的元素访问都是常数级的，当然最差情况就是线性

4.  对子集元素的遍历效率较低

5.  只有正向迭代（这个正向只是根据bucket的hash值来说）

```c++
// 初始化
set<int> s(arr.begin(), arr.end());  // 用一个vector来做初始化

// 插入
set.insert(val);    // 插入了单个元素，时间复杂度为对数级（参考BST的插入）
set.insert(v.begin(), v.end());  // Nlog(size+N)。如果已经排好序了，更快
    
// 返回值：pair<set<int>::iterator,bool>
set.insert(val).first    // 如上，指向新插入的位置的迭代器
set.insert(val).second    // 插入是否成功，可以用来判断是否重复

// 删除
set.erase(it);  // 常数级
set.erase(val);  // 对数级，根据BST的性质
set.erase(set.find(3), set.end());  // 线性级，begin()到end()的距离

// 查找
set.count(val);  // 对数级，返回0/1
set.find(val)  // 对数级，返回迭代器
set.count(val) == 0 // 找不到
set.find(val) != set.end()  // 找不到
// set特有，因为哈希版本没有排序。
set.lower_bound(val);  // 对数级
set.upper_bound(val); 

// 迭代
// unordered_set特有的对桶里面的遍历
for (auto i = 0; i != myset.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for (auto local_it = myset.begin(i); local_it!= myset.end(i); ++local_it )
      std::cout << " " << *local_it;
}
// 反的迭代器 std::set<int>::reverse_iterator
for (auto rit = myset.rbegin(); rit != myset.rend(); ++rit) {
    std::cout << ' ' << *rit;
}

```
