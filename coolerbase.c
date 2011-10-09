/*

i make this programm for work purpoises 

*programa conversor de bases de 2 até 100 e -2 a -54
requer lib "gmp", para compilar "gcc -o code code.c -lgmp"

*programm to convert base of two until sixty two and -2 util -54
require lib "gmp" to run, to compile folow this command
"gcc -o code code.c -lgmp"

Date: 13/12/2010

*History of Code
 I maked this programme for work motives,i needed do big convertions but i dont had time to do all
 So something every boring to do, Then so went make programme to do this. i had got finish all task 
 in right time. this is result of some minutes of work. 


Author: Antonio "Cooler_" 
contact: c00f3r@gmail.com
license: BSD
 
Thanks _mlk_ , m0nad,IAK,D3lf0 

K&R for book ansi C

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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gmp.h>

static int pegabase(char **p);
int erro(mpz_t op);

int main(int argc, char **argv) 
{

 long long BaseEntrada, BaseSaida;
 char *p, *num, buf[BUFSIZ];
 size_t size;
 mpz_t op;

 if(argc < 2 || argc > 3) 
 {
  fprintf(stderr, "Coded by Cooler_ \nbase convert v0.1\n between 2 until 100 & -2 until -54\n%s [numero] <Base>\n", argc ? *argv : "base");
  return EXIT_FAILURE;
 }

 BaseSaida = strtol(argv[argc-1], &p, 10);
 if(!argv[argc-1][0] || *p != 0 || !((BaseSaida > -55 && BaseSaida < -1) || (BaseSaida > 1 && BaseSaida < 101))) 
 {
  fprintf(stderr, "base invalida '%s'. pode estar entre -2 ,-54 e 2,100\n", argv[argc-1]);
  return EXIT_FAILURE;
 }

 if(argc == 2) 
 { 
  mpz_init(op);

   do {
    if(buf[0] == '\n') continue;
     size = strlen(buf);
    if(buf[size-1] == '\n') buf[--size] = 0;
   num = buf;
    if( (BaseEntrada = pegabase(&num)) == -1) 
    {
     fprintf(stderr, "base invalida '%s'. pode estar entre -2 ,-54 e 2 ,100\n", num);
     continue;
    }
    if(mpz_set_str(op, num, BaseEntrada) == -1) {
     fprintf(stderr, "Base %lld não bate com '%s'\n", BaseEntrada, num);
     continue;
    }
    if(!mpz_out_str(stdout, BaseSaida, op)) 
     erro(op);
    putchar('\n');
  } while(fgets(buf, sizeof buf, stdin) != NULL);

  mpz_clear(op);

 } else {
  num = argv[1];
  if((BaseEntrada = pegabase(&num)) == -1) 
  {
   fprintf(stderr, "base invalida '%s'. pode estar entre -2 ,-54 e 2 ,100\n", num);
   return EXIT_FAILURE;
  }
  if(mpz_init_set_str(op, num, BaseEntrada) == -1) 
   erro(op);
 
  if(!mpz_out_str(stdout, BaseSaida, op)) 
   erro(op);
  putchar('\n');
  mpz_clear(op);
 }
 return 0;
}

static int pegabase(char **p) 
{
 char *a, *b;
 long long res;
	
 if((a = strchr(*p, 'r')) != NULL) 
 {
  *a = 0;
  res = strtol(*p, &b, 10);
  if(*b != 0 || !((res > -55 && -1 > res) || (1 < res && 101 > res))) res = -1;
  else *p = a + 1;
 }
 else if(!strncmp(*p, "0x", 2)) res = 16, *p += 2;
 else if(**p == '0' && isdigit((unsigned char)p[0][1])) res = 8, ++*p;
 else res = 10;
 return  res;
}

int erro(mpz_t op) 
{
 perror(NULL);
 mpz_clear(op);
 return EXIT_FAILURE;
}
