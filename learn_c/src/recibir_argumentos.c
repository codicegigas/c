#include <stdio.h>

int main(int argc, char *argv[]) {
    //comprobacion argc actua como una variable que contiene el número de argumentos pasados al programa
    // argv es un array de cadenas que contiene los argumentos pasados al programa
    // argc cuenta el número de argumentos, incluyendo el nombre del programa
    if (argc < 2) {
        printf("Por favor, proporciona al menos un argumento.\n");
        return 1; // Error si no se proporcionan argumentos
    }
    // Imprimir el número de argumentos y los argumentos mismos

    printf("Número de argumentos: %d\n", argc - 1);
    printf("Argumentos:\n");
    
    int n;
    for (n = 1; n < argc; n++) {
        printf("Argumento %d: %s\n", n, argv[n]);
    }

    return 0; // Éxito
}