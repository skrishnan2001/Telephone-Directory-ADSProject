#include <iostream>
#include <string>
#include "Telephone_Directory.h"
using namespace std;

string accept_phone_num();
string accept_name();

int main()
{
	Phone_Directory directory;
	int ch;

	do
	{
		cout << "\n1. Insert a new record\n";
		cout << "2. Delete an existing record\n";
		cout << "3. Display the phone directory\n";
		cout << "4. Search by phone number\n";
		cout << "5. Search By Name\n";
		cout << "6. Partial matches\n";
		cout << "7. Frequently searched phone number\n";
		cout << "8. Exit\n\n";
		cout << "Enter your choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
		{
			string name, phone_num;
			name = accept_name();
			phone_num = accept_phone_num();
			directory.Insert_Record(phone_num, name);
			break;
		}

		case 2:
		{
			string phone_num;
			phone_num = accept_phone_num();
			directory.Delete_Record(phone_num);
			cout << "\nThe record has been deleted !\n";
			break;
		}

		case 3:
		{
			directory.count = 0;
			if (directory.Is_Empty())
			{
				cout << endl
					 << "\nThe phone directory doesn't have any records\n";
				break;
			}
			directory.Display_Records(directory.root);
			cout << endl;
			break;
		}

		case 4:
		{
			string phone_num;
			phone_num = accept_phone_num();
			directory.search_key(phone_num);
			break;
		}

		case 5:
		{
			string search_name;
			search_name = accept_name();

			if (!directory.name_found(search_name))
				cout << "\nThere are no records with name " << search_name << endl;

			else
			{
				cout << "\n--------------------------------------------\n";
				cout << "Name\t\t\tPhone number" << endl;
				cout << "--------------------------------------------\n";
				directory.search_by_name(search_name);

				cout << "--------------------------------------------\n";
			}
			break;
		}

		case 6:
		{
			string partial_detail;
			int f = 0;
			cout << endl
				 << "Enter the phone number/name : ";
			getline(cin >> ws, partial_detail);
			for (int i = 0; i < partial_detail.length(); i++)
			{
				if ((partial_detail[i] >= 65 && partial_detail[i] <= 90) || (partial_detail[i] >= 97 && partial_detail[i] <= 122))
				{
					f = 1;
					break;
				}
			}
			if (f == 0)
				directory.Partial_Matches(partial_detail);
			if (f == 1)
				directory.Partial_Matches_Name(partial_detail);
			break;
		}

		case 7:
		{
			directory.Frequent_keys();
			break;
		}
		}

	} while (ch != 8);
	cout << "\nExiting....Thank you!\n";
	return 0;
}

string accept_phone_num()
{
	string phone_num;
	cout << endl
		 << "Enter the phone number : ";
	getline(cin >> ws, phone_num);
	return phone_num;
}

string accept_name()
{
	string name;
	cout << endl
		 << "Enter the person's name : ";
	getline(cin >> ws, name);
	return name;
}
