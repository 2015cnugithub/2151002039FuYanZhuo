// �ṹ����ӡ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

void input(int &year, int &month);
void output(int year, int month);
void printHead(int year, int month);
void printDate(int year, int month);
int DaysofMonth(int year, int month);
bool IsLeapYear(int year);
int getFirstWeek(int year, int month);
void show(int days, int firstWeek);

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	int year, month;
	input(year, month);
	output(year, month);
	cout << endl;
	return 0;
}

void input(int &year, int &month)
{
	cout << "�������꣺";
	cin >> year;
	cout << "�������£�";
	cin >> month;
}
void output(int year, int month)
{
	printHead(year, month);
	printDate(year, month);
}
void printHead(int year, int month)
{
	cout.width(30);
	cout << endl << year << "��" << month << "��" << endl;
}
void printDate(int year, int month)
{
	int days=DaysofMonth(year, month);
	int firstWeek=getFirstWeek(year, month);
	show(days, firstWeek);
}
int DaysofMonth(int year, int month)
{
	switch (month)
	{
	case 2:
		if (IsLeapYear(year))
			return 29;
		else return 28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30; 
		break;
	default:
		return 31;
		break;
	}
}
bool IsLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? true : false);
}
/*
�������ڿ����ò��գ�Zeller����ʽ��ֻ�ʺ���1582��10��15��֮������Σ���
w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
w=y+[y/4]+[c/4]-2c+[26(m+1��/10]+d-1
��ʽ�еķ��ź������£�
c�����ͣ���ĸ���λ������
y���꣨��ĵ���λ������
m���£�m���ڵ���3��С�ڵ���14�����ڲ��չ�ʽ�У�ĳ���1��2��Ҫ������һ���13��14��
�����㣬����2005��1��1��Ҫ����2004���13��1�������㣩��
d���գ�
[]����ȡ������ֻҪ�������֡�
w�����ڣ�w��7ȡģ�ã�0-�����գ�1-����һ��2-���ڶ���3-��������4-�����ģ�
5-�����壬6-������
*/
int getFirstWeek(int year, int month)
{
	int c, y, m,d=1;
	int week;
	if (month == 1)
	{
		m = 13;
		year--;
	}
	else if (month == 2)
	{
		m = 14;
		year--;
	}
	else
		m = month;
	c = year / 100;
	y = year % 100;
	//w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
	week = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
	while (week<0){ week += 7; }
	return week % 7;
}
void setWidth(int a)
{
	cout << setw(a) << setfill(' ');
}
void show(int days, int firstWeek)
{
	int const a = 8;
	int week = firstWeek;
	string s[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	for (int i = 0; i < 7; i++)//�����������ڼ���ʾ����
	{
		setWidth(a);
		cout << s[i];
	}
	cout << endl;
	setWidth(week*a);//���ݵ�һ�������ڼ��������ո�
	cout << "";
	for (int i = 1; i <= days; i++)//��1�ſ�ʼ��ӡ����ʾ���Ϊa=8;
	{
		setWidth(a); cout << i;
		week++;
		if (week == 7)
		{
			cout << endl;
			week = 0;
		}
	}
}
