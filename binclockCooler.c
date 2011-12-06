/*
Simples brincadeira com ncurses
relogio binario


$ gcc -o binclockCooler binclockCooler.c -lncurses

by Cooler_
c00f3r[at]gmail[dot]com

thanks m0nad ;)

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ncurses.h>

#define loop(a, b, c) \
uc2bin(s[b], p); \
do{ for(i=a, k=c, j=CHAR_BIT-1; k--; i--, j--) \
    m[i][b]=p[j]; } while(0)

void uc2bin(int c, char *s);

int main() 
{
 struct tm *tm;
 time_t t;

 char m[4][7] = {0};
 char p[CHAR_BIT+1];
 char s[512];

 int i,j,k;

 initscr();
 cbreak();
 clear();
 scrollok(stdscr, TRUE);
 idlok(stdscr, TRUE);
 echo();
 attrset(A_BOLD);
 box(stdscr, 0, 0);
 start_color();
 init_pair(2, COLOR_YELLOW, COLOR_BLACK);
 attrset(COLOR_PAIR(2) | A_BOLD);
 
 mvprintw(2, 17, "   10000  100000  100000  10   10000 1000");
 mvprintw(3, 17, "   00     00  00  00  00  00   0     00 00");
 mvprintw(4, 17, "   00     00  00  00  00  00   000   0000");
 mvprintw(5, 17, "   00     00  00  00  00  00   0     00 00");
 mvprintw(6, 17, "   00001  000001  000001  0001 00001 00 001 ");
 mvprintw(7, 17, "      ...:::Binary:Clock:::... ");

 init_pair(1, COLOR_BLUE, COLOR_GREEN);
 curs_set(0);

 m[0][4] = ' ';
 m[0][2] = ' ';
 m[1][0] = ' ';
 m[0][0] = ' ';
 while(1) 
 {
  time(&t);
  tm = localtime(&t);
  if(!tm) 
   exit(EXIT_FAILURE);
  strftime(s, sizeof s, "%H%M%S", tm);
  for(i = 0; i < 6; s[i++] -= '0');
  loop(3, 1, 4);
  loop(3, 0, 2);
  loop(3, 3, 4);
  loop(3, 2, 3);
  loop(3, 5, 4);
  loop(3, 4, 3);
  for (i = 0; i < 4; i++) {
    move(11+i,31);
    sprintf(s, "%s",m[i]); 
    addstr(s);
  }/*
  move(11,31);
  sprintf(s, "%s",m[0]); 
  addstr(s);

  move(12,31);
  sprintf(s, "%s",m[1]); 
  addstr(s);
  
  move(13,31);
  sprintf(s, "%s",m[2]);
  addstr(s);
  
  move(14,31);
  sprintf(s, "%s",m[3]);  
  addstr(s);
*/
  refresh();
  sleep(1);
 }
 endwin();
 return 0;
}

void uc2bin(int c, char *s) 
{ 
 size_t i;
 unsigned char uc = c;

 for(i = 0; i < CHAR_BIT; i++, uc <<= 1)
   *s++ = !!(uc & (~(UCHAR_MAX >> 1))) + '0';
 *s = 0;
}
