#include <iostream>
#include "Turtle.h"
#include "windows.h"


using namespace std;


bool enterCommands(Turtle& _turtle) {
	char* str = new char[200];
	cout << endl << "Введите команды в строку: ";
	fgets(str, 200, stdin);
	str[strlen(str) - 1] = 0;
	try {
		Turtle::makeListOfComms(str, &_turtle);
	}
	catch (int) {
		delete[] str;
		return false;
	}
	delete[] str;
	return true;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Turtle _turtle;
	//enterCommands(_turtle);
	while (!enterCommands(_turtle))
		cerr << "Error: Something gone wrong";
	cout << endl << _turtle;
	//else cerr << "Error: Something gone wrong";

	//Демонстрация рисунка
	cout << endl << endl;
	followTurtle(_turtle);

	Turtle _turtle1;
	while (!enterCommands(_turtle1))
		cerr << "\nError: Something gone wrong";
	cout << endl << _turtle1;

	try {
	//Демонстрация конкатенации
	_turtle1 = _turtle[0] + _turtle1 + _turtle[2] + _turtle;
	cout << endl << "Строка №2: " << _turtle1 << endl;

	//Демонстрация получения команд по индексу
		_turtle[0] = _turtle1[0];
		cout << endl << "Строка №1: " << _turtle;
		//Демонстрация удаления команд
		_turtle.deleteCommand(2);
		cout << endl << "Строка №1: " << _turtle;
		_turtle.deleteCommand(1);
		cout << endl << "Строка №1: " << _turtle;
		_turtle.deleteCommand(0);
		cout << endl << "Строка №2: " << _turtle1 << endl;
		//Turtle _turtle2 = _turtle + _turtle1 + _turtle1;
		//cout << endl << "Строка №1: " << _turtle;
		cout << endl << "Строка №2: " << _turtle1 << endl;// << _turtle1 << _turtle1[2] << _turtle[1] << _turtle[2] << endl << endl;
		//cout << endl << "Строка №3: " << _turtle2;
	}
	catch (int) {
		cerr << "Wrong indexes";
	}


	try {
		//Демонстрация добавления команд
		_turtle.addCommand(0, _turtle[0]);
		cout << endl << "Строка №1: " << _turtle;
		_turtle.deleteCommand(0);
		cout << endl << "Строка №1: " << _turtle;
		_turtle.addCommand(1, _turtle[0]);
		cout << endl << "Строка №1: " << _turtle;
	}
	catch (int) {
		cerr << "\nWrong indexes";
	}

	return 0;
}
