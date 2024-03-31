#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <sstream>
#include "image.h"
using namespace std;
image::image(string Filename)
{
    version = "";
    height = 0;
    width = 0;
    maxgrey = 0;
    Data = NULL;
    rlcData = NULL;
    verticalprojection = NULL;
    horizontalprojection = NULL;
    combinedprojection = NULL;
    comment = "";
    filename = Filename;
    rlcList = new List();
    QueueRow = new queuei(5000);
    QueueCol = new queuei(5000);
    stackRow = new stack(5000);
    stackCol = new stack(5000);
    qarr = NULL;
    temparr = NULL;
    sarr = NULL; //constructor 
}
void image::readPGM()
{
    char c;
    ifstream myfile(filename);
    string inputLine = "";

    getline(myfile, inputLine);
    cout << "Version : " << inputLine << endl;
    version = inputLine;

    getline(myfile, inputLine);
    cout << "File name : " << inputLine << endl;

    getline(myfile, inputLine);
    cout << "Comment : " << inputLine << endl;
    comment = inputLine;

    getline(myfile, inputLine);
    string subsize1 = inputLine.substr(0, 3);
    string subsize2 = inputLine.substr(4, 3);
    height = stoi(subsize1);
    width = stoi(subsize2);
    cout << "Height is " << height << " and Width is " << width << endl;


    getline(myfile, inputLine);
    cout << "Max grey level : " << inputLine << endl;
    string subgrey = inputLine.substr(0, 3);
    maxgrey = stoi(subgrey);
    //took all the string data into different string variables 
    rlcData = new int* [height];
    for (int i = 0; i < height; i++) {
        rlcData[i] = new int[width];
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rlcData[i][j] = 0;
        }
    }


     Data = new int* [height];
    for (int i = 0; i < height; i++) {
        Data[i] = new int[width];
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {

            myfile >> c;
            if (c == 'ÿ' || c == '1')
            {
                Data[i][j] = 255;
            }
            else
            {
                Data[i][j] = 0;
            }
      }
    }
    //reads data , on is 255, off is 0
    myfile.close();
    log.logging("Reading image");
 
}
void image::readPGMhash()
{
    char c;
    ifstream myfile(filename);
    string inputLine = "";

    getline(myfile, inputLine);
    cout << "Version : " << inputLine << endl;
    version = inputLine;

    /*getline(myfile, inputLine);
    cout << "File name : " << inputLine << endl;

    getline(myfile, inputLine);
    cout << "Comment : " << inputLine << endl;
    comment = inputLine;*/

    getline(myfile, inputLine);
  /*  string subsize1 = inputLine.substr(0, 3);
    string subsize2 = inputLine.substr(4, 3);
    height = stoi(subsize1);
    width = stoi(subsize2);*/
    height = 640;
    width = 400;
    cout << "Height is " << height << " and Width is " << width << endl;


    getline(myfile, inputLine);
    cout << "Max grey level : " << inputLine << endl;
    //string subgrey = inputLine.substr(0, 3);
    maxgrey = 255;

    rlcData = new int* [height];
    for (int i = 0; i < height; i++) {
        rlcData[i] = new int[width];
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rlcData[i][j] = 0;
        }
    }


    Data = new int* [height];
    for (int i = 0; i < height; i++) {
        Data[i] = new int[width];
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {

            myfile >> c;
            if (c == 'ÿ' || c == '1')
            {
                Data[i][j] = 255;
            }
            else
            {
                Data[i][j] = 0;
            }
        }
    }

    myfile.close();
    log.logging("Reading image");
    //made a different read function for the other images, because the format was a bit different
    //not fully generic because of visual studio errors.

}
int image::getheight()
{
    log.logging("getting height");
    return height;
}
int image::getwidth()
{
    log.logging("getting width");
    return width;
}
int image::GetPixel(int row, int col)
{
    if (row >= 0 && row <= 256 && col >= 0 && col <= 256)
        return Data[row][col];
    else
    {
        cout << "Out of range, returning garbage value" << endl;
        return -1;
    }
    log.logging("getting pixel coordinates");

}
void image::SetPixel(int row, int col,int val)
{
    if (row >= 0 && row <= 256 && col >= 0 && col <= 256)
    {
        if (val == 255 || val == 0)
            val = Data[row][col];
        else
            cout << "Wrong pixel value, value must be 0 or 255" << endl;
    }
    else
    {
        cout << "Out of range"<< endl;
    }
    log.logging("Setting pixel coordinates");

}
int image::GetSize()
{
    log.logging("getting size of image");
    return height * width;
}
void image::ConvertNegative()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (Data[i][j] == 255)
                Data[i][j] = 0;
            else
                Data[i][j] = 255;
        }
    }
   save();
   log.logging("converting image to its negative");
   //on turns to off,off turns to on simple code
}
void image::printData()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << " " << Data[i][j];
        }
        cout << endl;
    }
    log.logging("Printing Data array");

}
long double image::MeanPixelValue()
{
     long double mean = 0;
     int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mean = Data[i][j] + mean;
            count++;
        }
    }
    log.logging("Getting mean pixel value");
    return mean /count;
}
void image::mean_row()
{
    int blacksum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(Data[i][j] == 255)
            blacksum++;
        }
        cout << "Mean black pixels in " << i+1 << " row are: " << blacksum << endl;
        blacksum = 0;
    }
    log.logging("Getting mean of black pixels row by row");

}
int image::whitePixels()
{
    int white = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (Data[i][j] == 0)
            white = 1 + white;
        }
    }
    log.logging("Getting number of white pixels");
    return white;
}
int image::blackPixels()
{
    int black = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(Data[i][j]==255)
            black = 1 + black;
        }
    }
    log.logging("Getting number of black pixels");
    return black;

}
void image::save() {

    ofstream outfile;
    outfile.open(filename, ios::out | ios :: binary);
    outfile << version << endl;
    outfile << filename << endl;
    outfile << comment << endl;
    outfile << height << " " << width << endl;
    outfile << maxgrey << endl;

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (Data[i][j] == 255 )
                outfile << 1;
            else
                outfile << 0;
        }
        outfile << endl;
    }
    outfile.close();
    log.logging("Saving file");
}
void image::saveF(string file) {

    ofstream outfile;
    outfile.open(file, ios::out);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rlcData[i][j] == 255)
                outfile << 1;
            else
                outfile << 0;
        }
        outfile << endl;
    }
    outfile.close();
    log.logging("Saving file with filename");
}
int** image::returnData()
{
    log.logging("Returning Data array");
    return Data;
}
int image::getmaxgrey()
{
    log.logging("Getting max grey value");
    return maxgrey;
}
string image::getcomment()
{
    log.logging("Getting comment");
    return comment;
}
string image::getfilename()
{
    log.logging("Getting filename");
    return filename;
}
void image::RLCencoding()
{
    rlcList->add(height);
    rlcList->add(width);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (Data[i][j] == 255 )
            {
                if (Data[i][j - 1] == 0)
                {
                    rlcList->add(j);
                }
                if (Data[i][j + 1] == 0)
                {
                    rlcList->add(j);
                }
            }
        }
        rlcList->add(-1);
    }
    log.logging("RLC encoding");
    //identifies two cases in which the pixel should be inserted into RLC list

}
void image::RLCdecoding(string rlcFile)
{
    ofstream newout;
    newout.open(rlcFile, ios::out);
    Node* iterator = rlcList->returnhead();
   int highlimit = 0;
   int lowlimit = 0;
   int linebreaker = 0;
  int rlcheight =iterator->getData();
   iterator = iterator->getNext();
   int temp = 0;
   temp = rlcheight * iterator->getData();
   int spaces = 0;
   int controlvariable = 0; //variables used for RLC decoding
   for (int i = 0; i < temp;)
   {
       if (iterator->getNext() == nullptr)
       {
           break;
       }// breaks loop when list becomes empty
       iterator = iterator->getNext();   
       linebreaker = iterator->getData();
       if (linebreaker == -1)
       {//when -1 is identified , line ends, but before that
           controlvariable++;
           if (highlimit <= rlcheight)
           {
               for (int j = highlimit; j < rlcheight; j++)
               {
                   newout << ' ';//we fill the remaining spaces with space
                 
               }
           }
           Node* temp = iterator->getNext();
           if (iterator->getNext() == nullptr)
           {
               break;
           }
           if (temp->getData() == -1)
           {
                   for (int j = rlcheight - highlimit; j < rlcheight; j++)
                   {
                       newout << ' ';
                   }             
           }//used for fully empty lines
           newout << endl;
           spaces = 0;
       }
       else
       {
           lowlimit = linebreaker;
           for (int j = spaces; j < linebreaker; j++)
           {
               newout << ' ';
           }//spaces till first on bits
           iterator = iterator->getNext();
           if (iterator->getNext() == nullptr)
           {
               break;
           }
           highlimit = iterator->getData();
           for (int j = lowlimit; j < highlimit; j++)
           {
               newout << '1';
               if(controlvariable < 256 && j < 256)
               rlcData[controlvariable][j] = 1;
           }//on bits between two coordinates
           spaces = highlimit;
       }      
   }
    newout.close();
    log.logging("RLC decoding");

}
void image::RLCnegative(string rlcFile)
{
    ofstream newout;
    newout.open(rlcFile, ios::out);

 for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (rlcData[i][j] == 1)
            {
                rlcData[i][j] = 0;
                newout << ' ';
            }
            else
            {
                rlcData[i][j] = 1;
                newout <<'1';
            }
        }
        newout << endl;
    }
 newout.close();
 log.logging("Converting image to negative thru RLC");

}
void image::RLCFormatBlackPixels()
{
    int tempv = 0;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (rlcData[i][j] == 1)
            {
                tempv++;
            }    
        } 
    }
    cout << "The number of black pixels are : " << tempv << endl;
    log.logging("Getting number of black pixels through RLC");

}
void image::displayrlclist()
{
    rlcList->displayList();
    log.logging("Displaying RLC list");
}
void image::makingprojections()
{
    verticalprojection = new int[height];
    horizontalprojection = new int[width];
    int blackpixv = 0;
    int blackpixh = 0;
    //makes two array size height & width for projections
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (Data[i][j] == 255)
                blackpixv++;
        }
        verticalprojection[i] = blackpixv;
        blackpixv = 0;
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (Data[j][i] == 255)
            {
                blackpixh++;
            }
        }
        if(blackpixh==0)
        horizontalprojection[i] = 0;
        else
        {
            horizontalprojection[i] = blackpixh;
            blackpixh = 0;
        }
    }
  //fills both arrays 
   
    combinedprojection = new int[height + width];
    for (int i = 0; i < height; i++)
    {
        combinedprojection[i] = verticalprojection[i];
    }
    for (int i = 0; i < width; i++)
    {
        combinedprojection[i+height] = verticalprojection[i];
    }//fills combinedprojections array of size height+width
    log.logging("Making projections");

}
int image::returnimagesum()
{
    makingprojections();
    int capicity = height + width;
    int rem = capicity % 4;

    if (rem!=0)
    {
        int* newarray=new int[capicity-rem+4];
        for (int i=0; i < capicity; i++)
           newarray[i]=combinedprojection[i];
        for (int i = capicity; i < capicity + 4 - rem; i++)
            newarray[i]=0;
        
        delete[] combinedprojection;
        combinedprojection=newarray;  
        capicity=capicity+4-rem;  
    }


    int returnsum=0;
    for (int i=0;i<capicity;i +=4)    
        returnsum = returnsum +combinedprojection[i]*1000+combinedprojection[i+1]*100+combinedprojection[i+2]*10+combinedprojection[i+3];
    
    //basically normalise the array by adding 0s to make it divisable by 4 and then 
    //applied 4 digit folding
    log.logging("Returning sum for hash");
        return returnsum;
}
void image::findcomponentsQueue()
{
    qarr = new int* [height];
    for (int i = 0; i < height; i++) {
        qarr[i] = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            qarr[i][j] = 0;
        }
    }
    temparr = new int* [height];
    for (int i = 0; i < height; i++) {
        temparr[i] = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temparr[i][j] = Data[i][j];
        }
    }
    ofstream outfile;
    outfile.open("queue.pgm", ios::out | ios::binary);
    outfile << "P5" << endl;
    outfile << "queue.pgm" << endl;
    outfile << "#converted PNM file" << endl;
    outfile << height << " " << width << endl;
    outfile << maxgrey << endl;


    cout << "Enter row number between 0-256" << endl;
    int rowq;
    cin >> rowq;
    cout << "Enter column number between 0-256" << endl;
    int colq;
    cin >> colq;
    while ((rowq > height || rowq < 0) || (colq < 0 || colq > height))
    {
        cout << "Out of bound value provided, enter again" << endl;
        cout << "Enter row number between 0-256" << endl;
        cin >> rowq;
        cout << "Enter column number between 0-256" << endl;
        cin >> colq;
    }
    int controlval;
    if (Data[rowq][colq] == 0)
        controlval = 0;
    else
        controlval = 255;

    RecursiveComponentQueue(rowq,colq, controlval);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (qarr[i][j] == 1)
                outfile << 'ÿ';
            else
                outfile << ' ';
        }
        outfile << endl;
    }
    outfile.close();
    cout << "File made through connected components using queues" << endl;

    //Basically, we take in a variable that tells us whether the pixel provided by the user is 
    //from background and foreground, after that we use that to find its neighbors
    //suppose that variable name is control
    //First we check if that variables coordinates are out of bound or not, if it is we return
    //Next we check if its pixel value matches with control, if it doesnt we return
    //We also check if it 2 or not , 2 indicates if that coordinate has been used or not
    //basically 2 is a flag
    //After that, we proceed to change that coordinate value to 2
    //Next we enque the coordinates, and deque the queue
    //Finally we call the function for all 8 neighbors
}
void image::findcomponentsStack()
{
    sarr = new int* [height];
    for (int i = 0; i < height; i++) {
        sarr[i] = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sarr[i][j] = 0;
        }
    }
    temparr = new int* [height];
    for (int i = 0; i < height; i++) {
        temparr[i] = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temparr[i][j] = Data[i][j];
        }
    }
    ofstream outfile;
    outfile.open("stack.pgm", ios::out | ios::binary);
    outfile << "P5" << endl;
    outfile << "cc.pgm" << endl;
    outfile << "#converted PNM file" << endl;
    outfile << height << " " << width << endl;
    outfile << maxgrey << endl;


    cout << "Enter row number between 0-256" << endl;
    int rowq;
    cin >> rowq;
    cout << "Enter column number between 0-256" << endl;
    int colq;
    cin >> colq;
    while ((rowq > height || rowq < 0) || (colq < 0 || colq > height))
    {
        cout << "Out of bound value provided, enter again" << endl;
        cout << "Enter row number between 0-256" << endl;
        cin >> rowq;
        cout << "Enter column number between 0-256" << endl;
        cin >> colq;
    }
    int controlval;
    if (Data[rowq][colq] == 0)
        controlval = 0;
    else
        controlval = 255;

    RecursiveComponentStack(rowq, colq, controlval);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (sarr[i][j] == 1)
                outfile << 'ÿ';
            else
                outfile << ' ';
        }
        outfile << endl;
    }
    outfile.close();
    cout << "File made through connected components using stack" << endl;
}
void image::RecursiveComponentQueue(int userow, int usercol, int controlval)
{
    if (userow < 0 || userow >= height || usercol < 0 || usercol >= width) {
        return;
    }
    if (temparr[userow][usercol] != controlval || temparr[userow][usercol] == 2) {

        return;
    }
    temparr[userow][usercol] = 2;
    QueueRow->enqueue(userow);
    QueueCol->enqueue(usercol);
 
    while (QueueRow->isEmpty() == false && QueueCol->isEmpty() == false)
    {
        qarr[QueueRow->dequeue()][QueueCol->dequeue()] = 1;
    }

    RecursiveComponentQueue( userow - 1, usercol,  controlval);
    RecursiveComponentQueue( userow + 1, usercol,  controlval);
    RecursiveComponentQueue( userow, usercol - 1,  controlval);
    RecursiveComponentQueue( userow, usercol + 1,  controlval);
    RecursiveComponentQueue( userow - 1, usercol - 1,  controlval);
    RecursiveComponentQueue( userow + 1, usercol + 1,  controlval);
    RecursiveComponentQueue( userow + 1, usercol - 1,  controlval);
    RecursiveComponentQueue( userow - 1, usercol + 1,  controlval);
}
void image::RecursiveComponentStack(int userow, int usercol, int controlval)
{
    if (userow < 0 || userow >= height || usercol < 0 || usercol >= width) {
        return;
    }
    if (temparr[userow][usercol] != controlval || temparr[userow][usercol] == 2) {

        return;
    }
    temparr[userow][usercol] = 2;
    stackRow->push(userow);
    stackCol->push(usercol);

      while (stackRow->isEmpty() == false && stackCol->isEmpty() == false)
      {
          sarr[stackRow->pop()][stackCol->pop()] = 1;
      }
    RecursiveComponentStack(userow - 1, usercol, controlval);
    RecursiveComponentStack(userow + 1, usercol, controlval);
    RecursiveComponentStack(userow, usercol - 1, controlval);
    RecursiveComponentStack(userow, usercol + 1, controlval);
    RecursiveComponentStack(userow - 1, usercol - 1, controlval);
    RecursiveComponentStack(userow + 1, usercol + 1, controlval);
    RecursiveComponentStack(userow + 1, usercol - 1, controlval);
    RecursiveComponentStack(userow - 1, usercol + 1, controlval);
}
void image::quadtreeimpl()
{
    int nesize = height * width;
    int* quadarr = new int[nesize];

    for (int q = 0; q < height; q++)
    {
        for (int t = 0; t < width; t++)
        {
            quadarr[q * width + t] = Data[q][t];
        }
    }
    qt_node q;
    add_values(&q, quadarr, height, width);
    build_tree(&q, 255);


    cout << "Nodes: " << count_tree_nodes(&q) << endl;
    cout << "Pixel check: " << check_num_pixels(&q) << endl;
    log.logging("Q5 implementation");


}
