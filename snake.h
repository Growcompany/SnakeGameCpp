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
    bool Run(int stage, int *all_score);

private:
    void Initialize();
    bool HandleInput();
    void Update();
    void GrowthItem();
    void PoisonItem();
    void D_GrowthItem();
    bool IsGameOver();
    void Update_scoreboard();

    int width, height;
    std::vector<Point> snake;
    std::vector<items> Growth_items;
    std::vector<items> Poison_items;
    std::vector<items> D_Growth_items;
    int direction;
    int Growth_time;
    int Poison_time;
    int D_Growth_time;
    int Growth_cnt; // how much eat growth iteams
    int Poison_cnt; // how much eat poison_items
    int D_Growth_cnt;
    bool nextstage;
    bool gameOver;
    int score;

};

#endif
