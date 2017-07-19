//
// Created by lulitao on 16-12-14.
//

#ifndef ALL_H
#define ALL_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <iomanip>
#include <queue>
#include <locale>
#include <codecvt>

using namespace std;

const int MAXN = 2.1e5, MAXE = 1.1e6; ///N and E number in a graph;

// constant about block index
const double MIN_INTV = 0.05; //50m
const double MINX = 120.0000, MAXX = 122.16,
        MINY = 30.000, MAXY = 32.2,
//120.001,122.152:30.0001,32.1105
        INTVX = 0.031, INTVY = 0.027;
const int XNUM = 1500, YNUM = 1500;

const int MAXP = 5.1e6; //total number of points

const int MAX_ORDER = 5.1e5;

const int INTV_T = 10; //simulate every 10 sec

const int MAXR = 140000;

#endif //ALL_H
/*
 * notes:
 *  p_b : containing all the points in the road, including "interval points"
 *  order_b : containg all the start points of the order to be processed
 */