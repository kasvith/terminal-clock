#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define COLUMNS 6
#define ROWS 5

const int numbers[11][ROWS][COLUMNS] = {
		{
			//0
			{1,1,1,1,1,1},
			{1,1,0,0,1,1},
			{1,1,0,0,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1}
		},{
			//1
			{0,0,0,0,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1}
		},{
			//2
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{1,1,1,1,1,1},
			{1,1,0,0,0,0},
			{1,1,1,1,1,1}
		},
		{
			//3
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{1,1,1,1,1,1}
		},{
			//4
			{1,1,0,0,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1}
		},{
			//5
			{1,1,1,1,1,1},
			{1,1,0,0,0,0},
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{1,1,1,1,1,1}
		},{
			//6
			{1,1,1,1,1,1},
			{1,1,0,0,0,0},
			{1,1,1,1,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1}
		},{
			//7
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1},
			{0,0,0,0,1,1}
		},{
			//8
			{1,1,1,1,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1}
		},{
			//9
			{1,1,1,1,1,1},
			{1,1,0,0,1,1},
			{1,1,1,1,1,1},
			{0,0,0,0,1,1},
			{1,1,1,1,1,1}
		},{//comma
            {0,0,0,0,0,0},
			{0,0,1,1,0,0},
			{0,0,0,0,0,0},
			{0,0,1,1,0,0},
			{0,0,0,0,0,0}
        }

	};

void update();
void printNumber(WINDOW* ,const int array[ROWS][COLUMNS]);
void refreshWindows();
WINDOW *create_newwin(int height, int width, int starty, int startx);
void initWindows();
void initColors();
void clearWindows();

WINDOW* hourLeft;
WINDOW* hourRight;
WINDOW* minutesLeft;
WINDOW* minutesRight;
WINDOW* secondsLeft;
WINDOW* secondsRight;
WINDOW* commaOne;
WINDOW* commaTwo;

int color = 8;

int main(int argc, char const *argv[]){
	initscr();
 	noecho();
 	curs_set(FALSE);

	initWindows();
	start_color();
	initColors();

    //print static commas
    printNumber(commaOne, numbers[10]);
    printNumber(commaTwo, numbers[10]);
    wrefresh(commaOne);
    wrefresh(commaTwo);

    //update time
	while(1){
		update();
	}

	endwin();
	return 0;
}

void initWindows(){
	hourLeft     = create_newwin(ROWS, COLUMNS, 1, 1);
	hourRight    = create_newwin(ROWS, COLUMNS, 1, 8);
	commaOne     = create_newwin(ROWS, COLUMNS, 1, 14);
	minutesLeft  = create_newwin(ROWS, COLUMNS, 1, 20);
	minutesRight = create_newwin(ROWS, COLUMNS, 1, 27);
	commaTwo     = create_newwin(ROWS, COLUMNS, 1, 33);
	secondsLeft  = create_newwin(ROWS, COLUMNS, 1, 39);
	secondsRight = create_newwin(ROWS, COLUMNS, 1, 46);
}

void initColors(){
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
}

void refreshWindows() {
	wrefresh(hourLeft);
	wrefresh(hourRight);
	wrefresh(minutesLeft);
	wrefresh(minutesRight);
	wrefresh(secondsLeft);
	wrefresh(secondsRight);
}

void clearWindows() {
    wclear(hourLeft);
	wclear(hourRight);
	wclear(minutesLeft);
	wclear(minutesRight);
	wclear(secondsLeft);
	wclear(secondsRight);
}

void printNumber(WINDOW* win, const int array[ROWS][COLUMNS]){
	int i, j;
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			if(array[i][j] == 1){
                wattron(win,COLOR_PAIR(color));
				wprintw(win," ");
                wattroff(win,COLOR_PAIR(color));
			}else{
				wprintw(win," ");
			}
		}
	}
}

void update(){
    clearWindows();

 	time_t rawtime;
	struct tm * timeinfo;
	rawtime = time (NULL);
	timeinfo = localtime (&rawtime);

	printNumber(hourLeft, numbers[timeinfo->tm_hour / 10]);
	printNumber(hourRight, numbers[timeinfo->tm_hour % 10]);
	printNumber(minutesLeft, numbers[timeinfo->tm_min / 10]);
	printNumber(minutesRight, numbers[timeinfo->tm_min % 10]);
	printNumber(secondsLeft, numbers[timeinfo->tm_sec / 10]);
	printNumber(secondsRight, numbers[timeinfo->tm_sec % 10]);

	refreshWindows();
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}
