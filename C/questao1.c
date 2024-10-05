#include <stdio.h>

int main(){
    int INDICE = 13, SOMA = 0, k;

    for(k = 0; k < INDICE; k = k + 1){
        SOMA += k;
    }

    printf("\nsoma: %d", SOMA);

    return 0;
}

