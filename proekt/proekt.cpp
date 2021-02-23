#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <conio.h>
using namespace std;

struct Dish
{
	string m_Name;
	string m_About;
	string m_Weight;
	string m_Price;
	string m_NameRest;
	int m_numberOfDish;

	Dish() {}
	Dish(string n, string about, string w, string p) :m_Name(n), m_Weight(w), m_Price(p), m_About(about) {}
	void Show()
	{
		cout << "Name: " << m_Name << " -- " << m_About << endl <<
			"Weight: " << m_Weight << endl <<
			"Price: " << m_Price << endl;
	}
};

class Restoran
{
protected:
	map<int, Dish>m_Menu;
	string m_NameRest;
	string m_StreetRest;
	string m_RaitRest;
	int countDishOfMenu;
	string m_fileName;
public:
	Restoran() {}
	Restoran(string name, string street, string rait, string namefileMenu) :
		m_NameRest(name), m_StreetRest(street), m_RaitRest(rait), countDishOfMenu(0),m_fileName(namefileMenu)
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
				temp.m_NameRest = m_NameRest;
				m_Menu.emplace(countDishOfMenu++, temp);
			}
		}
		catch (exception& ex)
		{
			cout << "Error open file: " << ex.what() << endl;
		}
		inFile.close();
	}

	Dish getDish(int number)
	{
		for (auto& i : m_Menu)
		{
			if (i.first == number)
				return i.second;
		}
	}

	void ShowInfoRest()
	{
		cout << "Name restoran: " << m_NameRest << endl <<
			"Street: " << m_StreetRest << endl <<
			"Raiting: " << m_RaitRest << endl;
		ShowMenu();
		cout << endl;
	}
	void SaveChangeMenu()
	{
		ofstream file(m_fileName, ofstream::out);
		if (!file.is_open())
		{
			cout << "File is not open!" << endl;
		}
		else
		{
			for_each(m_Menu.begin(), m_Menu.end(), [&](pair<int, Dish>p)
				{
					file << p.second.m_Name << endl;
					file << p.second.m_About << endl;
					file << p.second.m_Weight << endl;
					file << p.second.m_Price << endl;
				});
			file.close();
		}

	}
	void ShowMenu()
	{
		cout << "=======MENU=======" << endl;
		for (auto& i : m_Menu)
		{
			cout << "ID: " << i.first + 1 << endl;
			i.second.Show();
		}
		cout << endl;
	}

	string getName()
	{
		return m_NameRest;
	}

	string getRating()
	{
		return m_RaitRest;
	}

	void EditTheRestoran()
	{
		string change;
		cout << "What needs to be changed? (1 - Name of Restoran, 2 - Street Restoran, 3 - Raiting)" << endl;
		char choose = _getche();
		cout << "\nEnter the new info: ";
		getline(cin, change);
		switch (choose)
		{
		case '1':  m_NameRest = change; break;

		case '2': m_StreetRest = change; break;
		case '3': m_RaitRest = change; break;
		default: cout << "incorrect choose" << endl;
		}

	}
	void EditTheDish(int index)
	{
		for (auto& i : m_Menu)
			if ((index - 1) == i.first)
			{
				string change;
				cout << "What needs to be changed? (1 - Name of Dish, 2 - About Dish, 3 - Weight Dish, 4 - Price Dish)" << endl;
				char choose = _getche();
				cout << "\nEnter the new info: ";
				getline(cin, change);
				switch (choose)
				{
				case '1':  i.second.m_Name = change; break;

				case '2': i.second.m_About = change; break;
				case '3':i.second.m_Weight = change; break;
				case '4':i.second.m_Price = change; break;
				default: cout << "incorrect choose" << endl;
				}
			}
	}

	void CreateNewDish(string name, string about, string weight, string price)
	{
		m_Menu.emplace(countDishOfMenu++, Dish(name, about, weight, price));
	}
};

class Basket
{
protected:
	vector<Dish> m_buy;
	int nSum = 0;
	int countDishOfBasket;
public:

