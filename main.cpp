#include <iostream>
#include <ncurses.h>
using namespace std;

int main(){
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    noecho();

    int map_x = 22;
    int map_y = 35;

    char map[map_x][map_y];
    for(int i=0; i<map_x; i++){
        for(int j=0; j<map_y; j++){
            map[i][j] = '0';
        }
        map[i][0] = '1';
        map[i][map_y-1] = '1';
    }

    for(int i=0; i<map_y; i++){
        map[0][i] = '1';
        map[map_x-1][i] = '1';
    }

    map[0][0] = '2';
    map[map_x-1][0] = '2';
    map[0][map_y-1] = '2';
    map[map_x-1][map_y-1] = '2';

    for(int i=0; i<map_x; i++){
        for(int j=0; j<map_y; j++){
            const char temp = map[i][j];
            mvprintw(1+i,1+j, "%c",map[i][j]);
        }
    }

    int vertical_x = COLS / 2;
    for(int y=0; y < LINES; ++y){
        mvaddch(y, vertical_x, '|');
    }
    
    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_UP:
                mvprintw(0, 0, "Up Arrow");
                break;
            case KEY_DOWN:
                mvprintw(0, 0, "Down Arrow");
                break;
            case KEY_LEFT:
                mvprintw(0, 0, "Left Arrow");
                break;
            case KEY_RIGHT:
                mvprintw(0, 0, "Right Arrow");
                break;
            default:
                mvprintw(0, 0, "Other Key");
                break;
        }
        refresh();
    }

    refresh();
    getch();
    endwin();
    return 0;
}