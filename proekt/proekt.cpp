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
	int m_numberOfDish;
	Dish() {}
	Dish(string n, string w, string p) :m_Name(n), m_Weight(w), m_Price(p) {}
	void Show()
	{
		cout << "Name: " <<m_Name << " -- " << m_About << endl;
		cout << "Weight: " << m_Weight << endl;
		cout << "Price: " << m_Price << endl;
		
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
	
	Dish getDish(int number)
	{
		return m_Menu[number-1];
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
	vector<Dish> m_buy;
public:
	void AddElement(Dish obj, int nNumber = 1) 
	{ 
		obj.m_numberOfDish = nNumber;
		m_buy.push_back(obj);
	}
	void DelElement(int name) 
	{ 
		m_buy.erase(m_buy.begin() + name-1);
	}
	void ShowBasket()
	{
		int nSum = 0;
		cout << "===================In basket===========\n";
		cout << cout.width(30) << m_buy.size() << " Element" << endl;

		for (auto& i : m_buy)
		{
			i.Show();
			nSum += (stoi(i.m_Price) * i.m_numberOfDish);
			cout << "Number of dish: " << i.m_numberOfDish << endl;
			cout << "==============\n";
		}
		cout << "Total: " << nSum << endl;
	}

	void addNumber(string name, int number)
	{
		auto it = find_if(m_buy.begin(), m_buy.end(), [=](Dish obj)->bool
			{
				return obj.m_Name == name;
			});
		it->m_numberOfDish = number;
	}

	bool SaveCheck(string namefile)
	{
		ofstream outFile(namefile, ofstream::out);
		try
		{
			if (!outFile.is_open()) throw 0;
			for_each(m_buy.begin(), m_buy.end(),
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
	Restoran buk("Pobeda", "Stysa 2", "9/10", "LoadMenuToRestoran.txt");
	buk.ShowInfoRest();

	Basket bas;
	bas.AddElement(Dish("Cesar", "122", "113"));
	bas.AddElement(Dish("Cesar", "12", "200"));
	bas.AddElement(Dish("Shuba", "122", "113"));
	bas.AddElement(Dish("Olive", "122", "113"));
	bas.AddElement(buk.getDish(2),2);
	bas.ShowBasket();
	bas.SaveCheck("testSaveCheck.txt");

}