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

	void EditTheRestoran() // changed
	{
		cin.ignore();
		string change;
		cout << "What needs to be changed? (1 - Name of Restoran, 2 - Street Restoran, 3 - Raiting)" << endl;
		char choose = _getch();
		cout << "\nEnter the new info: ";
		getline(cin, change);
		switch (choose)
		{
		case '1':  m_NameRest = change; break;

		case '2': m_StreetRest = change; break;
		case '3': m_RaitRest = change += "/10"; break;
		default: cout << "incorrect choose" << endl;
		}
	}

	void EditTheDish(int index) // changed
	{
		for (auto& i : m_Menu)
			if ((index - 1) == i.first)
			{
				cin.ignore();
				string change;
				cout << "What needs to be changed? 1 - Name of Dish, 2 - Inf About Dish, 3 - Weight of Dish, 4 - Price of Dish" << endl;
				char choose = _getch();
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

	void AddElement(Dish obj, int countDish) // changed
	{
		if (countDish > 0)
		{
			obj.m_numberOfDish = countDish;
			nSum += (stoi(obj.m_Price) * obj.m_numberOfDish);
			m_buy.push_back(obj);
			countDishOfBasket++;
		}
	}

	void DelElement(int name, int quantity) // changed
	{
		name -= 1;
		if (name < countDishOfBasket)
		{
			//TODO
			if (quantity >= m_buy[name].m_numberOfDish)
			{
				m_buy.erase(m_buy.begin() + name);
			}
			else
			{
				m_buy[name].m_numberOfDish-= quantity;
			}
			nSum = 0;
			for (auto i : m_buy)
			{
				nSum += (stoi(i.m_Price) * i.m_numberOfDish); // тут напевно можна шось краще придумати, але вже 5-45 і я не соображаю і хочу хоть трохи поспати)
			}
		}
	}

	void ShowBasket()
	{
		cout << "===================In basket=================\n";
		int i = 0;
		for_each(m_buy.begin(), m_buy.end(), [&](Dish p)
			{
				cout << "ID: " << ++i << "\nDish: " << p.m_Name << "\nQuantity: " << p.m_numberOfDish << "\nCost: " << p.m_Price << endl; // changed
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
					outFile << "Name: " << vd.m_Name << " x" << vd.m_numberOfDish << "---Restaurant: " << vd.m_NameRest << " | ";
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
	vector<Restoran>{ Restoran("Mama_Italia", "Ternopil","7/10","Mama_Italia.txt"), Restoran("Thai_life","Lviv","6/10","Thai_life.txt"),
		Restoran("Sushi", "Kiev","9/10","Sushi.txt"), Restoran("Ukrainian_food", "Kiev","8/10","Ukrainian_food.txt") } };
	Basket bas;
	bool avtorization = false;
	bool work = true;
	int baskInd = 1; // added
	while (work)
	{
		int choice;
		if (!avtorization)
		{
			cout << "0 - Avtorization to Admin" << endl;
			cout << "1 - Show restaurants." << endl;
			cout << "2 - Search by restaurant name." << endl;
			cout << "3 - Show restaurants by rating." << endl;
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
				if (count <= adm.getVectorRest().size())
				{
					if (count == 0)
					{
						break;
					}
					else
					{
						adm.getVectorRest()[count - 1].ShowMenu();
						int dish = 1;
						cout << "Choose dishes, type 0 to go back" << endl;
						while (dish != 0)
						{
							cin >> dish;
							if (dish != 0)
							{
								int quantity = 0;
								cout << "How much you want to add?" << endl;
								cin >> quantity;
								bas.AddElement(adm.getVectorRest()[count - 1].getDish(dish - 1), quantity); // ?
								bas.getDish(baskInd++).m_NameRest = adm.getVectorRest()[count - 1].getName(); // ?
							}
						}

					}
				}
				else
				{
					cout << "Wrong input!" << endl;
				}
			}break;
			case 2:
			{
				cin.ignore();
				string name;
				cout << "Type name of the restaurant to search: " << endl;
				getline(cin, name);
				bool search = false;
				int Num = 0;
				for (auto i : adm.getVectorRest()) // ?
				{
					if (i.getName() == name)
					{
						cout << "There is restaurant with name \"" << name << "\"" << endl;
						search = true;
						adm.getVectorRest()[Num].ShowInfoRest();
						int dish = 1;
						cout << "Choose dishes, type 0 to go back" << endl;
						while (dish != 0)
						{
							cin >> dish;
							if (dish != 0)
							{
								int count = 0;
								cout << "How much you want to add?" << endl;
								cin >> count;
								bas.AddElement(adm.getVectorRest()[Num].getDish(dish - 1), count); // ?
								bas.getDish(baskInd++).m_NameRest = adm.getVectorRest()[Num].getName();
							}
						}
					}
					Num++;
				}
				if (search == false)
				{
					cout << "Restaurant not found!" << endl;
				}
			}break;
			case 3: // added
			{
				sort(adm.getVectorRest().begin(), adm.getVectorRest().end(), [](Restoran n1, Restoran n2)
					{
						return n1.getRating() < n2.getRating();
					});
				int count = 1;
				for (auto& i : adm.getVectorRest())
				{
					cout << count << ": ";
					cout << "Name: "<<i.getName() << " Rating: "<< i.getRating() << endl;
					count++;
				}
					
			}break;
			case 4: // changed
			{
				bool basket = true;
				int choice = 0;
				cout << "1 - Show basket, 2 - Save Check, 3 - Delete dish in Basket, 4 - Exit from basket" << endl;
				while (basket)
				{
					cin >> choice;
					if (choice == 1)
						bas.ShowBasket();
					else if (choice == 3)
					{
						int del = 0;
						int quantity = 0;
						cout << "Enter the position to delete: " << endl;
						cin >> del;
						cout << "Enter quantity to delete: " << endl;
						cin >> quantity;
						bas.DelElement(del, quantity);
					}
					else if (choice == 2)
					{
						string name; string street; string number; string time;

						cout << "Enter your name: "; cin >> name;
						cout << "Enter your phone number: "; cin >> number;
						cout << "Enter your street: "; cin >> street;
						cout << "Time: "; cin >> time;

						bas.SaveCheck("testSaveCheck.txt", name, street, number, time);
					}
					else if (choice == 4)
					{
						break;
					}
					else
					{
						cout << "Wrong input!" << endl;
					}
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
			cout << "Select restoraunt to edit information!" << endl;
			cin >> count;
			adm.getVectorRest()[count - 1].ShowInfoRest();
			cout << "1 - Change info of rest, 2 - Change info of menu?, 3 - Create a new dish?, 4 - Exit" << endl;
			chang = _getch();
			if (chang == '1') adm.getVectorRest()[count - 1].EditTheRestoran();
			else if (chang == '2')
			{
				int ind;
				adm.getVectorRest()[count - 1].ShowMenu();
				cout << "Enter the number of dish to edit" << endl;
				cin >> ind;
				adm.getVectorRest()[count - 1].EditTheDish(ind);
			}
			else if (chang == '3')
			{
				cin.ignore();
				string n, a, w, p;
				cout << "Enter the name of new Dish" << endl; cin >> n;
				cout << "Enter information about new Dish " << endl; cin >> a;
				cout << "Enter weigtht of the new Dish" << endl; cin >> w;
				cout << "Enter price of the new Dish" << endl; cin >> p;
				adm.getVectorRest()[count - 1].CreateNewDish(n, a, w, p);
			}
			else if (chang == '4')
			{
				break;
			}
			else cout << "Wrong input!" << endl;
		}
	}
}
