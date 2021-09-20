#include <stdio.h>
#include <semaphore.h>
#include "SalaServico.h"

int capacidade;
int nG = 0, nC = 0;
int nGesperando = 0, NCesperando = 0;
sem_t filaGatos;
sem_t filaCaes;
sem_t chegada;

void abre_petshop(int tamanho){
    capacidade = tamanho;
    sem_init(&filaGatos,0,0);
    sem_init(&filaCaes,0,0);
    sem_init(&chegada,0,1);
}

void um_gato_quer_servico(){

    sem_wait(&chegada);

    if(nC > 0 || nG == capacidade){

        nGesperando++;

        sem_post(&chegada);

        sem_wait(&filaGatos);
    }
    else{

        nG++;

        printf("\n\nUm gato entrou DIRETO, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

        sem_post(&chegada);
    }


}

void gato_atendido(){

    sem_wait(&chegada);
    nG--;

    printf("\n\nUm gato saiu, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
  

    if(nG == 0 && NCesperando > 0){
        while(nC < capacidade && NCesperando > 0){

             
            nC++;
            NCesperando--;
            
            printf("\n\nUm cao entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
            sem_post(&filaCaes);

        }
    }

    else if(nGesperando > 0){
        while(nG < capacidade && nGesperando > 0){

            nG++;
            nGesperando--;
            printf("\n\nUm gato entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
            sem_post(&filaGatos);

        }
    }

    sem_post(&chegada); 

}

void um_cao_quer_servico(){

    sem_wait(&chegada);

    if(nG > 0 || nC == capacidade){

        NCesperando++;

        sem_post(&chegada);

        sem_wait(&filaCaes);

    }

    else{

        nC++;

        printf("\n\nUm cao entrou DIRETO, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

        sem_post(&chegada);
    }

}

void cao_atendido(){

    sem_wait(&chegada);
    nC--;

    printf("\n\nUm cao saiu, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);


    if (NCesperando > 0){
        while(nC < capacidade && NCesperando > 0){
            NCesperando--;
            nC++;
            printf("\n\nUm cao entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
            sem_post(&filaCaes);
        }
    }

    else if (nGesperando > 0 && nC == 0){
        printf("\n\n A CAPACIDADE É DE: %d\n\n", capacidade);
        while(nG < capacidade && nGesperando > 0){
            nGesperando--;
            nG++;
            printf("\n\nUm gato entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
            sem_post(&filaGatos);
        }
    }

    sem_post(&chegada);
}

void fecha_petshop(){
    sem_close(&chegada);
    sem_close(&filaGatos);
    sem_close(&filaCaes);
}