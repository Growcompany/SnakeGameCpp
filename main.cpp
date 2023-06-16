#include <iostream>
#include <ncurses.h>
#include "snake.cpp"
#include "map.cpp"
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

int main(){
    int stage = 1;
    while(stage<5){
        initialize();
        set_map(stage);
        print_map(map);
        SnakeGame s;
        if(s.Run()){ // go to next stage
            print_result(true);
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
            print_result(false);
            bool restart = false;
            while(true){
                int key = getch();
                if(key == 'R' || key == 'r'){
                    restart = true;
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
