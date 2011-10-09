/*

GarageCode Genial Creations Hehehe
http://GarageCode.tk

*Function this programm
I use to test many URLs in TXT file to search a string on source URL
use this code to test poxys list and other things...

*require
 libcurl-dev
 visit this site to many things "http://curl.haxx.se"

*tested with GCC but wheel in others compilers...
 i wheel on Unix/Linux/*BSD this: 
    gcc -o program program.c -l curl; ./program     

Author: Antonio "Cooler_" 
contact: tony.unix@yahoo.com.br
license: BSD

visit this site: http://BotecoUnix.com.br
Real Geeks BotecoUnix

greetz 
Thanks muzgo,_mlk_ ,m0nad,IAK,Fox,D3lf0 and nibbles. 
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
#include <string.h>
#include <stdlib.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
 
#define log "url.txt"
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory) {
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
  }
  return realsize;
}


int main(){
    FILE *fp;

    char str[536],nome[50],lista[50];

  struct MemoryStruct chunk;

  CURL *curl_handle;  
  curl_global_init(CURL_GLOBAL_ALL); 

  printf("put string to find in URLs: ");
   fgets(nome, sizeof(nome), stdin);
   nome[strlen(nome)-1] = '\0';
  printf("put URLs List: ");
   fgets(lista, sizeof(lista), stdin);
   lista[strlen(lista)-1] = '\0';

  fp = fopen(lista, "r");
    if(!fp) return 1; 
  while(fgets(str,sizeof(str),fp) != NULL) {
      chunk.memory=NULL; 
      chunk.size = 0;  
      int len = strlen(str)-1;
  
      if(str[len] == '\n') str[len] = 0;
      printf("\n %s", str);

    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, str);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; pl; rv:1.9.0.17) Gecko/2009122116 Firefox/3.0.17 ");
    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
   //   printf("%s \x0a",chunk.memory);


    if (chunk.memory && strstr(chunk.memory,nome)!=NULL) {
     FILE *arq;
     printf(" <---String Found !"); 
     arq=fopen(log,"a"); 
     if(!arq) exit(1); 
     fprintf(arq,"%s\n",str); 
     fclose(arq); 
    }

    if(chunk.memory) free(chunk.memory);
    curl_global_cleanup();
  }
  printf("\n--------------\n Search the end,see the file url.txt \t\t");
  fclose(fp);
  return 0;
}
