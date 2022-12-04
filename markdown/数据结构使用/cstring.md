cstring中字符串一般都是char *


### strcasecmp
比较两个字符串是否相等，\0结尾。
```c++
if (strcasecmp(method,"GET") == 0)
```

### strcasecmp
strcasecmp指定位数
```c++
if (strncasecmp(m_url,"http://",7) == 0)
```

### strpbrk
在源字符串（s1）中找出最先含有搜索字符串（s2）中任一字符的位置并返回，若找不到则返回空指针。
```c++
这里面s2里面有空格和tab，用于分析请求行
char *m_url = strpbrk(text, " \t");
```


### strspn
检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
```c++
// m_url此时指向的是第一个空格后的一个字符，但不知道之后是否还有，将m_url向后偏移，通过查找，继续跳过空格和\t字符，指向请求资源的第一个字符
m_url += strspn(m_url, " \t");
```


### strchr
该函数返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL。
```c++
char *strchr(const char *str, int c);

// m_url 为http://www.runoob.com/aa.jpg，找到目标/aa.jpg
m_url = strchr(m_url,'/');

```

### atol
把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。
```c++
long int atol(const char *str);

m_content_length = atol(text);
```