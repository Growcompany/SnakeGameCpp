#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

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
    bool IsGameOver();

    int width, height;
    std::vector<Point> snake;
    int direction;
    bool gameOver;
};

#endif