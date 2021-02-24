#include "Admin.h"

Dish::Dish() {}
Dish::Dish(string n, string about, string w, string p) :m_Name(n), m_Weight(w), m_Price(p), m_About(about) {}
void Dish::Show()
{
	string str;

		cout << "  "<<m_Name;
		cout.width(31 - m_Name.length());
		int weight = stoi(m_Weight);
		if (weight < 100)
		{
			cout << " | " << " " << m_Weight << "    | ";
			cout << " " << m_Price;
		}
		else
		{
			cout << " | " << " " << m_Weight << "   | ";
			cout << " " << m_Price;
		}
		int price = stoi(m_Price);
		if (price > 100)
		{
			cout.width(3);
		}
		else
		{
			cout.width(4);
		}
		cout << "|" << endl;
		cout << "Details: " << m_About << endl;

}