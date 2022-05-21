#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
    int chave;
    int altura;
    struct no* esquerdo;
    struct no* direito;
} BST;

int Max(int a, int b) {
    return (a > b) ? a : b;
}

BST* novoNo(int chave) {
    BST* aux = (BST *)malloc(sizeof(BST));

    aux->chave = chave;
    aux->direito = NULL;
    aux->esquerdo = NULL;
    aux->altura = 1;

    return aux;
}

int Altura(BST* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return raiz->altura;
}

int FatorBalanceamento(BST* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return Altura(raiz->esquerdo) - Altura(raiz->direito);
}

int buscaChave(BST* raiz, int chave) {

    if(raiz == NULL){
        return 0;
    }
    if (chave > raiz->chave) {
        buscaChave(raiz->direito, chave);
    }
    else if (chave < raiz->chave) {
        buscaChave(raiz->esquerdo, chave);
    }
    else if (raiz->chave == chave) {
        return 1;
    }
}

BST* RotR(BST* raiz) {
    //Armazenando pra onde a raiz apontava
    BST* b = raiz->esquerdo;
    //Pegando a subarvore direita de B, para manter as propriedades da BST
    BST* t2 = b->direito;

    //Rotacionando
    b->direito = raiz;
    raiz->esquerdo = t2;

    //Recalculando as alturas
    b->altura = Max(Altura(b->esquerdo), Altura(b->direito));
    raiz->altura = Max(Altura(raiz->esquerdo), Altura(raiz->direito));

    // printf("Fazendo rotR no %d\n", raiz->chave);
    return b;
}

BST* RotL(BST* raiz) {
    BST* b = raiz->direito;

    BST* t1 = b->esquerdo;

    b->esquerdo = raiz;
    raiz->direito = t1;

    raiz->altura = Max(Altura(raiz->esquerdo), Altura(raiz->direito));
    b->altura = Max(Altura(b->esquerdo), Altura(b->direito));

    // printf("Fazendo rotL no %d\n", raiz->chave);
    return b;
}

BST* avlInsert(BST* raiz, int chave) {
    if (raiz == NULL) {
        return novoNo(chave);
    }

    //Verificando onde colocar o No
    if (chave < raiz->chave)
    {
        raiz->esquerdo = avlInsert(raiz->esquerdo, chave);
    }
    else if (chave > raiz->chave) {
        raiz->direito = avlInsert(raiz->direito, chave);
    }
    else {
        return raiz;
    }

    //Atualizar o fator de balanceamento em toda insercao eh importante!
    //Balancear a arvore

    raiz->altura = Max(Altura(raiz->esquerdo), Altura(raiz->direito)) + 1;

    int fb = FatorBalanceamento(raiz);

    //Se o fator de balanceamento for maior que 1, a arvore esta desequilibrada para a esquerda
    //Entao precisamos fazer uma rotacao para a direita
    if (fb > 1 && FatorBalanceamento(raiz->esquerdo) == 1) {
        return RotR(raiz);
    }

    if (fb > 1 && FatorBalanceamento(raiz->esquerdo) == -1) {
        raiz->esquerdo = RotL(raiz->esquerdo);
        return RotR(raiz);
    }

    if (fb < -1 && FatorBalanceamento(raiz->direito) == -1) {
        return RotL(raiz);
    }

    if (fb < -1 && FatorBalanceamento(raiz->direito) == 1) {
        raiz->direito = RotR(raiz->direito);
        return RotL(raiz);
    }

    return raiz;
}

BST* bstInsert(BST* raiz, int chave) {
    if (raiz == NULL) {
        return novoNo(chave);
    }
    //Verificando onde colocar o No
    if (chave < raiz->chave)
    {
        raiz->esquerdo = bstInsert(raiz->esquerdo, chave);
    }
    else if (chave > raiz->chave) {
        raiz->direito = bstInsert(raiz->direito, chave);
    }
    
    raiz->altura = Max(Altura(raiz->esquerdo), Altura(raiz->direito)) + 1;

    return raiz;
}


void InOrder(BST* raiz) {
    if (raiz == NULL) {
        return;
    }

    InOrder(raiz->esquerdo);
    printf("%d\n", raiz->chave);
    InOrder(raiz->direito);
}

void PreOrder(BST* raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d\n", raiz->chave);
    PreOrder(raiz->esquerdo);
    PreOrder(raiz->direito);
}

void PostOrder(BST* raiz) {
    if (raiz == NULL) {
        return;
    }

    PostOrder(raiz->esquerdo);
    PostOrder(raiz->direito);
    printf("%d\n", raiz->chave);
}


