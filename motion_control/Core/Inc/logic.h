#pragma once
#include "motion.h"

extern Position_edc25 my_pos;
extern Position_edc25 target;
extern Position_edc25 path[50];
extern int pathlen ;
extern int myMap_new[64];
extern Position_edc25 Base;

int mymove_new(Position_edc25* from, Position_edc25* to) ;
int InitBase();//0为左上角，1为右下角
int move_target(Position_edc25 *from,Position_edc25 *to,int v);
void gohome();
int make_choice();
int Trade();
