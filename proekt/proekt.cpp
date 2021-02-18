#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class Order
{
	string m_NameOrder;
	string m_AboutOrder;
	map<string, float>m_SkladOrder;
	int m_PriceOrder;
public:
	Order(string name, map<string,float>sklad,int price){}//todo
	int getPrice() { return m_PriceOrder; }
	string getName() { return m_NameOrder; }
	void Show()
	{}
};
class Restoran
{
protected:
	string m_NameRestoran;
	string m_Street;
	vector<Order>m_Menu;
	int m_OpenTime;
	int m_CloseTime;
};
class Person :public Restoran
{
protected:
	string m_Name;
	int m_Age;
	string m_Sex;
public:
	virtual void EditOrBuy(string) = 0;
	virtual void DelOfMenu_or_DelOfBasket() = 0;
	virtual void ShowInfoOfTime_or_setInfoTime() = 0;
};
class Admin: public Person
{
	
public:
	void EditOrBuy(string nameOrder) override
	{
		for(auto i :m_Menu)
			if (i.getName()==nameOrder)
			{
				//setName
				//setAbout
				//setSklad ....
			}
	}
};
class User : public Person
{
	vector<Order>Basket;
	string m_street;
	int m_MaxCash;
public:
	void EditOrBuy(string nameOrder) override
	{
		for (auto i : m_Menu)
			if (i.getName() == nameOrder)
			{
				Basket.push_back(i);
			}
		///////todo
	}
};