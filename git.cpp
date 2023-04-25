#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

ifstream input;
ofstream output;

string subject[9] = { "���.��" , "���.��" , "����.���." , "�.�." , "���������� " , "���-��" , "�������" , "���������" , "��.��." };

struct date {
	int day;
	int month;
	int year;
};

bool checkdate(date data)
{
	if (data.day >= 1 and data.day <= 31 and data.month >= 1 and data.month <= 12 and data.year <= 2023 and data.year >= 1000)
		return true;
	else
		return false;
}

class marks
{
public:
	string name;
	int amarks[8];
};

class node {
public:
	string secname;
	string name;
	string fac;
	string kafedra;
	string group;
	string studak;
	date dr;
	bool pol;
	int postup;
	class marks ocenka[9];
	class node* next;
	node()
	{
		for (int i = 0; i < 9; i++)
		{
			this->ocenka[i].name = subject[i];
		}
	}
};

class node* myhead;

int countitem = 0;

void printdate(date data)
{
	if (data.day > 9)
	{
		cout << data.day;
	}
	else
	{
		cout << '0' << data.day;
	}
	cout << '.';
	if (data.month > 9)
	{
		cout << data.month;
	}
	else
	{
		cout << '0' << data.month;
	}
	cout << '.';
	cout << data.year << ' ';
}
void printitem()
{
	class node* current = myhead;
	cout << endl;
	system("cls");
	cout << '\t' << "0.\t �������� ������ ��������." << endl << endl;
	int item = 0;
	while (current)
	{
		cout << '\t' << item + 1 << ".\t";
		item++;
		cout << "  " << current->secname << ' ' << current->name << ' ' << current->group << endl;
		current = current->next;
	}
}

void safe()
{
	output.open("file.txt", ios_base::out);
	class node* current = myhead;
	while (current)
	{
		output << current->secname << ' ' << current->name << ' ' << current->fac << ' ' << current->kafedra << ' ' << current->group << ' ' << current->studak << ' ';
		output << current->dr.day << ' ' << current->dr.month << ' ' << current->dr.year << ' ' << current->pol << ' ' << current->postup << ' ';
		for (int i = 0; i < 9; i++)
		{

			for (int j = 0; j < 8; j++)
			{
				output << current->ocenka[i].amarks[j] << ' ';
			}
		}
		output << endl;
		current = current->next;
	}
	output.close();
}

void additem(node data, int& Count)
{
	class node* newitem = new node();
	newitem->secname = data.secname;
	newitem->name = data.name;
	newitem->fac = data.fac;
	newitem->kafedra = data.kafedra;
	newitem->group = data.group;
	newitem->studak = data.studak;
	newitem->dr.day = data.dr.day;
	newitem->dr.month = data.dr.month;
	newitem->dr.year = data.dr.year;
	newitem->pol = data.pol;
	newitem->postup = data.postup;
	for (int i = 0; i < 9; i++)
	{
		newitem->ocenka[i] = data.ocenka[i];
	}
	if (Count == 0)
	{
		newitem->next = NULL;
	}
	else
	{
		newitem->next = myhead;
	}
	myhead = newitem;
	countitem++;
	Count++;
}

void deleteitem(int index, int& count)
{
	if (index > 0 and count > 0 and index <= count)
	{

		class node* current = myhead;
		class node* old;
		if (index == 1)
		{
			old = myhead;
			myhead = current->next;
			delete old;
			countitem--;
			count--;
		}
		else {
			int i = 0;
			while (current)
			{
				if (i == index - 2) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					countitem--;
					count--;
					break;
				}
				current = current->next;
				i++;
			}

		}
	}
	safe();
}

void printmarks(node* otm)
{
	for (int i = 0; i < 9; i++)
	{
		cout << otm->ocenka[i].name << ' ';
	}
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 5) cout << "  ";
			cout << otm->ocenka[j].amarks[i] << "       ";
		}
		cout << endl;
	}
	cout << endl;
}

void editmarks(node* stud, int index)
{
	system("cls");
	class node* current = myhead;
	for (int i = 0; i < index - 1; i++)
	{
		current = current->next;
	}
	printmarks(current);
	cout << "����� ������� ��� ��������� ���������������:\n 1 - ����� \n 2 - ����� \n 3 - ����.���. \n 4 - �.�. \n 5 - ���������� \n 6 - ���-�� \n 7 - ������� \n 8 - ��������� \n 9 - ��.�� \n";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 0:
		break;
	default:
		cout << "�������������� ��������: " << current->ocenka[ch - 1].name << endl;
		int sem;
		cout << "������� ������� ��� ���������: �� 1 �� 8\n";
		cin >> sem;
		switch (sem)
		{
		case 0:
			break;
		default:
		a9:			int mark;
			cout << "������� �������: �� 2 �� 5\n";
			cin >> mark;
			if (mark < 2 or mark > 5)
			{
				cout << "������ ����� �������: ������� ������� �� �������� �� 2 �� 5.\n";
				goto a9;
			}
			current->ocenka[ch - 1].amarks[sem - 1] = mark;
			break;
		}
		break;
	}

}

