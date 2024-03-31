#include "hash.h"
Hash::Hash(int size)
{
    this->size = size;
    hashList = new List*[size];
    for (int i = 0; i < size; i++)
    {
        hashList[i] = new List();
    }
}
int Hash::HashFunction(int value)
{
    return value % size;
}
void Hash::insert(int value)
{
    int index = HashFunction(value);
    hashList[index]->add(value);
    cout << "added at " << index << " index" << endl;
}
bool Hash::find(int value)
{
    int index = HashFunction(value);
    if (hashList[index]->find(value) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Hash::remove(int value)
{
    int index = HashFunction(value);
    if (find(value) == true)
    {
        hashList[index]->remove(value);
        return true;
    }
    else
    {
        return false;
    }
        
}