
#include "Admin.h"

Dish::Dish() {}
Dish::Dish(string n, string about, string w, string p) :m_Name(n), m_Weight(w), m_Price(p), m_About(about) {}
void Dish::Show()
{
	cout << "Name: " << m_Name << " -- " << m_About << endl <<
		"Weight: " << m_Weight << endl <<
		"Price: " << m_Price << endl;
}