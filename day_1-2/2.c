/*
  Rodin Fedor m3o-121b-20
*/

#include <stdlib.h> 
#include <stdio.h>
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

void initByRandMas(int* imas, int size)  {

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

int testPushToMas(int* source, int val, int size) {

  initByRandMas(mas, size);

  int masFirst = mas[0], masSecond = mas[1], masPreLast = mas[size - 2]; 

  pushToMas(mas, val, size);

  if(mas[0] ==  val && mas[1] ==  masFirst && mas[2] == masSecond && mas[size - 1] ==  masPreLast) 
    return 1;
  else
    return 0;


}

int main() {

  srand(time(NULL));

  initByRandMas(mas, MASSIZE);

  printMas(mas, MASSIZE);

  pushToMas(mas, PUSH_VALUE, MASSIZE);

  printMas(mas, MASSIZE);  

  if (testPushToMas(mas, PUSH_VALUE, MASSIZE) == 1)
    printf("Test successful\n");
  else
    printf("Test failed\n");
  

  return 0;
}
