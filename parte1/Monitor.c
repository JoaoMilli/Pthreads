#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Monitor.h"

/*Define a capacidade máxima do banheiro*/

#define CAPACIDADE_MAXIMA 3

pthread_mutex_t mutexBanheiro;          //mutex que garante exclusao mutua ao mudar dados referentes ao banheiro
pthread_cond_t liberaVascaino;          //variavel de condicao que controla a entrada e saida de vascainos
pthread_cond_t liberaFlamenguista;      //variavel de condicao que controla a entrada e saida de flamenguistas
int nFlamenguistas;                     //numero de flamenguistas no banheiro
int nVascainos;                         //numero de vascainos no banheiro
int nPessoas;                           //numero total de pessoas no banheiro


/*Inicia o mutex e as variaveis de condicao*/

void inicia(){
    pthread_mutex_init(&mutexBanheiro, NULL);
    pthread_cond_init(&liberaVascaino, NULL);
    pthread_cond_init(&liberaFlamenguista, NULL);
}

void flamenguistaQuerEntrar(){

    /*Tranca o mutex, impedindo que outra thread acesse essa regiao*/

    pthread_mutex_lock(&mutexBanheiro);

    /*Thread flamenguista checa se o banheiro esta lotado ou se tem algum vascaino dentro*/

    while(nPessoas == CAPACIDADE_MAXIMA || nVascainos != 0){

        /*Caso o banheiro esteja lotado ou tem algum vascaino dentro a thread eh bloqueada e libera o mutex do banheiro,
        a thread sera desbloqueada novamente quando a variavel de condicao liberaFlamenguista for sinalizada*/

        pthread_cond_wait(&liberaFlamenguista, &mutexBanheiro);
    }

    /*Caso o banheiro nao esteja lotado e nao existe vascaino dentro, a thread flamenguista sai do loop e incrementa os contadores,
    sinalizando que o torcedor entrou no banheiro*/

    nPessoas++;
    nFlamenguistas++;

    printf("\n\nEntrou um flamenguista, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);

    /*Desbloqueia o mutex banheiro, para que outras threads possam entrar na regiao critica*/

    pthread_mutex_unlock(&mutexBanheiro);
}

void flamenguistaSai(){

    /*Tranca o mutex, impedindo que outra thread acesse essa regiao*/

    pthread_mutex_lock(&mutexBanheiro);

    /*Decrementa os contadores, simbolizando a saida do flamenguista do banheiro*/

    nPessoas--;
    nFlamenguistas--;

    printf("\n\n Saiu um flamenguista, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);

    /*Desbloqueia o mutex banheiro, para que outras threads possam entrar na regiao critica*/
    pthread_mutex_unlock(&mutexBanheiro);

    /*Envia sinais com as variaveis de condicao liberaVascaino e liberaFlamenguista, a funcao pthread_cond_broadcast envia o sinal para
    todas as thread que estejam bloqueadas esperando o sinal passado como argumento, o sinal eh passado primeiro para os vascainos atraves
    da variavel liberaVascaino, para depois ser passada para os flamenguistas atraves da variavel liberaFlamenguista*/

    /*As threads esperando por esses sinais estao executando vascainoQuerEntrar ou flamenguistaQuerEntrar, simbolizando a espera de um torcedor
    para uma vaga no banheiro*/

    pthread_cond_broadcast(&liberaVascaino);
    sleep(1);
    pthread_cond_broadcast(&liberaFlamenguista); 
}

/*A implementacao das funcoes vascainoQuerEntrar e vascainoSai sao semelhantes as funcoes dos flamenguistas*/

void vascainoQuerEntrar(){

    pthread_mutex_lock(&mutexBanheiro);
    while(nPessoas == CAPACIDADE_MAXIMA || nFlamenguistas != 0){
        pthread_cond_wait(&liberaVascaino, &mutexBanheiro);
    }

    nPessoas++;
    nVascainos++;

    printf("\n\nEntrou um vascaino, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);
    pthread_mutex_unlock(&mutexBanheiro);

}

void vascainoSai(){
    pthread_mutex_lock(&mutexBanheiro);
    nPessoas--;
    nVascainos--;
    printf("\n\nSaiu um vascaino, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);
    pthread_mutex_unlock(&mutexBanheiro);

    pthread_cond_broadcast(&liberaVascaino);
    sleep(1);
    pthread_cond_broadcast(&liberaFlamenguista); 
}