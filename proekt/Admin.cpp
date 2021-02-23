#include "Admin.h"

Admin::Admin(vector<Restoran> restorans) :m_restorans(restorans)
{
	ifstream aFile("passwords.txt");
	try
	{
		if (!aFile.is_open()) throw 0;
		while (!aFile.eof())
		{
			string f, s;
			getline(aFile, f, '|');

			getline(aFile, s, '|');
			m_admPass.push_back(make_pair(f, s));
		}
	}
	catch (exception& ex)
	{
		cout << "Error: " << ex.what() << endl;
	}
	aFile.close();
}
vector<Restoran>& Admin::getVectorRest() { return m_restorans; }
bool Admin::Avtorization()
{

	if (!ok)
	{
		string s, p;
		cout << "Enter the name: "; cin >> s;
		cout << "Enter the password: "; cin >> p;
		for (auto& i : m_admPass)
			if (i.first == s) (i.second == p) ? ok = true : ok = false;
		if (ok) cout << "Hello, admin " << s << endl;
		else cout << "Incorrect name or password. Try again!" << endl;
		Avtorization();
	}
	return ok;
}