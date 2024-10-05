#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

long int dimensionarArquivo(FILE *file){

    fseek(file, 0, SEEK_END);    // Move o indicador de posição para o final do arquivo
    long int tamanhoArquivo = ftell(file); // Obtém o tamanho do arquivo
    fseek(file, 0, SEEK_SET);    // Move o indicador de posição de volta para o início do arquivo

    return tamanhoArquivo;
}

char *bufferJson(FILE *file, long int tamanhoArquivo){

    char *jsonDados = (char *)malloc(tamanhoArquivo + 1); // Aloca memória para armazenar os dados do arquivo JSON
    fread(jsonDados, 1, tamanhoArquivo, file);            // Lê os dados do arquivo e os armazena no buffer jsonDados
    jsonDados[tamanhoArquivo] = '\0'; // Adiciona um caractere nulo ao final dos dados para garantir que seja uma string válida

    return jsonDados;
}

int main(){

    FILE *file = fopen("dados.json", "r"); // Abre o arquivo JSON no modo de leitura
    if (!file)
    {
        printf("Erro ao abrir o arquivo JSON.\n"); // Se houver erro ao abrir o arquivo, exibe uma mensagem de erro
    }

    long int tamanhoArquivo = dimensionarArquivo(file); // Obtém o tamanho do arquivo

    char *jsonDados = bufferJson(file, tamanhoArquivo); // Lê os dados do arquivo e os armazena no buffer jsonDados

    fclose(file); // Fecha o arquivo após a leitura

    cJSON *dados = cJSON_Parse(jsonDados); // Faz o parse dos dados JSON e os armazena na estrutura cJSON
    
    if (!dados)
        printf("Erro ao fazer o parse do JSON.\n"); // Se houver erro ao fazer o parse do JSON, exibe uma mensagem de erro

    free(jsonDados);     // Libera a memória alocada para jsonDados

    int numDados = cJSON_GetArraySize(dados); // Obtém o número de elementos no array

    int valores[numDados], index = 0, maioresQueMedia = 0;
    double menorValor = 0, maiorValor = 0, soma = 0, media = 0;
    
    for (int i = 0; i < numDados; i++)
    {                                                     // Itera sobre cada objeto no array
        cJSON *root = cJSON_GetArrayItem(dados, i); // Obtém o objeto objeto atual

        cJSON *valor = cJSON_GetObjectItem(root, "valor");

        if (valor->valuedouble > 0)
        {
            valores[index] = valor->valuedouble;
            index++;

            if(valor->valuedouble > maiorValor)
                maiorValor = valor->valuedouble;

            soma += valor->valuedouble;
        }
        
    }
    
    if(index > 0)
        media = soma / index;

    if(index > 1){ // Verifica se ha mais do que dois dias com valor > 0
        menorValor = valores[0];
        for (int i = 1; i < index; i++)
        {
            if (valores[i] < menorValor)
                menorValor = valores[i];

            if (valores[i] > media)
            {
                maioresQueMedia++;
            }
        }
    }
    else
        menorValor = valores[index-1];

    cJSON_Delete(dados); // Libera a memória alocada para root

    printf("menor valor: %.4f\n", menorValor);
    printf("maior valor: %.4f\n", maiorValor);
    printf("media mensal: %.4f\n", media);
    printf("valores maiores que a media: %d\n", maioresQueMedia);

    return 0;
}