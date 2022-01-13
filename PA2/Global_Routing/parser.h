#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "wire.h"
using std::cerr;
using std::endl;
using std::fstream;
using std::string;
using std::stringstream;
using std::vector;

void readFile(string inputFilename, int &row, int &col, int &capacity, vector<wire> &wires);