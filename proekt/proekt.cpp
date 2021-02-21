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

	Dish() {}
	Dish(string n, string about, string w, string p) :m_Name(n), m_Weight(w), m_Price(p), m_About(about) {}
	void Show()
	{
		cout <<
			"Name: " << m_Name << " -- " << m_About << endl <<
			"Weight: " << m_Weight << endl <<
			"Price: " << m_Price << endl;
	}
};

class Restoran
{
	protected:
	map<int,Dish>m_Menu;
	string m_NameRest;
	string m_StreetRest;
	string m_RaitRest;
	int countDishOfMenu;
public:
	Restoran(){}
	Restoran(string name, string street, string rait, string namefileMenu) :
		m_NameRest(name), m_StreetRest(street), m_RaitRest(rait), countDishOfMenu(0)
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

				m_Menu.emplace(countDishOfMenu++,temp);
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
		if(number <= m_Menu.size())		//TODO
			return m_Menu[number-1];
	}

	void ShowInfoRest()
	{
		cout << "Name restoran: " << m_NameRest << endl;
		cout << "Street: " << m_StreetRest << endl;
		cout << "Raiting: " << m_RaitRest << endl;
		cout << "=======MENU=======" << endl;
		for (auto& i : m_Menu) i.second.Show();
		cout << endl;
	}

	void ShowMenu()
	{
		cout << "=======MENU=======" << endl; // added
		for (auto& i : m_Menu) i.second.Show();
		cout << endl;
	}

	string getName()
	{
		return m_NameRest; // added
	}

	string getRating()
	{
		return m_RaitRest; // added
	}
};

class Basket
{
protected:
 multimap<int,Dish> m_buy;
	int nSum = 0;
public:
	void AddElement(Dish obj, int countDish) 
	{ 
		m_buy.emplace(countDish, obj);
		nSum += stoi(obj.m_Price);
	}

	void DelElement(int name) 
	{ 
		auto it = find_if(m_buy.begin(), m_buy.end(), [=](pair<int,Dish>p) 
			{
				return p.first == name;
			});

		nSum -= (it->first * stoi(it->second.m_Price));	
		m_buy.erase(it);
	}

	void ShowBasket()
	{
		cout << "===================In basket===========\n";
	
		for_each(m_buy.begin(), m_buy.end(), [&](pair<int, Dish>p)
			{
				cout << "Dish: " << p.second.m_Name << " x" << p.first;
				nSum += p.first;
			});
		cout << "Total: " << nSum << endl;
	}

	//void setNumber(int id, int number)
	//{
	//	auto it = find_if(m_buy.begin(), m_buy.end(), [=](int k,Dish obj)->bool	// TODO
	//		{
	//			return obj == id;
	//		});
	//	it->m_numberOfDish = number;
	//}

