#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>

using namespace std;

typedef map<string, pair<int, int>> Dict;
typedef map<string, long> Backpack;

Dict ReadF(string fileName) //���������� ����� � ���������� �������
{
	ifstream istr(fileName);
	Dict elements;
	string name,weight,price;
	while (istr >> name >> weight >> price)
	{
		try
		{			
			elements[name] = pair<int, int>(stoi(weight), stoi(price));
		}
		catch (const std::invalid_argument& err) //���������� ���� ���\���� - �� ����� �����
		{
			cout << "Corrupted data in file" <<endl;
		}
	}

	return elements;
}

int main()
{
	string fileName = "fruits.txt"; //���� �������

	Dict fruits; //�������

	fruits = ReadF(fileName); 

	Backpack backpack; //���������

	string command,name, count;

	bool flag = true; //���� ������������ ���������� �������

	while (cin >> command) //���� �����
	{
		flag = true;
		if (command == "Add")  //������� ����������
		{
			cin >> name >> count;
			Dict::iterator it = fruits.find(name);
			if (it != fruits.end()) //���� ����� ���� � �������
			{
				try
				{
					Backpack::iterator it2 = backpack.find(name); 
					if (it2 == backpack.end()) //���� ������ ���� � ��������� �� ���������
					{
						backpack[name] = stoi(count); 
					}
					else //����� ����������� ��������
					{
						backpack[name] += stoi(count);
					}
				}
				catch (const std::invalid_argument& err) //�������� ��� ���������� - ����� �����
				{
					cout << "Wrong value. Command not performed" << endl;
					flag = false;
				}
			}
			else //���� ���� - ������
			{
				cout << "Unknown fruit. Command not performed" << endl;
				flag = false;
			}
		}
		else if (command == "Remove") //������� ��������
		{
			cin >> name >> count;
			try
			{
				Backpack::iterator it = backpack.find(name);
				if (it == backpack.end()) //���� ���� ������ � ��������� - ������
				{
					cout << "Unknown fruit. Command not performed" << endl;
					flag = false;
				}
				else //���� ���� � ���������
				{
					if (backpack[name] < stoi(count)) //���� ������� ������ �������� - ������
					{
						cout << "Cant remove " << stoi(count) << " only " << backpack[name] << " " << name << " left" << endl;
						flag = false;
					}
					else if (backpack[name] == stoi(count)) //��� ��������� ������� �� ���������
					{
						backpack.erase(name);
					}
					else //���� ������� ������ �������� �� ���������
					{
						backpack[name] -= stoi(count);
					}
				}
			}
			catch (const std::invalid_argument& err) //�������� ��� ���������� - ����� �����
			{
				cout << "Wrong value. Command not performed" << endl;
				flag = false;
			}
		}
		else if (command == "Print") //������� ������
		{
			cout << setw(20) << left << "Fruit" //���������
				<< setw(10) << left << "Count"
				<< setw(15) << left << "Sum Weight"
				<< setw(10) << left << "Price"
				<< endl;

			long long sumW, sumP; //������� ���������� ���� � ����
			sumW = sumP = 0;
			for (auto it = backpack.begin(); it != backpack.end(); ++it) //����� ���������
			{
				Dict::iterator it2 = fruits.find((*it).first);
				cout  <<setw(20) << left << (*it).first  
					<< setw(10) << left << (*it).second 
					<< setw(15) << left << (long long)((*it2).second.first*(*it).second)
					<< setw(10) << left << (*it2).second.second
					<< endl;
				sumW += (long long)((*it2).second.first*(*it).second);
				sumP += (long long)((*it2).second.second*(*it).second);
			}
			cout << endl;
			cout << "Summary Weight: " << sumW << " Summary Price: " << sumP << endl;;
		}
		else //��������� ����
		{
			cout << "Unknown command" << endl;
		}
		if (flag) //����� ������������ ���������� �������
		{
			cout << "Done" << endl;
		}
	}
}
