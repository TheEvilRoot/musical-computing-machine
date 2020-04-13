#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

void show_time(WINDOW *win, char prefix) {
	clock_t n = clock();
	while (1) {
		mvwprintw(win,0,0,"%c: %ld\n", prefix, n);
		wrefresh(win);
		n = time(NULL);
		sleep(1);
	}
}

int child(WINDOW *win) {
	show_time(win, 'C');	
	return 0;
}

int parent(WINDOW *win) {
	show_time(win, 'P');
	return 0;
}

int main() {
	initscr();
	noecho();
	WINDOW *win = newwin(10, 16, 0, 0);
	WINDOW *win1 = newwin(10, 16, 0, 32);

	int flag = fork();
	switch(flag) {
		case -1: exit(-1);
		case 0: return child(win);
		default: return parent(win1);
	}
	return 0;
}
