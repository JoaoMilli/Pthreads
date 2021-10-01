#include <stdio.h>
#include <semaphore.h>
#include "SalaServico.h"

int capacidade;         //Capacidade da sala
int nG = 0, nC = 0;     //Numero de gatos e numero de caes dentro da sala
int nGesperando = 0, NCesperando = 0;   //Numero de gatos e caes esperando na fila
sem_t filaGatos;        //semaforo que controla a fila de gatos
sem_t filaCaes;         //semaforo que controla a fila de caes
sem_t chegada;          //semaforo que controla o acesso a regioes criticas


/*Funcao que inicia os semaforos de SalaServico e define a capacidade da sala*/

void abre_petshop(int tamanho){
    capacidade = tamanho;

    /*filaGatos e filaCaes sao inicializados com 0, fazendo com que bloqueiem sempre quando sem_wait eh invocado*/
    /*chegada eh inicializado com 1 e funciona como um mutex*/

    sem_init(&filaGatos,0,0);
    sem_init(&filaCaes,0,0);
    sem_init(&chegada,0,1);
}

/*Função iniciada quando um gato quer entrar na sala de servico*/

void um_gato_quer_servico(){

    /*Entra na regiao critica*/
    sem_wait(&chegada);

    /*Se houver caes na sala ou a capacidade da sala esta cheia, o gato eh colocado em espera*/
    if(nC > 0 || nG == capacidade){

        /*Incrementa o contador de gatos esperando*/
        nGesperando++;

        /*Sai da regiao critica*/
        sem_post(&chegada);

        /*bloqueia a thread invocando sem_wait no semaforo filaGatos*/
        sem_wait(&filaGatos);
    }

    /*Se nao houver caes na sala e a capacidade da sala nao esta cheia, o gato entra na sala*/
    else{

        /*Incrementa o contador de gatos esperando*/
        nG++;

        printf("\n\nUm gato entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

        sem_post(&chegada);
    }


}

/*Função iniciada quando um gato sai da sala de servico*/

void gato_atendido(){

    /*Entra na regiao critica*/
    sem_wait(&chegada);

    /*Decrementa o contador de gatos na sala*/
    nG--;

    printf("\n\nUm gato saiu, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);
  
    /*Se a sala nao contem mais gatos e existem caes esperando na fila, a sala vai sendo preenchida com caes ate que se atinja a capacidade
    maxima ou nao haja mais caes esperando*/

    if(nG == 0 && NCesperando > 0){
        while(nC < capacidade && NCesperando > 0){

            /*Incrementa o contador de caes na sala*/
            nC++;

            /*Decrementa o contador de caes esperando na fila*/
            NCesperando--;
            
            printf("\n\nUm cao entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

            /*Libera um cao da fila de espera*/
            sem_post(&filaCaes);

        }
    }

    /*Se nao existem caes esperando na fila ou ainda existem gatos na sala,a sala vai sendo preenchida com gatos ate que se atinja a capacidade
    maxima ou nao haja mais gatos esperando*/

    else if(nGesperando > 0){
        while(nG < capacidade && nGesperando > 0){

            /*Incrementa o contador de gatos na sala*/
            nG++;

            /*Decrementa o contador de gatos esperando na fila*/
            nGesperando--;

            printf("\n\nUm gato entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

            /*Libera um gato da fila de espera*/
            sem_post(&filaGatos);

        }
    }

    /*Sai da regiao critica*/
    sem_post(&chegada); 

}

/*Função iniciada quando um cao quer entrar na sala de servico*/

void um_cao_quer_servico(){

    /*Entra na regiao critica*/
    sem_wait(&chegada);

    /*Se existem gatos na sala ou a capacidade da sala eh maxima, o cao eh colocado na fila de espera*/
    if(nG > 0 || nC == capacidade){

        /*Incrementa o contador de caes esperando na fila*/
        NCesperando++;

        /*Sai da regiao critica*/
        sem_post(&chegada);

        /*bloqueia a thread invocando sem_wait no semaforo filaCaes*/
        sem_wait(&filaCaes);

    }

    /*Se nao existem gatos na sala e a capacidade nao eh maxima, o cao entra na sala*/

    else{

        /*Incrementa o contador de caes na sala*/
        nC++;

        printf("\n\nUm cao entrou DIRETO, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

        /*Sai da regiao critica*/
        sem_post(&chegada);
    }

}

void cao_atendido(){

    /*Entra na regiao critica*/
    sem_wait(&chegada);

    /*Decrementa o contador de caes na sala*/
    nC--;

    printf("\n\nUm cao saiu, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

    /*Se houver caes esperando na fila, a sala eh preenchida ate que nao haja mais caes esperando na fila ou
    a capacidade da sala seja maxima*/

    if (NCesperando > 0){
        while(nC < capacidade && NCesperando > 0){

            /*Decrementa o valor de caes esperando*/
            NCesperando--;

            /*Incrementa o valor de caes na sala*/
            nC++;
            printf("\n\nUm cao entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

            /*Libera um cao da fila de espera*/
            sem_post(&filaCaes);
        }
    }

    /*Se nao houver caes esperando na fila e houver gatos esperando na fila sendo que nao exista nenhum cao dentro da sala,
    sala eh preenchida ate que nao haja mais gatos esperando na fila ou a capacidade da sala seja maxima*/

    else if (nGesperando > 0 && nC == 0){
        while(nG < capacidade && nGesperando > 0){

            /*Decrementa o contador de gatos esperando*/
            nGesperando--;

            /*Incrementa o valor de gatos na sala*/
            nG++;


            printf("\n\nUm gato entrou, a sala de servico contém %d caes e %d gatos\n\n", nC, nG);

            /*Libera um gato da fila de espera*/
            sem_post(&filaGatos);
        }
    }

    /*Sai da regiao critica*/
    sem_post(&chegada);
}

/*Funcao que destroi os semaforos de SalaServico*/

void fecha_petshop(){
    sem_close(&chegada);
    sem_close(&filaGatos);
    sem_close(&filaCaes);
}