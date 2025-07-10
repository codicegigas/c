#include <stdio.h>

int main (){
    printf("Hola, el propositod de este programa es saludar, ¿Podrias Proporcionarme tu nombre?\n");
    char nombre[50];
    scanf("%49s", nombre); // Limitar la entrada a 49 caracteres para evitar desbordamiento
    printf("Hola, %s. ¡Bienvenido al mundo de la programación en C!\n", nombre);
    printf("Espero que disfrutes aprendiendo C.\n");
    printf("¡Adiós!\n");
    return 0;
}