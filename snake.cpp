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
    Growth_time = time(NULL);
    Poison_time = time(NULL);
    Growth_cnt = 0;
    Poison_cnt = 0;
    snake.push_back({width/2, width/2}); // set snake start position
    snake.push_back({width/2+1, height/2});
    snake.push_back({width/2+2, height/2});
    map[width/2-1][width/2-1] = '#';
    map[width/2][width/2-1] = '#';
    map[width/2+1][width/2-1] = '#';
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

    if(map[y-1][x-1] == '+'){ //snake collision GrowthItem
        mvprintw(0, 0, "Get item!!!!!! %d %d", y-1, x-1);
        snake.insert(snake.end(), {snake.back().x, snake.back().y}); //insert plus tail
        map[y-1][x-1] = ' '; // renew room property
        int erase_pos;
        for(int i=0; i<Growth_items.size(); i++){ // find item in Growth_items 
            if(Growth_items[i].x == y && Growth_items[i].y == x){
                erase_pos = i;
                break;
            }
        }
        Growth_items.erase(Growth_items.begin()+erase_pos);

        Growth_cnt += 1;
    }

    if(map[y-1][x-1] == '-'){ // snake collision PoisionItem
        mvprintw(0, 0, "Poison item...-_-; %d %d", y-1, x-1);
        map[y-1][x-1] = ' '; // renew room property
        int erase_pos;
        for(int i=0; i<Poison_items.size(); i++){ // find item in Poison_items 
            if(Poison_items[i].x == y && Poison_items[i].y == x){
                erase_pos = i;
                break;
            }
        }
        Poison_items.erase(Poison_items.begin()+erase_pos);

        mvprintw(snake.back().y, snake.back().x, " "); //remove tail
        map[snake.back().y-1][snake.back().x-1] = ' ';
        snake.pop_back(); //remove tail

        Poison_cnt += 1;

        if(snake.size()<3){ // if less than 3 size snake
            gameOver = true;
            return;
        }
    }

    if(map[y-1][x-1] == 'D'){ // snake collision PoisionItem
        mvprintw(0, 0, "D_Growth_item; %d %d", y-1, x-1);
        snake.insert(snake.end(), {snake.back().x, snake.back().y}); //insert plus tail 1
        snake.insert(snake.end(), {snake.back().x, snake.back().y}); //insert plus tail 2
        map[y-1][x-1] = ' '; // renew room property
        int erase_pos;
        for(int i=0; i<D_Growth_items.size(); i++){ // find item in Poison_items 
            if(D_Growth_items[i].x == y && D_Growth_items[i].y == x){
                erase_pos = i;
                break;
            }
        }
        D_Growth_items.erase(D_Growth_items.begin()+erase_pos);

        D_Growth_cnt += 1;
    }

    map[y-1][x-1] = '#'; // renew map property(head moved snake)
    mvprintw(snake.back().y, snake.back().x, " "); // map recovery
    map[snake.back().y-1][snake.back().x-1] = ' '; // renew map property(tail moved snake)
    snake.pop_back();

    refresh();
}

bool SnakeGame::IsCollision() {
    if(snake[0].x < 2 || snake[0].x > MAP_Y-1 || snake[0].y<2 || snake[0].y> MAP_X-1){
        mvprintw(0, 0, "collision!!");
        gameOver = true;//restart game & endgame
        mvprintw(snake[0].x, snake.back().y, "1"); // restore wall
    }
    //mvprintw(0, 15,"%d %d", snake[0].x, snake[0].y);
    return true;
}

void SnakeGame::GrowthItem(){
    int now_time = time(NULL);

    mvprintw(0, 0, "b_time %d n_time %d G_item:%ld P_item:%ld", Growth_time, now_time, Growth_items.size(), Poison_items.size());
    if(Growth_items.size()>0){ // created item in 10 second & destory
        if(now_time - Growth_items[0].time>10){
            map[Growth_items[0].x-1][Growth_items[0].y-1] = ' ';
            mvprintw(Growth_items[0].x, Growth_items[0].y, " ");
            Growth_items.erase(Growth_items.begin());
        }
    }
    
    if((now_time - Growth_time) > 2 && (D_Growth_items.size()+Growth_items.size()+Poison_items.size())<3){ // 2 second create and lower than 3 .
        srand((unsigned int)time(NULL)); // set random now time
        int item_x = 2 + rand() % (MAP_X-2);
        int item_y = 2 + rand() % (MAP_Y-2);
        if(map[item_x-1][item_y-1] != ' '){ // if snake or other item exist
            return;
        }
        mvprintw(item_x, item_y, "+");
        map[item_x-1][item_y-1] = '+'; // renew map property to '+'
        mvprintw(0, 0, "create G_item!!!!!! %d %d", item_x-1, item_y-1);
        Growth_time = now_time;
        Growth_items.push_back({item_x, item_y, now_time});
    }
}

