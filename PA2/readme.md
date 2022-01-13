# PA2-Global Routing

## Problem Description
This programming assignment asks you to write a global router that can route 2-pin nets (connection between two points). The problem description below is a simplified routing problem. Given the problem size (the number of horizontal and vertical tiles), capacity, and a netlist, the global router routes all nets in the routing region. The main objective is to minimize the total overflows. Here the overflow on a tile boundary is calculated as the amount of demand that excesses the capacity, i.e., overflow = max(0, demand- capacity).

## Input
The file format for the global routing is illustrated, with comments in italics (these will not be in actual input files). The 1st line gives the problem size in terms of the number of horizontal and vertical tiles. Each global routing tile (tile in short) has a capacity on its four boundaries to measure the available space, which is the maximum number of routing paths passing through boundaries. The capacity value is given by the 2nd line. The 3rd line gives the number of nets and following indicate each net, including starting position and terminal position. The input file format is as follows:

![](https://i.imgur.com/y5mYjGL.png)

## Output

All the routes in the output could only be horizontal lines and vertical lines. For example (18, 61)-(19, 62) is not acceptable, because it is diagonal. Remember that each route could be different either in the x or y location only, and the difference must be 1. The output file format is as follows:
![](https://i.imgur.com/fsvLDYB.png)
![](https://i.imgur.com/Nita24G.png)

## Sample Case
![](https://i.imgur.com/iEGoghR.png)

## Hint
![](https://i.imgur.com/JNRKv5v.png)


## IDEA

1. 先把題目model成一個graph，利用$2^{(demand/capacity)}-1$來當其權重
2. 繞線順序可以從最小的開始繞
3. overflow 應最先避免，再來才是比走的格子數