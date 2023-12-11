#include "game.h"
#include <iomanip>
#include <windows.h>
using namespace std;

int myMap[8][8];
vector<Position_edc25> myPath;
bool visited[8][8] = { 0 };
int baseX;
int baseY;
int directX[4] = { -1, 0, 1, 0 };
int directY[4] = { 0, 1, 0, -1 };
int maxMiner = 0;
int tryNum = 0;
int theMaxMiner;

int getMapPosition(const Position_edc25& points) {
    int x = (int)points.x;
    int y = (int)points.y;
    return 8 * x + y;
}

void initMap() {
    cout << "Please enter base location (x, y): " << endl;
    cin >> baseX >> baseY;
    cout << "Please enter the number of chalcopyrite: " << endl;
    int num;
    cin >> num;
    cout << "Please enter the location of each chalcopyrite mine (x, y): " << endl;
    for (int i = 0; i < num; i++) {
        int a, b;
        cin >> a >> b;
        myMap[a][b] = 4;
    }
    theMaxMiner += 4 * num;
    cout << "Please enter the number of diamond mines: " << endl;
    cin >> num;
    cout << "Please enter the location of each diamond mine (x, y): " << endl;
    for (int i = 0; i < num; i++) {
        int a, b;
        cin >> a >> b;
        myMap[a][b] = 16;
    }
    theMaxMiner += 16 * num;
}

void printMap() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (myMap[i][j] == 4)
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            else if (myMap[i][j] == 16)
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            else
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << setw(2) << myMap[i][j] << ' ';
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int getDirection(int x, int y, int a, int b) {
    if (x == a) {
        if (b > y)
            return 1;
        else
            return 3;
    } else {
        if (a > x)
            return 0;
        else
            return 2;
    }
    return 0;
}

void updatePath(int x, int y, vector<Position_edc25>& path) {
    int n = path.size();
    //cout << "enter updatePath, the length of the path is " << n << endl;
    if (n < 2) {
        path.push_back(Position_edc25 { (float)x,(float)y });
        return;
    }
    int tmp1 = getDirection(x, y, (int)path[n - 1].x, (int)path[n - 1].y);
    int tmp2 = getDirection((int)path[n - 1].x, (int)path[n - 1].y, (int)path[n - 2].x, (int)path[n - 2].y);
    if (tmp1 != tmp2)
        path.push_back(Position_edc25 { (float)x,(float)y });
    else {
        path[n - 1].x = (float)x;
        path[n - 1].y = (float)y;
    }
}

void addPath(int x, int y, vector<Position_edc25>& path) {
    path.push_back(Position_edc25 { (float)x,(float)y });
}

bool findPath(int x, int y, int currMiner, int woolNum, vector<Position_edc25>& path) {
    currMiner += myMap[x][y];
    visited[x][y] = true;
    if (woolNum == 0) {
        if (currMiner > maxMiner) {
            maxMiner = currMiner;
            addPath(x, y, path);
            myPath = path;
            path.pop_back();
            if (maxMiner == theMaxMiner)
                return true;
        }
        tryNum++;
        visited[x][y] = false;
        return false;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + directX[i];
        int ny = y + directY[i];
        if (nx < 0 || nx>7 || ny < 0 || ny > 7)
            continue;
        if (visited[nx][ny])
            continue;
        addPath(x, y, path);
        if (findPath(nx, ny, currMiner, woolNum - 1, path))
            return true;
        path.pop_back();
    }
    visited[x][y] = false;
    return false;
}

bool decision() {
    cout << "start make decision" << endl;
    vector<Position_edc25> tmp;
    cout << "start find Path" << endl;
    findPath(baseX, baseY, 0, 8, tmp);
    return false;
}

void printPath(const vector<Position_edc25>& path) {
    int n = path.size();
    cout << "the length of path is " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << "[" << path[i].x << ", " << path[i].y << "]";
        if (i < n - 1)
            cout << "->";
    }
    cout << endl;
}

void printPath() {
    int n = myPath.size();
    cout << "final length of path is " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << "[" << myPath[i].x << ", " << myPath[i].y << "]";
        if (i < n - 1)
            cout << "->";
    }
    cout << endl;
    cout << "tryNum is " << tryNum << endl;
    cout << "the max mineral is " << maxMiner << endl;
}