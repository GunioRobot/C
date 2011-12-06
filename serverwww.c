// example how too do http server in C , by Cooler_
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//nossa porta
#define PORT    30666
 
int main (int argc, char *argv[])
{
   int serversock;
   struct sockaddr_in self;
 
   /* cria o socket */
   serversock = socket (AF_INET, SOCK_STREAM, 0) ;
   if ( serversock < 0 )
   {
      perror("Erro no socket");
      exit(1);
   }
 
   /* monta o endereço */
   bzero (&self, sizeof(self));
   self.sin_family = AF_INET;
   self.sin_port   = htons(PORT);
   self.sin_addr.s_addr = INADDR_ANY; /* uso o endereço do host */
 
   /* associa o endereço ao socket */
   if ( bind (serversock, (struct sockaddr*)&self, sizeof(self)) )
   {
      perror("Erro no bind");
      exit(1);
   }
 
   /* coloca o socket em escuta */
   if ( listen (serversock, 20) )
   {
      perror("Erro no listen");
      exit(1);
   }
 
   while (1)
   {
      int clientsock;   
      struct sockaddr_in client_addr;
      int addrlen = sizeof (client_addr);
      char * resposta ;
 
      /* aguarda e aceita uma conexão externa */
      clientsock = accept (serversock, (struct sockaddr*)&client_addr, &addrlen);
 
      printf ("Client %s:%d connected\n",
              inet_ntoa (client_addr.sin_addr),
              ntohs (client_addr.sin_port));
 
      /* envia uma resposta HTTP padrão */
      resposta = "HTTP/1.1 200 Ok\n\n<p><b>Servidor do Cooler_!! http://BotecoUnix.com.br</b></p><img src=\"http://i21.photobucket.com/albums/b256/rot_in_pieces/splatterhouse.gif\">\n" ;
 
      write (clientsock, resposta, strlen (resposta));
 
      /* fecha o socket da conexão recebida */
      close (clientsock);
   }
 
   /* encerra o socket servidor */
   close (serversock);
 
   return 0;
}