	Dish& getDish(int n)
	{
		return m_buy[n - 1];
	}

	void AddElement(Dish obj, int countDish = 1)
	{
		obj.m_numberOfDish = countDish;
		m_buy.push_back(obj);
		nSum += (stoi(obj.m_Price) * obj.m_numberOfDish);
		countDishOfBasket++;
	}

	void DelElement(int name)
	{
		if (name < countDishOfBasket)
		{
			m_buy.erase(m_buy.begin() + --name);
			nSum += (stoi(m_buy[name].m_Price) * m_buy[name].m_numberOfDish);
		}
	}

	void ShowBasket()
	{
		cout << "===================In basket===========\n";
		int i = 0;
		for_each(m_buy.begin(), m_buy.end(), [&](Dish p)
			{
				cout << "ID: " << ++i << "\tDish: " << p.m_Name << "\nCost: " << p.m_Price << endl;
			});
		cout << "\nTotal: " << nSum << endl;
	}

	void SaveCheck(string file, string n, string p, string s, string t)
	{
		ofstream outFile(file, ofstream::out);
		try
		{
			if (!outFile.is_open())
				throw 0;
			outFile << "Name user: " << n << endl;
			outFile << "Telephone: " << p << endl;
			outFile << "Street: " << s << endl;
			outFile << "Time: " << t << endl;
			for_each(m_buy.begin(), m_buy.end(),
				[&](Dish vd) {
					outFile << "Name: " << vd.m_Name << " x" << vd.m_numberOfDish << "---rest: " << vd.m_NameRest << " | ";
					outFile << "Price: " << stoi(vd.m_Price) * vd.m_numberOfDish << endl;
				});
			outFile << "Total price: " << nSum << endl;
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}

		outFile.close();
	}
};

