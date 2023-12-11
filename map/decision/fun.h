#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Position_edc25 {
    float x;
    float y;
};

void setSpeed(int val);

void rotate(float angle);

uint8_t getHeightOfId(uint8_t id);

void getPosition(Position_edc25* Pos);

void getPositionOpponent(Position_edc25* Pos);

// 获取敏捷
uint8_t getAgility();

// 获取当前生命
uint8_t getHealth();

// 获取最大生命
uint8_t getMaxHealth();

// 获取力量
uint8_t getStrength();

// 获取绿宝石数量
uint8_t getEmeraldCount();

// 获取羊毛数量
uint8_t getWoolCount();

// 攻击指定ID的位置
void attack_id(uint8_t chunk_id);

// 在指定ID的块上放置方块
void place_block_id(uint8_t chunk_id);

// 指定ID的物品交易
void trade_id(uint8_t item_id);