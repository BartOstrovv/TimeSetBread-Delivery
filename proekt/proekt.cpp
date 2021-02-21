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
	int m_id = 0;

	Dish() {}
	Dish(string n, string w, string p) :m_Name(n), m_Weight(w), m_Price(p) {}
	void Show()
	{
		cout << "ID: " << m_id << endl <<
			"Name: " << m_Name << " -- " << m_About << endl <<
			"Weight: " << m_Weight << endl <<
			"Price: " << m_Price << endl;
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
				temp.m_id = m_Menu.size() + 1;
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
		if(number <= m_Menu.size())		//TODO
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

	void ShowMenu()
	{
		cout << "=======MENU=======" << endl; // added
		for (auto& i : m_Menu) i.Show();
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
	vector<Dish> m_buy;
	int nSum = 0;
public:
	void AddElement(Dish obj, int nNumber = 1) 
	{ 
		obj.m_numberOfDish = nNumber;
		obj.m_id = m_buy.size() + 1;
		m_buy.push_back(obj);
	}

	void DelElement(int name) 
	{ 
		auto it = find_if(m_buy.begin(), m_buy.end(), [=](Dish obj) 
			{
				return obj.m_id == name;
			});

		nSum -= (stoi(it->m_Price) * it->m_numberOfDish);	
		m_buy.erase(it);
	}

	void ShowBasket()
	{
		nSum = 0;
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

	void setNumber(int id, int number)
	{
		auto it = find_if(m_buy.begin(), m_buy.end(), [=](Dish obj)->bool	// TODO
			{
				return obj.m_id == id;
			});
		it->m_numberOfDish = number;
	}

	bool SaveCheck(string namefile)
	{
		ofstream outFile(namefile, ofstream::out);
		try
		{
			if (!outFile.is_open()) 
				throw 0;
			for_each(m_buy.begin(), m_buy.end(),
				[&](Dish vd) {
					outFile << "Name: " << vd.m_Name << " | ";
					outFile << "Price: " << vd.m_Price << endl;
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

int main()
{
	/*Restoran buk("Pobeda", "Stysa 2", "9/10", "LoadMenuToRestoran.txt");
	buk.ShowInfoRest();

	Basket bas;
	bas.AddElement(Dish("Cesar", "122", "113"));
	bas.AddElement(Dish("Cesar", "12", "200"));
	bas.AddElement(Dish("Shuba", "122", "113"));
	bas.AddElement(Dish("Olive", "122", "113"));
	bas.AddElement(buk.getDish(3),2);
	bas.ShowBasket();
	cout << "=============del=========" << endl;
	bas.setNumber(5, 4);
	bas.DelElement(2);
	bas.ShowBasket();*/
	//bas.SaveCheck("testSaveCheck.txt");
	Restoran buk("Pobeda", "Stysa 2", "9/10", "LoadMenuToRestoran.txt");
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
	}
}