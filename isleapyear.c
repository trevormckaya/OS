#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    int year = atoi(argv[1]);
    scanf("%d", &year);


    if (year % 4 == 0){
        printf("%d was a leap year/n",year);
      }
    printf("%d was not a leap year/n",year);
    return 0;
}
