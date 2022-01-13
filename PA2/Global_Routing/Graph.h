#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
#include "wire.h"
using std::ostream;
using std::vector;

class Graph
{
public:
	friend ostream &operator<<(ostream &os, const Point &p);
	vector<vector<int>> verticalEdge;	// record the vertical cost.
	vector<vector<int>> horizontalEdge; // record the horizontal cost.
	vector<vector<Point>> tiles;
	int _row;
	int _col;
	Graph();
	Graph(int row, int col);
	void printMap();
	void printHorizontal();
	void printVertical();

private:
	void createGraph(int row, int col);
};
