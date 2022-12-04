//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：dealWithString
//	2016年10月27日下午 28日凌晨 Create by 姚昊
//  描述：字符串的基于KMP算法的基本操作，包含查找，插入，删除
//------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>

using namespace std;

const int maxn = 30;
int Next[maxn];

void get_Next(string a)
{
	int i, j;
	Next[0] = -1;
	for(int i = 1; i < a.length(); i++)
	{
		j = Next[i-1];		//另j等于前一个字符的next值
		while(a[j+1] != a[i] && j >= 0)		//检测a[i]是否等于序列前缀最后一位的下一位，如果是没问题，否则另j退回到原来的next值
			j = Next[j];
		if(a[j+1] == a[i])		//序列前缀最后一位的下一位等于该点，该点的对称性（前后子序列最大后缀长度）等于j的对称性+1
			Next[i] = j+1;	
		else		//说明该位置对称性不存在
			Next[i] = -1;
	}
}

int KMP(string src, string subs)
{
	int i = 0, j = 0;
	while(i < src.length() && j < subs.length())
	{
		if(src[i] == subs[j])
		{
			i++;
			j++;
		}
		else
		{
			if(j == 0)
				i++;
			else
				j = Next[j-1] + 1;
		}
	}
	return (j == subs.length()) ? (i - subs.length()) : -1;
}

char* insertString(string str, int place, string tp)
{
	int l1 = str.length();
	int l2 = tp.length();
	if(place < 0 || place > l1)		//错误判断
	{
		cout << "Out of range!" << endl;
		return NULL;
	}
	char* fs = new char[l1+l2+1];
	for(int i = 0; i < place; i++)
		fs[i] = str[i];
	for(int i = place; i < place+l2; i++)
		fs[i] = tp[i-place];
	for(int i = place+l2; i < l1+l2; i++)
		fs[i] = str[i-l2];
	fs[l1+l2] = '\0';
	return fs;
}

char* deleteString(string str, int place, int deleteNumber)
{
	int len = str.length();
	if(place < 0 || place > len)		//错误判断
	{
		cout << "Out of range!" << endl;
		return NULL;
	}
	char* fs = new char[len-deleteNumber+1];
	for(int i = 0; i < place; i++)
		fs[i] = str[i];
	int rest = len -place - deleteNumber;
	if(rest <= 0)
	{
		fs[place] = '\0';
		return fs;
	}
	else
	{
		for(int i = 0; i < rest; i++)
			fs[place+i] = str[i+deleteNumber+place];
		fs[place+rest] = '\0';
		return fs;
	}
}

char* deleteStringUsingKMP(string str, string subs)
{
	get_Next(subs);
	int lenOfSub = subs.length();
	int circleOfIndex = KMP(str, subs);
	char* temp;
	do
	{
		temp = deleteString(str, circleOfIndex, lenOfSub);
		str = temp;
		circleOfIndex = KMP(str, subs);
	} while(circleOfIndex != -1);
	return temp;
}

int main()
{
	//KMP算法查找，返回子串首元素下标在父串中的位置，返回-1表示没找到
	
	cout << "please input two string each line:" << endl;
	string src1, subs1;
	getline(cin, src1);		//获取两行字符串
	getline(cin, subs1);
	get_Next(subs1);		//获取子串的next[]
	int result = KMP(src1, subs1);		//获取找到元素的下标
	cout << result << endl;
	

	//插入操作，返回插入成功后的字符串，否则报错
	
	cout << "First input one string one line, then input the indexOfInsertString, then input the subString to Insert." << endl; 
	int place;
	string str2, sub2;
	getline(cin, str2);
	cin >> place; 
	cin.get();
	getline(cin, sub2);
	char* c1 = insertString(str2, place, sub2);
	if(c1)
		cout << c1 << endl;
	delete[] c1;


	//KMP删除操作，返回删除成功后的字符串(可以删除多个)，否则报错
	
	cout << "Please input one string one line, then input the subString to delete" << endl;
	string src3, sub3;
	getline(cin, src3);
	getline(cin, sub3);
	char* temp = deleteStringUsingKMP(src3, sub3);
	cout << temp << endl;
	delete[] temp;

	return 0;
}