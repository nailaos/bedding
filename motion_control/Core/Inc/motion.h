#ifndef __MOTION_H__
#define __MOTION_H__
#ifdef __cplusplus
extern "C" {
#endif

// 这里放置 C 语言代码，例如函数声明、结构体定义等
#include "main.h"
//全局变量
extern float vset;
#define PID_MAX 1000//改成自己设定的PWM波的单波�?长输出时�?
#define PID_MIN 0//改成自己设定的PWM波的单波�?长输出时间的相反�?
typedef struct{
  float sum;//误差关于时间的积�?
  float lr;//上一次的速度误差
  float Kp;
  float Ki;
  float Kd;}pidstr;
extern pidstr pidparm;//用于保存PID参数和用于计算PWM占空比的�?

//函数声明
void setv(float v);
void move_time(int dir,int t,int v);//dir:0向前，1向后；单位：ms,单位：cm/s
void setdir(int dir);
void rotate(int dir,float angle);
#ifdef __cplusplus
}
#endif


#endif //__MOTION_H
