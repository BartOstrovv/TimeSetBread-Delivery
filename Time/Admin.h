#pragma once

#include "Basket.h"

class Admin
{
	bool ok = false;
	vector<Restoran> m_restorans;
	vector <pair<string, string>> m_admPass;
public:
	Admin(vector<Restoran> restorans);
	vector<Restoran>& getVectorRest();
	bool Avtorization();
};