# stringstream
主要用途是做类型转换，用以代替之前标准的sprintf等


### 从字符串中获得int
```c++
string s = "0123";
stringstream ss(s);
int num;
ss >> num;  // num: 123
// 如果是0x123，还是44xx，会返回到异常符号前的数，即0，44
```


### 将int变成string
```c++
int num;
ss << num;
string s;
ss >> s;
```


### 将每行的数字加起来
```c++
string s;
stringstream ss;
int n, i, sum, a;
cin >> n;
getline(cin, s); // 读取换行
for (i=0; i<n; i++)
{
    getline(cin, s);
    ss.clear();
    ss.str(s);
    sum=0;
    while (1)
    {
        ss >> a;
        if ( ss.fail() ) break;
        sum+=a;
    }
    cout << sum << endl;
}
```


### 是否符合IP地址的某个字段（0~255）
```c++
bool isValid(string &s) {
    if (s.empty()) return false;
    stringstream ss(s);
    int num;
    ss >> num;
    return s[0]!='0' && num>=0 && num<=255;
}
```