/*
 ...::::Tetris:::... 
contact: c00f3r@gmail.com
author: Cooler_
-Qua Mar 23 15:58:48 2011
"so i see dead peoples!" 

 Logic based in IOCCC http://www.ioccc.org/1989/tromp.hint
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#define B_COLUNAS 12
#define B_LINHAS 23
#define B_SIZE (B_LINHAS * B_COLUNAS)
#define TopoEsquerda -B_COLUNAS-1       /* topo esquerda */
#define TopoCentro -B_COLUNAS         /* topo centro */
#define TopoDireita -B_COLUNAS+1       /* topo direita */
#define MeioEsquerda -1              /* meio esquerda */
#define MeioDireita  1               /* meio direita */
#define ChaoEsquerda  B_COLUNAS-1        /* chao esquerda */
#define ChaoCentro  B_COLUNAS          /* chao centro */
#define ChaoDireita  B_COLUNAS+1        /* chao direita */

long h[4];
int nivel=0,pontos=0;
int mesa[B_SIZE], sombra[B_SIZE];
int blocos[] = {
    7,  TopoEsquerda,  TopoCentro,  MeioDireita, 
    8,  TopoDireita,  TopoCentro,  MeioEsquerda, 
    9,  MeioEsquerda,  MeioDireita,  ChaoCentro, 
    3,  TopoEsquerda,  TopoCentro,  MeioEsquerda,
   12,  MeioEsquerda,  ChaoEsquerda,  MeioDireita,
   15,  MeioEsquerda,  ChaoDireita,  MeioDireita,
   18,  MeioEsquerda,  MeioDireita,   2,           /* tirando */
    0,  TopoCentro,  MeioEsquerda,  ChaoEsquerda,
    1,  TopoCentro,  MeioDireita,  ChaoDireita,
   10,  TopoCentro,  MeioDireita,  ChaoCentro,
   11,  TopoCentro,  MeioEsquerda,  MeioDireita,
    2,  TopoCentro,  MeioEsquerda,  ChaoCentro,
   13,  TopoCentro,  ChaoCentro,  ChaoDireita,
   14,  TopoDireita,  MeioEsquerda,  MeioDireita, 
    4,  TopoEsquerda,  TopoCentro,  ChaoCentro,
   16,  TopoDireita,  TopoCentro,  ChaoCentro,
   17,  TopoEsquerda,  MeioDireita,  MeioEsquerda, 
    5,  TopoCentro,  ChaoCentro,  ChaoEsquerda,
    6,  TopoCentro,  ChaoCentro,  2 * B_COLUNAS,   
};

void 
alarm_handler (int signal __attribute__ ((unused)))
{
 h[3]-=h[3]/3000;
 setitimer(0,(struct itimerval *)h,0);
} 

// atualizar mesa
int 
update (void)
{
 int A;
 int I=0,i=11;
 static int B=0;

 do{ 
  if((A=mesa[i])-sombra[i])
  {
   sombra[i]=A;
   if((i-++I)||(i%12<1) )
    printf("\033[%d;%dH",(I=i)/12,i%12*2+28);
   printf("\033[%dm  "+(B-A?0:5),A);
   B=A;
  }
  i++;
 }while(i<264);

 printf("\n\t\t\t\tCooler_'s Tetris");
 printf ("\n\t\t\t\tNivel: %d, Pontos: %d\n", nivel, pontos);
 printf ("\n\n\t\t\t\tZ - para direita , C - esquerda, X - muda Bloco ,S - sair\n");
//POG para o cursor do term ficar no fim
 sombra[263]=A=getchar();
 return A;
}

int 
fits_in(int *bloco, int pos)
{
 if(mesa[pos]||mesa[pos+bloco[1]]||mesa[pos+bloco[2]]||mesa[pos+bloco[3]])
  return 0;
 return 1;
}

void 
lugar(int *bloco, int pos, int b)
{
 mesa[pos]=b;
 mesa[pos+bloco[1]]=b;
 mesa[pos+bloco[2]]=b;
 mesa[pos+bloco[3]]=b;
}

int 
main(int argc __attribute__ ((unused)), char *argv[] __attribute__ ((unused)))
{
 int *backup,*bloco,*ptr;
 int pos=17,c=0,i=0,X=0;

 sigset_t set;
 struct sigaction action;
 
 char *chaves = "zxc ps";

 h[3]=1000000/(nivel=1);
 ptr=mesa;

 for(i=B_SIZE; i; i--)
  *ptr++=i<25||i%12<2?7:0;
   
 srand(getpid());
 system("stty cbreak -echo stop u");
  
 sigemptyset(&set);
 sigaddset(&set,SIGALRM);
 sigemptyset(&action.sa_mask);
 sigaddset(&action.sa_mask,SIGALRM);
 action.sa_flags=0;
 action.sa_handler=alarm_handler;
 sigaction(SIGALRM,&action,NULL);

//tempo
 alarm_handler(0);
 puts("\033[H\033[J");
 bloco=&blocos[rand()%7*4];

   while(1)
   {
    if(c<0)
    {
     if(fits_in(bloco,pos+12))
      pos+=12;    
     else
     {
      lugar(bloco,pos,7);
      ++pontos;
      for(X=0; X<252; X=12*(X/12+1))
       while(mesa[++X])
// se fazer 10 blocos apaga
        if(X%12==10)
        {
         while(X%12) 
          mesa[X--]=0; 
         c=update();
         while(--X) 
          mesa[X+12]=mesa[X];
         c=update();
        }
                
      bloco=&blocos[rand()%7*4];
      if(!fits_in(bloco,pos=17))
       c=chaves[5];
     }
    }
   
    if(c==chaves[0])         // z - "esquerda" 
     if(!fits_in(bloco, --pos))
      ++pos;
      
    if(c==chaves[1])         // X - "troca" 
    {
     backup=bloco;
     bloco=&blocos[4 * *bloco]; // roda posição 
     if(!fits_in(bloco, pos))
      bloco=backup;
    }

      if(c==chaves[2])         // c - "direita" 
       if(!fits_in(bloco, ++pos))
        --pos;
      
      if(c==chaves[3])         // <espaço> cair bloco atual
       while(fits_in(bloco,pos+12))  
        ++pontos,pos+=12;
         
      if(c==chaves[4]||c==chaves[5])
      {
         sigprocmask(SIG_BLOCK, &set, NULL);
         printf("\n\n\n\t\t\t...:::GAME-OVER:::...\n\n");
         puts("www.bugsec.com.br , irc.botecounix.com.br chanell #c00kies");
         printf("\nm0nad,_mlk_,I4K,D3lfo and BotecoUnix fellows\n\n");
         if(c==chaves[5])
          break;
         X=264;
         while(X--)
          sombra[X]=0;
         while(getchar()-chaves[4]);
         sigprocmask(SIG_BLOCK, &set, NULL);
      }

      lugar(bloco, pos, 7);
      c=update();
      lugar(bloco, pos, 0);
   }
 system("stty sane");

 return 0;
}

