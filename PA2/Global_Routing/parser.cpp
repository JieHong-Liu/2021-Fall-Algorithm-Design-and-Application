#include "parser.h"
void readFile(string inputFilename, int &row, int &col, int &capacity, vector<wire> &wires)
{
    string inputStr;
    fstream inputFileStream;
    inputFileStream.open(inputFilename);
    if (!inputFileStream.is_open())
    {
        cerr << "Cannot open file: " << inputFilename << endl;
    }
    else
    {
        // deal with grid.
        stringstream ss; //基本的初始化stringstream
        string tmp;
        int numnet;
        ss.str("");
        ss.clear();
        getline(inputFileStream, inputStr);
        ss << inputStr;
        ss >> tmp >> row >> col;
        // deal with capacity
        ss.str("");
        ss.clear();
        getline(inputFileStream, inputStr);
        ss << inputStr;
        ss >> tmp >> capacity;
        // deal with num net
        ss.str("");
        ss.clear();
        getline(inputFileStream, inputStr);
        ss << inputStr;
        ss >> tmp >> tmp >> numnet;
        for (int i = 0; i < numnet; i++) //一行一行讀資料
        {
            ss.str("");
            ss.clear();
            getline(inputFileStream, inputStr);
            wire w;
            int index, start_x, start_y, end_x, end_y;
            ss << inputStr;
            ss >> index >> start_x >> start_y >> end_x >> end_y;
            w.setWire(index, start_x, start_y, end_x, end_y);
            wires.push_back(w);
        }
        inputFileStream.close();
    }
}