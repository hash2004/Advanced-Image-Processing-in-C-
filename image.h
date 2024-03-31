#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <sstream> 
#include "LinkedList.h"
#include "quadtree.h"
#include "logger.h"
#include "tqueue.h"
#include "stack.h"
using namespace std;
class image
{
	string version;
	int** Data;
	int height;
	int width;
	int maxgrey;
	string comment;
	string filename;
	List* rlcList;
	void save();
	void saveF(string file);
	int** rlcData;
	int* verticalprojection;
	int* horizontalprojection;
	int* combinedprojection;
	logger log;
	queuei* QueueRow;
	queuei* QueueCol;
	stack* stackRow;
	stack* stackCol;
	int** temparr;
	int** qarr;
	int** sarr;
public:
	image(string Filename);
	int getmaxgrey();
	string getcomment();
	string getfilename();
	int getheight();
	int getwidth();
	void readPGM();
	void readPGMhash();
	int GetPixel(int row, int col);
	void SetPixel(int row, int col,int val);
	int GetSize();
	void ConvertNegative();
	void printData();
	long double MeanPixelValue();
	int whitePixels();
	int blackPixels();
	void mean_row();
	int** returnData();
	void RLCencoding();
	void RLCdecoding(string rlcFile);
	void RLCFormatBlackPixels();
	void RLCnegative(string rlcFile);
	void displayrlclist();
	void makingprojections();
	int returnimagesum();
	void RecursiveComponentQueue(int userow,int usercol, int controlval);
	void RecursiveComponentStack(int userow, int usercol, int controlval);
	void findcomponentsQueue();
	void findcomponentsStack();
	void quadtreeimpl();
};