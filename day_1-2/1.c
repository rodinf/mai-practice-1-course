/*
  Rodin Fedor m3o-121b-20
*/

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define PUSH_VALUE 307

#define MASSIZE 10 // 1000

int mas[MASSIZE];

void printMas(int* source, int size)  {

  for (int i = 0; i < size; i++)
  {
    printf("%i ", source[i]);
  }
  
  printf("\n");

}

void initByZeroMas(int* imas, int size)  {

  int sz = 0;

  if(size > MASSIZE)
    size = MASSIZE; 

  for(int i = 0; i < size; i++) 
  {
    mas[i] = rand()%100;
  }

}

void pushToMas(int* source, int val, int size) {

  for(int i = size - 1; i >= 0; i--) 
  {
    source[i] = source[i-1];
  }

  source[0] = val;

}

int main() {

  srand(time(NULL));

  initByZeroMas(mas, MASSIZE);

  printMas(mas, MASSIZE);

  pushToMas(mas, PUSH_VALUE, MASSIZE);

  printMas(mas, MASSIZE);  

  return 0;
}
