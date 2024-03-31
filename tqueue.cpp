#include "tqueue.h"
#include <iostream>

using namespace std;

queuei::queuei(int s)
{
    size = s;
    array = new int[size];
    front = -1;
    back = -1;
}
queuei::~queuei()
{
    delete[] array;
}
void queuei::enqueue(int item)
{
    if (isFull())
    {
        cout << "queuei IS FULL" << endl;
        return;
    }
    if (isEmpty())
    {
        front++;
        back++;
    }
    else
        back++;
    array[back] = item;
}
int queuei::dequeue()
{
    if (isEmpty())
    {
        cout << "queuei IS EMPTY" << endl;
        return 0;
    }
    int temp = array[front];
    if (front == back)
    {
        front = -1;
        back = -1;
    }
    else
        front++;
    return temp;
}
void queuei::display()
{
    if (isEmpty())
    {
        cout << "queuei IS EMPTY" << endl;
        return;
    }
    for (int i = front; i <= back; i++)
        cout << array[i] << " ";
    cout << endl;
}
bool queuei::isEmpty()
{
    if (front == -1 && back == -1)
        return true;
    else
        return false;
}
bool queuei::isFull()
{
    if (back == size - 1)
        return true;
    else
        return false;
}