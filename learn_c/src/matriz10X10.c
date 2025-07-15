#include <stdio.h>

int x,y;
//Este codigo puede parecer poco estructurado
//Como solo se indica una sola instruccion no es necesario ponerla entre llaves
//El uso de x++, printf("\n") en el encabezado del for también es válido. En C, puedes incluir múltiples expresiones separadas por comas.
int main(){
    for (x=0;x<10;x++, printf("\n"))
        for(y=0 ; y <10; y++)
        printf("%c",1);
    return 0;

}