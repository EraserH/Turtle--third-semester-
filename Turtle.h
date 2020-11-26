//������������ ����� ��������, � ���� ���� ��������������� ����

#include <iostream>
#pragma once

//const char* turtle ::commands[5] = { "CW", "CCW", "GO", "DRAW", "SKIP" }; 
// �� �������, ������ �������, �������� ��� �� ��������
//const char* directionList;

struct commandArray;

using namespace std;

class Turtle{
private:
	static enum Commands {
		CW, //�� �������	(������� ������������ ���� ���������)
		CCW, //������ �������	(������ ������������ ���� ���������)
		GO,
		DRAW,
		SKIP
	};

	struct commandArray {
		unsigned int command;
		unsigned int stepsNum = 0;
	};

	//� ��� �� ����� �������, ���� ���
	static unsigned int checkCommands(char*, Turtle::commandArray**);

private: //������ �������
	commandArray* listOfComm;
	size_t size;
	Turtle(commandArray* _listOfComm, size_t _size);
public:

	//����������� �� ���������
	Turtle();

	//��� ��� ����������, �� �� ������

	//�����������
	Turtle(size_t _size);

	//����������� �����������
	Turtle(const Turtle& _commands);

	//�������� ������������ ������������
	Turtle& operator=(const Turtle& _commands);

	//����������� �����������
	Turtle(Turtle&& _commands)noexcept;

	//�������� ������������ ������������
	Turtle& operator=(Turtle&& _commands)noexcept;

	bool operator==(Turtle _turtle)const;
	bool operator!=(Turtle _turtle)const;

	//����������
	~Turtle();

	static void makeListOfComms(char*, Turtle*);

	//�������� ��������� ������� �� �������
	commandArray& operator[](size_t);

	//����� �������� ������� �� �������
	void deleteCommand(size_t);

	//����� ���������� ������� �� ������� (���������, ��������� �� ������� ������)
	void addCommand(size_t, commandArray);

	//�������� �������� ���� ����������
	friend Turtle operator+(Turtle, Turtle); 
	//��������� �� ������ ��� ����� � ������� ���������� ���������� ��������

	//�������� �������� ���������� � ������� (���������� ������� � ����� �������)
	friend Turtle operator+(Turtle, commandArray);

	//�������� �������� ������� � ���������� (���������� ������� � ������ �������)
	friend Turtle operator+(commandArray, Turtle);

	//�������� ������ ������� ������ (���������, ����� �������� ��� ���)
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