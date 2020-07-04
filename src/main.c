/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS 4 
#define MAX 64

pthread_mutex_t chave; 

int qntd_primos=0,numeros=0; // Variaveis auxiliares
unsigned int numb[MAX]; //Vetor que armazena os números que serão analisados

unsigned long int ver_primo(unsigned long int Num) //Essa função retorna o número 1 se o número é primo, e 0 caso contrário
{
   int qntd_divisores = 0, div = 0;
   if (Num==0) qntd_divisores = 0;
   else if (Num==1) qntd_divisores = 0;
   else 
   {
      for (unsigned int j = 2; j <= Num/2; j++) //Laço que verifica se cada número é primo.
      {
         if (Num%j==0)
         {
            qntd_divisores++;
            break;
         }  
      }
      if (qntd_divisores==0)
         {
            div++;
         } else
         {
            qntd_divisores = 0;      
         }
   } 
      return div;
}

void* worker(void *arg) //Função thread onde é realizada as verificações dos primos
{
  int* N = (int*)arg;
  int cond_inicial = (*N);

   int m = cond_inicial;
   while (m < numeros)
   {
      pthread_mutex_lock(&chave);
      qntd_primos +=ver_primo(numb[m]);
      pthread_mutex_unlock(&chave);
      m+=NUMTHREADS;
   }

  return NULL;
}

int main() {

  pthread_t threads[NUMTHREADS]; //Vetor com threads
  char c;
  int cont=0,args_threads[NUMTHREADS]; //Variaveis auxiliares
   
  //Laços que inicializam os vetores para não lerem lixo
  for(cont = 0; cont<MAX;cont++) numb[cont] = '\0';
  for(cont = 0; cont<NUMTHREADS;cont++) threads[cont] = '\0';

  //Laço de leitura e armazenamento da entrada
  while ((c!='\n') && (c!=EOF)) 
  {
    c = scanf("%u",&numb[numeros]);
    numeros++;
  } 
  for (int i = 0; i < NUMTHREADS; i++) 
  {
     args_threads[i] = i;
     pthread_create(&(threads[i]),NULL,worker,&(args_threads[i]));  
  }

  //Essa função encerra todas as threads em execução.
  for (int i = 0; i < NUMTHREADS; i++) pthread_join(threads[i],NULL);     

  printf("%d\n",qntd_primos);
  return 0;
}
