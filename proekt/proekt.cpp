#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct Dish
{
	string m_Name;
	string m_Weight;
	string m_Price;
	int count = 1;
	Dish(string n, string w, string p) :m_Name(n), m_Weight(w), m_Price(p) {};
	void Show()
	{
		cout << "Name: " << m_Name << endl;
		cout << "Weight: " << m_Weight << endl;
		cout << "Price: " << m_Price << endl;
		cout << "==============\n";
	}
};
class Restoran
{
	vector<Dish>m_Menu;
	string m_NameRest;
	string m_StreetRest;
	string m_RaitRest;
public:
	Restoran(){}
	Restoran(vector<Dish> v, string name, string street, string rait) :
		m_NameRest(name), m_StreetRest(street), m_RaitRest(rait), m_Menu(v) {}
	void ShowInfoRest()
	{
		cout << "Name restoran: " << m_NameRest << endl;
		cout << "Street: " << m_StreetRest << endl;
		cout << "Raiting: " << m_RaitRest << endl;
		cout << "=======MENU=======" << endl;
		for (auto& i : m_Menu) i.Show();
		cout << endl;
	}
};
class Basket
{
	vector<Dish> PokypkaBlya;
	int countElement;
public:
	void AddElement(Dish obj) { PokypkaBlya.push_back(obj); countElement++; }
	void DelElement(int name) 
	{ 
		PokypkaBlya.erase(PokypkaBlya.begin() + name-1);
	 countElement--;
	}
	void ShowBasket()
	{
		cout << "===================In basket===========\n";
		for (auto &i : PokypkaBlya) i.Show();
		cout << "\t";
	}
};


int main()
{

	Basket bas;
	bas.AddElement(Dish("salat", "122", "113"));
	Restoran buk(vector<Dish>{Dish("salawwt", "122", "113"), Dish("salat", "122", "113"), Dish("salat", "122", "113")},"Restik","Brodrr","13,6");
	Restoran buk2(vector<Dish>{Dish("sawlat", "122", "113"), Dish("salat", "122", "113"), Dish("salat", "122", "113")}, "Restik", "Brodrr", "13,6");
	Restoran buk3(vector<Dish>{Dish("swddwalat", "122", "113"), Dish("salat", "122", "113"), Dish("salat", "122", "113")}, "aaaaaaaastik", "Baaarr", "13,6");
	vector<Restoran> r{ buk,buk2,buk3 };
	for (auto& i : r)
		i.ShowInfoRest();

}