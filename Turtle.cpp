//КОнструкторы нужно поменять, с ними беды фундаментальные беды

#include <iostream>
#include "Turtle.h"
#include <ctime>

bool TRACE = false;

//const char* turtle ::commands[5] = { "CW", "CCW", "GO", "DRAW", "SKIP" }; 
// по часовой, против часовой, рисовать или не рисовать
//const char directionList[4] = { 'r', 'd', 'l', 'u' }; //right, down, left, up

using namespace std;


unsigned int Turtle::checkCommands(char* string, Turtle::commandArray** _ptr) {
	
	unsigned int numberOfComm = 0;
	char word[6];
	auto mass = new Turtle::commandArray[50];
	auto sizeOfMass = 50;
	
	size_t index = 0;
	size_t i = 0;

	for (i; i < strlen(string); ++i) string[i] = tolower(string[i]);
	i = 0;

	while (string[i] != 0) {
		if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= '0' && string[i] <= '9')) {
			size_t j = 0;

			while (((string[i] >= 'a' && string[i] <= 'z') ||
				(string[i] >= '0' && string[i] <= '9')) && j < 5 && i < strlen(string)) {
				word[j] = string[i];
				++i;
				++j;
			}
			word[j] = 0;

			if (index >= sizeOfMass) {
				auto _mass = new Turtle::commandArray[sizeOfMass + 50];
				sizeOfMass += 50;

				for (size_t _i = 0; _i < sizeOfMass; ++_i){
					_mass[_i] = mass[_i];
				}

				delete[] mass;
				mass = _mass;
				_mass = nullptr;
			}

			//Переделать в switch
			if (strcmp(word, "cw") == 0) 
				mass[index].command = 'CW';
			else if (strcmp(word, "ccw") == 0) 
				mass[index].command = 'CCW';
			else if (strcmp(word, "draw") == 0) 
				mass[index].command = 'DRAW';
			else if (strcmp(word, "skip") == 0) 
				mass[index].command = 'SKIP';

			else {
				if (strlen(word) < 3) {
					throw - 1;
				}
				else if (word[0] != 'g' || word[1] != 'o') {
					throw - 1;
				}
				for (size_t z = 2; z < strlen(word); ++z) {
					if (word[z] < '0' || word[z] > '9') {
						throw - 1;
					}
				}
				mass[index].command = 'GO';
				char dynamsteps[4];
				size_t z;
				for (z = 2; z < strlen(word); ++z) {
					dynamsteps[z - 2] = word[z];
				}
				dynamsteps[z - 2] = 0;
				mass[index].stepsNum = atoi(dynamsteps);
			}
			++numberOfComm;
			++index;
		}

		++i;
	}
	*_ptr = mass;
	return numberOfComm;
}

//КОНСТРУКТОР ПО УМОЛЧАНИЮ
Turtle::Turtle() : listOfComm(new Turtle::commandArray[0]), size(0)
{
	if (TRACE)
		cout << endl << "DEBUG: _Default_ constructor worked here" << endl;
	//стоит ли здесь выделять память под пустой массив, или просто обнулить указатель?
}

//Эти два объединить, но не срочно

//КОНСТРУКТОР
Turtle::Turtle(size_t _size) :
	listOfComm(new commandArray[_size]), size(_size)
	//Длину, наверное, убрать надо
{
	if (TRACE)
		cout << endl << "DEBUG: Constructor worked here" << endl;
	//Здесь объект просто создаётся, элементы никак не инициализируются
}

//КОНСТРУКТОР КОПИРОВАНИЯ
Turtle::Turtle(const Turtle& _commands) :
	listOfComm(new Turtle::commandArray[_commands.size]), size(_commands.size)
{
	if (TRACE)
		cout << endl << "DEBUG: _Copy_ constructor worked here" << endl;
	for (size_t i = 0; i < size; ++i)
	{
		listOfComm[i] = _commands.listOfComm[i];
	}
}

