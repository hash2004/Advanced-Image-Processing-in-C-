#pragma once
class queuei
{
private:
    int* array;
    int size;
    int front;
    int back;
public:
    queuei(int s);
    ~queuei();
    void enqueue(int item);
    int dequeue();
    void display();
    bool isEmpty();
    bool isFull();
};