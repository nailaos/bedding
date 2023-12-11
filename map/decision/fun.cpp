#include "fun.h"
#include <iostream>
using namespace std;

void setSpeed(int val) {
    cout << "set speed to " << val << endl;
}

void rotate(float angle) {
    cout << "rotate " << angle << endl;
}

uint8_t getHeightOfId(uint8_t id) {
    return 0;
}

void getPosition(Position_edc25* Pos) {
    Pos->x = 0.0;
    Pos->y = 0.0;
}

// 获取敏捷
uint8_t getAgility() {
    return 0;
}

// 获取当前生命
uint8_t getHealth() {
    return 20;
}

// 获取最大生命
uint8_t getMaxHealth() {
    return 20;
}

// 获取力量
uint8_t getStrength() {
    return 20;
}

// 获取绿宝石数量
uint8_t getEmeraldCount() {
    return 0;
}

// 获取羊毛数量
uint8_t getWoolCount() {
    return 8;
}

// 攻击指定ID的位置
void attack_id(uint8_t chunk_id) {
    cout << "attack " << chunk_id << endl;
}

// 在指定ID的块上放置方块
void place_block_id(uint8_t chunk_id) {
    cout << "place " << chunk_id << endl;
}

// 指定ID的物品交易
void trade_id(uint8_t item_id) {
    cout << "trade " << item_id << endl;
}