#define BLOCO 10

typedef struct _item
{
    int conta; //contador
    char *termo; //palavra
} Item;



typedef struct _mapa
{
    int total; // número de itens no mapa
    int blocos; // número de blocos de itens alocados
    Item **lista; // vetor de ponteiros para itens
} Mapa;



//inicia um mapa vazio
void inicia_mapa (Mapa *mp);



// insere um item com termo s e conta=1
void insere_termo (Mapa *mp, char *s);



// incrementa contador do termo s, retorna 1 se não encontrou o termo
int incrementa (Mapa *mp, char *s);




// escreve  ́c` no contador do termo s, retorna 1 se não encontrou o termo
int escreve_cont (Mapa *mp, char *s, int c);



// retorna contador do termo s
int le_contador (Mapa *mp, char *s);



// remove o item com termo s
void remove_termo (Mapa *mp, char *s);



// libera o espaço ocupado pelo mapa
void libera_mapa (Mapa * mp);



// retorna número de itens no mapa
int tamanho_mapa (Mapa * mp);



//retorna em ‘t’ o termo no índice e em  ́c ́ o seu contador
void le_termo (Mapa * mp, int i, char *t, int *c);


//visualização do mapa
void preview_mapa(Mapa *mapa);

//menu
int menu(void);


//visualização do mapa com max e min
void preview_mapa_ltd(Mapa *mapa,int max, int min);

void bubble_sort(Mapa *mapa);

int total_palavras(Mapa *mp);

int min_letras(Mapa *mapa,int min);