//ОПЕРАТОР ПРИСВАИВАНИЯ КОПИРОВАНИЕМ
Turtle& Turtle::operator=(const Turtle& _commands)
{
	if (TRACE)
		cout << endl << "DEBUG: _Copy_ (OPERATOR =) worked here" << endl;
	auto data = new Turtle::commandArray[_commands.size];
	for (size_t i = 0; i < _commands.size; ++i)
	{
		data[i] = _commands.listOfComm[i];
	}
	delete[] listOfComm;
	listOfComm = data;
	size = _commands.size;
	return *this;
}

//КОНСТРУКТОР ПЕРЕМЕЩЕНИЯ
Turtle::Turtle(Turtle&& _commands)noexcept :
	listOfComm(_commands.listOfComm), size(_commands.size)
{
	if (TRACE)
		cout << endl << "DEBUG: _Move_ constructor worked here" << endl;
	_commands.listOfComm = nullptr;
	_commands.size = 0;
}

//ОПЕРАТОР ПРИСВАИВАНИЯ ПЕРЕМЕЩЕНИЕМ
Turtle& Turtle::operator=(Turtle&& _commands)noexcept
{
	if (TRACE)
		cout << endl << "DEBUG: _Move_ (OPERATOR =) worked here" << endl;

	delete[] listOfComm;
	size = _commands.size;
	listOfComm = _commands.listOfComm;

	_commands.listOfComm = nullptr;
	_commands.size = 0;

	return *this;
}

//Оператор сравнения
bool Turtle::operator==(Turtle _turtle) const {
	if (size != _turtle.size)
		return false;
	for (size_t i = 0; i < size; ++i) {
		if (listOfComm[i].command != _turtle.listOfComm[i].command)
			return false;
		else if (listOfComm[i].command == 'GO')
			if (listOfComm[i].stepsNum != _turtle.listOfComm[i].stepsNum)
				return false;
	}
	return true;
}

//Оператор неравенства (тоже сравнения, но наоборот)
bool Turtle::operator!=(Turtle _turtle) const {
	return !operator==(_turtle);
}

//ДЕСТРУКТОР
Turtle::~Turtle()
{
	if (TRACE)
		cout << endl << "DEBUG: Destructor worked here" << endl;
	delete[] listOfComm;
	listOfComm = nullptr;
}

void Turtle::makeListOfComms(char* string, Turtle* first) {
	Turtle::commandArray* _ptr = NULL;
	unsigned int numberOfCommands;
	try {
		numberOfCommands = Turtle::checkCommands(string, &_ptr);
	}

	catch (int) {
		//cout << endl << "Вы ввели неправильный список команд. Повторите ввод.";
		delete[] _ptr;
		throw - 1;
	}

	//Turtle first;
	Turtle::commandArray* array = new Turtle::commandArray[numberOfCommands];
	for (size_t i = 0; i < numberOfCommands; ++i)
		array[i] = _ptr[i];
	delete[] (*first).listOfComm;
	(*first).size = numberOfCommands;
	(*first).listOfComm = array;
	array = nullptr;
	delete[] _ptr;
}

//ОПЕРАТОР ПОЛУЧЕНИЯ КОМАНДЫ ПО ИНДЕКСУ (плюётся ошибкой если что)
Turtle::commandArray& Turtle::operator[](size_t index) 
{
	if (index >= size || index < 0) 
		throw - 1;
	return listOfComm[index];
}

//МЕТОД УДАЛЕНИЯ КОМАНДЫ ПО ИНДЕКСУ (плюётся ошибкой если что)
void Turtle::deleteCommand(size_t index) {

	if (index >= size || index < 0)
		throw - 1;

	auto array = new Turtle::commandArray[size];
	auto j = 0;

	for (size_t i = 0; i < size; ++i) {
		if (i == index) continue;
		array[j] = listOfComm[i];
		++j;
	}

	--size;
	delete[] listOfComm;
	listOfComm = array;
}

