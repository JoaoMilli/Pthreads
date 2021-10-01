#ifndef SALASERVICO_H
#define SALASERVICO_H

/*Função iniciada quando um gato quer entrar na sala de servico*/
void um_gato_quer_servico();

/*Função iniciada quando um gato sai da sala de servico*/
void gato_atendido();

/*Função iniciada quando um cao quer entrar na sala de servico*/
void um_cao_quer_servico(); 

/*Função iniciada quando um cao sai da sala de servico*/
void cao_atendido();

/*Funcao que inicia os semaforos de SalaServico e define a capacidade da sala*/
void abre_petshop(int tamanho);

/*Funcao que destroi os semaforos de SalaServico*/
void fecha_petshop();

#endif