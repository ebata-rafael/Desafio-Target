#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

typedef struct dadosFaturamento
{
    int estado;
    double faturamento;
    double porcentagem;

}dadosFaturamento;

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

    dadosFaturamento estados[numDados];
    double soma = 0;
    
    for (int i = 0; i < numDados; i++)
    {                                                     // Itera sobre cada objeto no array
        cJSON *root = cJSON_GetArrayItem(dados, i); // Obtém o objeto objeto atual

        cJSON *estado = cJSON_GetObjectItem(root, "estado");
        cJSON *valor = cJSON_GetObjectItem(root, "valor");

        estados[i].estado = estado->valueint;
        estados[i].faturamento = valor->valuedouble;
        estados[i].porcentagem = 0;

        soma += valor->valuedouble;
        
    }

    for (int i = 0; i < numDados; i++)
    {
        estados[i].porcentagem = ((estados[i].faturamento / soma) * 100);
        printf("estado: %d - %% %.4f\n", estados[i].estado, estados[i].porcentagem);
    }

    cJSON_Delete(dados); // Libera a memória alocada para root

    return 0;
}