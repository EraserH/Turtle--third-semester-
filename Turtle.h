//КОнструкторы нужно поменять, с ними беды фундаментальные беды

#include <iostream>
#pragma once

//const char* turtle ::commands[5] = { "CW", "CCW", "GO", "DRAW", "SKIP" }; 
// по часовой, против часовой, рисовать или не рисовать
//const char* directionList;

struct commandArray;

using namespace std;

class Turtle{
private:
	static enum Commands {
		CW, //По часовой	(направо относительно носа черепашки)
		CCW, //Против часовой	(налево относительно носа черепашки)
		GO,
		DRAW,
		SKIP
	};

	struct commandArray {
		unsigned int command;
		unsigned int stepsNum = 0;
	};

	//А тут мы плюём ошибкой, если что
	static unsigned int checkCommands(char*, Turtle::commandArray**);

private: //Данные объекта
	commandArray* listOfComm;
	size_t size;
	Turtle(commandArray* _listOfComm, size_t _size);
public:

	//КОНСТРУКТОР ПО УМОЛЧАНИЮ
	Turtle();

	//Эти два объединить, но не срочно

	//КОНСТРУКТОР
	Turtle(size_t _size);

	//КОНСТРУКТОР КОПИРОВАНИЯ
	Turtle(const Turtle& _commands);

	//ОПЕРАТОР ПРИСВАИВАНИЯ КОПИРОВАНИЕМ
	Turtle& operator=(const Turtle& _commands);

	//КОНСТРУКТОР ПЕРЕМЕЩЕНИЯ
	Turtle(Turtle&& _commands)noexcept;

	//ОПЕРАТОР ПРИСВАИВАНИЯ ПЕРЕМЕЩЕНИЕМ
	Turtle& operator=(Turtle&& _commands)noexcept;

	bool operator==(Turtle _turtle)const;
	bool operator!=(Turtle _turtle)const;

	//ДЕСТРУКТОР
	~Turtle();

	static void makeListOfComms(char*, Turtle*);

	//ОПЕРАТОР ПОЛУЧЕНИЯ КОМАНДЫ ПО ИНДЕКСУ
	commandArray& operator[](size_t);

	//МЕТОД УДАЛЕНИЯ КОМАНДЫ ПО ИНДЕКСУ
	void deleteCommand(size_t);

	//МЕТОД ДОБАВЛЕНИЯ КОМАНДЫ ПО ИНДЕКСУ (проверить, правильно ли написан вообще)
	void addCommand(size_t, commandArray);

	//ОПЕРАТОР СЛОЖЕНИЯ ДВУХ ТРАЕКТОРИЙ
	friend Turtle operator+(Turtle, Turtle); 
	//Передаётся по ссылке для связи в цепочку выполнения нескольких операция

	//ОПЕРАТОР СЛОЖЕНИЯ ТРАЕКТОРИИ И КОМАНДЫ (ДОБАВЛЕНИЕ КОМАНДЫ В КОНЕЦ МАССИВА)
	friend Turtle operator+(Turtle, commandArray);

	//ОПЕРАТОР СЛОЖЕНИЯ КОМАНДЫ И ТРАЕКТОРИИ (ДОБАВЛЕНИЕ КОМАНДЫ В НАЧАЛО МАССИВА)
	friend Turtle operator+(commandArray, Turtle);

	//ОПЕРАТОР вывода массива команд (проверить, будет работать или нет)
	friend ostream& operator<<(std::ostream&, const Turtle&);

	friend ostream& operator<<(std::ostream&, const Turtle::commandArray);

	friend void followTurtle(Turtle _turtle);

	//friend void generateRandomCommands(Turtle&, int, int, int);
};

void drawTurtle(int*, int*, char, unsigned int, bool, char**, bool*, unsigned int&);

/*class Status {
private:
	friend class Turtle;

	const char directionList[5] = { 'r', 'd', 'l', 'u', 0 }; //right, down, left, up
	struct listOfStatuses {
		int xPos;
		int yPos;
		char direction;
		bool dr;
		listOfStatuses* next;
	};

private:
	listOfStatuses* head;
	unsigned length = 0;
	bool cash = true;

public:
	void change(Turtle::commandArray);

	unsigned calcLen(Turtle _turtle);

};*/