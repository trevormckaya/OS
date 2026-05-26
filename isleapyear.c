#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    int year = atoi(argv[1]);
    scanf("%d", &year);

    if (year % 4 == 0){
        if (year % 100 != 0) {
            printf("%d was a leap year",year);
            return 0;
        } else if (year % 400 == 0) {
            printf("%d was a leap year",year);
            return 0;
        }
      } 
    printf("%d was not a leap year",year);
    return 0;
}
