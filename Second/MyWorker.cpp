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
	char sex;//M�����У�W��ʾŮ
	double pay_per_hou;//Сʱ���ʶ�
};
ostream& operator <<(ostream& out,Worker& worker)
{
	return out<<"����:"<<"\t����:"<<"\t�Ա�:"<<"\tСʱ���ʶ�:"<<endl
		<<worker.name
		<<"\t"<<worker.age
		<<"\t"<<(worker.sex=='M'?"��":"Ů")
		<<"\t"<<worker.pay_per_hou
		<<(worker.pay_per_hou==30||worker.pay_per_hou==50?"(��нԱ��)":"(��ʱԱ��)")<<endl<<endl;
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
/*��ʱ������
*��ʱ���˵�н��ȼ���Ϊ10��20��40 US$/hour�����ȼ�
���ÿ�ܵĹ���ʱ����hours����40���ڣ�����н = Сʱ���ʶ� �� ʵ�ʹ���ʱ����
���ÿ�ܵĹ���ʱ����hours������40������н = Сʱ���ʶ� �� 40 + 1.5 �� Сʱ
���ʶ� ����ʵ�ʹ���ʱ�� - 40����

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
	cout<<this->name<<"�ļ�ʱн��:"<<sum<<endl;
}
//////////////////////////////////////////////////////////////////////////
/*��н������
��н���˵�н��ȼ�����Ϊ30��50 US$/hour�����ȼ���
���ÿ�ܵ�ʵ�ʹ���ʱ��������35Сʱ����40Сʱ����н�������а�������յ�
��/���٣�������40Сʱ���ֲ���н������н = Сʱ���ʶ� �� 40��
���ÿ�ܵ�ʵ�ʹ���ʱ������35Сʱ������35Сʱ��������н = Сʱ���ʶ�  ʵ
�ʹ���ʱ�� + 0.5 �� Сʱ���ʶ� �� (35 - ʵ�ʹ���ʱ��)��
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
	cout<<"��нн��:"<<sum<<endl;
}
//////////////////////////////////////////////////////////////////////////
/*
ͨ��һ���˵��ṹʵ����5�������п�������ѡ��һ�����ˣ���ʾ�ù��˵Ļ�
����Ϣ������ÿ�ܵ�ʵ�ʹ���ʱ����ͨ������̨���룩���㲢��ʾ�ù��˵���н��
ֱ��ѡ���˳�������
*/
void setHours(Worker &work)//���ù��˵Ĺ���ʱ��
{
	cout<<"������ù��˵Ĺ���ʱ��:";
	double hours;
	cin>>hours;
	cout<<endl;
	work.Compute_pay(hours);//���ù��˵�
}
int main()
{
	Worker *work[5];
	cout<<"***************ע����Ϣ**************"<<endl;
	int i;
	for(i=0;i<5;i++) 
	{
		cout<<(i+1)<<"������  ����  �Ա�(M:�У�W:Ů)  Сʱ���ʶ�(30,50Ϊ��нԱ��,10,20,40Ϊ��ʱԱ��)"<<endl;
		char name[10];int age;char sex;double pay;
		cin>>name>>age>>sex>>pay;//ע�Ṥ�˵���Ϣ
		if(pay==30||pay==50)//����ע��ĵ�Сʱ���ʶͬ��������ͬ�Ķ���
		{
			work[i]=new SalariedWorker;
			cout<<"��н����ע��ɹ���"<<endl;
		}
		else
		{
			work[i]=new HourlyWorker;
			cout<<"��ʱ����ע��ɹ���"<<endl;
		}
		work[i]->setWorker(name,age,sex,pay);//ע����ϵĹ��˳�ʼ��
		
	}
	system("cls");
	for(i=0;i<5;i++)
		cout<<(*work[i]);
	int cinflag=1;//ѡ���ǣ����ж�ѡ���ĸ���
	while (cinflag)
	{
		cout<<"\t"<<"\n��ѡ���˵���Ϣ(1-5��ѡ��0���˳�ѡ��):\n"<<endl;
		for (int i=0;i<5;i++)//��ʾ����Ա��������
		{
			cout<<(i+1)<<"��";
			(*work[i]).getName();
			cout<<"  ";
		}cout<<endl;
		cin>>cinflag;//����Ҫѡ�������
		system("cls");
		switch(cinflag)//���Ϊ0���˳�
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
