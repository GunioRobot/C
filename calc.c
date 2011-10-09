/*

GarageCode Genial Creations Hehehe
http://GarageCode.tk

*Function this programm
this program is a simple calculator,work with operator and number
i make this program for my friend d3lf0 study "ansi C"

*tested with GCC but wheel in others compilers...
 i wheel on Unix/Linux/*BSD this: 
    gcc -o program program.c; ./program     

Author: Antonio "Cooler_x86" 
contact: tony.unix@yahoo.com.br
license: BSD

visit this site: http://BotecoUnix.com.br
Real Geeks BotecoUnix

greetz 
Thanks _mlk_ , m0nad,IAK,Fox,D3lf0,nibbles and Chris Torek. 
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
// biblioteca de padrão de entrada e saida, standart input and output
#include <stdio.h>

//declaração das variaveis
char  line[100],operator; 
int   result,value;

// Banner 
char opcao_menu() {
 int i;
 char *banner[] = {
  "Operator Calc",
  "coded by Cooler_  visit http://botecounix.com.br",
  "put with example",
  "operators:+,-,*,/ ",
  "(s)para Sair",
  "-> ",
 };
// \x0a é a mesma coisa que \n para pular linha só que mais rapido como é hex
 for(i=0; i<=5; i++) printf(" %s \x0a",banner[i]);
}
   
int main() {
// chama o banner  e seta resultado para zero
    opcao_menu(); result = 0; 
    while (1) {
     printf("Resultado: %d\x0a", result );
     printf("Digite Operador e o numero : ");
// pega as duas entradas
     fgets(line, sizeof(line), stdin);
     sscanf(line, "%c %d", &operator, &value);
// se a entrada for s ou S programa sai
     if ((operator == 's') || (operator == 'S')) break;
//condições para verificar operador e fazer a conta com ultimo numero armazenado
// fazer result += value é a mesma coisa que fazer "result=result+value" soh que é mais rapido
     if (operator == '+') result += value;
     if (operator == '/') result /= value;
     if (operator == '-') result -= value;
     if (operator == '*') result *= value;
   } 
 return(0);
}
