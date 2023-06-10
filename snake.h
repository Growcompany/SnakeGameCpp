#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

struct Point {
    int x, y;
};

class SnakeGame {
public:
    SnakeGame();
    void Run(int max_x, int max_y);

private:
    void Initialize();
    void HandleInput();
    void Update();
    bool IsCollision(int max_x, int max_y);
    bool IsGameOver();
    void GrowthItem();
    void PositiveItem();

    int width, height;
    std::vector<Point> snake;
    int direction;
    bool gameOver;
};

#endif