void edititem(int index, int& Count)
{
	string a1, b1, c1;
	class node* current = myhead;
	if (index >= 0 and index <= countitem and countitem > 0)
	{
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		int st;
	c1:		system("cls");
		cout << "  " << current->secname << ' ' << current->name << ' ' << current->fac << ' ' << current->kafedra << ' ' << current->group << ' ' << current->studak << ' ';
		printdate(current->dr);
		if (current->pol == 1)
		{
			cout << "�������" << ' ';
		}
		else
		{
			cout << "�������" << ' ';
		}
		cout << current->postup;
		cout << endl;
		cout << endl;

		printmarks(current);
		cout << "\n\n�������, ��� ��� ��������� �������� � ������ ��������: \n 0 - ������� ��������\n 1 - ������� \n 2 - ���";
		cout << "\n 3 - ��������� \n 4 - �������� \n 5 - ������ \n 6 - ����� �������� ������ \n 7 - ���� �������� \n 8 - ��� \n 9 - ��� ����������� \n 10 - �������� ������ \n 11 - ��������� � ����\n";
		cin >> st;
		string a, b;
		switch (st)
		{
		case 0:
			deleteitem(index, Count);
			break;
		case 1:
		y1:			cout << "\n ������� ����� �������:\t";
			cin >> a;
			if (size(a) > 20)
			{
				cout << "������. ������� �� ������ ���� ������� 20 ��������\n";
				goto y1;
			}
			for (int i = 0; i < size(a); i++)
				if (a[i] >= '\0' && a[i] <= '@' or a[i] >= '[' && a[i] <= '`' or a[i] >= '{' && a[i] <= 191)
				{
					cout << "������. ������� ������ ��������� ������ ����� ���������� ��� �������� ��������\n";
					goto y1;
				}
			current->secname = a;
			break;
		case 2:
		y2:			cout << "\n ������� ����� ���:\t";
			cin >> b;
			if (size(b) > 20)
			{
				cout << "������. ��� �� ������ ���� ������� 20 ��������\n";
				goto y2;
			}
			for (int i = 0; i < size(b); i++)
				if (b[i] >= '\0' && b[i] <= '@' or b[i] >= '[' && b[i] <= '`' or b[i] >= '{' && b[i] <= 191)
				{
					cout << "������ �����. ��� ������ ��������� ������ ����� ���������� ��� �������� ��������\n";
					goto y2;
				}
			current->name = b;
			break;
		case 3:
			cout << "\n ������� ����� ���������:\t";
			cin >> current->fac;
			break;
		case 4:
			cout << "\n ������� ����� ��������:\t";
			cin >> current->kafedra;
			break;
		case 6:
			cout << "\n ������� ����� ����� �������� ������:\t";
			cin >> current->studak;
			break;
		case 5:
			cout << "\n ������� ����� ������:\t";
			cin >> current->group;
			break;
		case 7:
		p1:	cout << "\n ������� ����� ���� ��������:\t";
			date tempdata;
			cin >> a1 >> b1 >> c1;
			for (int i = 0; i < size(a1); i++) if (!(a1[i] > '/' and a1[i] < ':')) { cout << "� ���� ��������� ������������ ������ �����\n"; goto p1; }
			tempdata.day = stoi(a1);
			for (int i = 0; i < size(b1); i++) if (!(b1[i] > '/' and b1[i] < ':')) { cout << "� ���� ��������� ������������ ������ �����\n"; goto p1; }
			tempdata.month = stoi(b1);
			for (int i = 0; i < size(c1); i++) if (!(c1[i] > '/' and c1[i] < ':')) { cout << "� ���� ��������� ������������ ������ �����\n"; goto p1; }
			tempdata.year = stoi(c1);
			if (checkdate(tempdata)) current->dr = tempdata;
			else
			{
				cout << "������ � ���� ��������\n";
				goto p1;
			}
			break;
		case 8:
			cout << "\n ������� ����� ���: 1 - ������� 0 - �������\t";
			cin >> current->pol;
			break;
		case 9:
			cout << "\n ������� ����� ��� �����������:\t";
			cin >> current->postup;
			break;
		case 10:
			editmarks(current, index);
			break;
		case 11:
			break;
		default:
			goto c1;
		}
		safe();
	}
	else
	{
		cout << "������ ����� �������";
	}
}

