#include "Admin.h"

Dish::Dish() {}
Dish::Dish(string n, string about, string w, string p) :m_Name(n), m_Weight(w), m_Price(p), m_About(about) {}
void Dish::Show()
{
	cout << m_Name <<" | "<< m_Weight <<" | "<< m_Price <<" |"<< endl; // TODOO

}