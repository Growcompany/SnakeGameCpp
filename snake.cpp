#include "snake.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

char map[MAP_X][MAP_Y];

SnakeGame::SnakeGame() {
    width = 20;
    height = 20;
    direction = KEY_RIGHT;
    gameOver = false;
    snake.push_back({width/2, height/2}); // set snake start position
    snake.push_back({width/2+1, height/2});
    snake.push_back({width/2+2, height/2});
}

void SnakeGame::HandleInput() {
    int key = getch();
    switch (key) {
        case KEY_UP:
            if (direction == KEY_DOWN){
                gameOver = true;
            }
            else{
                direction = KEY_UP;
            }
            break;
        case KEY_DOWN:
            if (direction == KEY_UP){
                gameOver = true;
            }
            else{
                direction = KEY_DOWN;
            }
            break;
        case KEY_LEFT:
            if (direction == KEY_RIGHT){
                gameOver = true;
            }
            else{
                direction = KEY_LEFT;
            }
            break;
        case KEY_RIGHT:
            if (direction == KEY_LEFT){
                gameOver = true;
            }
            else{
                direction = KEY_RIGHT;
            }
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

    mvprintw(snake.back().y, snake.back().x, " "); // map recovery
    snake.pop_back();

    refresh();
}

bool SnakeGame::IsCollision() {
    if(snake[0].x < 2 || snake[0].x > MAP_Y-1 || snake[0].y<2 || snake[0].y> MAP_X-1){
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


void SnakeGame::GrowthItem(int *be_time, int *item_cnt){
    int now_time = clock();

    if(now_time - *be_time/CLOCKS_PER_SEC > 5 && *item_cnt<3){ // 5 second create and lower than 3
        srand((unsigned int)time(NULL)); // set random now time
        int item_x = 1 + rand() % (MAP_X-2);
        int item_y = 1 + rand() % (MAP_Y-2);
        mvprintw(item_x, item_y, "+");
        map[item_x-1][item_y-1] = '+';
        *item_cnt += 1;
    }

    *be_time = now_time;
}



bool SnakeGame::IsGameOver() {
    return gameOver;
}

void SnakeGame::Run() {
    int now_time = clock();
    int item_cnt = 0;
    while (!IsGameOver()) {
        HandleInput();
        Update();
        IsCollision();
        GrowthItem(&now_time, &item_cnt);
        napms(100);
    }
    mvprintw(0,0, "GAME OVER!!"); //show game over massage
    endwin();
}