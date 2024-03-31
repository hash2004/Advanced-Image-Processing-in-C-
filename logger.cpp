#include "logger.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
logger::logger()
{ 
	loggerfile = "logger.txt";
}
void logger::initialize()
{
	time_t t = time(NULL);
	tm* tPtr = localtime(&t);
		ofstream outfile;
		outfile.open(loggerfile, ios::app);
		outfile << endl << endl << endl;
		outfile << "Logger time: "<< (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
		outfile << "  " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << ":" << (tPtr->tm_sec) << endl;
		outfile.close();	
}
void logger::logging(string operation)
{
	ofstream outfile;
	outfile.open(loggerfile, ios::app);
	outfile << "The operation perfomed is : " << operation << endl;
	outfile.close();
}