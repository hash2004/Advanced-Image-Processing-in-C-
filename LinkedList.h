#pragma once
#include "Node.h"

class List
{
protected:
	Node* head;
	Node* current;
	Node* lastCurrent;
	int size;
public:
	List();
	~List();
	Node* getCurrent();
	Node* returnhead();
	//void setCurrent(Node* newCurrent);
	void add(int data);
	void remove(int dataToRemove);
	bool find(int data);
	void addAtFirstLocation(int data);
	void addAtLast(int data);
	void displayList();
	int returndata(Node* curr);
};

