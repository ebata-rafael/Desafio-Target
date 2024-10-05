#include <stdio.h>

int validaNumeroFibonacci(int numero){

    int segundoAntecessor = 0, antecessor = 1, auxiliar = 0;

    //verifica se o numero é negativo
    if (numero < 0)
        return 0;

    //verifica se não é um dos primeiros termos da sequencia
    if (numero == segundoAntecessor || numero == antecessor)
        return 1;

    do
    {   
        auxiliar = antecessor;
        antecessor = antecessor + segundoAntecessor;
        segundoAntecessor = auxiliar;

    } while (numero != antecessor && numero > antecessor); //verifica se o numero esta dentro da sequencia

    //verifica novamente caso tenha saido pela segunda condição do laço
    if(antecessor == numero)
        return 1;
    
    return 0;
}

int main(){

    int numero;

    printf("Informe um numero (positivo) para ver se pertence a sequencia de fibonacci: ");
    scanf("%d", &numero);

    if(validaNumeroFibonacci(numero))
        printf("\nPertence a sequencia\n");

    else
        printf("\nNao pertence a sequencia\n");
    

    return 0;
}