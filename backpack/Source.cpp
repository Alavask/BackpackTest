#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>

using namespace std;

typedef map<string, pair<int, int>> Dict;
typedef map<string, long> Backpack;

Dict ReadF(string fileName) //Сичтывание файла и заполнение словаря
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
		catch (const std::invalid_argument& err) //Вызывается если вес\цена - не целые числа
		{
			cout << "Corrupted data in file" <<endl;
		}
	}

	return elements;
}

int main()
{
	string fileName = "fruits.txt"; //Файл словаря

	Dict fruits; //Словарь

	fruits = ReadF(fileName); 

	Backpack backpack; //Инвентарь

	string command,name, count;

	bool flag = true; //Флаг правильности выполнения команды

	while (cin >> command) //Цикл ввода
	{
		flag = true;
		if (command == "Add")  //Команда добавления
		{
			cin >> name >> count;
			Dict::iterator it = fruits.find(name);
			if (it != fruits.end()) //Если фрукт есть в словаре
			{
				try
				{
					Backpack::iterator it2 = backpack.find(name); 
					if (it2 == backpack.end()) //Если фрукта нету в инвентаре то добавляем
					{
						backpack[name] = stoi(count); 
					}
					else //Иначе увеличиваем значение
					{
						backpack[name] += stoi(count);
					}
				}
				catch (const std::invalid_argument& err) //Проверка что количество - целое число
				{
					cout << "Wrong value. Command not performed" << endl;
					flag = false;
				}
			}
			else //Если нету - ошибка
			{
				cout << "Unknown fruit. Command not performed" << endl;
				flag = false;
			}
		}
		else if (command == "Remove") //Команда удаления
		{
			cin >> name >> count;
			try
			{
				Backpack::iterator it = backpack.find(name);
				if (it == backpack.end()) //Если нету фрукта в инвентаре - ошибка
				{
					cout << "Unknown fruit. Command not performed" << endl;
					flag = false;
				}
				else //Если есть в инвентаре
				{
					if (backpack[name] < stoi(count)) //Если удаляем больше текущего - ошибка
					{
						cout << "Cant remove " << stoi(count) << " only " << backpack[name] << " " << name << " left" << endl;
						flag = false;
					}
					else if (backpack[name] == stoi(count)) //При равенстве убираем из инвентаря
					{
						backpack.erase(name);
					}
					else //Если удаляем меньше текущего то уменьшаем
					{
						backpack[name] -= stoi(count);
					}
				}
			}
			catch (const std::invalid_argument& err) //Проверка что количество - целое число
			{
				cout << "Wrong value. Command not performed" << endl;
				flag = false;
			}
		}
		else if (command == "Print") //Команда вывода
		{
			cout << setw(20) << left << "Fruit" //Заголовок
				<< setw(10) << left << "Count"
				<< setw(15) << left << "Sum Weight"
				<< setw(10) << left << "Price"
				<< endl;

			long long sumW, sumP; //Подсчет суммарного веса и цены
			sumW = sumP = 0;
			for (auto it = backpack.begin(); it != backpack.end(); ++it) //Вывод элементов
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
		else //Остальной ввод
		{
			cout << "Unknown command" << endl;
		}
		if (flag) //Вывод правильности выполнения команды
		{
			cout << "Done" << endl;
		}
	}
}
