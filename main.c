#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Mapa.h"
#define TAM_ARQUIVO 100
#define TAM_STRING 100

//Exibe menu do programa
int menu(void);

//Remove 2 caracteres da string passada
void removeChar(char* s, char c1, char c2);

//permite que o usuário digite um arquivo que deseja ler
void lerArquivo(Mapa *mapa,char *ptr, char *arquivo,int *configmin);

//Exibe o ranking completo de palavras encontradas
void exibirRanking(Mapa *mapa, char *arquivo, int *tamanhoMapa);

//Exibe ranking de palavras com quantidade de acordo com parametro passado pelo usuário
void intervaloRanking(Mapa *mapa);

//Busca uma palavra especifica para o usuário
void buscaPalavra(Mapa *mapa, char *ptr);

//Exibe interface para usuário configurar qual quantidade de palavras minimas a considerar
void configura(Mapa *mapa, int *configmin);


int main(void)
{
    //Inicializa variaveis
    int configmin=0, tamanhoMapa;
    char arquivo[100];
    char palavra[100];
    int selecao=-1;
    Mapa mapa;

    setlocale(LC_ALL, "Portuguese");

    //loop enquanto usuário não selecionar opção de sair
    while(selecao != 6)
    {

        //chama função de menu
        selecao = menu();


        //Casos de uso para a seleção do usuário
        switch(selecao)
        {
        case 1:
            //Le arquivo e insere termos no mapa
            lerArquivo(&mapa, palavra, arquivo, &configmin);
            break;

        case 2:
            //Exibe o ranking completo de termos
            exibirRanking(&mapa, arquivo, &tamanhoMapa);
            break;

        case 3:
            //Solicita intervalo a usuário e exibe ranking
            intervaloRanking(&mapa);
            break;

        case 4:
            //busca palavra e exibe contador do termo
            buscaPalavra(&mapa,palavra);
            break;

        case 5:
            //chama interface de configuração do termo
            configura(&mapa,&configmin);
            break;
        }
    }

    return 0;
}



//Le arquivo e insere termos no mapa
void lerArquivo(Mapa *mapa,char *palavra, char *arquivo,int *configmin)
{
    //Inicia variavel de arquivo
    FILE *file;

    //libera memória alocada pelo mapa para reinicialo
    libera_mapa(mapa);

    //inicializa mapa alocando memória
    inicia_mapa(mapa);

    //Interface que pede ao usuário caminho do arquivo
    system("cls");
    printf("1 - Ler arquivo txt\n\n");
    printf("Digite o caminho\n> ");

    //Le input do usuário
    scanf("%s",arquivo);

    //tenta abrir arquivo para leitura
    file = fopen(arquivo,"r");
    //verifica se conseguiu abrir o arquivo
    if(file != NULL)
    {
        //caso o usuário consiga abrir o arquivo
        //loop escaneando todas as palavra do arquivo
        while(fscanf(file,"%s",palavra)!=EOF)
        {
            //verifica se palavras tem tamanho minimo exigido pela configuração
            if(strlen(palavra)>*configmin)
            {
                //remove ponto e virgula da palavra do texto
                removeChar(palavra,',','.');

                //transforma palavra em minusculo
                for(int i=0; i<strlen(palavra); i++)
                {
                    palavra[i] =tolower(palavra[i]);
                }
                //insere termo no mapa
                insere_termo(mapa, palavra);
            }
        }
        //ordena mapa e exibe
        system("cls");
        bubble_sort(mapa);
        preview_mapa(mapa);
    }
    else
    {
        printf("O arquivo não pode ser encontrado!\n\n");
        system("pause");
    }
}



//Exibe o ranking completo de termos
void exibirRanking(Mapa *mapa, char *arquivo, int *tamanhoMapa)
{
    system("cls");
    //exibe interface para o usuário com nome do arquivo
    printf("2 - Exibir ranking completo\n\n");
    printf("Arquivo: %s\n",arquivo);

    //retorna quantos termos existem no mapa
    *tamanhoMapa = total_palavras(mapa);

    //retorna quantidade de termos, ordena e exibe o mapa
    printf("Total de palavras: %i\n",*tamanhoMapa);
    bubble_sort(mapa);
    preview_mapa(mapa);
}




//Solicita intervalo a usuário e exibe ranking
void intervaloRanking(Mapa *mapa)
{
    int min,max;
    system("cls");

    //Exibe interface ao usuário
    printf("3 - Exibir intervalo de Ranking\n\n");
    //pergunta quantidade maxima de termos encontrados
    printf("Digite qtd max:\n> ");
    scanf("%i", &max);
    //pergunta quantidade maxima de termos encontrados
    printf("Digite qtd min:\n> ");
    scanf("%i", &min);

    //Ordena e exibe através dos parametros definidos pelo usuário
    bubble_sort(mapa);
    preview_mapa_ltd(mapa, max, min);
}




//busca palavra e exibe contador do termo
void buscaPalavra(Mapa *mapa, char *palavra)
{
    int contador;
    system("cls");
    //Exibe interface ao usuário
    printf("4 - Buscar palavra\n\n");
    //Pergunta palavra que o usuário deseja buscar
    printf("Digite a palavra\n> ");
    scanf("%s", palavra);
    //Retorna contador do termo
    contador =  le_contador(mapa,palavra);
    //Exibe ao usuário o contador
    printf("Quantidade: %i",contador);
}



//chama interface de configuração do termo
void configura(Mapa *mapa, int *configmin)
{
    int contador;
    system("cls");
    //Exibe interface ao usuário perguntando qual configuração ele deseja
    printf("Digite mínimo de caracteres a considerar:\n> ");
    scanf("%i", configmin);

    //Retorna contador com quantidade de termos para parametro definido pelo usuário
    contador = min_letras(mapa, *configmin);

    //Exibe contador
    printf("Total de palavras: %i", contador);
}

//Remove caracteres passados como parametro
void removeChar(char* s, char c1, char c2)
{

    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
    {
        if (s[i] != c1 && s[i]!=c2)
        {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}
