#pragma once
#include "fun.h"

struct Point {
    int x;
    int y;
    int num;
};

void initMap();
void printMap();
int getMapPosition(const Position_edc25& points);
bool findPath(int x, int y, int currMiner, int woolNum, vector<Position_edc25>& path);
void printPath(const vector<Position_edc25>& path);
void printPath();
bool decision();