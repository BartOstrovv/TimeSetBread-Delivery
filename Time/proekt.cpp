#include "Admin.h"

void ShowRestaurants(Admin& adm, bool rating)
{
	int Num = 1;
	if (rating)
	{
		cout << "Num|        Name        |Rating" << endl;
		cout << "------------------------------" << endl;
		for (auto& i : adm.getVectorRest())
		{
			cout << " " << Num << ".| ";
			if (i.getName().length() < 10)
			{
				cout << i.getName() << "\t\t| " << i.getRating() << endl;
			}
			else
			{
				cout << i.getName() << "\t| " << i.getRating() << endl;
			}
			Num++;
		}
		cout << endl;
	}
	else
	{
		cout << "Num|        Name        |" << endl;
		cout << "-------------------------" << endl;
		for (auto& i : adm.getVectorRest())
		{
			cout << " " << Num << ".| ";
			if (i.getName().length() < 10)
			{
				cout << i.getName() << "\t\t|" << endl;
			}
			else
			{
				cout << i.getName() << "\t|" << endl;
			}
			Num++;
		}
		cout << endl;
	}
}

void AddDish(Admin& adm, Basket& bas)
{
	int Num = 0;
	int quantity = 0;
	int dish = 0;
	cout << "Type number of restaurant to see menu:" << endl;
	cin >> Num;
	if (Num <= adm.getVectorRest().size() && (Num >= 1))
	{
		adm.getVectorRest()[Num - 1].ShowMenu();
		cout << "Choose dish from menu:" << endl;
		cin >> dish;
		if ((dish >= 1) && (dish <= adm.getVectorRest()[Num - 1].getCountOfDish()))
		{
			cout << "How much you want to add?" << endl;
			cin >> quantity;
			if (quantity > 0)
			{
				bas.AddElement(adm.getVectorRest()[Num - 1].getDish(dish - 1), quantity);
				bas.getDish(bas.getCountOfBasket()).m_NameRest = adm.getVectorRest()[Num - 1].getName();
			}
			else
			{
				system("cls");
				cout << "Quantity is 0, so nothing is added to the basket" << endl << endl;
			}
		}
		else
		{
			system("cls");
			cout << "Wrong input!" << endl << endl;
		}
	}
	else
	{
		system("cls");
		cout << "Wrong input!" << endl << endl;
	}
}

void SearchRestaurantName(Admin& adm, Basket& bas)
{
	cin.ignore();
	string name;
	cout << "Type name of the restaurant to search: " << endl;
	getline(cin, name);
	bool search = false;
	int Num = 0;
	int quantity = 0;
	int dish = 0;
	for (auto i : adm.getVectorRest())
	{
		if (i.getName() == name)
		{
			search = true;
			adm.getVectorRest()[Num].ShowInfoRest();
			cout << "Choose dish from menu:" << endl;
			cin >> dish;
			if ((dish >= 1) && (dish <= adm.getVectorRest()[Num].getCountOfDish()))
			{
				cout << "How much you want to add?" << endl;
				cin >> quantity;
				if (quantity > 0)
				{
					bas.AddElement(adm.getVectorRest()[Num].getDish(dish - 1), quantity);
					bas.getDish(bas.getCountOfBasket()).m_NameRest = adm.getVectorRest()[Num].getName();
				}
				else
				{
					system("cls");
					cout << "Quantity is 0, so nothing is added to the basket" << endl << endl;
				}
			}
			else
			{
				system("cls");
				cout << "Wrong input!" << endl << endl;
			}
		}
		Num++;
	}
	if (search == false)
	{
		system("cls");
		cout << "Restaurant not found!" << endl;
	}
}

void SortRestaurantsByRate(Admin& adm)
{
	sort(adm.getVectorRest().begin(), adm.getVectorRest().end(), [](Restoran n1, Restoran n2)
		{
			return n1.getRating() < n2.getRating();
		});
	ShowRestaurants(adm, true);
	cout << endl << endl;
}