void SnakeGame::PoisonItem(){
    int now_time = time(NULL);

    if(Poison_items.size()>0){ // created item in 10 second & destory
        if(now_time - Poison_items[0].time>10){
            map[Poison_items[0].x-1][Poison_items[0].y-1] = ' ';
            mvprintw(Poison_items[0].x, Poison_items[0].y, " ");
            Poison_items.erase(Poison_items.begin());
        }
    }

    if((now_time - Poison_time) > 5 && (D_Growth_items.size()+Growth_items.size()+Poison_items.size())<3){ // 5 second create and lower than 3 .
        srand((unsigned int)time(NULL)); // set random now time
        int item_x = 2 + rand() % (MAP_X-2);
        int item_y = 2 + rand() % (MAP_Y-2);
        if(map[item_x-1][item_y-1] != ' '){ // if snake or other item exist
            return;
        }
        mvprintw(item_x, item_y, "-");
        map[item_x-1][item_y-1] = '-';
        mvprintw(0, 0, "create P_item!!!!!! %d %d", item_x-1, item_y-1);
        Poison_time = now_time;
        Poison_items.push_back({item_x, item_y, now_time});
    }
}

void SnakeGame::D_GrowthItem(){
    int now_time = time(NULL);

    if(D_Growth_items.size()>0){ // created item in 10 second & destory
        if(now_time - D_Growth_items[0].time>10){
            map[D_Growth_items[0].x-1][D_Growth_items[0].y-1] = ' ';
            mvprintw(D_Growth_items[0].x, D_Growth_items[0].y, " ");
            D_Growth_items.erase(D_Growth_items.begin());
        }
    }
    
    if((now_time - D_Growth_time) > 7 && (D_Growth_items.size()+Growth_items.size()+Poison_items.size())<3){ // 7 second create and lower than 3 .
        srand((unsigned int)time(NULL)); // set random now time
        int item_x = 2 + rand() % (MAP_X-2);
        int item_y = 2 + rand() % (MAP_Y-2);
        if(map[item_x-1][item_y-1] != ' '){ // if snake or other item exist
            return;
        }
        mvprintw(item_x, item_y, "D");
        map[item_x-1][item_y-1] = 'D'; // renew map property to '+'
        mvprintw(0, 0, "create D_G_item!!!!!! %d %d", item_x-1, item_y-1);
        D_Growth_time = now_time;
        D_Growth_items.push_back({item_x, item_y, now_time});
    }
}

bool SnakeGame::IsGameOver() {
    return gameOver;
}

void SnakeGame::Update_scoreboard(){
    int vertical_x = COLS / 2 + 2;

    mvprintw(2, vertical_x, "Score  Board");
    mvprintw(3, vertical_x, "B : (%ld) / (15)",snake.size());
    mvprintw(4, vertical_x, "+ : (%d)",Growth_cnt);
    mvprintw(5, vertical_x, "- : (%d)",Poison_cnt);
    mvprintw(6, vertical_x, "G : (Gate Usage Count)");
    mvprintw(7, vertical_x, "D : (%d)",D_Growth_cnt);

    mvprintw(10, vertical_x, "Mission");
    mvprintw(11, vertical_x, "B : 10 (%c)", snake.size()>9 ? 'V':' ');
    mvprintw(12, vertical_x, "+ : 5 (%c)", Growth_cnt>4 ? 'V':' ');
    mvprintw(13, vertical_x, "- : 2 (%c)", Poison_cnt>1 ? 'V':' ');
    mvprintw(14, vertical_x, "G : 1 ( )");

    if(snake.size() > 9 && Growth_cnt > 4 && Poison_cnt > 1){
        // mvprintw(0,0, "GAME OVER!!");
        gameOver = true;
        endwin();
    }
}

void SnakeGame::Run() {
    while (!IsGameOver()) {
        HandleInput();
        Update();
        Update_scoreboard();
        IsCollision();
        GrowthItem();
        PoisonItem();
        D_GrowthItem();
        napms(180-snake.size()*10); // if snake size is longer speed up 2-(2)
    }
    mvprintw(0,0, "GAME OVER!!"); //show game over massage
    endwin();
}