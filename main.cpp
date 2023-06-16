#include <iostream>
#include <ncurses.h>
#include "snake.cpp"
using namespace std;

void initialize(){
    initscr(); // show scr
    WINDOW* win = newwin(1,1,0,0); // ? set win size
    clear(); //clear map
    cbreak(); 
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void set_map(char map[MAP_X][MAP_Y]){

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

int main(){
    initialize();
    set_map(map);
    print_map(map);
    
    SnakeGame s;
    s.Run();

    getch();
    endwin(); // shut down
    return 0;
}
