#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;
class logger
{
protected:
	string loggerfile;
public:
	logger();
	void initialize ();
	void logging(string operation);
};