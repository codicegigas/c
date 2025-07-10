#include <stdio.h>
#include <stdlib.h>
// Este programa muestra el tamaño en bytes de diferentes tipos de datos en C
int main() {
        printf("Tipo char: %ld bytes\n", sizeof(char));
        printf("Tipo short: %ld bytes\n", sizeof(short));
        printf("Tipo int: %ld bytes\n", sizeof(int));
        printf("Tipo long: %ld bytes\n", sizeof(long));
        printf("Tipo float: %ld bytes\n", sizeof(float));
        printf("Tipo double: %ld bytes\n", sizeof(double)); 
        getchar(); 
        return 0;
}