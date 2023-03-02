#include "DataProcessing.h"

void quickSort(BookInfo*& a, int l, int r)
{
    int mid = (l + r) / 2, i = l, j = r;
    BookInfo pivot = a[mid];

    while (i <= j)
    {
        while (a[i].id < a[mid].id)
            i++;
        while (a[j].id > a[mid].id)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    }

    if (i < r)
        quickSort(a, i, r);
    if (l < j)
        quickSort(a, l, j);
}

void sort(BookInfo*& a, int size)
{
    quickSort(a, 0, size - 1);
}

void mergeFiles(int counter, ofstream& outputFile)
{
    priority_queue<pair<BookInfo, int>, vector<pair<BookInfo, int>>, Compare> minHeap;
    ifstream* handles = new ifstream[counter];

    for (int i = 1; i <= counter; i++)
    {
        string sortedInputFileName = "chunk " + to_string(i) + ".csv";
        handles[i - 1].open(sortedInputFileName.c_str());
        BookInfo firstValue;
        while (!handles[i - 1].eof())
        {
            getline(handles[i - 1], firstValue.id, ',');
            getline(handles[i - 1], firstValue.other, '\n');
            minHeap.push(pair<BookInfo, int>(firstValue, i - 1));
        }
    }

    for (int i = 0; i < counter + 1; i++)
    {
        minHeap.pop();
    }

    while (minHeap.size() > 0)
    {

        pair<BookInfo, int> minPair = minHeap.top();
        minHeap.pop();
        outputFile << minPair.first.id << "," << minPair.first.other << '\n';
        BookInfo nextValue;
        flush(outputFile);
        if (getline(handles[minPair.second], nextValue.id, ',') &&
            getline(handles[minPair.second], nextValue.other, '\n'))
        {
            if (nextValue.id != "")
            {
                minHeap.push(pair<BookInfo, int>(nextValue, minPair.second));
            }
        }
    }
    // clean up
    for (int i = 1; i <= counter; i++)
    {
        handles[i - 1].close();
    }
    outputFile.close();
    delete[] handles; // free memory

}

void sortAndWrite(BookInfo* values, int size, int numberOfChunk)
{
    // sort(values, values + size);
    sort(values, size);
    string outputFileName = "chunk " + to_string(numberOfChunk) + ".csv";
    ofstream outputFile(outputFileName.c_str(), ios::binary);
    for (int i = 0; i < size; i++)
    {
        outputFile << values[i].id << "," << values[i].other << '\n';
    }
    outputFile.close();
}
