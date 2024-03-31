#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "hash.h"
#include <sstream> 
#include <ctime>
using namespace std;
int main()
{
    

    logger* log = new logger();
    log->initialize();
    image* test = new image("apple-18.pgm");
    test->readPGM();
    cout << "Welcome to Hashim's version of Data structures module." << endl;
    int user = 1;
    int temph = 0;
    int tempw = 0;
    int htemp = 0;
    int wtemp = 0; 
    int tempv = 0;
    while (user == 1 || user ==2 || user ==3 || user == 4 || user == 5 || user == 6)
    {
        cout << "Press 1 to see the implementation of question 1." << endl;
        cout << "Press 2 to see the implementation of question 2." << endl;
        cout << "Press 3 to see the implementation of question 3." << endl;
        cout << "Press 4 to see the implementation of question 4." << endl;
        cout << "Press 5 to see the implementation of question 5." << endl;
        cout << "Press 6 to see the implementation of question 6." << endl;

        cout << "Press anything else for termination" << endl;
        cin >> user;
        if (user == 1)
        {
            cout << "The mean pixel value is " << test->MeanPixelValue() << endl;
            cout << "The number of black pixels are " << test->blackPixels() << endl;
            cout << "The number of white pixels are " << test->whitePixels() << endl;
            cout << "Mean of black pixels in each row is: " << endl;
            test->mean_row();
            cout << endl;
            cout << "Enter pixel coordinates to get pixel value" << endl;
            cout << "Height : ";
            cin >> temph;
            cout << "Width : ";
            cin >> tempw;
            cout <<"Pixel value: "<< test->GetPixel(temph, tempw) << endl;
            cout << "Enter set pixel coordinates: " << endl;
            cout << "Height : ";
            cin >> htemp;
            cout << "Width : ";
            cin >> wtemp;
            cout << "value: ";
            cin >> tempv;
            test->SetPixel(htemp, wtemp,tempv);
            cout << "Do you want to convert the image to negative, 1 for yes, press any other integer to move on" << endl;
            cin >> tempv;
            if (tempv == 1)
            {
                test->ConvertNegative();
                cout << "Same Getpixel as before value is : " << test->GetPixel(temph, tempw) << endl;
                cout << "Same Setpixel as before value is : " << test->GetPixel(temph, tempw) << endl;
            }
            cout << "The size of this file is " << test->GetSize()<<" Bytes "  << endl;
        }
        if (user == 2)
        {
            test->findcomponentsQueue();
            log->logging("Connected components through queues");
        }
        if (user == 3)
        {
            test->findcomponentsStack();
            log->logging("Connected components through stacks");
        }
        if (user == 4)
        {
            test->RLCencoding();
            cout << "The image has been encoded in RLC formal. The information is stored in a list" << endl; 
            int tempv = 0;
            cout << "Press 1 to view the list, press any other integer to move on" << endl;
            cin >> tempv;
            if (tempv == 1)
                test->displayrlclist();
            test->RLCdecoding("RLC.txt");
            cout << "The RLC formatted list has been decoded and the image has been displayed in the rlc file" << endl;
            cout << "You can view it now" << endl;
            tempv = 0;
            cout << "If you want to convert the image to negative press 1, press anything for Q4 to terminate" << endl;
            cin >> tempv;
            if(tempv == 1)
                test->RLCnegative("RLC.txt");
           
            cout << "To view number of black pixels, press 1" << endl;
            tempv = 0;
            cin >> tempv;
            if (tempv == 1)
                test->RLCFormatBlackPixels();
        }
        if (user == 5)
        {
            test->quadtreeimpl();
        }
        if (user == 6)
        {
            Hash hashmap(23);

            image** hashIMAGES = new image*[30];
            string file_name = "image";
            for (int i = 0; i < 30; i++)
            {
                if (i < 10)
                {
                    stringstream ss;
                    ss << i+1;
                    string filehelp;
                    ss >> filehelp;
                    hashIMAGES[i] = new image(file_name + "00"+filehelp+".pgm");
                    hashIMAGES[i]->readPGMhash();
                    cout<<"Image number " << i + 1 << " ";
                    hashmap.insert(hashIMAGES[i]->returnimagesum());
                }
                else
                {
                    stringstream ss;
                    ss << i + 1;
                    string filehelp;
                    ss >> filehelp;
                    hashIMAGES[i] = new image(file_name + "0" + filehelp+".pgm");
                    hashIMAGES[i]->readPGMhash();
                    cout << "Image number " << i + 1 << " ";
                    hashmap.insert(hashIMAGES[i]->returnimagesum());
                }
            }   
            log->logging("30 images inserted into hashmap");
        }
    }
    return 0;
} 
