/*

 exemplo simplão de controle ao hardware

   abrindo cdrom,
   fazendo piscar a luz do seu teclado
   inútil , mais em termos de hardware
   é legal estudar :-) ioctl.h controlar 
   dispositivos da sua máquina...

autor:Cooler_  
contato:c00f3r[at]gmail[dot]com
bugsec.com.br

 gcc -o b b.c -02

rodar fora do xterm
*/
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <linux/cdrom.h>

int main()
{
 int led=0;

// eject no cdrom uso da cdrom.h
// configurar a string do dipositivo corretamente ;-)
 if(ioctl('/dev/cdrom',CDROMEJECT,0))
  puts("lol");

 while(1)
 {
  led=2*led+1;
  if(led&8)
   led^=9;
//uso da kd.h
//KDSETLED seta valor, KDGETLED pega valor
  if(ioctl(0,KDSETLED,led))
   return 0;
  sleep(1);
 }
 return 0;
}
