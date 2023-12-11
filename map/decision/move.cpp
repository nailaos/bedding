#include "move.h"
#include <cmath>
using namespace std;

bool arrive(const Position_edc25& from, const Position_edc25& to) {
    Position_edc25 curr = { 0.0,0.0 };
    getPosition(&curr);
    float distance = (to.x - curr.x) * (to.y - curr.y);
    if (distance < LEN)
        return true;
    return false;
}

bool putWool(const Position_edc25& from, const Position_edc25& to) {
    Position_edc25 curr = { 0.0,0.0 };
    getPosition(&curr);
    int id = getMapPosition(curr);
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
            return false;
        else
            place_block_id(id);
    }
    return true;
}

bool mymove(const Position_edc25& from, const Position_edc25& to) {
    setSpeed(SPEED);
    //rotate
    while (!arrive(from, to)) {
        if (!putWool(from, to) || decision()) {
            setSpeed(0);
            return false;
        }
    }
    setSpeed(0);
    return true;
}

void myMove() {
    for (int i = 1; i < myPath.size(); i++)
        if (!mymove(myPath[i - 1], myPath[i]))
            return;
}