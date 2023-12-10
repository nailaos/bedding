bool move() {
    setV();
    rotate();
    time = currtime;
    while (true) {
        while ((currtime - time) % N == 0) {
            if (arrive) {
                setV(0);
                return true;
            }
            if (choice()) {
                setV(0);
                return false;
            }
        }
    }
}

void Move(const vector<Position>& path) {
    for (int i = 1; i < path.size(); i++)
        move(Position[i - 1], Positiopn[i]);
}

while (true) {
    choice();
    switch (x) {
        case 0:
            move();
            break;
    }
}