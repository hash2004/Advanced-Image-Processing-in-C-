#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "image.h"
#include "stack.h"
#include <sstream> 
using namespace std;
stack ::stack()
{
capacity = 50;
data = new int [capacity];
size = 0;
this->capacity = capacity;
}

stack::stack(int capacity) {
	if (capacity <= 0)
	capacity = 50;
	data = new int [capacity];
	size = 0;
	this->capacity = capacity;
}
stack ::~stack() {
	delete[] data;
}
void stack ::push(int newElement) {
	if (size < capacity)
		data[size++] = newElement;
	//else
		//cout << "Stack is full" << endl;
}
int stack ::pop() {
	return data[--size];
}
int stack ::top() {
	return data[size - 1];
}
bool stack ::isEmpty() {
	return size == 0;
}
bool stack ::isFull() {
	return size == capacity;
}
void stack ::print() {
	for (int i = size - 1; i >= 0; --i)
		std::cout << data[i];
}
int stack ::getCapacity() {
	return capacity;
}
