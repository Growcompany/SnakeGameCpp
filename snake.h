#ifndef SNAKE_H
#define SNAKE_H

#define MAP_X 23 // set room row size
#define MAP_Y 30 // set room column size
#include <vector>
extern char map[MAP_X][MAP_Y];

struct Point {
    int x, y;
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
    void GrowthItem(int *be_time, int *item_cnt);
    bool IsGameOver();

    int width, height;
    std::vector<Point> snake;
    int direction;
    bool gameOver;
};

#endif