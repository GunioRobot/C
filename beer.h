/*
last check up 
03/08/2011
------------

       _____________
      (             )
      (____________ )
       |           |
       |           |
       |           |  
       |           |
      /             \
     /               \ 
    /                 \  
   /                   \
  /                     \
  (______________________) 
  |                      |
  |   ...:::Beer:::...   |
  |...::::Version:0.02::.|
  |                      |
  |______________________|
  |                      |
  |                      |
  |                      |
  |                      |
  |                      |
  (______________________)
0101010101010110101010101010101101010101010   

is held by Apache license 2.0
-----------------------
Beer simple C header

Authors: Cooler_,m0nad,ryonagana,b4r0n
E-mail: c00f3r[at]gmail[dot]com
date: 03/08/2011

thanks: 
  _mlk_,
  I4K("for cool macros and other things"),
  delfo,c0lt7r,B4r0n,joey,fokerbug,
  zepplin,voidpointer,muzgo,memset,b4r0n,novato_br...

*/

#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//macro to read stdin string
#define ReadString(a) fgets(a,sizeof(a),stdin),a[strlen(a)-1] = '\0'; 

//return elements of array
#define array_elements(array) (sizeof(array) / sizeof *(array))

//hide and unhide strings
#define UNHIDE_STR(str) do { char *p = str;  while (*p) *p++ += 0x19; } while (0)
#define HIDE_STR(str)   do { char *p = str;  while (*p) *p++ -= 0x19; } while (0)

// bitwise macros
#define XorSwap(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )
#define TST_FLAG(N, F)        ( (N) & (F) )
#define BIT_RANGE(N, M)       ( BIT_POS((M)+1 - (N))-1 << (N) )
#define BIT_SHIFTL(B, N)      ( (unsigned)(B) << (N) )
#define BIT_SHIFTR(B, N)      ( (unsigned)(B) >> (N) )
#define SET_MFLAG(N, F, V)    ( CLR_FLAG(N, F), SET_FLAG(N, V) )
#define CLR_MFLAG(N, F)       ( (N) &= ~(F) )
#define GET_MFLAG(N, F)       ( (N) & (F) )

#define BUGVIEW 1

#define DEBUG(x, s...) do { \
 if (!BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "%.*s %s[%d] %s(): ", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
} while (0);

// convert decimal to binary
char * dec2bin(int n, char * string)
{ 
 int i; 
 static int size = 8 * sizeof(int);
 
  for(i = size - 1; i >= 0; i--, n >>= 1) 
   string[i] = (01 & n) + '0';
 
 string[size] = '\0'; 
 return string; 
} 

// Hexadecimal to Character

// with bitwise
Hex2Char(char *Hex)
{
 char rch=0;
 int i=0; 

 while(i<2)
 {
  if ( *(Hex + i) >= '0' && *(Hex + i) <= '9' )
   rch = (rch << 4) + (*(Hex + i) - '0');
  else if ( *(Hex + i) >= 'A' && *(Hex + i) <= 'F' )
   rch = (rch << 4) + (*(Hex + i) - 'A' + 10);
  else
   break;
  i++;
 }
 return rch;
}

//simple version
static char char2Hex(unsigned char c)
{
 static const char *HexCharacters = "0123456789ABCDEF";
   if(c > 15)
   {
     DEBUG("error in char2Hex() %c",HexCharacters[c]);
     return -1;
   }
 return HexCharacters[c];
}

// unsigned char x[]={"google.com"}; string2hex(y,x,16)...
static void string2hex(char *Output, unsigned char *Input, int Length)
{
 char *Out;
 char First;
 char Second;

 Out = Output;
 while (Length > 0)
 {
  First = *Input / 0x10;
  Second = *Input % 0x10;
  *Out = char2Hex(First);
   Out++;
  *Out = char2Hex(Second);
   Out++;
   Length--;
   Input++;
 }
 *Out = '\0';
 return;
}

unsigned long hex2int(char *a, unsigned int len)
{
 int i=0;
 unsigned long val = 0;

 while(i<len)
 {
  if(a[i] <= 57)
   val += (a[i]-48)*(1<<(4*(len-1-i)));
  else
   val += (a[i]-55)*(1<<(4*(len-1-i)));
  i++;
 }
 return val;
}


//  Math functions
/*
MDC Máximo Divisor Comum,dois números inteiros é o maior número inteiro que divide 
ambos sem deixar resto.
*/
int mdc(int a,int b) 
{
  if(!b) 
   return a;
  else 
   return mdc(b,a%b);
}

