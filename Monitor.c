#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Monitor.h"

#define CAPACIDADE_MAXIMA 3

pthread_mutex_t mutexBanheiro;
pthread_cond_t liberaVascaino;
pthread_cond_t liberaFlamenguista;
int nFlamenguistas;
int nVascainos;
int nPessoas;

void inicia(){
    pthread_mutex_init(&mutexBanheiro, NULL);
    pthread_cond_init(&liberaVascaino, NULL);
    pthread_cond_init(&liberaFlamenguista, NULL);
}

void flamenguistaQuerEntrar(){

    pthread_mutex_lock(&mutexBanheiro);
    //printf("\nFlamenguista quer entrar, tem %d pessoas e %d vascainos\n\n", nPessoas, nVascainos);
    while(nPessoas == CAPACIDADE_MAXIMA || nVascainos != 0){
        pthread_cond_wait(&liberaFlamenguista, &mutexBanheiro);
        //printf("\nFlamenguista quer entrar, tem %d pessoas e %d vascainos\n\n", nPessoas, nVascainos);
    }

    nPessoas++;
    nFlamenguistas++;

    printf("\n\nEntrou um flamenguista, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);
    pthread_mutex_unlock(&mutexBanheiro);
}

void flamenguistaSai(){
    pthread_mutex_lock(&mutexBanheiro);
    nPessoas--;
    nFlamenguistas--;

    printf("\n\n Saiu um flamenguista, O banheiro tem %d pessoas, %d flamenguistas e %d vascainos\n\n", nPessoas, nFlamenguistas, nVascainos);
    pthread_mutex_unlock(&mutexBanheiro);

    pthread_cond_broadcast(&liberaVascaino);
    sleep(1);
    pthread_cond_broadcast(&liberaFlamenguista); 
}

void vascainoQuerEntrar(){

    pthread_mutex_lock(&mutexBanheiro);
    //printf("Vascaino quer entrar, tem %d pessoas e %d flamenguistas\n\n", nPessoas, nFlamenguistas);
    while(nPessoas == CAPACIDADE_MAXIMA || nFlamenguistas != 0){
        pthread_cond_wait(&liberaVascaino, &mutexBanheiro);
        //printf("Vascaino quer entrar, tem %d pessoas e %d flamenguistas\n\n", nPessoas, nFlamenguistas);
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