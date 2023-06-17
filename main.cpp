#include <iostream>
#include <ncurses.h>
#include "snake.cpp"
#include "map.cpp"
using namespace std;

void initialize(){
    initscr(); // show scr
    WINDOW* win = newwin(1,1,0,0); // ? set win size
    clear(); //clear room
    cbreak(); 
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

int main(){
    int stage = 1;
    int all_score = 0;
    while(stage<5){
        initialize();
        set_room(stage);
        print_room(room);
        SnakeGame s;
        if(s.Run(stage, &all_score)){ // go to next stage
            switch(stage){
                case 1:
                all_score += 50;
                break;
                case 2:
                all_score += 100;
                break;
                case 3:
                all_score += 150;
                break;
                case 4:
                all_score += 200;
                break;
            }
            print_result(true, all_score, stage);
            stage+=1;
            bool gonext = false;
            while(true){
                int key = getch();
                if(key == '\n'){ // \0 is enter butoon
                    gonext = true;
                    break;
                }
                else if (key == 27){ // 27 is Esc button
                    break;
                }
            }
            if(!gonext){ // if press esc end game
                break;
            }
        }
        else{ // gameover
            print_result(false, all_score, stage);
            bool restart = false;
            while(true){
                int key = getch();
                if(key == 'R' || key == 'r'){
                    restart = true;
                    stage = 1;
                    all_score = 0;
                    break;
                }
                else if (key == 27){ // 27 is Esc button
                    break;
                }
            }
            if(!restart){ // if press esc not restart
                break;
            }
        }
    }

    getch();
    endwin(); // shut down
    return 0;
}