	bool SaveCheck(string namefile)
	{
		ofstream outFile(namefile, ofstream::out|ofstream::app);
		try
		{
			if (!outFile.is_open()) 
				throw 0;
			for_each(m_buy.begin(), m_buy.end(),
				[&](pair<int,Dish> vd) {
					outFile << "Name: " << vd.second.m_Name << " | ";
					outFile << "Price: " << vd.second.m_Price << endl;
				});
			outFile << "Total price: " << nSum << endl;
			return true;
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
			return false;
		}
		outFile.close();
	}
};
class User : public Basket
{
	Basket m_bas;
	string m_Name;
	string m_numberPhone;
	string m_Street;
	string m_time;
public:
	User(Basket& bas) :m_bas(bas) {};
	User(string name, string number, string street,  string time):m_Name(name),m_numberPhone(number)
	,m_Street(street),m_time(time){}
	void setInfoUser(string n, string nom, string stret, string time)
	{
		m_Name = n; m_numberPhone = nom; m_Street = stret; m_time = time;
	}
	void Check(string file)
	{
		ofstream outFile(file, ofstream::out | ofstream::app);
		try
		{
			if (!outFile.is_open())
				throw 0;
			outFile << "Name user: " << m_Name << endl;
			outFile << "Telephone: " << m_numberPhone << endl;
			outFile << "Street: " << m_Street << endl;
			outFile << "Time: " << m_time << endl;
			m_bas.SaveCheck(file);
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
		outFile.close();
	}
};
class Admin : public Restoran
{
	bool ok = false;
	vector <pair<string, string>> m_adm;
public:
	Admin(Restoran rest) :Restoran(rest)
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
				m_adm.push_back(make_pair(f,s));
			}
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
		aFile.close();
	}
     bool Avtorization()
	{

		 if (!ok)
		 {
			 string s, p;
			 cout << "Enter the name: "; cin >> s;
			 cout << "Enter the password: "; cin >> p;
			 for (auto& i : m_adm)
				 if (i.first == s) (i.second == p) ? ok = true : ok = false;
			 if (ok) cout << "Hello, admin of " << m_NameRest << " - " << s << endl;
			 else cout << "Incorrect name or password. Try again!" << endl;
			 Avtorization();
		 }
		 return ok;
	}
	void CreateNewDish(string name, string about, string weight, string price)
	{
		if (Avtorization())
			m_Menu.emplace(countDishOfMenu++, Dish(name, about, weight, price));
		else cout << "Avtorization for start!" << endl;
	}
	void EditTheDish(int index)
	{
		if (Avtorization())
		{
			for (auto& i : m_Menu)
				if (index == i.first)
				{
					string change;
					cout << "what needs to be changed? (1 - Name of Dish, 2 - About Dish, 3 - Weight Dish, 4 - Price Dish" << endl;
					char choose = _getche();
					cout << "\nEnter the new info: "; cin >> change;
					switch (choose)
					{
					case '1':  i.second.m_Name = change; break;

					case '2': i.second.m_About = change; break;
					case '3':i.second.m_Weight = change; break;
					case '4':i.second.m_Weight = change; break;
					default: cout << "incorrect choose" << endl;
					}
				}
	}
	}
	void EditTheRestoran()
	{
		if (Avtorization())
		{
				string change;
					cout << "what needs to be changed? (1 - Name of Restoran, 2 - Street Restoran, 3 - Raiting" << endl;
					char choose = _getche();
					cout << "\nEnter the new info: "; cin >> change;
					switch (choose)
					{
					case '1':  m_NameRest = change; break;

					case '2': m_StreetRest = change; break;
					case '3': m_RaitRest = change; break;
					default: cout << "incorrect choose" << endl;
					}
		}
	}

	
};

int main()
{
	
	Admin Taras(Restoran("Shalash", "Ternopil", "7/10", "LoadMenuToRestoran.txt"));
	cout << endl;
	Taras.CreateNewDish("Burgeros", "Yalovychyna", "300 gramm", "120 grn");
	Taras.EditTheDish(1);
	Taras.ShowInfoRest();
	

	Basket bas;
	bas.AddElement(Dish("Cesar","wdwa", "122", "113"),2);
	bas.AddElement(Dish("Cesar","wawdawd", "12", "200"),4);
	bas.AddElement(Dish("Shuba","aaaaaaaaaaa", "122", "113"),5);
	bas.AddElement(Dish("Olive","vvvvvvvv", "122", "113"),2);
	User us(bas);
	us.setInfoUser("Jhon","037281930", "Stysa","14:45");
	us.Check("testSaveCheck.txt");
	
	//bas.SaveCheck("testSaveCheck.txt");
	/*Restoran buk("Pobeda", "Stysa 2", "9/10", "LoadMenuToRestoran.txt");
	Restoran buk1("sdgdsg", "Stysa 2", "6/10", "LoadMenuToRestoran.txt");
	Restoran buk2("ybuyhdfhgdl", "Stysa 2", "7/10", "LoadMenuToRestoran.txt");
	Restoran buk3("jkasdogf", "Stysa 2", "3/10", "LoadMenuToRestoran.txt");
	vector<Restoran> rest = {buk,buk1 ,buk2 ,buk3 };
	Basket bas;
	
	bool work = true;
	while (work)
	{
		int choice = 0;

		cout << "1 - Show restaurants." << endl;
		cout << "2 - Search by restaurant name." << endl;
		cout << "3 - Search by restaurant rating." << endl;
		cout << "4 - Go to basket." << endl;
		cout << "5 - Exit." << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			int count = 1;
			cout << "Restaurant list:" << endl;
			for (auto i : rest)
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
				rest[count].ShowMenu();
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
					bas.AddElement(rest[count].getDish(dish), 1);
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
							bas.AddElement(rest[count].getDish(dish), 1);
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
			for (auto i : rest)
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
			cout << "Show basket?" << endl << "1 - Yes, 2 - No" << endl;
			cin >> choice;
			if (choice == 1)
			{
				bas.ShowBasket();

			}
			else
			{
				break;
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
	}*/
}