class Admin 
{
	bool ok = false;
	vector<Restoran> m_restorans;
	vector <pair<string, string>> m_admPass;
public:
	Admin(vector<Restoran> restorans) :m_restorans(restorans)
	{
		ifstream aFile("passwords.txt");
		try
		{
			if (!aFile.is_open()) throw 0;
			while (!aFile.eof())
			{
				string f, s;
				getline(aFile, f, '|');

				getline(aFile, s, '|');
				m_admPass.push_back(make_pair(f, s));
			}
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
		aFile.close();
	}
	vector<Restoran>& getVectorRest() { return m_restorans; }
	bool Avtorization()
	{

		if (!ok)
		{
			string s, p;
			cout << "Enter the name: "; cin >> s;
			cout << "Enter the password: "; cin >> p;
			for (auto& i : m_admPass)
				if (i.first == s) (i.second == p) ? ok = true : ok = false;
			if (ok) cout << "Hello, admin " << s << endl;
			else cout << "Incorrect name or password. Try again!" << endl;
			Avtorization();
		}
		return ok;
	}
};

int main()
{

	Admin adm{
	vector<Restoran>{ Restoran("Mama_Italia", "Ternopil","7/10","Mama_Italia.txt"), Restoran("Thai_life","Lviv","8/10","Thai_life.txt"),
		Restoran("Sushi", "Kiev","9/10","Sushi.txt"), Restoran("Ukrainian_food", "Kiev","9/10","Ukrainian_food.txt") } };
	Basket bas;
	bool avtorization = false;
	/*bool work = true;
	while (work)
	{
		int choice;
		if (!avtorization)
		{
			cout << "0 - Avtorization to Admin" << endl;
			cout << "1 - Show restaurants." << endl;
			cout << "2 - Search by restaurant name." << endl;
			cout << "3 - Search by restaurant rating." << endl;
			cout << "4 - Go to basket." << endl;
			cout << "5 - Exit." << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
			{
				adm.Avtorization(); avtorization = true; break;
			}
			case 1:
			{
				int count = 1;
				cout << "Restaurant list:" << endl;
				for (auto& i : adm.getVectorRest())
				{
					cout << count << ": ";
					cout << i.getName() << endl;
					count++;
				}
				count = 0;
				cout << "Type number of restaurant to see menu, type 0 to go back " << endl;
				cin >> count;
				if (count == 0)
				{
					continue;
				}
				else
				{
					adm.getVectorRest()[count - 1].ShowMenu();
					int dish = 0;
					int YorN = 0;
					bool addDish = true;
					cout << "Dou you want to add dish to basket? " << endl;
					cout << "1 - Yes, 2 - No" << endl;
					cin >> YorN;
					if (YorN == 1)
					{
						cout << "Add dish to basket: ";
						cin >> dish;
						cout << "How match?" << endl;
						cin >> YorN;

						bas.AddElement(adm.getVectorRest()[count - 1].getDish(dish - 1), YorN);
						while (addDish)
						{
							cout << "Dou you want to add another dish from that restaurant?" << endl;
							cout << "1 - Yes, 2 - No" << endl;
							cin >> YorN;
							if (YorN == 1)
							{
								dish = 0;
								cout << "Add dish to basket: ";
								cin >> dish;
								cout << "How match?" << endl;
								cin >> YorN;
								bas.AddElement(adm.getVectorRest()[count - 1].getDish(dish - 1), YorN);
							

							}
							else
							{
								addDish = false;
							}
						}
					}
					else
					{
						break;
					}
				}
			}break;
			case 2:
			{
				cin.ignore();
				string name;
				cout << "Type name of the restaurant to search: " << endl;
				getline(cin, name);
				int Num = 1;
				for (auto& i : adm.getVectorRest())
				{
					if (i.getName() == name)
					{
						cout << "There is restaurant with name \"" << name << "\", it`s number is: " << Num << endl;
					}
					Num++;
				}
			}break;
			case 3:
			{

			}break;
			case 4:
			{
				int choice = 0;
				cout << "Show basket? - 1, SaveCheck - 2, Del dish in Basket - 3" << endl;
				cin >> choice;
				if (choice == 1)
					bas.ShowBasket();
				if (choice == 3)
				{
					int del;
					cout << "Enter the position to del: ";
					cin >> del;
					bas.DelElement(del);
				}
				if (choice == 2)
				{
					string name; string street; string number; string time;

					cout << "Enter your name: "; cin >> name;
					cout << "Enter your phone number: "; cin >> number;
					cout << "Enter your street: "; cin >> street;
					cout << "Time: "; cin >> time;

					bas.SaveCheck("testSaveCheck.txt", name, street, number, time);
				}
			}break;
			case 5:
			{
				work = false;
			}break;
			default:
			{
				cout << "Wrong input!" << endl;
			}
			}
		}
		else
		{
			char chang;
			int count = 1;
			cout << "Restaurant list:" << endl;
			for (auto& i : adm.getVectorRest())
			{
				cout << count << ": ";
				cout << i.getName() << endl;
				count++;
			}
			cout << "Select restoran to edit information!" << endl;
			cin >> count;
			adm.getVectorRest()[count - 1].ShowInfoRest();
			cout << "Change info of rest? - press 1\tChange info of menu? - press 2\tCreate a new dish? - press 3";
			chang = _getche();
			if (chang == '1') adm.getVectorRest()[count - 1].EditTheRestoran();
			if (chang == '2')
			{
				int ind;
				adm.getVectorRest()[count - 1].ShowMenu();
				cout << "Enter the number dish to edit" << endl;
				cin >> ind;
				adm.getVectorRest()[count - 1].EditTheDish(ind);
			}
			if (chang == '3')
			{
				string n, a, w, p;
				cout << "Enter the name fo new Dish" << endl; cin >> n;
				cout << "Enter information of new Dish " << endl; cin >> a;
				cout << "Enter the weigtht of new Dish" << endl; cin >> w;
				cout << "Enter the price of new Dish" << endl; cin >> p;
				adm.getVectorRest()[count - 1].CreateNewDish(n, a, w, p);
			}
		}
	}*/
}
