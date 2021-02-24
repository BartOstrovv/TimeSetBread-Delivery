#include "Admin.h"

Dish& Basket::getDish(int n)
{
	return m_buy[n - 1];
}

void Basket::AddElement(Dish obj, int countDish)
{
	bool search = false;
	if (countDish > 0)
	{
		for (auto &i : m_buy)
		{
			if (i.m_Name == obj.m_Name)
			{
				i.m_numberOfDish += countDish;
				search = true;
			}
		}
		if (search == false)
		{
			obj.m_numberOfDish = countDish;
			m_buy.push_back(obj);
			countDishOfBasket++;
		}
		
		nSum += (stoi(obj.m_Price) * obj.m_numberOfDish);
	}
}

void Basket::DelElement(int name, int quantity)
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
			m_buy[name].m_numberOfDish -= quantity;
		}
		nSum = 0;
		for (auto i : m_buy)
		{
			nSum += (stoi(i.m_Price) * i.m_numberOfDish);
		}
		countDishOfBasket--;
	}
	else
		cout << "Dish not found" << endl;
}

int Basket::getCountOfBasket()
{
	return countDishOfBasket;
}

void Basket::setNumber(int id, int number)
{
	//TOODO
}

void Basket::ShowBasket()
{
	cout << "===================In basket=================\n";
	int i = 0;
	for_each(m_buy.begin(), m_buy.end(), [&](Dish p)
		{
			int strSize = p.m_Name.size();

			cout << "ID: " << ++i << "\t | ";
			if (strSize <= 12)
			{
				cout << "Dish: " << p.m_Name.append(15 - strSize ,' ');
			}
			else
				cout << "Dish: " << p.m_Name.erase(12) + "...";
			cout << " | " << "Quantity: " << p.m_numberOfDish << "\t | " << "Cost: " << p.m_Price << endl;

		});
	cout << "\nTotal: " << nSum << endl;
}

void Basket::SaveCheck(string file, string n, string p, string s, string t)
{
	ofstream outFile(file, ofstream::out);
	try
	{
		if (!outFile.is_open())
			throw 0;
		outFile << "Name user: " << n << endl;
		outFile << "Street: " << p << endl;
		outFile << "Telephone: " << s << endl;
		outFile << "Time: " << t << endl;
		for_each(m_buy.begin(), m_buy.end(),
			[&](Dish vd) {
				outFile << "Name: " << vd.m_Name << " x" << vd.m_numberOfDish << "---Restaurant: " << vd.m_NameRest << " | ";
				outFile << "Price: " << stoi(vd.m_Price) * vd.m_numberOfDish << endl;
			});
		outFile << "Total price: " << nSum << endl;
	}
	catch (exception & ex)
	{
		cout << "Error: " << ex.what() << endl;
	}

	outFile.close();
}