#include "snake.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame() {
    width = 20;
    height = 20;
    direction = KEY_RIGHT;
    gameOver = false;
    snake.push_back({width/2, height/2}); // set snake start position
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
    
    int be_x = x;
    int be_y = y;

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
    mvprintw(y, x, "#"); // move snake

    mvprintw(snake.back().y, snake.back().x, "0"); // map recovery
    snake.pop_back();

    refresh();
}

bool SnakeGame::IsCollision(int max_x, int max_y) {
    if(snake[0].x < 2 || snake[0].x > max_y-1 || snake[0].y<2 || snake[0].y> max_x-1){
        mvprintw(0, 0, "collision!!");
        gameOver = true;//restart game & endgame
        mvprintw(snake[0].x, snake.back().y, "1"); // restore wall
    }
    else{
        mvprintw(0, 0, "------------");
    }
    //mvprintw(0, 15,"%d %d", snake[0].x, snake[0].y);
    return true;
}

bool SnakeGame::IsGameOver() {
    return gameOver;
}

void SnakeGame::Run(int max_x, int max_y) {
    while (!IsGameOver()) {
        HandleInput();
        Update();
        IsCollision(max_x, max_y);
        napms(100);
    }
    mvprintw(0,0, "GAME OVER!!"); //show game over massage
    endwin();
}

void SnakeGame::GrowthItem(){
    GrowthItem_x = rand() % width;
    GrowthItem_y = rand() % height;
    mvprintw(GrowthItem_x, GrowthItem_y, "G");
    GrowthItem = 0;
    
    if(y == GrowthItem_x && x == GrowthItem_y){
        GrowthItem += 1;
        GrowthItem_x = rand() % width;
        GrowthItem_y = rand() % height;
        mvprintw(GrowthItem_x, GrowthItem_y, "G");
    }
}

void SnakeGame::PositiveItem(){
    PositiveItem_x = rand() % width;
    PositiveItem_y = rand() % height;
    mvprintw(PositiveItem_x, PositiveItem_y, "P");
    PositiveItem = 0;
    
    if(y == PositiveItem_x && x == PositiveItem_y){
        PositiveItem += 1;
        PositiveItem_x = rand() % width;
        PositiveItem_y = rand() % height;
        mvprintw(PositiveItem_x, PositiveItem_y, "P");
    }
}
