#include "Admin.h"

Restoran::Restoran() {}
Restoran::Restoran(string name, string street, string rait, string namefileMenu) :
	m_NameRest(name), m_StreetRest(street), m_RaitRest(rait), countDishOfMenu(0), m_fileName(namefileMenu)
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

Dish Restoran::getDish(int number)
{
	for (auto& i : m_Menu)
	{
		if (i.first == number)
			return i.second;
	}
}

void Restoran::ShowInfoRest()
{
	cout << "Name restoran: " << m_NameRest << endl <<
		"Street: " << m_StreetRest << endl <<
		"Raiting: " << m_RaitRest << endl;
	ShowMenu();
	cout << endl;
}
void Restoran::SaveChangeMenu()
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
void Restoran::ShowMenu()
{
	cout << "=======MENU=======" << endl;
	for (auto& i : m_Menu)
	{
		cout << "ID: " << i.first + 1 << endl;
		i.second.Show();
	}
	cout << endl;
}

string Restoran::getName()
{
	return m_NameRest;
}

string Restoran::getRating()
{
	return m_RaitRest;
}

void Restoran::EditTheRestoran()
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

void Restoran::EditTheDish(int index)
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

void Restoran::CreateNewDish(string name, string about, string weight, string price)
{
	m_Menu.emplace(countDishOfMenu++, Dish(name, about, weight, price));
}