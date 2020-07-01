/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUMTHREADS 4 

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
            //printf("O número %ld não é primo\n", Num);
            qntd_divisores = 0;      
         }
   } 
      return div;
}

void* funcao_thread(void *arg) 
{
  int* N = (int*)arg;
  printf("Estou na thread %d!\n", *N);
  printf("Saindo da thread %d!\n", *N);

  return NULL;
}

int main(int argc, char **argv) {

  pthread_t threads[NUMTHREADS];
  
  void *args;
  int narg = 5;

  args = (void*) &narg;

  for (int i = 0; i < NUMTHREADS; i++)
  {
    pthread_create(&(threads[i]),NULL,funcao_thread,args);  
  }
  
  //Essa função encerra todas as threads em execução.
  for (int i = 0; i < NUMTHREADS; i++) pthread_join(threads[i],NULL);     

  
  

  scanf("%d\n",&narg);

  printf("Terminando programa!\n");
  return 0;
}
