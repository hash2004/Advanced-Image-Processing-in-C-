#pragma once
class Node
{
protected:
	Node* next;
	int data;
public:
	Node();
	~Node();
	Node(int data);
	Node* getNext();
	int getData();
	void setNext(Node* next);
	void setData(int data);
};