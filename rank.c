#include "rank.h"
#include "tools.h"

// Cria um Rank vazio e retorna um ponteiro para ele
Rank CriaRank(int volta, int size) {
    Rank R = malloc(sizeof(celRank));
    R->volta = volta;
    R->n = 0;
    R->nCiclista = malloc(size * sizeof(int));
    R->t = malloc(size * sizeof(int));
    R->size = size;
    return R;
}

// Insere ciclista num Rank sem utilização de listas ligadas
// A estrutura foi aproveitada para armazenar o rank final
void InsereCiclistaRank(Rank R, int ciclista, int t) {
    R->nCiclista[R->n] = ciclista;
    R->t[R->n] = t;
    (R->n)++;
}


// Insere um ciclista p no instante de tempo t em uma lista L
void InsereCiclista(ListaRank L, int size, int volta, int ciclista, int t) {
    Rank R = NULL; // Rank da volta correspondente
    if (L->rank == NULL) { // lista vazia
        L->rank = CriaRank(volta, size);
        R = L->rank;
    }
    else { // lista não vazia
        ListaRank Latual = L;
        while (1) { // busca se já existe um rank para essa volta
            if (Latual->rank->volta == volta) {
                R = Latual->rank;
                break;
            }
            if (Latual->prox == NULL) break;
            else Latual = Latual->prox;
        }
        if (R == NULL) { // Não existe, precisa criar
            ListaRank Lnovo = CriaListaRank();
            R = CriaRank(volta, size);
            Latual->prox = Lnovo;
            Lnovo->rank = R;
        }
    }
    R->nCiclista[R->n] = ciclista;
    R->t[R->n] = t;
    (R->n)++;
}


// Cria uma lista ligada de Ranks, com primeiro rank de tamanho size
// e retorna um ponteiro para a lista criada
ListaRank CriaListaRank() {
    ListaRank L = malloc(sizeof(ListaRank));
    L->rank = NULL;
    L->prox = NULL;
    return L;
}

// Destrói um Rank
void DestroiRank(Rank R) {
    free(R->nCiclista);
    free(R->t);
    free(R);
}

// Recebe uma ListaRank L e remove o rank do início da lista
void RemoveRank(ListaRank L) {
    Rank R = L->rank;
    L = L->prox;
    DestroiRank(R);
}

// Destrói uma lista de ranks
void DestroiListaRank(ListaRank L) {
    while (L->rank != NULL)
        RemoveRank(L);
}

// Imprime a lista de rank de uma volta específica
void imprimeRank(ListaRank L, int volta) {
    Rank R = NULL;
    for (ListaRank L1 = L; L1 != NULL; L1 = L1->prox)
        if (L1->rank->volta == volta) {
            R = L1->rank;
            break;
        }
    if (R == NULL) {
        printf("ERRO! Volta não encontrada na lista de ranks.\n");
        return;
    }
    printf("Ciclic\tPos\tTempo\n");
    for (int i = 0; i < R->n; i++) {
        printf("%d\t%d\t%d\n", R->nCiclista[i], i+1, R->t[i]);
    }
    printf("\n");
}

// Imprime a lista de rank final
void imprimeRankFinal(Rank R) {
    printf("Ciclic\tPos\tTempo\n");
    for (int i = R->n - 1; i >= 0; i--) {
        printf("%d\t%d\t%d\n", R->nCiclista[i], R->n - i, R->t[i]);
    }
    printf("\n");
}

// Recebe uma ListaRank L e uma volta e retorna um ponteiro para o Rank
// dessa volta.
Rank BuscaRank(ListaRank L, int volta) {
    Rank R = NULL;
    ListaRank Latual = L;
    while (1) { // busca se já existe um rank para essa volta
        if (Latual->rank->volta == volta) {
            R = Latual->rank;
            break;
        }
        if (Latual->prox == NULL) break;
        else Latual = Latual->prox;
    }
    return R;
}


// Recebe uma lista de ranks por volta e retorna o último colocado ao término
// dessa volta. Se houver mais de um último colocado, sorteia um deles
int ultimoColocado(ListaRank L, int volta) {
    int a, b;
    Rank R = BuscaRank(L, volta);
    if (R == NULL) {
        printf("ERRO! Volta não encontrada na função ultimoColocado.\n");
        return -1;
    }
    a = b = R->n - 1; // último índice
    while (R->t[a] == R->t[b])
        a--;
    a++;
    if (a == b) // só há um último colocado
        return R->nCiclista[a];
    return R->nCiclista[randInteger(a, b)];
}