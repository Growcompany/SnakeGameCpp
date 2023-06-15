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

class SnakeGame {
public:
    SnakeGame();
    void Run();

private:
    void Initialize();
    void HandleInput();
    void Update();
    bool IsCollision();
    void GrowthItem();
    void PoisonItem();
    bool IsGameOver();

    int width, height;
    std::vector<Point> snake;
    std::vector<items> Growth_items;
    std::vector<items> Poison_items;
    int direction;
    int Growth_time;
    int Poison_time;
    bool gameOver;
};

#endif