/*
MMC = mínimo múltiplo comum entre dois números é representado 
pelo menor valor comum pertencente aos múltiplos dos números. 
*/
int mmc(int a,int b) 
{
 int formula;
   if(!b) 
    return a;
   else 
    formula = (a*b)/(mdc(a,b));
 return (formula);
} 

// quadratic equation
char * baskara(float a, float b, float c, float *raizes) 
{
 float delta=((b*b)-4*(a*c));
 float x1=0,x2=0;
 char *reply;

 if((!a)||(delta<0))
 {
  DEBUG("error in equation baskara(), delta: %f ",delta);
  return 0; 
 }
 if(delta>0) 
  x1=((-b + ((float)bit_sqrt(delta)) )/(2*a));
 x2=((-b - ((float)bit_sqrt(delta)) )/(2*a));
 snprintf(reply,sizeof(reply)," X1 : %5.2f \n X2 : %5.2f\n",x1,x2);
 return reply;
}

// simple factorial
int factorial( int n )
{
 if(n<=1)
  return 1;
 else
  return n*factorial(n-1);
}

// test if var is prime
int isprime(int n)
{
 int d=2;

 if(n<=0)
 {
  DEBUG("error isprime(), n = %d ",n);
  return -1;
 }

 while(d<n) 
 {
  if(!(n%d))
   return 0;
  d+=2;
 }
 return 1;
}  

//square root by Cooler_
int bit_sqrt(int num)
{
//so 32 is sizeof(int)<<3
 int num0=num,result=0,tbit=1<<((sizeof(int)<<3)-2);

 if(num<=0)
 {
  DEBUG("error bit_sqrt(), num = %d ",num);
  return -1;
 }
        
 while(tbit>num0)
  tbit>>=2;     
 while(tbit^0)
 {
  if(num0>=result+tbit)
  {
   num0-=result+tbit;
   result=(result>>1)+tbit;
  }else
   result>>=1;
  tbit>>=2;
 }
 return result;
}

// test if is palindrome
int palindrome(const char *s)
{
  int x,y;
  
  y = strlen(s);
  for(x=0; x<y/2; x++)
  {
   if( s[x] != s[y-x-1] ) 
    return 0; 
  }
  return 1;
}

// return time
// example OutPut Wed Aug  3 18:26:24 2011
char *TimeNow()
{
 struct tm *local;
 time_t t;
 t = time(NULL);
 local = localtime(&t);
 local = gmtime(&t);
 return asctime(local);
}

// File jobs  ##############################################################
int CopyFile(char *fromfile, char *tofile)
{
 FILE *ifp, *ofp;
 int c;

 if((ifp = fopen(fromfile, "r")) == NULL) 
  return -1;
 if((ofp = fopen(tofile, "w")) == NULL) 
 { 
  fclose(ifp); 
  DEBUG("Error CopyFile()");
  return -1; 
 }

 while((c = getc(ifp)) != EOF)
  putc(c, ofp);

 fclose(ifp);
 fclose(ofp);
 return 0;
}

int WriteFile(char *file,char *str)
{
 FILE *arq;
 
 arq=fopen(file,"a"); 
  if(!arq) 
  {
   DEBUG("error in WriteFile() %s",file); 
   return 0;
  }
 fprintf(arq,"%s\n",str); 
 fclose(arq); 
 return 1;
}

// return lines from file, example:  const char *buff=readLine("log.txt"),printf("%s",buff);
const char *readLine(char * NameFile)
{
 FILE * file;
 file = fopen(NameFile, "r");
 if (file == NULL)
  return;

 char *lineBuffer=calloc(1,1), line[128];

 if( !file || !lineBuffer )
 {
  DEBUG("error in readLine() at %s",NameFile);
  exit(1);
 }

 while(fgets(line,sizeof line,file))  
 {
  lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line)+1);
  if(!lineBuffer)
  {
   DEBUG("error in readLine() at %s",NameFile);
   exit(2);
  }
  strcat(lineBuffer,line);
 }

 return lineBuffer;
}

/* #################################################################################
 to use with Sort functions
 example:
  char *list[] = { "madruga", "chaves", "kiko", "chiquinha", "inhonho" };
  qsort((void *)list, array_elements(list), sizeof(list[0]), sort_char);
*/

int sort_char( const void *a, const void *b) 
{
 return( strcmp(a,b) );
}

int sort_int(const void *a, const void *b) 
{
 long *a1, *b1;
 a1 = (long *)a; b1 = (long *)b;
 return (*a1 > *b1);
}


// ########################### other functions

char *RandomIp(void)
{     
 char *ipRand=NULL;
 int r1,r2,r3,r4;

 r1 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r2 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r3 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r4 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          

 ipRand=alloca(12*sizeof(char *));
 sprintf(ipRand,"%d.%d.%d.%d",r1,r2,r3,r4); 

 return ipRand; 
}


