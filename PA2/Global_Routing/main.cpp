#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <cmath>
#include "parser.h"
#include "Graph.h"
using namespace std;

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

bool wireCompare(wire w1, wire w2)
{
	return w1.distance < w2.distance;
}

class minHeapComparator
{
public:
	int operator()(const Point *p1, const Point *p2)
	{
		return p1->distance > p2->distance;
	}
};
Point *extractMIN(vector<Point *> &minHeap);
void initSingleSource(Graph &map, wire w);
void Dijkstra(Graph &map, wire w, int capacity);
void Relax(Point *current, Point *newPoint, vector<vector<int>> &edgeWeights, int capacity, Direction direction, Graph &map);
double edgeCost(double demand, double capacity);
bool BFS_check(Graph &map, Point *current, Direction direction);
void checkMINHEAP(vector<Point *> &minHeap);
void traceShortestPath(Graph &map, wire w, int capacity, string outputFilename);
int main(int argc, char *argv[])
{
	// parse the input
	int row = 4;
	int col = 4;
	int capacity = 2;
	vector<wire> wires;
	string inputFilename;
	string outputFilename;
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
	readFile(inputFilename, row, col, capacity, wires);
	Graph map(row, col);
	sort(wires.begin(), wires.end(), wireCompare); // sort the wires.
	for (int i = 0; i < wires.size(); i++)
	{
		Dijkstra(map, wires[i], capacity);
		traceShortestPath(map, wires[i], capacity, outputFilename);
	}

	return 0;
}
void initSingleSource(Graph &map, wire w)
{
	Point startPoint = w.startPos;
	for (int i = 0; i < map._row; i++)
	{
		for (int j = 0; j < map._col; j++)
		{
			map.tiles[i][j].distance = INFINITY - 1000000; // std::numeric_limits<double>::infinity();

			map.tiles[i][j].setPredecessor(NULL);
		}
	}
	map.tiles[startPoint.getx()][startPoint.gety()].distance = 0; // the min queue
}

void Dijkstra(Graph &map, wire w, int capacity)
{
	initSingleSource(map, w);
	vector<Point *> minHeap;
	// put every vertex to the minHeap
	for (int i = 0; i < map._row; i++)
	{
		for (int j = 0; j < map._col; j++)
		{
			minHeap.push_back(&map.tiles[i][j]);
		}
	}

	while (!minHeap.empty())
	{
		Point *current = extractMIN(minHeap);
		// cout << "minHeap.top = " << *current << endl;
		if (BFS_check(map, current, UP)) // legal point
		{
			// cout << "up:" << *current << current->up(map._row, map._col) << endl;
			Relax(current, &map.tiles[current->up(map._row, map._col).getx()][current->up(map._row, map._col).gety()], map.verticalEdge, capacity, UP, map);
		}
		if (BFS_check(map, current, RIGHT)) // legal point
		{
			// cout << "right:" << *current << current->right(map._row, map._col) << endl;
			Relax(current, &map.tiles[current->right(map._row, map._col).getx()][current->right(map._row, map._col).gety()], map.horizontalEdge, capacity, RIGHT, map);
		}
		if (BFS_check(map, current, DOWN)) // legal point
		{
			// cout << "down:" << *current << current->down(map._row, map._col) << endl;
			Relax(current, &map.tiles[current->down(map._row, map._col).getx()][current->down(map._row, map._col).gety()], map.verticalEdge, capacity, DOWN, map);
		}
		if (BFS_check(map, current, LEFT)) // legal point
		{
			// cout << "left:" << *current << current->left(map._row, map._col) << endl;
			Relax(current, &map.tiles[current->left(map._row, map._col).getx()][current->left(map._row, map._col).gety()], map.horizontalEdge, capacity, LEFT, map);
		}
	}
}

