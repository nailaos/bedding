#include <iostream>
#include "game.h"
#include "move.h"
using namespace std;

int main() {
    initMap();
    printMap();
    decision();
    printPath();
}