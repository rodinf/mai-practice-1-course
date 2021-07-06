/*
  Rodin Fedor m3o-121b-20

  compile using gcc with -lm flag to link "math.h":
  $ gcc -o 3-2.o 3-2.c -lm
*/

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>

#define LIST_LENGTH 10

#define TEST_PUSH_POSITION 5
#define TEST_PUSH_VALUE 307

typedef struct Node
{
  int value;
  struct Node *nextPtr;
} 
Node;

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

Node* initListByZero(Node *elFirstPtr) 
{
  Node *elCurrPtr = elFirstPtr;

  while (elCurrPtr != NULL)
  {
    elCurrPtr->value = 0;
    elCurrPtr = elCurrPtr->nextPtr;
  }
  
}

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

double geometricMean(Node *elFirstPtr) {
  Node *elCurrPtr = elFirstPtr;
  double 
    _geometricMean = 1,
    n = 0;

  while (elCurrPtr != NULL)
  {
    _geometricMean *= (double)elCurrPtr->value;
    elCurrPtr = elCurrPtr->nextPtr;
    n++;
  }

  _geometricMean = pow(_geometricMean, 1/n);

  return _geometricMean;
}

double arithmeticMean(Node *elFirstPtr) 
{
  Node *elCurrPtr = elFirstPtr;
  double 
    _arithmeticMean = 0,
    n = 0;

  while (elCurrPtr != NULL)
  {
    _arithmeticMean += (double)elCurrPtr->value;
    elCurrPtr = elCurrPtr->nextPtr;
    n++;
  }

  _arithmeticMean /= n;

  return _arithmeticMean;
} 

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

/* Tests */

int testCreateList(Node *elFirstPtr, int _length) 
{
  Node *elCurrPtr = elFirstPtr;
  int n = 0;

  while (elCurrPtr != NULL)
  {
    elCurrPtr = elCurrPtr->nextPtr;
    n++;
  }
  
  if(n == _length)
    return 0;
  else
    return 1;

}

int testInitListByZero(Node *elFirstPtr) 
{
  Node *elCurrPtr = elFirstPtr;

  while (elCurrPtr != NULL)
  {
    if(elCurrPtr->value != 0)
      return 1;

    elCurrPtr = elCurrPtr->nextPtr;
  }
  
  return 0;
}

int testPushIntToList(Node *elFirstPtr, int pushPosition, int pushValue) 
{
  Node *elCurrPtr = elFirstPtr;

  for(int i = 0; i < pushPosition; i++) {		
    if(elCurrPtr->nextPtr != NULL)
      elCurrPtr = elCurrPtr->nextPtr;
    else
      return 1;
  }

  if(elCurrPtr->value == pushValue)
    return 0;
  else
    return 1;
}

int testArichmeticMean()
{
  Node *testList = createList(10);
  Node *elCurrPtr = testList;

  int n = 1, sum = 0;

  while (elCurrPtr != NULL)
  {
    sum += n;
    elCurrPtr->value = n;
    elCurrPtr = elCurrPtr->nextPtr;
    n++;
  }

  n--;

  if(n < 10) {
    freeList(testList);
    return 1;
  }
  else if((double)sum / (double)n == arithmeticMean(testList)) {
    freeList(testList);
    return 0;
  }
  else {
    freeList(testList);
    return 1;
  }
}

int testGeometricMean()
{
  Node *testList = createList(10);
  Node *elCurrPtr = testList;

  int n = 1, mult = 1;

  while (elCurrPtr != NULL)
  {
    mult *= n;
    elCurrPtr->value = n;
    elCurrPtr = elCurrPtr->nextPtr;
    n++;
  }

  n--;

  if(n < 10) {
    freeList(testList);
    return 1;
  }
  else if(pow(mult, (double)1/n) == geometricMean(testList)) {
    freeList(testList);
    return 0;
  }
  else {
    freeList(testList);
    return 1;
  }
}

int main() 
{
  Node *myList = createList(LIST_LENGTH);
  showList(myList);
  testCreateList(myList, LIST_LENGTH) ? printf("Test failed\n") : printf("Test succeeded\n");

  initListByZero(myList);
  showList(myList);
  testInitListByZero(myList) ? printf("Test failed\n") : printf("Test succeeded\n");
  
  pushIntToList(myList, TEST_PUSH_POSITION, TEST_PUSH_VALUE);
  showList(myList);
  testPushIntToList(myList, TEST_PUSH_POSITION, TEST_PUSH_VALUE) ? printf("Test failed\n") : printf("Test succeeded\n");

  printf("Arithmetic mean\n%f\n", arithmeticMean(myList));
  testArichmeticMean() ? printf("Test failed\n") : printf("Test succeeded\n");

  printf("Geometric mean\n%f\n", geometricMean(myList));
  testGeometricMean() ? printf("Test failed\n") : printf("Test succeeded\n");

  freeList(myList);

  return 0;
}