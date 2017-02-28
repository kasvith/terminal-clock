#define COLUMNS 6
#define ROWS 5
#define BLOCK_LETTERS 1
#define DATE_LETTERS 2
#define COLOR_SIZE 8

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

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
const char* colors[] = {"black","red","green","yellow","blue","magenta","cyan","white"};

void update();
void printNumber(WINDOW* ,const int array[ROWS][COLUMNS]);
void refreshWindows();
WINDOW *create_newwin(int height, int width, int starty, int startx);
void initWindows();
void initColors();
void clearWindows();
void printDate(int, int, int);
void printUsage();
void printInvalidArgument(char*);
void processArgs(int argc, char *argv[]);
void setColor(char *);

//window definitions
WINDOW* hourLeft,*hourRight,*minutesLeft,*minutesRight,*secondsLeft,*secondsRight,*commaOne,*commaTwo,*date;

//range for colors are 0 - 7
int color = 7;

int main(int argc, char *argv[]){
	processArgs(argc, argv);

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

void setColor(char* c){
	int idx = -1;
	int tmp_clr = -1;
	for(idx = 0; idx < COLOR_SIZE; idx++){
		if(strcmp(c, colors[idx]) == 0){
			tmp_clr = idx;
		}
	}

	if(tmp_clr == -1){
		printf("'%s' : This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", c);
		exit(EXIT_FAILURE);
	}

	color = tmp_clr;
}

void processArgs(int argc, char *argv[]){
    int opt;

    while ((opt = getopt(argc, argv, "hC:"))!= -1) {
        switch (opt) {
            case 'C':
                setColor(optarg);
                break;

            case 'h':
                printUsage();
				exit(EXIT_SUCCESS);
                break;

			default:
				printUsage();
				exit(EXIT_FAILURE);
				break;
        }
    }
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
	date 		 = create_newwin(1, 10, ROWS + 2,  22);
}

void printDate(int y, int m, int d){
	wattron(date,COLOR_PAIR(DATE_LETTERS));
	wprintw(date,"%d-%d%d-%d%d", 1900+y, m/10, m%10, d/10, d%10);
	wattroff(date,COLOR_PAIR(DATE_LETTERS));
}

void initColors(){
	init_pair(BLOCK_LETTERS, COLOR_BLACK, color);
	init_pair(DATE_LETTERS, color, COLOR_BLACK);
}

void refreshWindows() {
	wrefresh(hourLeft);
	wrefresh(hourRight);
	wrefresh(minutesLeft);
	wrefresh(minutesRight);
	wrefresh(secondsLeft);
	wrefresh(secondsRight);
	wrefresh(date);
}

void clearWindows() {
	wclear(date);
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
                wattron(win,COLOR_PAIR(BLOCK_LETTERS));
				wprintw(win," ");
                wattroff(win,COLOR_PAIR(BLOCK_LETTERS));
			}else{
				wprintw(win," ");
			}
		}
	}
}

void printUsage(){
	printf("usage : clock -C <black|red|green|yellow|blue|magenta|cyan|white]\n");
	exit(1);
}

void printInvalidArgument(char* arg){

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

	printDate(timeinfo->tm_year, timeinfo->tm_mon + 1, timeinfo->tm_mday);

	refreshWindows();
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}
