
#pragma once

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

	Dish();
	Dish(string n, string about, string w, string p);
	void Show();
};