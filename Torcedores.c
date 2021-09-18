#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Monitor.h"

void* thread_flamenguista(void *id) { 
    int data = (int) id;
    
    while(1){
        printf("Eu sou o(a) flamenguista%d:...Estou apertado(a)! Vou no banheiro!\n",data); 
        flamenguistaQuerEntrar();
        printf ("Eu sou flamenguista-%d: ... UFA! Entrei no banheiro!\n",data); 
        sleep(5); 
        flamenguistaSai(); 
        printf ("Eu sou flamenguista-%d: ... Estou aliviado! Vou torcer!\n",data); 
        sleep(20); 
    }
}

void* thread_vascaina(void *id) { 
    int data = (int) id;
    
    while(1){
        printf("Eu sou o(a) vascaino%d:...Estou apertado(a)! Vou no banheiro!\n",data); 
        vascainoQuerEntrar();
        printf ("Eu sou vascaino-%d: ... UFA! Entrei no banheiro!\n",data); 
        sleep(5); 
        vascainoSai(); 
        printf ("Eu sou vascaino-%d: ... Estou aliviado! Vou torcer!\n",data); 
        sleep(20); 
    }
}

int main(){
    pthread_t torcedores[10];

    inicia();

    for (int i=0; i<10; i++){
        if(i%2 == 0){
            if(pthread_create(&torcedores[i], NULL, thread_flamenguista, (void*)i) != 0) printf("Falha!\n");
        }
        else{
            if(pthread_create(&torcedores[i], NULL, thread_vascaina, (void*)i) != 0) printf("Falha!\n");
        }
    }

    for (int i=0; i<10; i++){
        if(pthread_join(torcedores[i], NULL) != 0) printf("Falha!\n");
    }

    return 0;
}