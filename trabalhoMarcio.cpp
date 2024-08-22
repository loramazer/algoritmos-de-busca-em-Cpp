#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

#define TAM 20000

using namespace std;

struct no {
    int dado;
    struct no *esq;
    struct no *dir;
    int bal;
    char cor;
};

struct no* raiz=NULL, *raizAVL=NULL;

int vetor[TAM];
float contBS, contAVL, contAB, contBB;

void copiaVetor(int* novoVetor){
    for (int i = 0; i < TAM; i++){
        novoVetor[i] = vetor[i];
    }
}

void implementarVetor (){
    for (int i = 0; i < TAM; i++){
        vetor[i] = rand() % 30000;
    }
}

int gerarChave(){
    return rand();
}

// Rotação para a esquerda
void esquerda(struct no *p) {

    struct no *q, *hold;

    q = p->dir;
    hold = q->esq;
    q->esq = p;
    p->dir = hold;

}

//Rotação para a direita
void direita(struct no *p) {

    struct no *q, *hold;

    q = p->esq;
    hold = q->dir;
    q->dir = p;
    p->esq = hold;

}

// Cira um no e preenche os membros
struct no *cria_no(int valor) {
    struct no *aux = new (struct no);
    aux->dado=valor;
    aux->dir=NULL;
    aux->esq=NULL;
    aux->bal=0;
    return aux;
};

//Insere valor em uma árvore AVL
void insereArvoreAVL(int chave) {

    struct no *pp=NULL, *p=raizAVL, *pajovem=NULL, *ajovem=raizAVL, *q, *filho;
    int imbal;

    if (p==NULL) {             /* Arvore vazia */
        raizAVL = cria_no(chave);  /* Funcao para criacao de um novo no */
        return;
    }

    /* Insere chave e descobre ancestral mais jovem a ser desbalanceado */
    while (p!=NULL) {
        if (chave < p->dado)
            q = p->esq;
        else
            q = p->dir;
        if (q!=NULL)
            if (q->bal != 0) {
                pajovem=p;
                ajovem=q;
            }
        pp = p;
        p = q;
    }

    q = cria_no(chave);

    if (chave<pp->dado)
        pp->esq=q;
    else
        pp->dir=q;

    /* Balanceamento de todos os nós entre ajovem e q devem ser ajustados */
    if (chave<ajovem->dado)
        filho = ajovem->esq;
    else
        filho = ajovem->dir;

    p = filho;

    while (p!=q) {
        if (chave < p->dado) {
            p->bal=1;
            p=p->esq;
        } else {
            p->bal = -1;
            p=p->dir;
        }
    }

    if (chave<ajovem->dado)
        imbal = 1;
    else
        imbal = -1;

    if (ajovem->bal==0) {      /*Não houve desbalanceamento */
        ajovem->bal=imbal;
        return;
    }


    if (ajovem->bal!=imbal) {   /*Não houve desbalanceamento */
        ajovem->bal=0;
        return;
    }

    /* Houve desbalanceamento */
    if (filho->bal == imbal) {
        p=filho;
        if (imbal==1)        /* Faz rotação simples */
            direita(ajovem);
        else
            esquerda(ajovem);
        ajovem->bal=0;
        filho->bal=0;
    } else {
        if (imbal==1) {	  /*Faz rotação dupla */
            p=filho->dir;
            esquerda(filho);
            ajovem->esq=p;
            direita(ajovem);
        } else {
            p=filho->esq;
            direita(filho);
            ajovem->dir=p;
            esquerda(ajovem);
        }
        if (p->bal==0) {
            ajovem->bal=0;
            filho->bal=0;
        } else {
            if (p->bal == imbal) {
                ajovem->bal = - imbal;
                filho->bal = 0;
            } else {
                ajovem->bal = 0;
                filho->bal = imbal;
            }
        }
        p->bal=0;
    }

    if (pajovem == NULL)  /* Ajusta ponteiro do pai do ancestral mais jovem */
        raizAVL = p;
    else if (ajovem==pajovem->dir)
        pajovem->dir = p;
    else
        pajovem->esq = p;

    return;
}

void insereArvore(int valor) {

    struct no *atual, *anterior, *aux;

    aux = new(struct no);
    aux->dado = valor;
    aux->esq = NULL;
    aux->dir = NULL;

    if (raiz==NULL) {
        raiz = aux;
        return;
    }

    atual=raiz;

    while (atual!=NULL) {
        anterior=atual;
        if (valor < atual->dado)
            atual=atual->esq;
        else atual=atual->dir;
    }
    if (valor < anterior->dado)
        anterior->esq=aux;
    else anterior->dir=aux;
}

void buscaSequencial (int chave, int* vetor){
    int i = 0;
    while (i < TAM && vetor[i] < chave){
        i++;
        contBS++;
    }
 //   if (i != TAM)
 //       cout << "Encontrei na posicao " << i << endl;
 //   else cout << "Nao encontrei " << chave << endl;
}

