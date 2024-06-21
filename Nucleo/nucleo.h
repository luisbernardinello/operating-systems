#include<system.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* tipo DESCRITOR_PROC */

typedef struct desc_p{
    char nome[35];
    struct desc_p *fila_sem;
    struct desc_p *prox_desc;
    PTR_DESC contexto;
    enum{ativo, bloq_p, terminado} estado;
}DESCRITOR_PROC;

/* tipo PTR_DESC_PROC */

typedef DESCRITOR_PROC *PTR_DESC_PROC;

/* tipo semaforo */

typedef struct {	
	int s;
	PTR_DESC_PROC Q;
}semaforo;

extern void far inicia_fila();
extern void far inicia_semaforo(semaforo *sem, int n);
extern void far primitiva_p(semaforo *sem);
extern void far primitiva_v(semaforo *sem);
extern void far cria_processo(char nomeP[35], void far (*proc)());
extern void far termina_processo();
extern void far inicia_sistema();
