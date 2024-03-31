#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "image.h"
#include <sstream> 
using namespace std;
class stack {
private:
	int* data;
	int capacity;
	int size;
public:
	stack();
	stack(int capacity);
	~stack();
	void push(int newElement);
	int pop();
	int top();
	bool isEmpty();
	bool isFull();
	void print();
	int getCapacity();
};

