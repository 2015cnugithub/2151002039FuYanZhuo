#include <iostream>
#include<string.h>
using namespace std;

class CGoods
{
public:
	CGoods(long theNo,char *theName,double thePrice);
	CGoods(const CGoods& good);
	~CGoods();
	void showGoods();
	friend string getName(CGoods &cg);
	bool operator <(CGoods &goods);//<
	bool operator >=(CGoods &goods);//>=
	virtual void usedFor();
protected:
	char *p_brand;
private:
	long no;
	char *p_name;
	double price;
	static int count;
};
//////////////////////////////////////////////////////////////////////////

int CGoods::count=0;//静态变量初始化
CGoods::CGoods(long theNo,char *theName,double thePrice)
{
	no=theNo;
	p_name=new char[strlen(theName)+1];
	strcpy(p_name,theName);
//	p_name=theName;
	price=thePrice;
	++count;
}

CGoods::CGoods(const CGoods &good)
{
	no=good.no;
	price=good.price;
	p_name=new char[strlen(good.p_name)+1];
	if (p_name)
		strcpy(p_name,good.p_name);
}
CGoods::~CGoods()
{
	if (p_name)
	{	
		delete[] p_name;
	}

}
void CGoods::showGoods()
{
	cout<<"no:"<<no<<endl
		<<"name:"<<p_name<<endl
		<<"price:"<<price<<endl;
}
string getName(CGoods &cg)
{
	return cg.p_name;
}
bool CGoods::operator <(CGoods &goods)
{
	return(this->price<goods.price? true:false);
}
bool CGoods::operator >=(CGoods &goods)
{
	return (this->price>=goods.price?true:false);
}
void CGoods::usedFor()
{
	cout<<"base class usedFor"<<endl;
}
//////////////////////////////////////////////////////////////////////////
class CClothes:public CGoods
{
public:
	void usedFor();
	CClothes(char* brand,long theNo,char *theName,double thePrice);
	~CClothes();
protected:
private:
	//char *p_brand;
};
CClothes::CClothes(char* brand,long theNo,char *theName,double thePrice):CGoods(theNo,theName,thePrice)
{
	p_brand=new char[strlen(brand)+1];
	strcpy(p_brand,brand);
}
CClothes::~CClothes()
{
	if(p_brand)
		delete[] p_brand;
}
void CClothes::usedFor()
{
	cout<<"CClothes class usedFor  "<<p_brand<<endl;
}
//////////////////////////////////////////////////////////////////////////
class CFood:public CGoods
{
public:
	void usedFor();
	CFood(char* brand,long theNo,char *theName,double thePrice);
	~CFood();
protected:
private:
	//char *p_brand;
};
CFood::CFood(char* brand,long theNo,char *theName,double thePrice):CGoods(theNo,theName,thePrice)
{
	p_brand=new char[strlen(brand)+1];
	strcpy(p_brand,brand);
}
CFood::~CFood()
{
	if(p_brand)
		delete[] p_brand;
}
void CFood::usedFor()
{
	cout<<"CFood class usedFor  "<< p_brand<<endl;
}
//////////////////////////////////////////////////////////////////////////

int main()
{
	CGoods cd(1101,"book",1);
	CGoods cd1(cd);
	cd.showGoods();
	cout<<getName(cd)<<endl;
	CGoods cd2(1102,"iphone",2);
	cd2.showGoods();
	
	if (cd<cd2)
	{
		cout<<"cd<cd2"<<endl;
	}
	else
		cout<<"cd>=cd2"<<endl;
	CGoods *p;
	CClothes cc1("naike",1101,"clothes",555);
	//cc1.usedFor();
	p=&cd;
	//运行时的多态 
	cd.usedFor();
	p=&cc1;
	p->usedFor();
	//CClothes c2;

}
