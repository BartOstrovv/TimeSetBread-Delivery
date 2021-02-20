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
	string m_About;
	string m_Weight;
	string m_Price;
	int count = 1;
	Dish() {};
	Dish(string n, string w, string p) :m_Name(n), m_Weight(w), m_Price(p) {};
	void Show()
	{
		cout << "Name: " <<m_Name << " -- " << m_About << endl;
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
	Restoran(string name, string street, string rait, string namefileMenu) :
		m_NameRest(name), m_StreetRest(street), m_RaitRest(rait) 
	{
		ifstream inFile(namefileMenu, ifstream::in);
		Dish temp;
		try
		{
			if (!inFile.is_open()) throw 0;
			while (!inFile.eof())
			{
				getline(inFile, temp.m_Name);
				getline(inFile, temp.m_About);
				getline(inFile, temp.m_Weight);
				getline(inFile, temp.m_Price);
				m_Menu.push_back(temp);
		   }
		}
		catch (exception& ex)
		{
			cout << "Error open file: " << ex.what() << endl;
		}
	}
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
	bool SaveCheck(string namefile)
	{
		ofstream outFile(namefile, ofstream::out);
		try
		{
			if (!outFile.is_open()) throw 0;
			for_each(PokypkaBlya.begin(), PokypkaBlya.end(),
				[&](Dish vd) {
					outFile << "Name: " << vd.m_Name << " | ";
					outFile << "Price: " << vd.m_Price << endl;
				});
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
		outFile.close();
	}
};


int main()
{

	Basket bas;
	bas.AddElement(Dish("Cesar", "122", "113"));
	bas.AddElement(Dish("Cesar", "12", "200"));
	bas.AddElement(Dish("Shuba", "122", "113"));
	bas.AddElement(Dish("Olive", "122", "113"));
	bas.SaveCheck("testSaveCheck.txt");
	Restoran buk("Pobeda", "Stysa 2", "9/10", "LoadMenuToRestoran.txt");
	buk.ShowInfoRest();
}