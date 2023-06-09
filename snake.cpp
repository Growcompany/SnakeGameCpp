#include "snake.h"
#include <ncurses.h>

SnakeGame::SnakeGame() {
    width = 20;
    height = 20;
    direction = KEY_RIGHT;
    gameOver = false;
    snake.push_back({width/2, height/2});

    Initialize();
}

void SnakeGame::Initialize() {
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void SnakeGame::HandleInput() {
    int key = getch();
    switch (key) {
        case KEY_UP:
            if (direction != KEY_DOWN)
                direction = KEY_UP;
            break;
        case KEY_DOWN:
            if (direction != KEY_UP)
                direction = KEY_DOWN;
            break;
        case KEY_LEFT:
            if (direction != KEY_RIGHT)
                direction = KEY_LEFT;
            break;
        case KEY_RIGHT:
            if (direction != KEY_LEFT)
                direction = KEY_RIGHT;
            break;
    }
}

void SnakeGame::Update() {
    int x = snake[0].x;
    int y = snake[0].y;

    switch (direction) {
        case KEY_UP:
            y--;
            break;
        case KEY_DOWN:
            y++;
            break;
        case KEY_LEFT:
            x--;
            break;
        case KEY_RIGHT:
            x++;
            break;
    }

    snake.insert(snake.begin(), {x, y});
    mvprintw(y, x, "O");

    mvprintw(snake.back().y, snake.back().x, " ");
    snake.pop_back();

    refresh();
}

bool SnakeGame::IsGameOver() {
    return gameOver;
}

void SnakeGame::Run() {
    while (!IsGameOver()) {
        HandleInput();
        Update();
        napms(100);
    }

    getch();
    endwin();
}

int main() {
    SnakeGame game;
    game.Run();

    return 0;
}