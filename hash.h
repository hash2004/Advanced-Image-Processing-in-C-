#pragma once
#include "image.h"
#include <iostream>
using namespace std;
class Hash
{
protected:
	int size;
	List** hashList;
	int HashFunction(int value);
public:
	Hash(int size);
	void insert(int value);
	bool find(int value);
	bool remove(int value);

};