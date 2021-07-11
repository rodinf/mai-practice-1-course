/*
  Rodin Fedor m3o-121b-20
*/

#include <stdlib.h> 
#include <stdio.h>

typedef struct Node
{
  int value;
  struct Node *nextPtr;
} 
Node;

// создание односвязного списка

Node* createList(int _length)
{
  Node 
    *elFirstPtr = NULL,
    *elCurrPtr = NULL;

  elFirstPtr = (Node*)malloc(sizeof(Node));
  elCurrPtr = elFirstPtr;

  elCurrPtr->nextPtr = NULL; 

  for(int i = 0; i < _length - 1; i++) {
    elCurrPtr->nextPtr = (Node*)malloc(sizeof(Node));

    elCurrPtr = elCurrPtr->nextPtr;

    elCurrPtr->nextPtr = NULL;
  }
  return elFirstPtr;
}

// заполнение односвязного списка нулями

Node* initListByZero(Node *elFirstPtr) 
{
  Node *elCurrPtr = elFirstPtr;

  while (elCurrPtr != NULL)
  {
    elCurrPtr->value = 0;
    elCurrPtr = elCurrPtr->nextPtr;
  }
  
}

// вывод односвязного списка в консоль

void showList(Node *elFirstPtr)
{
  Node *elCurrPtr = elFirstPtr;

  while (elCurrPtr != NULL)
  {
    printf("%d ", elCurrPtr->value);
    elCurrPtr = elCurrPtr->nextPtr;
  }  

  printf("\n");
}

// добавление элемента в односвязный список на заданную позицию

int pushIntToList(Node *elFirstPtr, int pushPosition, int pushValue)
{
  Node *elPushPtr = (Node*)malloc(sizeof(Node));

  if(pushPosition <= 0 || elFirstPtr->nextPtr == NULL) {

    elPushPtr->value = elFirstPtr->value;
    elPushPtr->nextPtr = elFirstPtr->nextPtr;

    elFirstPtr->value = pushValue;
    elFirstPtr->nextPtr = elPushPtr;

    if(elFirstPtr->nextPtr == NULL)
      return 1;
  }
  else {
    Node *elCurrPtr = elFirstPtr;

    for(int i = 0; i < pushPosition - 1; i++) {
      elCurrPtr = elCurrPtr->nextPtr;
    }

    if(elCurrPtr == NULL)
      return 1;

    else {
      elPushPtr->value = pushValue;
      elPushPtr->nextPtr = elCurrPtr->nextPtr;

      elCurrPtr->nextPtr = elPushPtr;
    }
  }
  return 0;  
}

// удаление односвязного списка из памяти

void freeList(Node *elFirstPtr)
{
  Node *elTempPtr = elFirstPtr->nextPtr;

  while (elFirstPtr != NULL)
  {
    elTempPtr = elFirstPtr;
    elFirstPtr = elFirstPtr->nextPtr;
    free(elTempPtr);
  }	
}

int main() 
{
  Node *myList = createList(10);

  showList(myList);

  initListByZero(myList);

  showList(myList);
  
  pushIntToList(myList, 5, 307);

  showList(myList);

  freeList(myList);
  
  return 0;
}
