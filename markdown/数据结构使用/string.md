# string

底层是指向真正字符串的指针
[find底层原理](https://www.zhihu.com/question/392846851/answer/1211500754)
### 初始化
```c++
string s(n,'.');  // n个'.'

string s = s1;  // 浅拷贝，和vector的=操作差不多

char chs[10] = "12345";
string b(s,s+4);  // 复制char数组前4个
```
### 遍历
```c++
for (auto c:str)  // char

// .size()的类型是非负整数string:type_size
for (decltype(s.size()) index = 0; index != s.size(); index++)
    s[index] = toupper(s[index]);  // tolower

for (auto a = s.begin(); a != s.end(); a++)
    *a = toupper(*a);  
```
### 小函数
```c++
// 查找从pos开始的"xx"出现的位置，没有pos就是第一个
auto pos = s.find("xx", pos);
if (pos != string::npos)  // 找不到

// 截取从pos开始的n个字符拷贝并返回，没有n就是从pos开始的全部字符，注意s没变
b = s.substr(pos, n);

// 删除，没写end就是那一个，原来位置的被挤到后面
s.erase(begin,end)

// 两个字符串比较
a == b
a.compare(b)

// 插入，返回插入的位置
it = s.insert(s.begin()+5, '.')

// 数字与string的转换，浮点也行
string s = to_string(num);
int v = stoi(s);

// 判断是否是个数，得自己实现
bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


```

### 排序
```c++
// 多个字符串拼接在一起，按字典序排列的快速方法
bool cmp0(string a, string b) {    // 这里就不太适合常量引用
    return a + b < b + a;
}
```

### 模拟栈
```c++
string s;
s.empty();  // 是否为空
s.back();  // 栈顶
s.push_back(ch);
s.pop_back();
```