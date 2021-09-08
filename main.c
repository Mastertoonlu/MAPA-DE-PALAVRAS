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

//permite que o usu�rio digite um arquivo que deseja ler
void lerArquivo(Mapa *mapa,char *ptr, char *arquivo,int *configmin);

//Exibe o ranking completo de palavras encontradas
void exibirRanking(Mapa *mapa, char *arquivo, int *tamanhoMapa);

//Exibe ranking de palavras com quantidade de acordo com parametro passado pelo usu�rio
void intervaloRanking(Mapa *mapa);

//Busca uma palavra especifica para o usu�rio
void buscaPalavra(Mapa *mapa, char *ptr);

//Exibe interface para usu�rio configurar qual quantidade de palavras minimas a considerar
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

    //loop enquanto usu�rio n�o selecionar op��o de sair
    while(selecao != 6)
    {

        //chama fun��o de menu
        selecao = menu();


        //Casos de uso para a sele��o do usu�rio
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
            //Solicita intervalo a usu�rio e exibe ranking
            intervaloRanking(&mapa);
            break;

        case 4:
            //busca palavra e exibe contador do termo
            buscaPalavra(&mapa,palavra);
            break;

        case 5:
            //chama interface de configura��o do termo
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

    //libera mem�ria alocada pelo mapa para reinicialo
    libera_mapa(mapa);

    //inicializa mapa alocando mem�ria
    inicia_mapa(mapa);

    //Interface que pede ao usu�rio caminho do arquivo
    system("cls");
    printf("1 - Ler arquivo txt\n\n");
    printf("Digite o caminho\n> ");

    //Le input do usu�rio
    scanf("%s",arquivo);

    //tenta abrir arquivo para leitura
    file = fopen(arquivo,"r");
    //verifica se conseguiu abrir o arquivo
    if(file != NULL)
    {
        //caso o usu�rio consiga abrir o arquivo
        //loop escaneando todas as palavra do arquivo
        while(fscanf(file,"%s",palavra)!=EOF)
        {
            //verifica se palavras tem tamanho minimo exigido pela configura��o
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
        printf("O arquivo n�o pode ser encontrado!\n\n");
        system("pause");
    }
}



//Exibe o ranking completo de termos
void exibirRanking(Mapa *mapa, char *arquivo, int *tamanhoMapa)
{
    system("cls");
    //exibe interface para o usu�rio com nome do arquivo
    printf("2 - Exibir ranking completo\n\n");
    printf("Arquivo: %s\n",arquivo);

    //retorna quantos termos existem no mapa
    *tamanhoMapa = total_palavras(mapa);

    //retorna quantidade de termos, ordena e exibe o mapa
    printf("Total de palavras: %i\n",*tamanhoMapa);
    bubble_sort(mapa);
    preview_mapa(mapa);
}




//Solicita intervalo a usu�rio e exibe ranking
void intervaloRanking(Mapa *mapa)
{
    int min,max;
    system("cls");

    //Exibe interface ao usu�rio
    printf("3 - Exibir intervalo de Ranking\n\n");
    //pergunta quantidade maxima de termos encontrados
    printf("Digite qtd max:\n> ");
    scanf("%i", &max);
    //pergunta quantidade maxima de termos encontrados
    printf("Digite qtd min:\n> ");
    scanf("%i", &min);

    //Ordena e exibe atrav�s dos parametros definidos pelo usu�rio
    bubble_sort(mapa);
    preview_mapa_ltd(mapa, max, min);
}




//busca palavra e exibe contador do termo
void buscaPalavra(Mapa *mapa, char *palavra)
{
    int contador;
    system("cls");
    //Exibe interface ao usu�rio
    printf("4 - Buscar palavra\n\n");
    //Pergunta palavra que o usu�rio deseja buscar
    printf("Digite a palavra\n> ");
    scanf("%s", palavra);
    //Retorna contador do termo
    contador =  le_contador(mapa,palavra);
    //Exibe ao usu�rio o contador
    printf("Quantidade: %i",contador);
}



//chama interface de configura��o do termo
void configura(Mapa *mapa, int *configmin)
{
    int contador;
    system("cls");
    //Exibe interface ao usu�rio perguntando qual configura��o ele deseja
    printf("Digite m�nimo de caracteres a considerar:\n> ");
    scanf("%i", configmin);

    //Retorna contador com quantidade de termos para parametro definido pelo usu�rio
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