int PARTITION (int* vetor, int inicio, int final){
    int aux;
    int pivo = vetor [inicio]; //define o primeiro elemento como pivo
    int i = inicio - 1; 
    int j = final + 1;

    while (true){ //ocorre ate que i e j se encontrem
        do{ j--; } //se move pra esquerda
        while (vetor[j] > pivo); // ate encontrar elemento <= ao pivo
        do {i++;} //se move pra direita
        while (vetor[i] < pivo); //ate encontrar elemento >= ao pivo
        if (i < j){
            aux=vetor[i];
            vetor[i]=vetor[j];
            vetor[j]=aux;
        } else return j;
    }
}

void QUICKSORT (int* vetor, int inicio, int final){
    if (inicio < final){ //se inicio for maior ou igual a final ja esta ordenado
        int q = PARTITION (vetor, inicio, final); //particiona o subvetor e retorna o pivo no final
        QUICKSORT (vetor, inicio, q); //ordena o subvetor esquerdo (elementos menores que o pivo)
        QUICKSORT (vetor, q + 1, final);//ordena o subvetor direito(elementos maiores que o pixo)
    }
}

void buscaBinaria(int chave, int* vetor){
    int inicio = 0;
    int fim = TAM-1;
    int meio;
    while (inicio <= fim){
        meio = (inicio+fim)/2;
        contBB++;
        if (vetor[meio] == chave) {
   //         cout << "A chave está na posição " << meio << endl;
            return;
        } else if (vetor[meio] < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

  //  cout << "Não foi possível encontrar a chave" << endl;
}


struct no* buscaArvore(struct no* raiz, int chave) {
    //se a raiz é nula ou a chave está na raiz
    if (raiz == nullptr){
    //    cout<< "nao encontrei"<<endl;
        return raiz;
    }
    contAB++;
    if(raiz->dado == chave){
     //   cout<<"encontrei chave"<<endl;
        return raiz;
    }
    // busca na subárvore direita
    if (raiz->dado < chave){
        return buscaArvore(raiz->dir, chave);
    }
    // busca na subárvore esquerda
    return buscaArvore(raiz->esq, chave);
}

struct no* buscaArvoreAVL(struct no* raiz, int chave) {
    //se a raiz é nula ou a chave está na raiz
    if (raiz == nullptr){
    //    cout<< "nao encontrei"<<endl;
        return raiz;
    }
    contAVL++;
    if(raiz->dado == chave){
    //    cout<<"encontrei chave"<<endl;
        return raiz;
    }
    // busca na subárvore direita
    if (raiz->dado < chave){
        return buscaArvoreAVL(raiz->dir, chave);
    }
    // busca na subárvore esquerda
    return buscaArvoreAVL(raiz->esq, chave);
}

int main (){
    float opBB = 0, opBS= 0, opAVL = 0, opAB = 0;
    int rep = 1000;
    int buscaB[TAM];
    implementarVetor();
    cout<<"Implementando vetor"<< endl;
    // copiaVetor(buscaS);
    // cout<<"Copia vetor S"<< endl;

    copiaVetor(buscaB);
    cout<<"copia vetor B"<< endl;
    QUICKSORT(buscaB ,0, TAM-1);


    for(int j = 0; j < TAM; j++){
        insereArvore(vetor[j]);
        // cout<<"Inserindo na arvore"<< endl;
        // cout<<j<<endl;
    }

    for(int j = 0; j < TAM; j++){
        insereArvoreAVL(vetor[j]);
        // cout<<"Inserindo na arvore AVL"<< endl;
        // cout<<j<<endl;
    }

    for(int i = 0; i < rep; i++){
        int chave = gerarChave();
       // cout<<"chave "<<chave<< endl;
 
        buscaSequencial(chave, buscaB);
     //   cout<<"Busca sequencial"<< endl;
        
        buscaBinaria(chave, buscaB);
     //   cout<<"Busca binaria"<< endl;
        
        buscaArvore(raiz, chave);
     //   cout<<"Busca arvore"<< endl;
        
        buscaArvoreAVL(raizAVL, chave);
     //   cout<<"Busca arvore AVL"<< endl;
        
     //   cout<< i<< endl;
    }
    
    opBB = contBB / rep;
    opAB = contAB / rep;
    opAVL = contAVL / rep;
    opBS = contBS / rep;
    cout << " Busca Sequencial: "<< opBS << " Busca Binaria: " << opBB << " Busca em Arvore Binaria: " << opAB 
    << " Busca em Arvore AVL: "<< opAVL<< endl;
    //cout << "Busca Sequencial: "<<contBS << " Busca Binaria: " << contBB << " Busca em Arvore Binaria: " << contAB 
    //<< "Busca em Arvore AVL: "<< contAVL<< endl;
    return 0;
}