void creatingfile()
{
	output.open("file.txt", ios_base::app);
	output.close();
}

int countofrows()
{
	int count = 0;
	input.open("file.txt", ios_base::in);
	while (!input.eof())
	{
		if (input.get() == '\n')
		{
			count++;
		}
	}
	input.close();
	return count;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node temp;
	setlocale(LC_ALL, "ru");
	string a1, b1, c1;
	int ch;
	int count = 0;
	creatingfile();
	count = countofrows();
	cout << " count = " << count << endl;
	int& Count = count;
	int max = count;


	input.open("file.txt", ios_base::in);
	for (int i = 0; i < max; i++)
	{
		input >> temp.secname >> temp.name >> temp.fac >> temp.kafedra >> temp.group >> temp.studak >> temp.dr.day >> temp.dr.month >> temp.dr.year >> temp.pol >> temp.postup;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				input >> temp.ocenka[i].amarks[j];
			}
		}
		additem(temp, Count);
	}
	input.close();


a1:	printitem();
	cout << "\n �������, ���� ������ ��������: \n";
	cin >> ch;
	if (ch > countitem or ch < 0) { cout << "������. ������ �������� ������\n"; goto a1; }
	string a, b;
	switch (ch)
	{
	case 0:
	b1:		cout << "������� �������:\n";
		cin >> a;
		if (size(a) > 20)
		{
			cout << "������. ������� �� ������ ���� ������� 20 ��������\n";
			goto b1;
		}
		for (int i = 0; i < size(a); i++)
			if (a[i] >= '\0' && a[i] <= '@' or a[i] >= '[' && a[i] <= '`' or a[i] >= '{' && a[i] <= 191)
			{
				cout << "������ �����. ������� ������ ��������� ������ ����� ���������� ��� �������� ��������\n";
				goto b1;
			}
		temp.secname = a;
	b2:		cout << "�������  ���:\n";
		cin >> b;
		if (size(b) > 20)
		{
			cout << "������. ��� �� ������ ���� ������� 20 ��������\n";
			goto b2;
		}
		for (int i = 0; i < size(b); i++)
			if (b[i] >= '\0' && b[i] <= '@' or b[i] >= '[' && b[i] <= '`' or b[i] >= '{' && b[i] <= 191)
			{
				cout << "������ �����. ��� ������ ��������� ������ ����� ���������� ��� �������� ��������\n";
				goto b2;
			}
		temp.name = b;
		cout << "�������  ���������:\n";
		cin >> temp.fac;
		cout << "�������  ��������:\n";
		cin >> temp.kafedra;
		cout << "�������  ������:\n";
		cin >> temp.group;
		cout << "�������  ����� �������� ������:\n";
		cin >> temp.studak;
	z1:		cout << "�������  ���� ��������:\n";
		date tempdata;
		cin >> a1 >> b1 >> c1;
		for (int i = 0; i < size(a1); i++) if (!(a1[i] > '/' and a1[i] < ':')) { cout << "� ���� ����� ������������ ������ �����\n"; goto z1; }
		tempdata.day = stoi(a1);
		for (int i = 0; i < size(b1); i++) if (!(b1[i] > '/' and b1[i] < ':')) { cout << "� ���� ����� ������������ ������ �����\n"; goto z1; }
		tempdata.month = stoi(b1);
		for (int i = 0; i < size(c1); i++) if (!(c1[i] > '/' and c1[i] < ':')) { cout << "� ���� ����� ������������ ������ �����\n"; goto z1; }
		tempdata.year = stoi(c1);
		if (checkdate(tempdata)) temp.dr = tempdata;
		else
		{
			cout << "������ � �������� ����\n";
			goto z1;
		}
		cout << "�������  ���: 1 - ������� 0 - �������\n";
		cin >> temp.pol;
		cout << "������� ��� �����������:\n";
		cin >> temp.postup;
		cout << "������� ������� �� ���������:\n";
		for (int i = 0; i < 9; i++)
		{
			cout << "������������� ������� �� ��������: " << temp.ocenka[i].name << endl;
			for (int j = 0; j < 8; j++)
			{
			x3:				int test;
				cin >> test;
				if (test < 2 or test > 5)
				{
					cout << "\n ������. ������� �� ����� ���� ������ 2 ��� ������ 5\n";
					goto x3;
				}
				temp.ocenka[i].amarks[j] = test;

			}
		}
		additem(temp, Count);
		safe();
		goto a1;
	default:
		edititem(ch, Count);
		goto a1;
	}
}