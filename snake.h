#ifndef SNAKE_H
#define SNAKE_H

#define MAP_X 23 // set room row size
#define MAP_Y 30 // set room column size
#include <vector>
extern char map[MAP_X][MAP_Y];

struct Point {
    int x, y;
};

struct items {
    int x, y, time;
};

struct gateItems {
    Point gate1, gate2;
    int time;
};

struct GateItemInfo {
    std::pair<int, int> gate1;
    std::pair<int, int> gate2;
};

struct Gate {
    Point entry;
    Point exit;
};

class SnakeGame {
public:
    SnakeGame();
    void Run();

private:
    void HandleInput();
    void Update();
    bool IsCollision();
    void GrowthItem();
    void PoisonItem();
    void GateItem();
    bool IsGameOver();
    void Initialize();
    void SetMap();
    void PrintMap();

    int width, height;
    std::vector<Point> snake;
    std::vector<items> Growth_items;
    std::vector<items> Poison_items;
    std::vector<gateItems> Gate_items;
    std::vector<Gate> gates;
    int direction;
    int Growth_time;
    int Poison_time;
    int Gate_time;
    bool gameOver;
};

#endif
