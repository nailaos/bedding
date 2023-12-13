#include "motion.h"
#include "jy62.h"
#include "usart.h"
#include "decision.h"
#include "math.h"
#include "stdbool.h"
#include "stdlib.h"
float vset = 0;
unsigned int my_time = 0;
pidstr pidparm = { 0,0,100,5,200 };

void setv(float v) {
	pidparm.lr = 0.0;
	pidparm.sum = 0.0;//每一次设置速度时都要把pid参数中的lr和sum归零，减少误差
	vset = v;
}

void move_time(int dir, int t, int v) {
	setdir(dir);
//	setv(10);
//	HAL_Delay(100);
//	setv(20);
//	HAL_Delay(100);
	setv(v);
	HAL_Delay(t);
	setv(0);
}

void check_yaw(float max_err){
	float Yaw = GetYaw();
	while (Yaw==0){
		Yaw = GetYaw();
	}
	if(((Yaw>=0.0&&Yaw<=max_err)||(Yaw < 360&&Yaw>360-max_err))){
		InitAngle();
		return ;
	}
	else{
		if(Yaw<360.0-Yaw){
			while(Yaw>3.0&&Yaw<180.0){
				setdir(7);
				setv(10);
				Yaw = GetYaw();
				while (Yaw==0){
					Yaw = GetYaw();
				}
			}
			setv(0);
		}
		else{
			while(Yaw<360.0-3.0&&Yaw>180.0){
				setdir(6);
				setv(10);
				Yaw = GetYaw();
				while (Yaw==0){
					Yaw = GetYaw();
				}
			}
			setv(0);
		}
	}
	InitAngle();
}
void setdir(int dir) {
	if (dir == 0) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);//设置四个电机的转向?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}//前进
	else if (dir == 1) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//设置四个电机的转�?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	} else if (dir == 2) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//设置四个电机的转�?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	} else if (dir == 3) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);//设置四个电机的转�?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	else if(dir ==4){//向左平移
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//设置四个电机的转向?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else if(dir == 5){//向右平移
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);//设置四个电机的转�?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	else if(dir == 6){//向左校准
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//设置四个电机的转向?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else if(dir ==7){//向右校准
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);//设置四个电机的转向?
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}
}
void rotate(int dir, float angle) {
	setdir(dir);
	//float yaw = GetYaw();
	float pitch = GetPitch();


	if (pitch != 0) {
		setv(30);
		InitAngle();//航向角Yaw清零
		if (dir == 2) {
			float yaw = GetYaw();
			while (!(yaw > angle - 5 && yaw < angle + 5)) {
				yaw = GetYaw();
			}
			setv(0);
		}//左转
		else if (dir == 3) {
			while (GetYaw() > (360 - angle) + 5) {
				//待补充！！
			}
			setv(0);
		}//右转
	}
}

bool arrive(Position_edc25* a, Position_edc25* b) {
	Position_edc25 curr = { 0.0,0.0 };
	getPosition(&curr);
	float distance = (b->posx - curr.posx) * (b->posy - curr.posy);
	if (distance < LEN)
		return true;
	return false;
}

void putwool(Position_edc25* a, Position_edc25* b, int* woolnum) {
	Position_edc25 curr = { 0.0,0.0 };
	getPosition(&curr);
	int id = getMapPosition(&curr);
	if (abs(a->posx - b->posy) < 0.5) {
		if (a->posy > b->posy)
			id -= 1;
		else
			id += 1;
	} else {
		if (a->posx > b->posx)
			id -= 8;
		else
			id += 8;
	}
	if (!getHeightOfId(id))
		place_block_id(id);
}

bool my_move(Position_edc25* a, Position_edc25* b) {
	setv(SPEED);
	//rotate
	unsigned int last_time = my_time;
	while (true) {
		if (my_time - last_time) {
			last_time = my_time;
			// putwool(a, b, woolnum);  //这句中的woolnum会报错，检查一下
			if (arrive(a, b)) {
				setv(0);
				return true;
			}
			if (makedecision()) {
				setv(0);
				return false;
			}
		}
	}
	return false;
}

void my_Move(Position_edc25* path, int size) {
	for (int i = 1; i < size; i++)
		if (!my_move(&path[i - 1], &path[i]))
			return;
}
