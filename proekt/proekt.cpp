﻿#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
class Dish
{
	string m_NameDish;
	string m_AboutDish;
	map<string, float>m_SkladDish;
	int m_PriceDish;
public:
	Dish(string name,string about, map<string, float>sklad, int price):
		m_NameDish(name), m_AboutDish(about),m_SkladDish(sklad),m_PriceDish(price){}
	int getPrice() { return m_PriceDish; }
	string getName() { return m_NameDish; }
	string getAbout() { return m_AboutDish;}
	void Show(bool withoutSklad = true)
	{
		cout << "Dish: " << m_NameDish << " - " << m_AboutDish << "!" << endl;
		cout << "Price: " << m_PriceDish << endl;
		if (withoutSklad)
		{
			cout << "=======Sklad========\n";
			cout << "Stepan" << endl;
			for_each(m_SkladDish.begin(), m_SkladDish.end(), 
				[&](pair<string, float>p) {cout << p.first << " = " << p.second << " gram\n"; });
		}
	}
	
};
class Restoran
{
protected:
	string m_NameRestoran;
	string m_Street;
	vector<Dish>m_Menu;
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
	string m_password;
public:
	void EditOrBuy(string nameOrder) override
	{
		for(auto &i :m_Menu)
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
	vector<Dish>Basket;
	string m_street;
	int m_MaxCash;
public:
	void EditOrBuy(string nameOrder) override
	{
		for (auto &i : m_Menu)
			if (i.getName() == nameOrder)
			{
				Basket.push_back(i);
			}
		///////todo
		cout << "added";
	}
};
int main(int argc, char* argv[])
{
	Dish cez("Cezar", "Ahyennuy salat", map<string, float>{make_pair("Povmidor", 0.25),make_pair("Orgirok", 0.5)},100);
	cez.Show();
	cout << "Step" << endl;
}
