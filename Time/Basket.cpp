#include "Admin.h"

Dish& Basket::getDish(int n)
{
	return m_buy[n - 1];
}

void Basket::AddElement(Dish obj, int countDish)
{
	bool search = false;

	for (auto& i : m_buy)
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

void Basket::DelElement(int id, int quantity)
{
	if (id <= countDishOfBasket)
	{
		id -= 1;
		nSum -= (stoi(m_buy[id].m_Price) * m_buy[id].m_numberOfDish);

		if (quantity >= m_buy[id].m_numberOfDish)
			m_buy.erase(m_buy.begin() + id);
		else
			m_buy[id].m_numberOfDish -= quantity;

		countDishOfBasket--;
	}
	else
		cout << "Dish not found" << endl;
}

void Basket::Cancel()
{
	m_buy.clear();
	Basket::nSum = 0;
}

int Basket::getCountOfBasket()
{
	return countDishOfBasket;
}

void Basket::ShowBasket()
{
	cout << "=============================Busket=============================\n";
	int i = 0;

	for_each(m_buy.begin(), m_buy.end(), [&](Dish p)
		{
			int strSize = p.m_Name.size();

			cout << "| ID: " << ++i << "\t | ";
			if (strSize <= 12)
			{
				cout << "Dish: " << p.m_Name.append(15 - strSize ,' ');
			}
			else
				cout << "Dish: " << p.m_Name.erase(12) + "...";
			cout << " | " << "Quantity: " << p.m_numberOfDish << "\t | " << "Cost: " << p.m_Price << "\t|" << endl;
		});
	cout << "================================================================\n";
	cout << "\nTotal: " << nSum << endl;
}

void Basket::SaveCheck(string file, string n, string p, string s, string t)
{
	ofstream outFile(file, ofstream::out);
	try
	{
		if (!outFile.is_open())
			throw 0;
		
		outFile << "Name user: " << n << endl << 
			"Street: " << p << endl << 
			"Telephone: " << s << endl << 
			"Time: " << t << endl;

		for_each(m_buy.begin(), m_buy.end(),
			[&](Dish vd) {
				outFile << "Name: " << vd.m_Name << " x" << 
					vd.m_numberOfDish << "---Restaurant: " << 
					vd.m_NameRest << " | " << 
					"Price: " << stoi(vd.m_Price) * vd.m_numberOfDish << endl;
			});
		outFile << "Total price: " << nSum << endl;
	}
	catch (exception & ex)
	{
		cout << "Error: " << ex.what() << endl;
	}

	outFile.close();
}