void gerarArvores(int quantidadeAmostras, int quantidadeNos) {
    srand(time(NULL));
    clock_t inicio, fim, iniAVL, fimAVL, iniBST, fimBST;
    double tempoGeral = 0,tempoGeralTotal = 0, tempoAVL = 0, tempoAVLTotal = 0, tempoBST = 0, tempoBSTTotal = 0;

    int * alturasBST = malloc(sizeof(int) * quantidadeAmostras);
    int * alturasAVL = malloc(sizeof(int) * quantidadeAmostras);

    int mediaGeral = 0;
    int mediaBST = 0;
    int mediaAVL = 0;

    //for para gerar todas arvores
    for (int i = 0; i < quantidadeAmostras; i++) {
        BST* bst = NULL;
        BST* avl = NULL;
        inicio = clock();
        for (int j = 0; j < quantidadeNos; j++) {
            int randNum = rand() % quantidadeNos + 1;
            while(buscaChave(bst, randNum) != 0 && buscaChave(avl, randNum) != 0){
                randNum = rand() % quantidadeNos + 1;
            }

            iniBST = clock();
            bst = bstInsert(bst, randNum);
            fimBST = clock();
            tempoBSTTotal += ((double) (fimBST - iniBST)/CLOCKS_PER_SEC);

            iniAVL = clock();
            avl = avlInsert(avl, randNum);
            fimAVL = clock();
            tempoAVLTotal += ((double) (fimAVL - iniAVL)/CLOCKS_PER_SEC);
        }
        fim = clock();
        tempoGeralTotal += ((double) (fim - inicio)/CLOCKS_PER_SEC);



        //Armazenando altura de cada arvore
        alturasAVL[i] = avl->altura;
        alturasBST[i] = bst->altura;

        // printf("EM ORDEM: BST(%d)\n", i + 1);
        // InOrder(bst);
        // printf("EM ORDEM: AVL(%d)\n", i + 1);
        // InOrder(avl);

        // printf("POS ORDEM: BST(%d)\n", i + 1);
        // PostOrder(bst);
        // printf("POS ORDEM: AVL(%d)\n", i + 1);
        // PostOrder(avl);

        free(bst);
        free(avl);
    }

    //Calculando a media geral de construcao
    tempoGeral = tempoGeralTotal/quantidadeAmostras;
    tempoAVL = tempoAVLTotal/quantidadeAmostras;
    tempoBST = tempoBSTTotal/quantidadeAmostras;

    int totalAVL = 0;
    int totalBST = 0;

    for(int i = 0; i < quantidadeAmostras; i++){
        totalAVL += alturasAVL[i];
        totalBST += alturasBST[i];        
    }

    // printf("totalAVL: %d\n", totalAVL);
    // printf("totalBST: %d\n", totalBST);

    mediaAVL = totalAVL/quantidadeAmostras;
    mediaBST = totalBST/quantidadeAmostras;
    mediaGeral = (mediaAVL + mediaBST)/2 ;

    //Tela
    printf("\nExperimento com A = %d e N = %d\n", quantidadeAmostras, quantidadeNos);

    printf("----------------------------\n");

    printf("Altura media geral: %d\n", mediaGeral);
    printf("Tempo medio geral de construcao: %f segundo(s)\n", tempoGeral);
    printf("Tempo total geral de construcao das %d arvores: %f segundo(s)\n", quantidadeAmostras, tempoGeralTotal);

    printf("----------------------------\n");

    printf("Altura media BST comum: %d\n", mediaBST);
    printf("Tempo medio de construcao de cada BST: %f segundo(s)\n", tempoBST);
    printf("Tempo total de construcao das %d BST's: %f segundo(s)\n", quantidadeAmostras, tempoBSTTotal);

    printf("----------------------------\n");

    printf("Altura media AVL: %d\n", mediaAVL);
    printf("Tempo medio de construcao de cada AVL: %f segundo(s)\n", tempoAVL);
    printf("Tempo total de construcao das %d AVL's: %f segundo(s)\n", quantidadeAmostras, tempoAVLTotal);

    printf("----------------------------\n");

    free(alturasAVL);
    free(alturasBST);
}

void MenuSimulacao(){
    int qtdAmostras, qtdElementos;
    
    printf("Digite a quantidade de amostras: ");
    scanf("%d", &qtdAmostras);
    printf("Digite a quantidade de elementos para cada amostra: ");
    scanf("%d", &qtdElementos);

    gerarArvores(qtdAmostras, qtdElementos);
}



int main(void) {

    int opt = 0;

    while(opt != 2){
        printf("Menu: 1) Nova simulacao 2) Sair\n");
        scanf("%d", &opt);

        if(opt == 1){
            MenuSimulacao();
        }
    }

    return 0;
}