// 结构化打印日期.cpp : 定义控制台应用程序的入口点。
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
	cout << "请输入年：";
	cin >> year;
	cout << "请输入月：";
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
	cout << endl << year << "年" << month << "月" << endl;
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
计算星期可以用蔡勒（Zeller）公式（只适合于1582年10月15日之后的情形）：
w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
w=y+[y/4]+[c/4]-2c+[26(m+1）/10]+d-1
公式中的符号含义如下：
c：世纪（年的高两位数）；
y：年（年的低两位数）；
m：月（m大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月
来计算，比如2005年1月1日要看作2004年的13月1日来计算）；
d：日；
[]代表取整，即只要整数部分。
w：星期；w对7取模得：0-星期日，1-星期一，2-星期二，3-星期三，4-星期四，
5-星期五，6-星期六
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
	for (int i = 0; i < 7; i++)//将日历的星期几显示出来
	{
		setWidth(a);
		cout << s[i];
	}
	cout << endl;
	setWidth(week*a);//根据第一天是星期几来缩进空格
	cout << "";
	for (int i = 1; i <= days; i++)//从1号开始打印，显示宽度为a=8;
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
