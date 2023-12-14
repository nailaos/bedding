#include "game.h"
#include "usart.h"
#include <stdlib.h>

#define SPE 30
#define WOOL 16

int myMap[8][8] = {0};
int visited[8][8];
Position_edc25* myPath;
int myBase[2] = { 0, 0 };
int pathLen;
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int maxMinerNum = 0;
int tryNum = 0;
int upperLimit = 56;

void initMap(char* mapInfo) {
    for (int i = 0; i < 64; i++) {
        int x = i / 8;
        int y = i % 8;
        int val = mapInfo[i] - '0';
        myMap[x][y] = val;
        upperLimit += val;
    }
}

void printMap() {
	myMap[2][2] = 4;
	myMap[3][3] = 8;
	myMap[4][4] = 16;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            u1_printf("%d ", myMap[i][j]);
        u1_printf("\n");
    }
}


int getMapId(Position_edc25* points) {
    int x = (int)points->posx;
    int y = (int)points->posy;
    return 8 * y + x;
}

int findPath(int x, int y, int currMiner, int woolNum, Position_edc25* path, int* len) {
    currMiner += myMap[x][y];
    visited[x][y] = 1;
    if (woolNum == 0) {
        if (currMiner > maxMinerNum) {
            maxMinerNum = currMiner;
            path[*len].posx = (float)y;
            path[*len].posy = (float)x;
            *len = *len + 1;
            pathLen = *len;
            for (int i = 0; i < pathLen; i++)
                myPath[i] = path[i];
            *len = *len - 1;
            if (maxMinerNum == upperLimit / 2)
                return 1;
        }
        tryNum++;
        visited[x][y] = 0;
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx>7 || ny < 0 || ny > 7)
            continue;
        if (visited[nx][ny])
            continue;
        path[*len].posx = (float)y;
        path[*len].posy = (float)x;
        *len = *len + 1;
        if (findPath(nx, ny, currMiner, woolNum - 1, path, len))
            return 1;
        *len = *len - 1;
    }
    visited[x][y] = 0;
    return 0;
}

void printPath() {
    u1_printf("final length of path is %d\n", pathLen);

    for (int i = 0; i < pathLen; i++) {
        u1_printf("[%f, %f]", myPath[i].posx, myPath[i].posy);
        if (i < pathLen - 1)
            u1_printf("->");
    }
    u1_printf("\n");

    u1_printf("tryNum is %d\n", tryNum);
    u1_printf("the max mineral is %d\n", maxMinerNum);
}

int arrive(Position_edc25* from, Position_edc25* to) {
    Position_edc25 curr;
    getPosition(&curr);
    float distance = (to->posx - curr.posx) * (to->posy - curr.posy);
    if (distance < LEN)
        return 1;
    return 0;
}

int accident() {
    return 0;
}

int putWool(Position_edc25* from, Position_edc25* to) {
    Position_edc25 curr;
    getPosition(&curr);
    int id = getMapId(&curr);
    if (abs(from->posx - to->posx) < 0.5) {
        if (from->posy > to->posy)
            id -= 1;
        else
            id += 1;
    } else {
        if (from->posx > to->posx)
            id -= 8;
        else
            id += 8;
    }
    if (!getHeightOfId(id)) {
        if (getWoolCount() == 0)
            return 0;
        else
            place_block_id(id);
    }
    return 1;
}

int mymove(Position_edc25* from, Position_edc25* to) {
    setv(SPE);
    //rotate
    while (!arrive(from, to)) {
        if (!putWool(from, to) || accident()) {
            setv(0);
            return 0;
        }
    }
    setv(0);
    return 1;
}

int myMove() {
    for (int i = 1; i < pathLen; i++)
        if (!mymove(&myPath[i - 1], &myPath[i]))
            return 0;
    return 1;
}

int decide() {
    Position_edc25* tmp = (Position_edc25*)calloc(64, sizeof(Position_edc25));
    int len = 0;
    for(int i = 0; i < 8; i++)
    	for(int j = 0; j < 8; j++)
    		visited[i][j] = 0;
    tryNum = 0;
    findPath(myBase[0], myBase[1], 0, 8, tmp, &len);
    free(tmp);
    return 0;
}

void myTrade() {

}

void executeTask(int x) {
    if (x == 0) {
    	printMap();
        printPath();
        myMove();
        int res = myMove();
        if (res)
            myTrade();
    }
}

void gameRun() {
    myPath = (Position_edc25*)calloc(64, sizeof(Position_edc25));
    while (1) {
        int res = decide();
        executeTask(res);
    }
}
