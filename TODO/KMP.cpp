//-----------------------------------������˵����----------------------------------------------
//  ��������:��dealWithString
//	2016��10��27������ 28���賿 Create by Ҧ�
//  �������ַ����Ļ���KMP�㷨�Ļ����������������ң����룬ɾ��
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
		j = Next[i-1];		//��j����ǰһ���ַ���nextֵ
		while(a[j+1] != a[i] && j >= 0)		//���a[i]�Ƿ��������ǰ׺���һλ����һλ�������û���⣬������j�˻ص�ԭ����nextֵ
			j = Next[j];
		if(a[j+1] == a[i])		//����ǰ׺���һλ����һλ���ڸõ㣬�õ�ĶԳ��ԣ�ǰ������������׺���ȣ�����j�ĶԳ���+1
			Next[i] = j+1;	
		else		//˵����λ�öԳ��Բ�����
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
	if(place < 0 || place > l1)		//�����ж�
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
	if(place < 0 || place > len)		//�����ж�
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
	//KMP�㷨���ң������Ӵ���Ԫ���±��ڸ����е�λ�ã�����-1��ʾû�ҵ�
	
	cout << "please input two string each line:" << endl;
	string src1, subs1;
	getline(cin, src1);		//��ȡ�����ַ���
	getline(cin, subs1);
	get_Next(subs1);		//��ȡ�Ӵ���next[]
	int result = KMP(src1, subs1);		//��ȡ�ҵ�Ԫ�ص��±�
	cout << result << endl;
	

	//������������ز���ɹ�����ַ��������򱨴�
	
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


	//KMPɾ������������ɾ���ɹ�����ַ���(����ɾ�����)�����򱨴�
	
	cout << "Please input one string one line, then input the subString to delete" << endl;
	string src3, sub3;
	getline(cin, src3);
	getline(cin, sub3);
	char* temp = deleteStringUsingKMP(src3, sub3);
	cout << temp << endl;
	delete[] temp;

	return 0;
}