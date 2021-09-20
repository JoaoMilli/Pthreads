#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "SalaServico.h"

void* thread_cao(void *id);
void* thread_gato(void *id);

int main(){

    int capacidade, numGatos, numCaes;
    int i,j;

    printf("Qual a capacidade do PetShop?: ");
    scanf("%d", &capacidade);
    printf("\nQual o numero de cachorros?: ");
    scanf("%d", &numCaes);
    printf("\nQual o numero de gatos?: ");
    scanf("%d", &numGatos);

    pthread_t animais[numCaes+numGatos];

    abre_petshop(capacidade);

    for (i=0; i<numCaes; i++){

        if(pthread_create(&animais[i], NULL, thread_cao, (void*)i) != 0) printf("Falha!\n");

    }
    for (j=0; j<numGatos; j++, i++){
        if(pthread_create(&animais[i], NULL, thread_gato, (void*)i) != 0) printf("Falha!\n");

    }

    for (i=0; i<numCaes+numGatos; i++){
        if(pthread_join(animais[i], NULL) != 0) printf("Falha!\n");
    }

    fecha_petshop();

    return 0;
}

void* thread_cao(void *id){
    int data = (int)id;
    srand(time(NULL));
    sleep(rand()%5);
    printf("\n\nChegou um cão na fila de espera com id %d\n\n", data);
    um_cao_quer_servico();
    printf ("\n\nO cão %d entrou para a sala de servico\n\n",data); 
    sleep(5);
    cao_atendido();
    printf ("\n\nO cão %d foi atendido\n\n",data); 
}

void* thread_gato(void *id){
    int data = (int)id;
    srand(time(NULL));
    sleep(rand()%5);
    printf("\n\nChegou um gato na fila de espera com id %d\n\n", data);
    um_gato_quer_servico();
    printf ("\n\nO gato %d entrou para a sala de servico\n\n",data); 
    sleep(5);
    gato_atendido();
    printf ("\n\nO gato %d foi atendido\n\n",data);
}