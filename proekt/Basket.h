#pragma once

#include "Restoran.h"

class Basket
{
protected:
	vector<Dish> m_buy;
	int nSum = 0;
	int countDishOfBasket;
public:
	Dish& getDish(int n);
	void AddElement(Dish obj, int countDish);
	void DelElement(int name, int quantity);
	void ShowBasket();
	void SaveCheck(string file, string n, string p, string s, string t);
};