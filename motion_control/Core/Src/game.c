#include "game.h"

#define SPEED 30
#define WOOL 16

int myMap[8][8];
int visited[8][8];
Position_edc25* myPath;
int myBase[2] = { 0, 0 };
int pathLen;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int maxMinerNum = 0;
int tryNum = 0;
int upperLimit;

void initMap(char* mapInfo) {
    for (int i = 0; i < 64; i++) {
        int x = i / 8;
        int y = i % 8;
        int val = mapInfo[i] - '0';
        myMap[x][y] = val;
        upperLimit += val;
    }
}

int getMapId(Position_edc25* points) {
    int x = (int)points.x;
    int y = (int)points.y;
    return 8 * y + x;
}

int findPath(int x, int y, int currMiner, int woolNum, Position_edc25* path, int* len) {
    currMiner += myMap[x][y];
    visited[x][y] = 1;
    if (woolNum == 0) {
        if (currMiner > maxMinerNum) {
            maxMinerNum = currMiner;
            path[*len].posx = (float)x;
            path[*len].posy = (float)y;
            *len++;
            pathLen = *len;
            for (int i = 0; i < pathLen; i++)
                myPath[i] = path[i];
            *len--;
            if (maxMinerNum == upperLimit / 2)
                return 1;
        }
        tryNum++;
        visited[x][y] = 0;
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + directX[i];
        int ny = y + directY[i];
        if (nx < 0 || nx>7 || ny < 0 || ny > 7)
            continue;
        if (visited[nx][ny])
            continue;
        path[*len].posx = (float)x;
        path[*len].posy = (float)y;
        *len++;
        if (findPath(nx, ny, currMiner, woolNum - 1, path, len))
            return 1;
        *len--;
    }
    visited[x][y] = 0;
    return 0;
}

int arrive(Position_edc25* from, Position_edc25* to) {
    Position_edc25* curr = new Position_edc25;
    getPosition(&curr);
    float distance = (to.x - curr.x) * (to.y - curr.y);
    if (distance < LEN)
        return 1;
    return 0;
}

int accident() {
    return 0;
}

int putWool(Position_edc25* from, Position_edc25* to) {
    Position_edc25* curr = new Position_edc25;
    getPosition(&curr);
    int id = getMapId(curr);
    if (abs(from.x - to.x) < 0.5) {
        if (from.y > to.y)
            id -= 1;
        else
            id += 1;
    } else {
        if (from.x > to.x)
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
    setv(SPEED);
    //rotate
    while (!arrive(from, to)) {
        if (!putWool(from, to) || accident()) {
            setv(0);
            return 0;
        }
    }
    setSpeed(0);
    return 1;
}

int myMove() {
    for (int i = 1; i < pathLen; i++)
        if (!mymove(&myPath[i - 1], &myPath[i]))
            return -1;
    for (int i = pathLen - 1; i > 0; i--)
        if (!mymove(&myPath[i], &myPath[i - 1]))
            return 0;
    return 1;
}

int decide() {
    Position_edc25* tmp = (Position_edc25*)calloc(64, sizeof(Position_edc25 = ));
    int len = 0;
    findPath(myBase[0], myBase[0], 0, getWoolCount(), tmp, &len);
    free(tmp);
    return 0;
}

void myTrade() {

}

void executeTask(int x) {
    if (x == 0) {
        findPath();
        int res = myMove();
        if (res)
            myTrade();
    }
}

void gameRun() {
    myPath = (Position_edc25*)calloc(64, sizeof(Position_edc25 = ));
    while (1) {
        int res = decide();
        executeTask(res);
    }
}