/*

GarageCode Genial Creations Hehehe
http://GarageCode.tk

*Function this programm
this program i use to create tables to work with Boole's table
recently i make this code to help my Friend in high school.
everybody hate wrote boole's table on computer and with hands..
This programm is a solution dudes!

*tested with GCC but wheel in others compilers...
 i wheel on Unix/Linux/*BSD this: 
    gcc -o program program.c; ./program

Author: Antonio "Cooler_x86" 
contact: tony.unix@yahoo.com.br
license: BSD

visit this site: http://BotecoUnix.com.br
Real Geeks BotecoUnix

greetz 
Thanks _mlk_ , m0nad,IAK,Fox,nibbles and Chris Torek. 
K&R for book ansi C

reference and Big greetz 
http://web.torek.net/torek/ 

      .--..--..--..--..--..--.
    .' \  (`._   (_)     _   \
  .'    |  '._)         (_)  |
  \ _.')\      .----..---.   /
  |(_.'  |    /    .-\-.  \  |
  \     0|    |   ( O| O) | o|
   |  _  |  .--.____.'._.-.  |
   \ (_) | o         -` .-`  |
    |    \   |`-._ _ _ _ _\ /
    \    |   |  `. |_||_|   |     Solution!
    | o  |    \_      \     |     -.   .-.
    |.-.  \     `--..-'   O |     `.`-' .'
  _.'  .' |     `-.-'      /-.__   ' .-'
.' `-.` '.|='=.='=.='=.='=|._/_ `-'.'
`-._  `.  |________/\_____|    `-.'
   .'   ).| '=' '='\/ '=' |
   `._.`  '---------------'
           //___\   //___\
             ||       ||
             ||_.-.   ||_.-.
            (_.--__) (_.--__)

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define w printf
#define wf fprintf
//MAx columms to create
#define MAX 1536
#define log "table.txt"

// Banner 
char opcao_menu() {
 int i;
 char *banner[] = {
  "Boole logic table generator",
  "coded by Cooler_x86  visit http://botecounix.com.br",
  "(1)create table A B C D",
  "(2)create table A B C ",
  "(0)Sair",
  "-> ",
 };
 for(i=0; i<=5; i++) w(" %s \x0a",banner[i]);
}

void create() {
 int a[MAX], b[MAX], c[MAX], d[MAX], i, cont=0, choice;
//take stdin from user
 w("Number of columns has a table?\x0a"); scanf("%d",&choice);
 int aa = 0, bb = 0, cc = 0, dd = 0;
 a[0] = 0; b[0] = 0; c[0] = 0; d[0] = 0;
//solution from nibbles
 for (i = 0; i < choice; ++i) {
   if (!(i % 8)) aa = !aa;
   if (!(i % 4)) bb = !bb;
   if (!(i % 2)) cc = !cc; 
   dd = !dd;
   a[i] =aa?0:1;
   b[i] =bb?0:1;
   c[i] =cc?0:1;
   d[i] =dd?0:1;
 }
// List STDOUT Table all rows A,B,C,D
 w(" \x0a  List Table with rows\x0a +---+---+---+---+-------+\x0a"); w(" | A | B | C | D |   S   |\x0a"); w(" +---+---+---+---+-------+\x0a");
 for(i=0; i<choice; i++) w(" | %i | %i | %i | %i |       | \x0a",a[i],b[i],c[i],d[i]); w(" +-----------------------+\x0a");
//Save table in Log file,defined in constant named log  
 FILE *arq; 
 arq=fopen(log,"a"); if(!arq) exit(1); 
 wf(arq," \x0a List Table with rows\x0a +---+---+---+---+-------+\x0a"); 
 wf(arq," | A | B | C | D |   S   |\x0a"); wf(arq," +---+---+---+---+-------+\x0a");
 for(i=0; i<choice; i++) wf(arq," | %i | %i | %i | %i |       | \x0a",a[i],b[i],c[i],d[i]);  
 wf(arq," +-----------------------+\x0a")&&fclose(arq); 
}


void add() {
 int a[MAX], b[MAX], c[MAX], i, cont=0, choice;

//take stdin from user
 w("Number of columns has a table?\x0a"); scanf("%d",&choice);

 int aa = 0, bb = 0, cc = 0;
 a[0] = 0; b[0] = 0; c[0] = 0; 
 for (i = 0; i < choice; ++i) {
   if (!(i % 8)) aa = !aa;
   if (!(i % 4)) bb = !bb;
   if (!(i % 2)) cc = !cc; 
   a[i] =aa?0:1;
   b[i] =bb?0:1;
   c[i] =cc?0:1;
 }

// List STDOUT Table all rows A,B,C
 w(" \x0a  List Table with rows\x0a +---+---+---+-------+\x0a"); w(" | A | B | C |   S   |\x0a"); w(" +---+---+---+-------+\x0a");
 for(i=0; i<choice; i++) w(" | %i | %i | %i |       | \x0a",a[i],b[i],c[i]); w(" +--------------------+\x0a");

//Save table in Log file,defined in constant named log  
 FILE *arq; 
 arq=fopen(log,"a"); if(!arq) exit(1); 
 wf(arq," \x0a List Table with rows\x0a +---+---+---+-------+\x0a"); 
 wf(arq," | A | B | C |   S   |\x0a"); wf(arq," +---+---+---+-------+\x0a");
 for(i=0; i<choice; i++) wf(arq," | %i | %i | %i |       | \x0a",a[i],b[i],c[i]);  
 wf(arq," +-------------------+\x0a")&&fclose(arq); 
}

// call the functions
int main(int args, char * arg[]) {
 int op;  
 while (op!=0) {
   opcao_menu();
   scanf("%d",&op);
   if(op==1) create(); 
   if(op==2) add();
 }
 return 0;
}
