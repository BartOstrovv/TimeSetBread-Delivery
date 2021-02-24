
#pragma once

#include "Dish.h"

class Restoran
{
protected:
	map<int, Dish>m_Menu;
	string m_NameRest;
	string m_StreetRest;
	string m_RaitRest;
	int countDishOfMenu;
	string m_fileName;
public:
	Restoran();
	Restoran(string name, string street, string rait, string namefileMenu);
	Dish getDish(int number);
	void ShowInfoRest();
	void SaveChangeMenu();
	void ShowMenu();
	string getName();
	string getRating();
	void EditTheRestoran();
	void EditTheDish(int index);
	void CreateNewDish(string name, string about, string weight, string price);
};