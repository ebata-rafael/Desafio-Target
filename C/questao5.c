#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    char caractere;
    struct stack *prox;
}stack;

void descarregarStringBuffer(stack **buffer){

    stack *lixo = NULL;

    while(*buffer){

        printf("%c", (*buffer)->caractere);

        lixo = *buffer;
        *buffer = (*buffer)->prox;
        free(lixo);
    }

    *buffer = NULL;
}

void inverterCaractereString (char *string){

    stack *buffer = NULL, *novo = NULL;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {

            novo = (stack *) malloc(sizeof(stack));
            novo->caractere = string[i];
            novo->prox = buffer;

            buffer = novo;
        }
        else{
            descarregarStringBuffer(&buffer);    
            printf(" ");
        }
    }
    descarregarStringBuffer(&buffer);
}

int main(){

    char *string = "hello";

    inverterCaractereString(string);

    return 0;
}