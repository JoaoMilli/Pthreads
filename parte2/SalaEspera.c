#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "SalaServico.h"

/*Thread que representa um cao*/
void* thread_cao(void *id);

/*Thread que representa um gato*/
void* thread_gato(void *id);

int main(){

    int capacidade, numGatos, numCaes;  //capacidade total, numero de gatos e caes
    int i,j;                            //inteiros auxiliares


    /*Recebe a capacidade do petshop, numero de gatos e cachorros a serem atendidos pela entrada padrao*/

    printf("Qual a capacidade do PetShop?: ");
    scanf("%d", &capacidade);
    printf("\nQual o numero de cachorros?: ");
    scanf("%d", &numCaes);
    printf("\nQual o numero de gatos?: ");
    scanf("%d", &numGatos);

    /*Cria identificadores de threads, um para cada animal*/

    pthread_t animais[numCaes+numGatos];

    /*Inicia os semaforos utilizados para a sicronizacao de threads, assim como a capacidade do petshop*/
    abre_petshop(capacidade);

    /*Eh criada uma thread para cada animal, threads que representam gatos irao executar a funcao thread_gato, enquanto
    threads que representam caes irao executar a funcao thread_cao*/

    for (i=0; i<numCaes; i++){

        if(pthread_create(&animais[i], NULL, thread_cao, (void*)i) != 0) printf("Falha!\n");

    }
    for (j=0; j<numGatos; j++, i++){
        if(pthread_create(&animais[i], NULL, thread_gato, (void*)i) != 0) printf("Falha!\n");

    }

    /*Usa o join para fazer com que a main espere o termino de todas as threads criadas*/

    for (i=0; i<numCaes+numGatos; i++){
        if(pthread_join(animais[i], NULL) != 0) printf("Falha!\n");
    }

    /*Deleta os semaforos alocados*/

    fecha_petshop();

    return 0;
}

/*Thread que representa um cao*/

void* thread_cao(void *id){
    int data = (int)id; //Faz o typecast do dado que representa o id do cao (inteiro)

    /*Espera um tempo aleatorio para que o cao chegue na fila e execute a funcao um_cao_quer_servico*/
    srand(time(NULL));
    sleep(rand()%5);
    printf("\n\nChegou um cão na fila de espera com id %d\n\n", data);
    um_cao_quer_servico();
    /*Ao sair da função, significa que o cao entrou na sala de servico*/
    printf ("\n\nO cão %d entrou para a sala de servico\n\n",data); 
    sleep(5);
    /*Apos 5 segundos o cao eh atendido e liberado*/
    cao_atendido();
    printf ("\n\nO cão %d foi atendido\n\n",data); 
}

/*Thread que representa um gato*/

void* thread_gato(void *id){
    int data = (int)id;     //Faz o typecast do dado que representa o id do gato (inteiro)

    /*Espera um tempo aleatorio para que o gato chegue na fila e execute a funcao um_gato_quer_servico*/
    srand(time(NULL));
    sleep(rand()%5);
    printf("\n\nChegou um gato na fila de espera com id %d\n\n", data);
    um_gato_quer_servico();
    /*Ao sair da função, significa que o gato entrou na sala de servico*/
    printf ("\n\nO gato %d entrou para a sala de servico\n\n",data); 
    sleep(5);
    /*Apos 5 segundos o gato eh atendido e liberado*/
    gato_atendido();
    printf ("\n\nO gato %d foi atendido\n\n",data);
}