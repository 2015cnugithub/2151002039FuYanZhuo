#include <iostream>
#include<iomanip>
#include <string.h>
using namespace std;
class Worker
{
public:

	virtual	void setWorker(char *name,int age,char sex,double pay);
	virtual void Compute_pay(double hours) = 0;
	friend ostream& operator <<(ostream& out, Worker& worker);
	void getName()
	{
		cout<<name<<"   ";
	}
	
private:
protected:
	char *name;
	int age;
	char sex;//M便是男，W表示女
	double pay_per_hou;//小时工资额
};
ostream& operator <<(ostream& out,Worker& worker)
{
	return out<<"姓名:"<<"\t年龄:"<<"\t性别:"<<"\t小时工资额:"<<endl
		<<worker.name
		<<"\t"<<worker.age
		<<"\t"<<(worker.sex=='M'?"男":"女")
		<<"\t"<<worker.pay_per_hou
		<<(worker.pay_per_hou==30||worker.pay_per_hou==50?"(计薪员工)":"(计时员工)")<<endl<<endl;
}
void Worker::setWorker(char *name,int age,char sex,double pay)
{
	this->name=new char[strlen(name)+1];
	if(this->name)
		strcpy(this->name,name);
	this->age=age;
	this->sex=sex;
	this->pay_per_hou=pay;
}
//////////////////////////////////////////////////////////////////////////
/*计时工人类
*计时工人的薪金等级分为10、20和40 US$/hour三个等级
如果每周的工作时数（hours）在40以内，则周薪 = 小时工资额 × 实际工作时数；
如果每周的工作时数（hours）超过40，则周薪 = 小时工资额 × 40 + 1.5 × 小时
工资额 ×（实际工作时数 - 40）。

*/
class HourlyWorker:public Worker
{
public:
	void Compute_pay(double hours);
	~HourlyWorker()
	{
		if(name)
			delete []name;
	}
protected:
private:
};
void HourlyWorker::Compute_pay(double hours)
{
	double sum=0;
	if (hours<=40)
	{
		sum=pay_per_hou*hours;
	}
	else
	{
		sum=pay_per_hou*(40+1.5*(hours-40));
	}
	cout<<this->name<<"的计时薪资:"<<sum<<endl;
}
//////////////////////////////////////////////////////////////////////////
/*计薪工人类
计薪工人的薪金等级，分为30和50 US$/hour两个等级。
如果每周的实际工作时数不少于35小时，则按40小时计周薪（允许有半个工作日的
事/病假），超出40小时部分不计薪，即周薪 = 小时工资额 × 40；
如果每周的实际工作时数少于35小时（不含35小时），则周薪 = 小时工资额  实
际工作时数 + 0.5 × 小时工资额 × (35 - 实际工作时数)。
*/
class SalariedWorker:public Worker
{
public:
	void Compute_pay(double hours);
	~SalariedWorker()
	{
		if(name)
			delete []name;
	}
protected:
private:
};
void SalariedWorker::Compute_pay(double hours)
{
	double sum=0;
	if (hours>=35)
	{ 
		hours=40;
		sum=hours*pay_per_hou;
	}
	else
	{
		sum=pay_per_hou*(hours+0.5*(35-hours));
	}
	cout<<"计薪薪资:"<<sum<<endl;
}
//////////////////////////////////////////////////////////////////////////
/*
通过一个菜单结构实现在5个工人中可以任意选择一个工人，显示该工人的基
本信息，根据每周的实际工作时数（通过控制台输入）计算并显示该工人的周薪。
直至选择退出操作。
*/
void setHours(Worker &work)//设置工人的工作时间
{
	cout<<"请输入该工人的工作时间:";
	double hours;
	cin>>hours;
	cout<<endl;
	work.Compute_pay(hours);//调用工人的
}
int main()
{
	Worker *work[5];
	cout<<"***************注册信息**************"<<endl;
	int i;
	for(i=0;i<5;i++) 
	{
		cout<<(i+1)<<"、姓名  年龄  性别(M:男，W:女)  小时工资额(30,50为计薪员工,10,20,40为计时员工)"<<endl;
		char name[10];int age;char sex;double pay;
		cin>>name>>age>>sex>>pay;//注册工人的信息
		if(pay==30||pay==50)//根据注册的的小时工资额不同来创建不同的对象
		{
			work[i]=new SalariedWorker;
			cout<<"计薪工人注册成功！"<<endl;
		}
		else
		{
			work[i]=new HourlyWorker;
			cout<<"计时工人注册成功！"<<endl;
		}
		work[i]->setWorker(name,age,sex,pay);//注册完毕的工人初始化
		
	}
	system("cls");
	for(i=0;i<5;i++)
		cout<<(*work[i]);
	int cinflag=1;//选择标记，来判断选择哪个人
	while (cinflag)
	{
		cout<<"\t"<<"\n请选择工人的信息(1-5：选择0：退出选择):\n"<<endl;
		for (int i=0;i<5;i++)//显示所有员工的名称
		{
			cout<<(i+1)<<"、";
			(*work[i]).getName();
			cout<<"  ";
		}cout<<endl;
		cin>>cinflag;//输入要选择的姓名
		system("cls");
		switch(cinflag)//如果为0则退出
		{
		case 0:break;
		case 1:cout<<*work[cinflag-1];setHours(*work[cinflag-1]);break;
		case 2:cout<<*work[cinflag-1];setHours(*work[cinflag-1]);break;
		case 3:cout<<*work[cinflag-1];setHours(*work[cinflag-1]);break;
		case 4:cout<<*work[cinflag-1];setHours(*work[cinflag-1]);break;
		case 5:cout<<*work[cinflag-1];setHours(*work[cinflag-1]);break;
		}
	}
	system("pause");
}