//МЕТОД ДОБАВЛЕНИЯ КОМАНДЫ ПО ИНДЕКСУ (проверить, правильно ли написан вообще) 
//(плюётся ошибкой если что)
void Turtle::addCommand(size_t index, Turtle::commandArray _command) {
	if (index > size || index < 0)
		throw - 1;

	auto array = new Turtle::commandArray[++size];
	auto j = 0;

	for (size_t i = 0; i < size; ++i) {
		if (i == index) {
			array[i] = _command;
			continue; //Здесь j не увеличится
		}
		array[i] = listOfComm[j];
		++j;
	}

	delete[] listOfComm;
	listOfComm = array;

}

//ОПЕРАТОР СЛОЖЕНИЯ ДВУХ ТРАЕКТОРИЙ
//надо бы проверку на самоприсваивание бахнуть типа: list1 = list1+list2 (типа +=)
Turtle operator+(Turtle first, Turtle second)
{
	if (TRACE)
		cout << endl << "DEBUG: _Object+Object_ Operator+ worked here";
	Turtle result;
	delete[] result.listOfComm;
	result.listOfComm = new Turtle::commandArray[first.size + second.size];
	for (size_t i = 0; i < first.size; ++i)
	{
		result.listOfComm[i] = first.listOfComm[i];
	}

	for (size_t i = first.size; i < first.size + second.size; ++i)
	{
		result.listOfComm[i] = second.listOfComm[i - first.size];
	}
	result.size = first.size + second.size;
	//Turtle result(L, first.size + second.size);
	return result;
}

//ОПЕРАТОР СЛОЖЕНИЯ ТРАЕКТОРИИ И КОМАНДЫ (ДОБАВЛЕНИЕ КОМАНДЫ В КОНЕЦ МАССИВА)
Turtle operator+(Turtle first, Turtle::commandArray Command)
{
	if (TRACE)
		cout << endl << "DEBUG: _Object+Command_ Operator+ worked here";
	auto arr = new Turtle::commandArray[first.size + 1];
	for (size_t i = 0; i < first.size; ++i)
		arr[i] = first.listOfComm[i];
	arr[first.size] = Command;
	Turtle result;
	delete[] result.listOfComm;
	result.listOfComm = arr;
	result.size = first.size + 1;
	return result;
}

//ОПЕРАТОР СЛОЖЕНИЯ КОМАНДЫ И ТРАЕКТОРИИ (ДОБАВЛЕНИЕ КОМАНДЫ В НАЧАЛО МАССИВА)
Turtle operator+(Turtle::commandArray Command, Turtle first)
{
	if (TRACE)
		cout << endl << "DEBUG: _Command+Object_ Operator+ worked here";
	auto arr = new Turtle::commandArray[first.size + 1];
	arr[0] = Command;
	for (size_t i = 1; i <= first.size; ++i)
		arr[i] = first.listOfComm[i-1];
	Turtle result;
	delete[] result.listOfComm;
	result.listOfComm = arr;
	result.size = first.size + 1;
	return result;
}

//Функция вывода массива команд (проверить, будет работать или нет)
ostream& operator<<(ostream& out, const Turtle& first) {
	//out << endl << "out_operator worked here";
	string str = "";
	for (size_t i = 0; i < first.size; ++i) {
		switch (first.listOfComm[i].command) {
		case 'CW':
			str += "CW ";
			break;
		case 'CCW':
			str += "CCW ";
			break;
		case 'GO':
			str += "GO";
			char intToStr[4];
			_itoa_s(first.listOfComm[i].stepsNum, intToStr, 10);
			str += intToStr;
			str += " ";
			break;
		case 'DRAW':
			str += "DRAW ";
			break;
		case 'SKIP':
			str += "SKIP ";
			break; 
		/*switch (first.listOfComm[i].command) {
		case 0:
			out << "CW" << endl;
			break;
		case 1:
			out << "CCW" << endl;
			break;
		case 2:
			out << "GO" << " " << first.listOfComm[i].stepsNum << endl;
			break;
		case 3:
			out << "DRAW" << endl;
			break;
		case 4:
			out << "SKIP" << endl;
			break;*/
		}
	}
	//cout << str << endl;
	out <<  str;
	return out;
}