void AdministratorMenu(Admin& adm, Basket& bas)
{
	bool work = true;
	while (work)
	{
		char chang;
		int Num = 0;
		ShowRestaurants(adm, false);
		cout << "Select restaurant to edit information." << endl;
		cin >> Num;
		if ((Num > 0) && (Num <= adm.getVectorRest().size()))
		{
			adm.getVectorRest()[Num - 1].ShowInfoRest();
			cout << "1 - Change info of rest, 2 - Change menu, 3 - Create a new dish, 4 - Exit" << endl;
			cin.ignore();
			chang = _getch();
			if (chang == '1') adm.getVectorRest()[Num - 1].EditTheRestoran();
			else if (chang == '2')
			{
				int ind;
				adm.getVectorRest()[Num - 1].ShowMenu();
				cout << "Enter the number of dish to edit" << endl;
				cin >> ind;
				adm.getVectorRest()[Num - 1].EditTheDish(ind);
				cout << "Save changes? 1 - Yes, 2 - No: " << endl;
				ind = (char)_getche();
				if (ind == '1') adm.getVectorRest()[Num - 1].SaveChangeMenu();
				if (ind == '2') cout << "Changes aren`t saved!" << endl;
				system("cls");
			}
			else if (chang == '3')
			{
				cin.ignore();
				string n, a, w, p;
			
				cout << "Enter the name of new Dish: "; cin >> n; cin.clear(); cin.ignore();
				cout << "Enter the information about new Dish: "; getline(cin, a); 
				cout << "Enter the weight of new Dish: "; cin >> w;
				cout << "Enter the price of new Dish: ";  cin.ignore();  cin.clear(); cin >> p;
				adm.getVectorRest()[Num - 1].CreateNewDish(n, a, w, p);
				cout << "Save changes? 1 - Yes, 2 - No: ";
				int ind = (char)_getche();
				if (ind == '1') adm.getVectorRest()[Num - 1].SaveChangeMenu();
				if (ind == '2') cout << "Changes aren`t saved!" << endl;
				system("cls");
			}
			else if (chang == '4')
			{
				work = false;
			}
			else cout << "Wrong input!" << endl;
		}
		else
		{
			cout << "Wrong input!" << endl;
		}
	}
}

void BasketMenu(Basket& bas)
{
	bool basket = true;
	int choice = 0;
	int dish = 0;
	int quantity = 0;
	while (basket)
	{
		cout << "1 - Show basket, 2 - Save Check, 3 - Delete dish in basket, 4 - Clear basket, 5 - Exit from basket" << endl;
		cin >> choice;
		if ((choice > 0) && (choice < 6))
		{
			switch (choice)
			{
			case 1:
			{
				bas.ShowBasket();
			}break;
			case 2:
			{
				system("cls");
				string name; string street; string number; string time;

				cout << "Enter your name: "; cin >> name;
				cout << "Enter your phone number: "; cin >> number;
				cout << "Enter your street: "; cin >> street;
				cout << "Time: "; cin >> time;
				string nameToFile = "Orders\\Client_" + name + ".txt";
				bas.SaveCheck(nameToFile, name, street, number, time);
			}break;
			case 3:
			{
				cout << "Enter the position to delete: " << endl;
				cin >> dish;
				cout << "Enter quantity to delete: " << endl;
				cin >> quantity;
				bas.DelElement(dish, quantity);
				system("cls");
				cout << "Dish deleted." << endl;
			}break;
			case 4:
			{
				bas.Cancel();
				system("cls");
				cout << "Your basket is empty now." << endl;
			}break;
			case 5:
			{
				basket = false;
			}break;
			default:
			{
				cout << "Wrong input!" << endl;
			}
			}
		}
	}
}

int main()
{
	Admin adm{
	vector<Restoran>{ Restoran("Mama_Italia", "Ruska,2","7/10","Mama_Italia.txt"), Restoran("Thai_life","Kyivska,9","6/10","Thai_life.txt"),
		Restoran("Sushi", "Medova,4","9/10","Sushi.txt"), Restoran("Ukrainian_food", "Kaminna,1","8/10","Ukrainian_food.txt") } };
	Basket bas;
	bool avtorization = false;
	bool work = true;
	while (work)
	{
		int choice;
		if (!avtorization)
		{
			cout << "0 - Avtorization to Admin" << endl;
			cout << "1 - Show restaurants." << endl;
			cout << "2 - Search by restaurant name." << endl;
			cout << "3 - Show restaurants by rating." << endl;
			cout << "4 - Go to basket." << endl;
			cout << "5 - Exit." << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
			{	adm.Avtorization(); avtorization = true; }break;
			case 1:
			{	ShowRestaurants(adm, false);
			AddDish(adm, bas);
			system("cls");
			 }break;
			case 2:
			{	SearchRestaurantName(adm, bas);
			system("cls"); }break;
			case 3:
			{	SortRestaurantsByRate(adm); }break;
			case 4:
			{	BasketMenu(bas); }break;
			case 5:
			{	work = false; }break;
			default:
			{	cout << "Wrong input!" << endl; }
			}
		}
		else
		{
			AdministratorMenu(adm, bas);
			system("cls");
			break;
		}
	}
}
