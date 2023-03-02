#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct BookInfo
{
    string id;
    string other;
};

class Compare
{
public:
    bool operator()(pair<BookInfo, int> pair1, pair<BookInfo, int> pair2)
    {
        return pair1.first.id > pair2.first.id;
    }
};

void quickSort(BookInfo*& a, int l, int r);
void sort(BookInfo*& a, int size);
void mergeFiles(int counter, ofstream& outputFile);
void sortAndWrite(BookInfo* values, int size, int numberOfChunk);