ostream& operator<<(std::ostream& out, const Turtle::commandArray _command) {
	string str = "";
	switch (_command.command) {
	case 'CW':
		str += "CW ";
		break;
	case 'CCW':
		str += "CCW ";
		break;
	case 'GO':
		str += "GO";
		char intToStr[4];
		_itoa_s(_command.stepsNum, intToStr, 10);
		str += intToStr;
		str += " ";
		break;
	case 'DRAW':
		str += "DRAW ";
		break;
	case 'SKIP':
		str += "SKIP ";
		break;
	}
	out << str;
	return out;
}

void drawTurtle(int* xPos, int* yPos, char direction, unsigned int number,
	bool ifdraw, char** field, bool *symbolCash, unsigned int& length) {
	bool cash = true;
	
	if (*symbolCash)
		field[*yPos][*xPos] = '*'; //Если точка под S закрашена, это надо запомнить
	else field[*yPos][*xPos] = '.';

	if (number == 0 && ifdraw) {
		*symbolCash = true;
		return;
	}

	unsigned int numberOfSteps = 0; //можно снова запихнуть в класс
	switch (direction) {
	case 'r':
		for (size_t i = 0; i < number; ++i) {
			if (*xPos > 19) {
				*xPos = 19;
				break;
			}
			if (ifdraw)
				field[*yPos][*xPos] = '*';
			++(*xPos);
			++numberOfSteps;
			cash = false;
		}
		break;
	case 'u':
		for (size_t i = 0; i < number; ++i) {
			if (*yPos < 0) {
				*yPos = 0;
				break;
			}
			if (ifdraw)
				field[*yPos][*xPos] = '*';
			--(*yPos);
			++numberOfSteps;
			cash = false;
		}
		break;
	case 'l':
		for (size_t i = 0; i < number; ++i) {
			if (*xPos < 0) {
				*xPos = 0;
				break;
			}
			if (ifdraw)
				field[*yPos][*xPos] = '*';
			--(*xPos);
			++numberOfSteps;
			cash = false;
		}
		break;
	case 'd':
		for (size_t i = 0; i < number; ++i) {
			if (*yPos > 19) {
				*yPos = 19;
				break;
			}
			if (ifdraw)
				field[*yPos][*xPos] = '*';
			++(*yPos);
			++numberOfSteps;
			cash = false;
		}
		break;
	}
	if (field[*yPos][*xPos] == '*')
		*symbolCash = true;
	else *symbolCash = false;

	field[*yPos][*xPos] = 'S';

	if (!cash)
		length += numberOfSteps;

	return;
}

void followTurtle(Turtle _turtle) {
	int xPos = 0;
	int yPos = 0;
	char direction = 'r';
	bool ifdraw = true;
	unsigned length = 0;
	bool cash = true;
	bool symbolCash = false;

	char** field = new char* [20]; // Поле (матрица) 20 на 20
	for (size_t i = 0; i < 20; ++i)
		field[i] = new char[20];

	for (size_t i = 0; i < 20; ++i) 
		for (size_t j = 0; j < 20; ++j)
			field[i][j] = '.';

	for (size_t i = 0; i < _turtle.size; ++i) {
		switch (_turtle.listOfComm[i].command) {
		case 'CW':
			if (direction == 'r')
				direction = 'd';
			else if (direction == 'd')
				direction = 'l';
			else if (direction == 'l')
				direction = 'u';
			else if (direction == 'u')
				direction = 'r';
			break;
		case 'CCW':
			if (direction == 'r')
				direction = 'u';
			else if (direction == 'u')
				direction = 'l';
			else if (direction == 'l')
				direction = 'd';
			else if (direction == 'd')
				direction = 'r';
			break;
		case 'DRAW':
			ifdraw = true;
			break;
		case 'SKIP':
			ifdraw = false;
			break;
		case 'GO':
			drawTurtle(&xPos, &yPos, direction, _turtle.listOfComm[i].stepsNum, 
				ifdraw, field, &symbolCash, length);
			break;
		}
	}

	for (size_t i = 0; i < 20; ++i) { 
		cout << endl;
		for (size_t j = 0; j < 20; ++j)
			cout << field[i][j] << " ";
	}
	//CW GO5 GO0 SKIP CCW GO3
	//CW GO5 SKIP GO0 CCW GO3
	//CW GO5 GO0 CCW GO3 Go0 ccw go5 go0 ccw go15 skip cw cw

	cout << endl << endl << "ROUTE LENGTH = " << length << endl;
}

