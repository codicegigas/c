#include <stdio.h>

int radius, area;

int main(){
    printf("Enter Radious (i.e. 10): ");
    scanf( "%d", &radius);
    area = 3.14159 * radius * radius;
    printf( "\n\nArea = %d", area);
    return 0;
}