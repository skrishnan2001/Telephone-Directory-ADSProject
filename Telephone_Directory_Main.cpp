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
		cout << "5. Partial matches\n";
		cout << "6. Frequently searched phone number\n";
		cout << "7. Exit\n\n";
		cout << "Enter your choice : ";
		cin >> ch;
		switch(ch)
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
					if(directory.Is_Empty())
					{
						cout << endl << "\nThe phone directory doesn't have any records\n";
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
					string phone_num;
					phone_num = accept_phone_num();
					directory.Partial_Matches(phone_num);
					break;
				}	
			
			case 6:
				directory.Frequent_keys();
				break;
		}
		
	} while(ch != 7);
	return 0;
}

string accept_phone_num()
{
	string phone_num;
	cout << endl << "Enter the phone number : ";
	getline(cin >> ws, phone_num);
	return phone_num;
}

string accept_name()
{
	string name;
	cout << endl << "Enter the person's name : ";
	getline(cin >> ws, name);
	return name;
}


