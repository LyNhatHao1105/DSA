#include "DataProcessing.h"

int main()
{
    time_t timer = clock();
    int numberOfChunks = 1;
    int maxSizeofMemory = 1000000;
    int chunkSize = maxSizeofMemory / sizeof(int);
    BookInfo* inputValues = new BookInfo[chunkSize];
    BookInfo readValue;
    int currentCount = 0;
    bool unprocessedData = true;

    ifstream inputFile("Books_rating.csv");

    cout << "Finish reading" << endl;

    string firstLine;

    getline(inputFile, firstLine);

    while (!inputFile.eof())
    {
        getline(inputFile, readValue.id, ',');
        getline(inputFile, readValue.other, '\n');
        unprocessedData = true;
        inputValues[currentCount++] = readValue;
        if (currentCount == chunkSize)
        {
            sortAndWrite(inputValues, currentCount, numberOfChunks);
            numberOfChunks++;
            currentCount = 0;
            unprocessedData = false;
        }
    }
    if (unprocessedData)
    {
        sortAndWrite(inputValues, currentCount, numberOfChunks);
    }
    else
    {
        numberOfChunks--;
    }
    cout << "Finish divide and sort" << endl;

    inputFile.close();
    delete[] inputValues; // free memory

    string outputFileName = "sorted_books_rating.csv";
    ofstream outputFile(outputFileName.c_str());

    outputFile << firstLine << endl;

    if (numberOfChunks > 0)
    {
        priority_queue<pair<BookInfo, int>, vector<pair<BookInfo, int>>, Compare> minHeap;
        cout << "Writing to output file..." << outputFileName << endl;
        mergeFiles(numberOfChunks, outputFile);
    }
    cout << "Finish merge in: " << (clock() - timer) / 1000 << " seconds.";
    return 0;
}