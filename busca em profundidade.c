#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct pos
{
    int m[3][3];
    int x;
    int y;
} pos;

void print(pos e);
int comp(pos x, pos y);
void copy(pos *dest, pos *orig);

pos RES;
int PAS;
typedef struct Apos
{
    pos sol;
    struct Apos *pai;
    struct Apos *next;
} Apos;
Apos *buscaProf(Apos *arv);
void psol(Apos *t);
int main(int argc, char** argv)
{
    PAS=0;
    int i, c = 0;
    //prepara arvore
    Apos *t, *f;
    for (i = 0; i < 3; i++)
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            RES.m[i][j]=c++;
        }

    }
    t = (Apos*) malloc(sizeof (Apos));
    init(&t->sol);
    t->pai = NULL;
    f = buscaProf(t);
    psol(f);
    return (EXIT_SUCCESS);
}

Apos *buscaProf(Apos *arv)
{
    //print(arv->sol);
    //printf("vez:%d\n",vez);
    Apos *aux, *aux1, *ret = NULL;
    int tem;
    if (comp(arv->sol, RES))
    {
        return arv;
    }
    else
    {
        //cima
        if (arv->sol.x - 1 >= 0)
        {
            //alocando o filho
            aux = (Apos*) malloc(sizeof(Apos));
            //setando pai
            aux->pai = arv;
            //copiando tabuleiro
            copy(&(aux->sol), &(arv->sol));
            //arrumando peça vazia
            aux->sol.x = arv->sol.x - 1;
            //trocando as peças
            aux->sol.m[arv->sol.x][arv->sol.y] = aux->sol.m[aux->sol.x][aux->sol.y];
            aux->sol.m[aux->sol.x][aux->sol.y] = 0;
            //verificando pre existencia
            tem = 0;
            aux1 = arv;
            while (aux1 != NULL)
            {
                if (comp(aux->sol, aux1->sol))
                {
                    tem = 1;
                    break;
                }
                aux1 = aux1->pai;
            }
            if (tem)
            {
                free(aux);
            }
            else
            {
                ret = buscaProf(aux);
                if (ret != NULL)
                    return ret;

                else
                    free(aux);
            }
        }
        //baixo
        if (arv->sol.x + 1 < 3)
        {
            //alocando o filho
            aux = (Apos*) malloc(sizeof (Apos));
            //setando pai
            aux->pai = arv;
            //copiando tabuleiro
            copy(&(aux->sol), &(arv->sol));
            //arrumando peça vazia
            aux->sol.x = arv->sol.x + 1;
            //trocando as peças
            aux->sol.m[arv->sol.x][arv->sol.y] = aux->sol.m[aux->sol.x][aux->sol.y];
            aux->sol.m[aux->sol.x][aux->sol.y] = 0;
            //verificando pre existencia
            tem = 0;
            aux1 = arv;
            while (aux1 != NULL)
            {
                if (comp(aux->sol, aux1->sol))
                {
                    tem = 1;
                    break;
                }
                aux1 = aux1->pai;
            }
            if (tem)
            {
                free(aux);
            }
            else
            {
                ret = buscaProf(aux);
                if (ret != NULL)
                    return ret;

                else
                    free(aux);
            }
        }
        //esquerda
        if (arv->sol.y - 1 >= 0)
        {
            //alocando o filho
            aux = (Apos*) malloc(sizeof (Apos));
            //setando pai
            aux->pai = arv;
            //copiando tabuleiro
            copy(&(aux->sol), &(arv->sol));
            //arrumando peça vazia
            aux->sol.y = arv->sol.y - 1;
            //trocando as peças
            aux->sol.m[arv->sol.x][arv->sol.y] = aux->sol.m[aux->sol.x][aux->sol.y];
            aux->sol.m[aux->sol.x][aux->sol.y] = 0;
            //verificando pre existencia
            tem = 0;
            aux1 = arv;
            while (aux1 != NULL)
            {
                if (comp(aux->sol, aux1->sol))
                {
                    tem = 1;
                    break;
                }
                aux1 = aux1->pai;
            }
            if (tem)
            {
                free(aux);
            }
            else
            {
                ret = buscaProf(aux);
                if (ret != NULL)
                    return ret;

                else
                    free(aux);
            }
        }
        //direita
        if (arv->sol.y + 1 < 3)
        {
            //alocando o filho
            aux =  (Apos*)malloc(sizeof (Apos));
            //setando pai
            aux->pai = arv;
            //copiando tabuleiro
            copy(&(aux->sol), &(arv->sol));
            //arrumando peça vazia
            aux->sol.y = arv->sol.y + 1;
            //trocando as peças
            aux->sol.m[arv->sol.x][arv->sol.y] = aux->sol.m[aux->sol.x][aux->sol.y];
            aux->sol.m[aux->sol.x][aux->sol.y] = 0;
            //verificando pre existencia
            tem = 0;
            aux1 = arv;
            while (aux1 != NULL)
            {
                if (comp(aux->sol, aux1->sol))
                {
                    tem = 1;
                    break;
                }
                aux1 = aux1->pai;
            }
            if (tem)
            {
                free(aux);
            }
            else
            {
                ret = buscaProf(aux);
                if (ret != NULL)
                    return ret;

                else
                    free(aux);
            }
        }
        //printf("erro\n");
        return NULL;
    }
}

void psol(Apos *t)
{
    if(t->pai!=NULL)
    {
        psol(t->pai);
    }
    print(t->sol);
    printf("passo:%d\n",PAS++);
    fflush(stdout);
    //sleep(1);
}
void print(pos e)
{
    int i;
    printf("_____________\n");
    for (i = 0; i < 3; i++)
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            if (e.m[i][j] != 0)
                printf("|%d  ", e.m[i][j]);
            else
                printf("|*  ");

        }
        printf("|\n|___|___|___|\n");
    }
}

int comp(pos x, pos y)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            if (x.m[i][j] != y.m[i][j])
                return 0;
        }
    }
    return 1;
}

void copy(pos *dest, pos *orig)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            dest->m[i][j] = orig->m[i][j];
        }
    }
    dest->x = orig->x;
    dest->y = orig->y;
}

int init(pos *e)
{
    FILE *arq = fopen("init", "r");
    if (arq != NULL)
    {
        // e = alloca(sizeof (pos));
        int i;
        for (i = 0; i < 3; i++)
        {
            int j;
            for (j = 0; j < 3; j++)
            {
                fscanf(arq, "%d", &(e->m[i][j]));
                if (e->m[i][j] == 0)
                {
                    e->x = i;
                    e->y = j;
                }
            }
        }
        return 1;
    }
    else
        return 0;

}
