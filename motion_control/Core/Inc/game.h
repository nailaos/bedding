#pragma once
#include "motion.h"

void initMap(char* mapInfo);
void printMap();
void gameRun();
int getMapId(Position_edc25* points);
int getdir(Position_edc25* from, Position_edc25* to);
