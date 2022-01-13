#include "Graph.h"
#include <iostream>
using std::cout;
using std::endl;

Graph::Graph()
{
    this->_row = 0;
    this->_col = 0;
    createGraph(_row, _col); // resize the graph
}
Graph::Graph(int row, int col)
{
    this->_row = row;
    this->_col = col;
    createGraph(row, col);
}
void Graph::printMap()
{
    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            cout << tiles[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::printHorizontal()
{
    cout << "The horizontal Edge:" << endl;
    for (int i = 0; i < this->_row; i++)
    {
        for (int j = 0; j < this->_col - 1; j++)
        {
            cout << this->horizontalEdge[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::printVertical()
{
    cout << "The vertical Edge:" << endl;
    for (int i = 0; i < this->_row - 1; i++)
    {
        for (int j = 0; j < this->_col; j++)
        {
            cout << this->verticalEdge[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::createGraph(int row, int col)
{
    // create matrix.
    tiles.resize(row);
    verticalEdge.resize(row - 1);
    horizontalEdge.resize(row);
    for (int i = 0; i < row; i++)
    {
        tiles[i].resize(col);
    }

    for (int i = 0; i < row - 1; i++)
    {
        verticalEdge[i].resize(col);
    }

    for (int i = 0; i < row; i++)
    {
        horizontalEdge[i].resize(col - 1);
    }
    // Create zero weights.
    for (int i = 0; i < row - 1; i++)
    {
        for (int j = 0; j < col; j++)
        {
            verticalEdge[i][j] = 0;
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col - 1; j++)
        {
            horizontalEdge[i][j] = 0;
        }
    }
    // init tiles
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tiles[i][j].setx(i);
            tiles[i][j].sety(j);
        }
    }
}
