#include <stdio.h>
#include <math.h>

int main() {

    int year;
    printf("Enter an integer: ");
    scanf("%d", &year);

    if (year % 4 == 0){
      if (year % 400 == 0) {
        printf("year is prime\n");
      }
      if (year % 100 != 0){
        printf("year is prime\n");
        }
      }
    return 0;
}
