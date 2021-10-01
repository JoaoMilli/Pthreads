#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Monitor.h"

/*Thread que representa o torcedor flamenguista*/

void* thread_flamenguista(void *id) { 
    int data = (int) id; //Faz o typecast do dado que representa o id do torcedor (inteiro)

    /*A thread fica em um loop infinito chamando funções do monitor*/
    
    while(1){
        printf("Eu sou o(a) flamenguista%d:...Estou apertado(a)! Vou no banheiro!\n",data); 
        flamenguistaQuerEntrar();
        printf ("Eu sou flamenguista-%d: ... UFA! Entrei no banheiro!\n",data); 
        sleep(5); 
        flamenguistaSai(); 
        printf ("Eu sou flamenguista-%d: ... Estou aliviado! Vou torcer!\n",data); 
        sleep(10); 
    }
}

/*Thread que representa o torcedor vascaino*/

void* thread_vascaina(void *id) { 
    int data = (int) id; //Faz o typecast do dado que representa o id do torcedor (inteiro)
    

    /*A thread fica em um loop infinito chamando funções do monitor*/

    while(1){
        printf("Eu sou o(a) vascaino%d:...Estou apertado(a)! Vou no banheiro!\n",data); 
        vascainoQuerEntrar();
        printf ("Eu sou vascaino-%d: ... UFA! Entrei no banheiro!\n",data); 
        sleep(5); 
        vascainoSai(); 
        printf ("Eu sou vascaino-%d: ... Estou aliviado! Vou torcer!\n",data); 
        sleep(10); 
    }
}

int main(){

    /* Cria 10 identificadores de threads para representar cada jogador, sendo uma thread um torcedor */

    pthread_t torcedores[10];

    /*Inicia os mutexes do monitor que serão utilizados para a sicronização das threads*/

    inicia();

    /*Cria 10 threads e faz com que 5 dessas executem thread_flamenguista, representando 5 flamenguistas e as outras 5 executem a thread vascaina,
    representando 5 vascainos*/

    for (int i=0; i<10; i++){
        if(i%2 == 0){
            if(pthread_create(&torcedores[i], NULL, thread_flamenguista, (void*)i) != 0) printf("Falha na criacao da thread!\n");
        }
        else{
            if(pthread_create(&torcedores[i], NULL, thread_vascaina, (void*)i) != 0) printf("Falha na criacao da thread!\n");
        }
    }

    /* Usa o join para fazer com que a main espere o termino de todas as 10 threads criadas */

    for (int i=0; i<10; i++){
        if(pthread_join(torcedores[i], NULL) != 0) printf("Falha no join da thread!\n");
    }

    return 0;
}