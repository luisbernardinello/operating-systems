#include<system.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/* ------------ nucleo------------ */

typedef struct desc_p{
    char nome[35];
    struct desc_p *fila_sem;
    struct desc_p *prox_desc;
    PTR_DESC contexto;
    enum{ativo, bloq_p, terminado} estado;
}DESCRITOR_PROC;

typedef DESCRITOR_PROC *PTR_DESC_PROC;

PTR_DESC d_esc;
PTR_DESC_PROC prim;


typedef struct{ 
    unsigned bx1,es1;
}regis;

typedef union k{
    regis x;
    char far *y;
}APONTA_REG_CRIT;

APONTA_REG_CRIT a;

typedef struct{
    int s;
    PTR_DESC_PROC Q;
}semaforo;

void far inicia_semaforo(semaforo *sem, int n){
    sem->s = n;
    sem->Q = NULL;
}



void far inicia_fila(){
  prim = NULL;
}

void far cria_processo(char nomeP[35], void far (*proc)()){
    PTR_DESC_PROC p_aux;
    p_aux = (PTR_DESC_PROC)malloc(sizeof(struct desc_p));
    strcpy(p_aux->nome,nomeP);
    p_aux->estado = ativo;                                       
    p_aux->contexto = cria_desc();
    newprocess(proc,p_aux->contexto);
    p_aux->fila_sem = NULL;
    p_aux->prox_desc = NULL;
    if(prim == NULL){
        prim = p_aux;
        p_aux->prox_desc = p_aux;
    }else{
        PTR_DESC_PROC p = prim;
        while(p->prox_desc != prim)
            p = p->prox_desc;
        p->prox_desc = p_aux;
    }
    p_aux->prox_desc = prim;
}

void far termina_processo(){
    disable();
    prim->estado = terminado;
    enable();
    while(1);
}

void far volta_dos(){
    disable();
    setvect(8,p_est->int_anterior);
    enable();
    exit(0);
}

PTR_DESC_PROC far procura_prox_ativo() {
    PTR_DESC_PROC prox_ativo = prim->prox_desc;
    while (prox_ativo != prim) {
        if (prox_ativo->estado == ativo) {
            return prox_ativo;
        }
        prox_ativo = prox_ativo->prox_desc;
    }
    return NULL;
}


void far primitiva_p(semaforo *sem){
    PTR_DESC_PROC p_aux;
    disable();
    if(sem->s > 0)
        sem->s--;
    else{
        prim->estado = bloq_p;/* muda o estado do processo corrente para bloqueado(bloq_p) */
        if(sem->Q == NULL)
            sem->Q = prim;
        else{
        	p_aux = sem->Q;
            while(p_aux->fila_sem != NULL)/*posiciona o ponteiro no ultimo elemento da fila*/
                p_aux = p_aux->fila_sem;
            p_aux->fila_sem = prim;/*insere o prim no final da fila Q*/
        }
        p_aux = prim;
        if((prim = procura_prox_ativo()) == NULL){
            volta_dos();
        }
        transfer(p_aux->contexto,prim->contexto);
    }
    enable();
}

void far primitiva_v(semaforo *sem){
    PTR_DESC_PROC p_aux;
    disable();
    if(sem->Q == NULL){
        sem->s++;
    }else{
        sem->Q->estado = ativo;
        p_aux = sem->Q;
        sem->Q = sem->Q->fila_sem;
        p_aux->fila_sem = NULL;
    }
    enable();
}

void far escalador(){
    p_est->p_origem = d_esc;                        
    p_est->p_destino = prim->contexto;
    p_est->num_vetor = 8;
    _AH=0x34;
    _AL=0x00;
    geninterrupt(0x21);
    a.x.bx1 = _BX;
    a.x.es1 = _ES;
    while(1){
        iotransfer();
        disable();
        if(!*a.y){
            if((prim = procura_prox_ativo()) == NULL)
                volta_dos();
            p_est->p_destino = prim->contexto;
        }                                   
        enable();
    }
}

void far inicia_sistema(){
    PTR_DESC d_aux;              
    d_esc = cria_desc();
    d_aux = cria_desc();
    newprocess(escalador,d_esc);
    transfer(d_aux,d_esc);
}