#include "Admin.h"

int main()
{
	Admin adm{
	vector<Restoran>{ Restoran("Mama_Italia", "Ternopil","7/10","Mama_Italia.txt"), Restoran("Thai_life","Lviv","6/10","Thai_life.txt"),
		Restoran("Sushi", "Kiev","9/10","Sushi.txt"), Restoran("Ukrainian_food", "Kiev","8/10","Ukrainian_food.txt") } };
	Basket bas;
	bool avtorization = false;
	bool work = true;
	int baskInd = 1; // added
	int quantity = 0;
	int Num = 1;
	int dish = 1;
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
			{
				adm.Avtorization(); avtorization = true; break;
			}
			case 1:
			{
				Num = 1;
				cout << "Restaurant list:" << endl;
				for (auto& i : adm.getVectorRest())
				{
					cout << Num << ": ";
					cout << i.getName() << endl;
					Num++;
				}
				cout << "Type number of restaurant to see menu, type 0 to go back " << endl;
				cin >> Num;
				if (Num <= adm.getVectorRest().size())
				{
					if (Num == 0)
					{
						break;
					}
					else
					{
						adm.getVectorRest()[Num - 1].ShowMenu();
						cout << "Choose dishes, type 0 to go back" << endl;
						dish = 1;
						while (dish != 0)
						{
							cin >> dish;
							if (dish != 0)
							{
								cout << "How much you want to add?" << endl;
								cin >> quantity;
								bas.AddElement(adm.getVectorRest()[Num - 1].getDish(dish - 1), quantity);
								bas.getDish(baskInd++).m_NameRest = adm.getVectorRest()[Num - 1].getName();
							}
						}

					}
				}
				else
				{
					cout << "Wrong input!" << endl;
				}
			}break;
			case 2:
			{
				cin.ignore();
				string name;
				cout << "Type name of the restaurant to search: " << endl;
				getline(cin, name);
				bool search = false;
				Num = 0;
				for (auto i : adm.getVectorRest())
				{
					if (i.getName() == name)
					{
						cout << "There is restaurant with name \"" << name << "\"" << endl;
						search = true;
						adm.getVectorRest()[Num].ShowInfoRest();
						dish = 1;
						cout << "Choose dishes, type 0 to go back" << endl;
						while (dish != 0)
						{
							cin >> dish;
							if (dish != 0)
							{
								cout << "How much you want to add?" << endl;
								cin >> quantity;
								bas.AddElement(adm.getVectorRest()[Num].getDish(dish - 1), quantity);
								bas.getDish(baskInd++).m_NameRest = adm.getVectorRest()[Num].getName();
							}
						}
					}
					Num++;
				}
				if (search == false)
				{
					cout << "Restaurant not found!" << endl;
				}
			}break;
			case 3:
			{
				sort(adm.getVectorRest().begin(), adm.getVectorRest().end(), [](Restoran n1, Restoran n2)
					{
						return n1.getRating() < n2.getRating();
					});
				Num = 1;
				for (auto& i : adm.getVectorRest())
				{
					cout << Num << ": ";
					cout << "Name: "<<i.getName() << " Rating: "<< i.getRating() << endl;
					Num++;
				}
					
			}break;
			case 4:
			{
				bool basket = true;
				int choice = 0;
				cout << "1 - Show basket, 2 - Save Check, 3 - Delete dish in Basket, 4 - Exit from basket" << endl;
				while (basket)
				{
					cin >> choice;
					if (choice == 1)
						bas.ShowBasket();
					else if (choice == 3)
					{
						cout << "Enter the position to delete: " << endl;
						cin >> dish;
						cout << "Enter quantity to delete: " << endl;
						cin >> quantity;
						bas.DelElement(dish, quantity);
					}
					else if (choice == 2)
					{
						string name; string street; string number; string time;

						cout << "Enter your name: "; cin >> name;
						cout << "Enter your phone number: "; cin >> number;
						cout << "Enter your street: "; cin >> street;
						cout << "Time: "; cin >> time;

						bas.SaveCheck("testSaveCheck.txt", name, street, number, time);
					}
					else if (choice == 4)
					{
						break;
					}
					else
					{
						cout << "Wrong input!" << endl;
					}
				}
			}break;
			case 5:
			{
				work = false;
			}break;
			default:
			{
				cout << "Wrong input!" << endl;
			}
			}
		}
		else
		{
			char chang;
			Num = 1;
			cout << "Restaurant list:" << endl;
			for (auto& i : adm.getVectorRest())
			{
				cout << Num << ": ";
				cout << i.getName() << endl;
				Num++;
			}
			cout << "Select restaraunt to edit information!" << endl;
			cin >> Num;
			adm.getVectorRest()[Num - 1].ShowInfoRest();
			cout << "1 - Change info of rest, 2 - Change info of menu?, 3 - Create a new dish?, 4 - Exit" << endl;
			chang = _getch();
			if (chang == '1') adm.getVectorRest()[Num - 1].EditTheRestoran();
			else if (chang == '2')
			{
				int ind;
				adm.getVectorRest()[Num - 1].ShowMenu();
				cout << "Enter the number of dish to edit" << endl;
				cin >> ind;
				adm.getVectorRest()[Num - 1].EditTheDish(ind);
			}
			else if (chang == '3')
			{
				cin.ignore();
				string n, a, w, p;
				cout << "Enter the name of new Dish" << endl; cin >> n;
				cout << "Enter information about new Dish " << endl; cin >> a;
				cout << "Enter weigtht of the new Dish" << endl; cin >> w;
				cout << "Enter price of the new Dish" << endl; cin >> p;
				adm.getVectorRest()[Num - 1].CreateNewDish(n, a, w, p);
			}
			else if (chang == '4')
			{
				break;
			}
			else cout << "Wrong input!" << endl;
		}
	}
}