bool BFS_check(Graph &map, Point *current, Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return current->up(map._row, map._col).getx() != -1 && current->up(map._row, map._col).gety() != -1;
	case Direction::RIGHT:
		return current->right(map._row, map._col).getx() != -1 && current->right(map._row, map._col).gety() != -1;
	case Direction::DOWN:
		return current->down(map._row, map._col).getx() != -1 && current->down(map._row, map._col).gety() != -1;
	case Direction::LEFT:
		return current->left(map._row, map._col).getx() != -1 && current->left(map._row, map._col).gety() != -1;
	default:
		return false;
	}
}
void Relax(Point *current, Point *newPoint, vector<vector<int>> &edgeDemand, int capacity, Direction direction, Graph &map) // edge weights record its demand
{

	if (direction == Direction::UP || direction == Direction::RIGHT)
	{
		edgeDemand[current->getx()][current->gety()] += 1; // update the edge cost
		if (newPoint->distance > current->distance + edgeCost(edgeDemand[current->getx()][current->gety()], capacity))
		{
			newPoint->distance = current->distance + edgeCost(edgeDemand[current->getx()][current->gety()], capacity); // update distance
			newPoint->setPredecessor(current);
		}
		edgeDemand[current->getx()][current->gety()] -= 1; // update the edge cost
	}
	else
	{
		edgeDemand[newPoint->getx()][newPoint->gety()] += 1; // update the edge cost
		if (newPoint->distance > current->distance + edgeCost(edgeDemand[newPoint->getx()][newPoint->gety()], capacity))
		{
			newPoint->distance = current->distance + edgeCost(edgeDemand[newPoint->getx()][newPoint->gety()], capacity); // update distance
			newPoint->setPredecessor(current);
		}
		edgeDemand[newPoint->getx()][newPoint->gety()] -= 1; // minus that demand since it's not the real wire.
	}
	// cout << "update distance: " << newPoint->distance << endl;
}

double edgeCost(double demand, double capacity)
{
	if (demand < capacity)
	{
		return 0;
	}
	else
	{
		return 10000;
	}
}

Point *extractMIN(vector<Point *> &minHeap)
{
	double min = (minHeap[0]->distance);
	int minIndex = 0;
	for (int i = 0; i < minHeap.size(); i++)
	{
		if (minHeap[i]->distance < min)
		{
			min = minHeap[i]->distance;
			minIndex = i;
		}
	}
	Point *ret = minHeap[minIndex];
	minHeap.erase(minHeap.begin() + minIndex);
	return ret;
}

void checkMINHEAP(vector<Point *> &minHeap)
{
	cout << "MIN HEAP:" << endl;
	for (int i = 0; i < minHeap.size(); i++)
	{
		cout << *minHeap[i] << " with distance = " << minHeap[i]->distance << endl;
	}
	cout << "END of MIN HEAP:" << endl;
}

void traceShortestPath(Graph &map, wire w, int capacity, string outputFilename)
{
	ofstream outputFileStream;
	outputFileStream.open(outputFilename, ios::app);
	stack<Point *> pathStack;
	Point *current = &map.tiles[w.endPos.getx()][w.endPos.gety()];
	while (current->getPredecessor() != NULL)
	{
		pathStack.push(current);
		if (current->getPredecessor()->getx() == current->getx() - 1) // from top to bot
		{
			map.verticalEdge[current->getPredecessor()->getx()][current->getPredecessor()->gety()] += 1;
		}
		else if (current->getPredecessor()->getx() == current->getx() + 1) // from bot to top
		{
			map.verticalEdge[current->getx()][current->gety()] += 1;
		}
		else if (current->getPredecessor()->gety() == current->gety() - 1) // from left to right
		{
			map.horizontalEdge[current->getPredecessor()->getx()][current->getPredecessor()->gety()] += 1;
		}
		else if (current->getPredecessor()->gety() == current->gety() + 1) // from right to left
		{
			map.horizontalEdge[current->getx()][current->gety()] += 1;
		}
		current = current->getPredecessor();
	}
	pathStack.push(&w.startPos);
	// cout << w.index << " " << pathStack.size() - 1 << endl;
	outputFileStream << w.index << " " << pathStack.size() - 1 << endl;
	if (pathStack.size() - 1 == 0)
	{
		cout << "FUCK DIJKSTRA BUGS" << endl;
		cout << "endPoint = " << w.endPos << endl;
	}
	Point tmp = *pathStack.top();
	while (pathStack.size() != 1)
	{
		pathStack.pop();
		outputFileStream << tmp << " " << *pathStack.top() << endl;
		tmp = *pathStack.top();
	}
	outputFileStream.close();
}