/*void generateRandomCommands(Turtle& _turtle, int size, int min, int max) {
	srand(time(0));
	for (auto i = 0; i < size; ++i) {
		//_turtle.listOfComm[i].command = rand();
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		// Равномерно распределяем рандомное число в нашем диапазоне
		_turtle.listOfComm[i].command = static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

}*/

/*Turtle& Turtle::makeListOfComms(char* string) {
	unsigned int numberOfCommands;
	try {
		numberOfCommands = Turtle::checkCommands(string);
	}

	catch (int) {
		cout << endl << "Вы ввели неправильный список команд. Повторите ввод.";
		throw - 1;
	}

	//Создаём объект и удаляем нулевой массив из кучи
	Turtle first = Turtle();
	delete[] first.listOfComm;

	//Новый массив
	auto Mass = new Turtle::commandArray[numberOfCommands];

	//Слово
	char word[6]; //Выделение памяти под word
	char* dynamsteps; //Строка для количества шагов, если команда GO

	size_t index = 0;

	size_t i = 0;
	while (string[i] != 0) { //Побуквенное добавление слова из строки
		string[i] = tolower(string[i]);
		if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= '0' && string[i] <= '9')) {
			size_t j = 0;

			//Создание слова
			while ((string[i] >= 'a' && string[i] <= 'z') ||
				(string[i] >= '0' && string[i] <= '9' || j > 5)) {
				word[j] = string[i];
				++i;
				++j;
			}
			word[j] = 0;

			//Проверка на соответствие какой-либо из команд
			if (strcmp(word, "cw") == 0) {
				first.listOfComm[index].command = 'CW';
				first.listOfComm[index].stepsNum = 0;
			}
			else if (strcmp(word, "ccw") == 0) {
				first.listOfComm[index].command = 'CCW';
				first.listOfComm[index].stepsNum = 0;
			}
			else if (strcmp(word, "draw") == 0) {
				first.listOfComm[index].command = 'DRAW';
				first.listOfComm[index].stepsNum = 0;
			}
			else if (strcmp(word, "skip") == 0) {
				first.listOfComm[index].command = 'SKIP';
				first.listOfComm[index].stepsNum = 0;
			}

			else if (word[0] == 'g' && word[1] == 'o') {
				first.listOfComm[index].command = 'GO';
				char dynamsteps[4]; 
				for (size_t z = 2; z < strlen(word); ++z) {
					dynamsteps[z - 2] = word[z];
				}
				first.listOfComm[index].stepsNum = atoi(dynamsteps);

			}

			else throw - 1;
			//Вообще, проверка на это должна быть в методе checkCommands
			++index;
		}

		++i;
	}
	return first;
}*/

/*unsigned Status::calcLen(Turtle _turtle) {
	if (cash) return length;

	unsigned len = 0;
	for (size_t i = 0; i < _turtle.size; ++i)
		if (_turtle.listOfComm[i].command == 'GO')
			len += _turtle.listOfComm[i].stepsNum;
	return len;
}

void Status::change(Turtle::commandArray _command) {
	switch (_command.command) {
	case 'CW':
		if (direction == 'u')
			direction = directionList[0];
		else {
			size_t i = 0;
			for (i; i < 3; ++i)
				if (direction == directionList[i])
					break;
			direction = directionList[++i];
		}
		break;
	case 'CCW':
		if (direction == 'r')
			direction = directionList[0];
		else {
			size_t i = 1;
			for (i; i < 4; ++i)
				if (direction == directionList[i])
					break;
			direction = directionList[--i];
		}
		break;
	case 'DRAW':
		dr = true;
		break;
	case 'SKIP':
		break;
	case 'GO':
		break;
	}
}*/