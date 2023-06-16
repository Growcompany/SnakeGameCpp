#include <iostream>
#include <ncurses.h>
#include "snake.h"

void set_map(int stage){

    for(int i=0; i<MAP_X; i++){
        for(int j=0; j<MAP_Y; j++){
            map[i][j] = ' ';
        }
        map[i][0] = '1';
        map[i][MAP_Y-1] = '1';
    }

    for(int i=0; i<MAP_Y; i++){
        map[0][i] = '1';
        map[MAP_X-1][i] = '1';
    }

    map[0][0] = '2';
    map[MAP_X-1][0] = '2';
    map[0][MAP_Y-1] = '2';
    map[MAP_X-1][MAP_Y-1] = '2';

    switch(stage){
        case 1: //set stage1 map
            for(int i=10; i<15; i++){
                map[MAP_X/4][i] = '1'; 
            }
            break;
        case 2: //set stage2 map
            break;
        case 3:
            break;
        case 4:
            break;
    }

}

void print_map(char map[MAP_X][MAP_Y]){
    for(int i=0; i<MAP_X; i++){
            for(int j=0; j<MAP_Y; j++){
                const char temp = map[i][j];
                mvprintw(1+i,1+j, "%c",map[i][j]);
            }
        }
    
    int vertical_x = COLS / 2; 
    for(int y=0; y < LINES; ++y){ // draw middle line in map
        mvaddch(y, vertical_x, '|');
    }
}

void print_result(bool nextstage){
    int height = 8;
    int width = 26;
    int x = (LINES - height) / 2;
    int y = (COLS - width) / 8;

    WINDOW *win = newwin(height, width, x, y);
    box(win, 0, 0);

    if(nextstage){
        mvwprintw(win, height / 2-3, width/2-6, "<next stage>");
        mvwprintw(win, height / 2, 1, "Enter: next stage");
    }
    else{
        mvwprintw(win, height / 2-3, width/2-5, "<GameOver>");
        mvwprintw(win, height / 2, 1, "R: game restart");
    }
    mvwprintw(win, height / 2-2, 1, "Press the key...");
    mvwprintw(win, height / 2+1, 1, "ESC: close game");

    refresh();
    wrefresh(win);
}