//test if e-mails is valid
int email_isvalid(const char *address) 
{
  int count = 0;
  const char *c, *domain;
  static char *rfc822_specials = "()<>@,;:\\\"[]";

  /* first we validate the name portion (name@domain) */
  for (c = address;  *c;  c++) 
  {
    if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == '\"')) 
    {
      while (*++c) 
      {
        if (*c == '\"') 
         break;
        if (*c == '\\' && (*++c == ' ')) 
         continue;
        if (*c <= ' ' || *c >= 127) 
         return 0;
      }
      if(!*c++) 
       return 0;
      if(*c == '@') 
       break;
      if(*c != '.') 
       return 0;
      continue;
    }
    if(*c == '@') 
     break;
    if(*c <= ' ' || *c >= 127) 
     return 0;
    if(strchr(rfc822_specials, *c)) 
     return 0;
  }
  if(c == address || *(c - 1) == '.') 
   return 0;
  /* next we validate the domain portion (name@domain) */
  if(!*(domain = ++c)) 
   return 0;
  do {
    if (*c == '.') 
    {
      if (c == domain || *(c - 1) == '.') return 0;
      count++;
    }
    if (*c <= ' ' || *c >= 127) return 0;
    if (strchr(rfc822_specials, *c)) return 0;
  } while (*++c);
  return (count >= 1);
}

//use input to escape SQL Injection
char *scapeSQL(const char *input, char quote, int wildcards) {
  char       *out, *ptr;
  const char *c;
   
  /* If every character in the input needs to be escaped, the resulting string
   * would at most double in size.  Also, include room for the surrounding
   * quotes.
   */
  if (quote != '\'' && quote != '\"') return 0;
  if (!(out = ptr = (char *)sbrk(strlen(input) * 2 + 2 + 1))) return 0;
  *ptr++ = quote;
  for (c = input;  *c;  c++) {
    switch (*c) {
      case '\'': case '\"':
        if (quote == *c) *ptr++ = *c;
        *ptr++ = *c;
        break;
      case '%': case '_': case '[': case ']':
        if (wildcards) *ptr++ = '\\';
        *ptr++ = *c;
        break;
      case '\\': *ptr++ = '\\'; *ptr++ = '\\'; break;
      case '\b': *ptr++ = '\\'; *ptr++ = 'b';  break;
      case '\n': *ptr++ = '\\'; *ptr++ = 'n';  break;
      case '\r': *ptr++ = '\\'; *ptr++ = 'r';  break;
      case '\t': *ptr++ = '\\'; *ptr++ = 't';  break;
      default:
        *ptr++ = *c;
        break;
    }
  }
  *ptr++ = quote;
  *ptr = 0;
  return out;
}

// func by  m0nad
void urlobfuscator (char * url, char * obf)
{
  int i;
  for (i = 0; i < (int)strlen (url); i++) 
   snprintf (obf+strlen(obf), sizeof obf, "%02X", url [i]);
//  obf [strlen (obf)] = 0;
   obf[i*2] = 0;
}


//func by ryonagana
void changeCharacter(char *dest, const char* str, const char search, const char replace)
{
  while(*dest = *str)
  {
   if(*dest == search)
    *dest =  replace;
   *dest++;
   *str++;
  }
}

// return reverse string
char *strrev(char *str)
{
 char *p1, *p2;

 if(! str || ! *str)
  return str;
 for(p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
 {
  *p1 ^= *p2;
  *p2 ^= *p1;
  *p1 ^= *p2;
 }
 return str;
}

//simple split , char **b = split("bla la ca zo ?", ' '); pust(b[1])...
char **split(char *str, char s)
{
  char **buff = NULL;
  char word[515] = {0};
  int nbrCase = 0;
  int iWord;
  int i;
  
  for(i = 0; str[i] != '\0'; i++)
   if(str[i] == s)
    nbrCase++;
  nbrCase += 1;
  
  if(!(buff = alloca(sizeof(char *) * nbrCase)))
   DEBUG("error in split()");
 
  for(i = 0, nbrCase = 0, iWord = 0; str[i] != '\0'; i++, iWord++)
  {
    word[iWord] = str[i];
    if(str[i] == s)
    {
      if(!(buff[nbrCase] = alloca(sizeof(char) * strlen(word) + 1)))
        DEBUG("error in split()");
      strcpy(buff[nbrCase], word);
      nbrCase++;
      iWord = 0;
      bzero(word, 515);
    }
  }
  return buff;
}

