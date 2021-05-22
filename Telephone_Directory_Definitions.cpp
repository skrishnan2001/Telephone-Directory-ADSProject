#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <string>
#include "Telephone_Directory.h"
using namespace std;

Phone_Directory :: Phone_Directory()
{
	nullRecord = new node;
	nullRecord->left = nullRecord->right = nullRecord;
	root = nullRecord;
}

Phone_Directory :: ~Phone_Directory()
{
	Make_Empty(root);
	delete root;
}

void Phone_Directory :: Insert_Record(string phone_num, string name)
{
	node *newRecord = new node;
	newRecord->left = newRecord->right = nullRecord;
	newRecord->phone_num = phone_num;
	newRecord->name = name;
	
	if(root == nullRecord)
		root = newRecord;
	
	else
	{
		splay(phone_num, root);
		if(phone_num < root->phone_num)
		{
			newRecord->left = root->left;
			newRecord->right = root;
			root->left = nullRecord;
			root = newRecord;
		}
		
		else if(phone_num > root->phone_num)
		{
			newRecord->right = root->right;
			newRecord->left = root;
			root->right = nullRecord;
			root = newRecord;
		}
		
		else
			return;
	}
	cout << "\nEntry has been successfully inserted into the directory!!\n" ;
}

void Phone_Directory :: splay(string phone_num, node *&t)
{
	node header;
	header.left = header.right = nullRecord;
	node *leftTreeMax, *rightTreeMin;
	leftTreeMax = rightTreeMin = &header;
	nullRecord->phone_num = phone_num;
	while(1)
	{
		if(phone_num < t->phone_num)
		{
			if(phone_num < t->left->phone_num)
				rotate_with_left_child(t);
			
			if(t->left == nullRecord)
				break;
			
			rightTreeMin->left = t;
			rightTreeMin = t;
			t=t->left;
		}
		
		else if(phone_num > t->phone_num)
		{
			if(phone_num > t->right->phone_num)
				rotate_with_right_child(t);
			
			if(t->right == nullRecord)
				break;
			
			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}
		
		else
			break;
	}
	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}

void Phone_Directory :: rotate_with_left_child(node *&k2)
{
	node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void Phone_Directory :: rotate_with_right_child(node *&k2)
{
	node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
}

void Phone_Directory :: Delete_Record(string phone_num)
{
	node *newTree = NULL;
	if(!contains(phone_num))
	{
		cout << phone_num << " is not present in the directory!!\n\n";
		return;
	}
	
	if(root->right == nullRecord)
		newTree = root->left;
	
	else
	{
		newTree = root->right;
		splay(phone_num, newTree);
		newTree->left = root->left;
	}
	delete root;
	root = newTree;
}

bool Phone_Directory :: contains(string phone_num)
{
	splay(phone_num, root);
	return root->phone_num == phone_num;
}

bool Phone_Directory :: Is_Empty()
{
	return root == nullRecord;
}

void Phone_Directory :: Make_Empty(node *&t)
{
	while(t != nullRecord)
		Delete_Record(t->phone_num);
}

int Phone_Directory::count = 0;

void Phone_Directory :: Display_Records(node *t)
{
	if(t == NULL)
	{
		cout << "\nThe phone directory has zero entries!!\n";
		return;
	}
	cout << "\n--------------------------------------------\n";
	cout << "Name\t\t\tPhone number" << endl;
	cout << "--------------------------------------------\n";
	print(t);
	cout << "--------------------------------------------\n";
}

void Phone_Directory :: print(node *&t)//Preorder traversal
{
	if(t != t->left)
	{
		cout << t->name << "\t\t" << t->phone_num << endl;
		print(t->left);
		print(t->right);
	}
}

void Phone_Directory :: search_key(string phone_num)
{
	if(!contains(phone_num))
	{
		cout << phone_num << " is not present in the directory!!\n";
		return;
	}
	cout << endl;
	cout << "Name : " << root->name << endl;
	cout << "Phone number : " << root->phone_num << endl;
	root->count++;
}

void Phone_Directory :: Partial_Matches(string phone_num)
{
	vector<node *> Partial_Matched_phonenum;
	stack<node *> TEMP_Stk;
	if(Is_Empty())
	{
		cout << "\nThe phone directory is empty !!\n";
		return;
	}
	TEMP_Stk.push(root);
	int count_keys = 1;
	while(TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		int m = temp->phone_num.size(), n = phone_num.size();
		int LCS[m + 1][n + 1];
		int result = 0;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= n; j++)
			{
				if(i == 0 || j == 0)
				{
					LCS[i][j] = 0;
					continue;
				}
				char L = temp->phone_num[i - 1], R = phone_num[j - 1];
				
				
				
				if(L == R)
				{
					LCS[i][j] = LCS[i - 1][j - 1] + 1;
					//result = max(result, LCS[i][j]);
				}
				
				else
					LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
		if(LCS[m][n] == n)
		{
			cout << count_keys << "." << temp->phone_num << endl;
			count_keys++;
			Partial_Matched_phonenum.push_back(temp);
		}
		
		if(temp->right != nullRecord)
			TEMP_Stk.push(temp->right);
		
		if(temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}
	if(Partial_Matched_phonenum.size() == 0)
	{
		cout << "\nNo partial matches found !!" << endl;
		return;
	}
	int choice;
	cout << endl << "Enter your choice : ";
	cin >> choice;
	if(choice < 1 || choice > Partial_Matched_phonenum.size())
	{
		cout << "\nInvalid choice !!\n";
		return;
	}
	node *Final = Partial_Matched_phonenum[choice - 1];
	cout << endl;
	cout << "Name : " << Final->name << endl;
	cout << "Phone number : " << Final->phone_num << endl;
	Final->count++;
	splay(Final->phone_num, root);
}

void Phone_Directory :: Frequent_keys()
{
	vector<node *> Frequents;
	stack<node *> TEMP_Stk;
	if(Is_Empty())
	{
		cout << "\nThe phone directory has zero records !!\n";
		return;
	}
	TEMP_Stk.push(root);
	while(TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		if(temp->count > 0)
		{
			Frequents.push_back(temp);
			sort(Frequents);
		}
		
		if(temp->right != nullRecord)
			TEMP_Stk.push(temp->right);
		
		if(temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}
	
	if(Frequents.size() == 0)
	{
		cout << "\nNo phone number was searched\n";
		return;
	}
	cout << endl;
	for(int i = 0; i < Frequents.size(); i++)
	{
		cout << "Name : " << Frequents[i]->name << endl;
		cout << "Phone number : " << Frequents[i]->phone_num << endl;
		cout << "Search frequency : " << Frequents[i]->count << endl << endl;
	}
}

void Phone_Directory :: sort(vector<node *> &Frequents)
{
	int size = Frequents.size();
	node *last = Frequents[size - 1];
	int i = size - 2;
	while(i >= 0 && Frequents[i]->count < last->count)
	{
		Frequents[i + 1] = Frequents[i];
		i--;
	}
	Frequents[i + 1] = last;
}
