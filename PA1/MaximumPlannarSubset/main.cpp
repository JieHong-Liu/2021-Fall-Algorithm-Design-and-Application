#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

int MPS(int NumberOfVertex, vector<pair<int, int> > &v, vector<vector<int> > &dp);
int getOpposite(vector<pair<int, int> > &v, int v1)
{
    for (int k = 0; k < v.size(); k++)
    {
        if (v[k].first == v1)
        {
            // cout << "getChord("<<v1<<")="<<v[k].second << endl;
            return v[k].second;
        }
        else if (v[k].second == v1)
        {
            // cout << "getChord("<<v1<<")="<<v[k].first << endl;
            return v[k].first;
        }
    }

    cout << "No chords found!!!" << endl;
    return -1;
}

void readFile(vector<pair<int, int> > &v, string inputFilename, int &NumberOfVertex)
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
        getline(inputFileStream, inputStr);
        NumberOfVertex = stoi(inputStr);
        //基本的初始化stringstream
        stringstream ss;
        while (getline(inputFileStream, inputStr)) //一行一行讀資料
        {
            ss.str("");
            ss.clear();
            if (inputStr == "0")
            {
                cout << "End of file: v.size()  = " << v.size() << endl;
            }
            else
            {
                pair<int, int> p;
                ss << inputStr;
                ss >> p.first >> p.second;
                v.push_back(p);
            }
        }
        inputFileStream.close();
    }
}

void sortChords(vector<pair<int, int> > &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            if (v[j].first > v[j + 1].first)
            {
                pair<int, int> tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

void getChord(int i, int j, vector<pair<int, int> > &v, vector<vector<int> > &dp,vector<pair<int,int> >&recordChordList)
{
    // cout << "getChord:" << endl;
    if (i >= j)
        return;
    int k = getOpposite(v, j);
    pair<int, int> p;
    p.first = k;
    p.second = j;
    if (i == k)
    {
        recordChordList.push_back(p);
        getChord(i + 1, j - 1, v, dp,recordChordList);
    }
    else if (k > j || k < i) // k is out of range
    {
        getChord(i, j - 1, v, dp,recordChordList);
    }
    else if (k < j && k > i) // i < k < j
    {
        //case 3-1
        if (dp[i][j - 1] < 1 + dp[k + 1][j - 1] + dp[i][k - 1])
        {
            recordChordList.push_back(p);
            getChord(k + 1, j - 1, v, dp,recordChordList);
            getChord(i	  , k - 1, v, dp,recordChordList);
        }
        //case 3-2
        else
        {
            getChord(i	  , j - 1, v, dp,recordChordList);
        }
    }
}

void writeFile(vector<pair<int, int> > &v, string outputFilename, int NumberOfVertex, vector<vector<int> > &dp,vector<pair<int,int> > &recordChordList)
{
    ofstream outputFileStream;
    outputFileStream.open(outputFilename);
    int ans = MPS(NumberOfVertex, v, dp);
	cout << ans << endl;
    outputFileStream << ans << endl;
    getChord(0, NumberOfVertex - 1, v, dp,recordChordList);
    sortChords(recordChordList);
    // cout << "recordChordList.size() = " << recordChordList.size() << endl;
    for (int i = 0; i < recordChordList.size(); i++)
    {
        // cout << recordChordList[i].first << "," << recordChordList[i].second << endl;
        outputFileStream << recordChordList[i].first << " " << recordChordList[i].second << endl;
    }
    outputFileStream.close();
}

int main(int argc, char *argv[])
{
    // A List to record Answer.
	vector<pair<int, int> > recordChordList;
    // dynamic allocate of chords.
    vector<pair<int, int> > chordList;
    int NumberOfVertex;
    // deal with input.
    string inputFilename, outputFilename;
    if (argc == 3)
    {
        inputFilename = argv[1];
        outputFilename = argv[2];
    }
    else
    {
        cout << "Input Error" << endl;
        cout << "Usage :./ [exe][input file][output file] " << endl;
        exit(1);
    }
    const clock_t begin_time = clock();
    readFile(chordList, inputFilename, NumberOfVertex);
    // build table.
    vector<vector<int> > dpTable;
    dpTable.resize(NumberOfVertex);
    for (int i = 0; i < NumberOfVertex; ++i)
    {
        dpTable[i].resize(NumberOfVertex);
    }
    // deal with output.
    writeFile(chordList, outputFilename, NumberOfVertex, dpTable,recordChordList);
    std::cout << "Finish N = " << NumberOfVertex << " in " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s " << endl;
    return 0;
}

int MPS(int NumberOfVertex, vector<pair<int, int> > &v, vector<vector<int> > &dp)
{
    for (int j = 0; j < NumberOfVertex; j++)
    {
        int k = getOpposite(v, j);
        for (int i = 0; i < j; i++)
        {
            if (i >= j)
            {
                dp[i][j] = 0;
            }
            else
            {
                if (k == -1)
                {
                    cout << "ERROR k=-1" << endl;
                    return -1;
                }

                if (k == i)
                {
                    dp[i][j] = 1 + dp[i + 1][j - 1];
                }
                else if (k > j || k < i)
                {
                    dp[i][j] = dp[i][j - 1];
                }
                else if (k < j && k > i) // i < k < j
                {
                    int v1 = dp[i][j - 1];
                    int v2 = 1 + dp[k + 1][j - 1] + dp[i][k - 1];
                    if (v1 >= v2)
                    {
                        dp[i][j] = v1;
                    }
                    else
                    {
                        dp[i][j] = v2;
                    }
                }
                else
                {
                    cout << "ERROR" << endl;
                }
            }
        }
    }
    return dp[0][NumberOfVertex - 1];
}
