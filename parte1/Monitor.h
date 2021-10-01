#ifndef MONITOR_H
#define MONITOR_H

/*Função iniciada quando um flamenguista quer entrar no banheiro*/

void flamenguistaQuerEntrar(); 

/*Função iniciada quando um flamenguista sai do banheiro*/

void flamenguistaSai();

/*Função iniciada quando um vascaino quer entrar no banheiro*/

void vascainoQuerEntrar(); 

/*Função iniciada quando um vascaino sai do banheiro*/

void vascainoSai();

/*Inicia o mutex e as variaveis de condicao do monitor*/

void inicia();

#endif 