/*
  Rodin Fedor m3o-121b-20
*/

#include <stdio.h>

int calcVariant(int _myNum, int _overallNum)
{
    return (_myNum % _overallNum + 1);
}

int main() 
{
    const int myNum = 17, overallNum = 10;

    printf("%i\n", calcVariant(myNum, overallNum));
    
    return 0;
}