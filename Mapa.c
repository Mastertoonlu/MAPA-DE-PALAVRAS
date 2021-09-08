#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Mapa.h"


void inicia_mapa (Mapa *mp)
{


    //Realiza alocação de memória para itens do mapa
    mp->lista = (Item **) malloc(BLOCO * sizeof(Item*));
    //verifica se alocou memória com sucesso
    if(mp->lista != NULL)
    {
        mp->blocos = 1;
        mp->total = 0;
    }
    //Exibe mensagem caso não seja possivel alocar
    else
    {
        printf("Não foi possivel alocar sua memoria");
        system("pause");
    }

}


//Insere termo no mapa
void insere_termo (Mapa *mp, char *s)
{

    int logico =1;



    if(mp->total != 0)
    {

        //Incrementa termo s
        logico= incrementa(mp,s);

    }

    //Caso não tenha incrementado termo realiza processo de alocação de memória
    if( logico != 0 )
    {


        //verifica se o bloco já está no limite
        if((mp->total % BLOCO) == 9)
        {
            //caso esteja no limite aloca mais memória para os ponteiros de ponteiros de items
            mp->lista = (Item **) realloc(mp->lista,(mp->blocos+1)*(BLOCO) * sizeof(Item));
            mp->blocos ++;
        }

        //Aloca ponteiro de item
        mp->lista[mp->total] = (Item *) malloc(sizeof(Item));

        //Aloca espaço suficiente para o termo
        mp->lista[mp->total]->termo = (char *) malloc((strlen(s)+1)* sizeof(char));


        //Altera o termo do item alocado
        strcpy(mp->lista[mp->total]->termo,s);
        mp->lista[mp->total]->conta = 1;

        mp->total ++;
    }


}


//Incrementa termo s
int incrementa (Mapa *mp, char *s)
{
    for(int i=0; i<(mp->total); i++)
    {
        //verifica se termo já existe na lista
        if(strcmp(mp->lista[i]->termo, s)==0)
        {
            //incrementa
            mp->lista[i]->conta ++;
            return 0;
        }
    }

    return 1;
}


//altera o contador do termo
int escreve_cont (Mapa *mp, char *s, int c)
{

    for(int i=0; i<(mp->total); i++)
    {
        //Busca pelo termo
        if(strcmp(mp->lista[i]->termo, s) == 0)
        {
            //altera contador por c
            mp->lista[i]->conta = c;
            return 0;
        }
    }

    return 1;
}

// retorna contador do termo s
int le_contador (Mapa *mp, char *s)
{
    int x=0;

    for(int i=0; i<(mp->total); i++)
    {
        //Busca pelo termo
        if(strcmp(mp->lista[i]->termo, s) == 0)
        {
            //retorna contador
            x = mp->lista[i]->conta;
            return x;
        }
    }
    return x;
}


//remove termo s do mapa
void remove_termo (Mapa *mp, char *s)
{

    for(int i=0; i<(mp->total); i++)
    {
        //Busca pelo termo
        if(strcmp(mp->lista[i]->termo, s) == 0)
        {

            //libera item do indice i encontrado
            free(mp->lista[i]);
            //ajusta espaço desocupado
            mp->lista[i] = mp->lista[mp->total-1];

            mp->total--;

            //Verifica se precisa realocar memória para desocupar espaço desnecessário
            if(mp->total<(mp->blocos-1)*BLOCO)
            {
                //Realoca memória desnecessária
                mp->lista = (Item **) realloc (mp->lista, (mp->blocos-1)*BLOCO*sizeof(Item *));
                mp->blocos--;
            }

        }
    }


}


//Libera mapa
void libera_mapa (Mapa *mp)
{
    free(mp->lista);
}




int tamanho_mapa (Mapa * mp)
{
    //Retorna quantidade de termos no mapa
    return mp->total;
}

void preview_mapa(Mapa *mapa)
{
    int tamanhoPalavra;
    printf("\nPalavra\t\t\t\tQtd\n\n");

    for(int i=0 ; i< (mapa->total) ; i++)
    {
        tamanhoPalavra = strlen(mapa->lista[i]->termo);
        printf("%s",mapa->lista[i]->termo);

        for(int j=0; j<33-tamanhoPalavra; j++)
        {
            printf(" ");
        }

        printf("%i\n\n",mapa->lista[i]->conta);
    }

}


//Lê termo no indice i e retorna em t o termo e em c o contador
void le_termo (Mapa * mp, int i, char *t, int *c)
{

    i--;
    strcpy(t, mp->lista[i]->termo);
    *c = mp->lista[i]->conta;
}

int menu(void)
{

    int selecao;

    printf("\n\nMenu:\n");
    printf("1 - Ler arquivo txt\n");
    printf("2 - Exibir ranking completo\n");
    printf("3 - Exibir intervalo de Ranking\n");
    printf("4 - Buscar palavra\n");
    printf("5 - Opções\n");
    printf("6 - Sair\n");
    scanf("%d",&selecao);

    return selecao;
}



void preview_mapa_ltd(Mapa *mapa,int max,int min)
{
    int tamanhoPalavra;
    printf("\nPalavra\t\t\t\tQtd\n\n");

    for(int i=0 ; i< (mapa->total) ; i++)
    {
        if( (mapa->lista[i]->conta >=min) && (mapa->lista[i]->conta <=max))
        {
            tamanhoPalavra = strlen(mapa->lista[i]->termo);
            printf("%s",mapa->lista[i]->termo);
            for(int j=0; j<33-tamanhoPalavra; j++)
            {
                printf(" ");
            }
            printf("%i\n\n",mapa->lista[i]->conta);
        }


    }

}


void bubble_sort(Mapa *mapa)
{

    int aux;
    char *auxf;


    for (int k = 1; k < mapa->total; k++)
    {


        for (int j = 0; j < (mapa->total - 1); j++)
        {


            if (mapa->lista[j]->conta < mapa->lista[j + 1]->conta)
            {
                //rankeia os pesos
                auxf          = mapa->lista[j]->termo;
                mapa->lista[j]->termo     = mapa->lista[j + 1]->termo;
                mapa->lista[j + 1]->termo = auxf;

                //altera organiza os lotes
                aux          = mapa->lista[j]->conta;
                mapa->lista[j]->conta     = mapa->lista[j + 1]->conta;
                mapa->lista[j + 1]->conta = aux;
            }
        }
    }


}


int total_palavras(Mapa *mp)
{
    int x=0;

    for(int i=0 ; i< (mp->total) ; i++)
    {
        x += mp->lista[i]->conta;
    }

    return x;
}


int min_letras(Mapa *mapa,int min)
{
    int x = 0, tamanho;

    for(int i=0 ; i< (mapa->total) ; i++)
    {

        tamanho = strlen(mapa->lista[i]->termo);

        if(tamanho>=min)
        {
            x += mapa->lista[i]->conta;
        }

    }
    return x;
}
