#include <stdio.h>
#include <stdlib.h>
#include <nucleo.h>

/*
Uma tribo de selvagens jantam juntos ao redor de um grande caldeirao contendo M porções de um ensopado de missionario cozido.
Quando um selvagem quer comer, ele se serve de uma porção no caldeirão, a não ser que o caldeirão esteja vazio. Se o caldeirão estiver vazio,
 o selvagem acorda o cozinheiro e então aguarda o cozinheiro completar novamente o caldeirão. Após encher o caldeirao, o cozinheiro retorna ao seu sono.
*/

#define M 10

int porcoes = 0;
semaforo mutex;
semaforo cald_vazio;
semaforo cald_cheio;
int caldeirao_vazio = 1;
FILE *arquivo;

/* abre o arquivo de saida */
void abrir_arquivo() {
    arquivo = fopen("jantselv.txt", "w");
    if (arquivo == NULL) {
        exit(1);
    }
}

/* fecha o arquivo de saida */
void fechar_arquivo() {
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}

/* enche o caldeirão */
void encher_caldeirao() {
    porcoes += M;
    caldeirao_vazio = 0;
    fprintf(arquivo, "Cozinheiro levanta e enche o caldeirao com %d porções de missionario.\n", M);
}

/* simula o cozinheiro dormindo */
void dormir() {
    fprintf(arquivo, "Cozinheiro esta dormindo.\n");
}

/* acorda o cozinheiro */
void acorda_cozinheiro() {
    fprintf(arquivo, "Selvagem ficou sem comida e acordou o cozinheiro.\n");
}

/* simula o selvagem comendo */
void comer() {
    fprintf(arquivo, "Selvagem esta comendo.\n");
}

/* Cozinheiro (produtor) */
void far cozinheiro() {
    while (1) {
        primitiva_p(&cald_vazio);  /* espera o caldeirão ficar vazio */
        primitiva_p(&mutex);       /* entra na região critica */
        if (porcoes == 0) {
            encher_caldeirao();    /* enche o caldeirão somente se estiver vazio */
        }
        primitiva_v(&mutex);       /* sai da região critica */
        primitiva_v(&cald_cheio);  /* avisa que o caldeirão esta cheio */
        dormir();                  /* cozinheiro volta a dormir */
    }
    termina_processo();
}

/* Selvagem (consumidor) */
void far selvagem() {
    int i = 0;
    while (i < 50) {
        primitiva_p(&mutex);       /* entra na região critica */
        if (porcoes == 0) {
            if (!caldeirao_vazio) {
                caldeirao_vazio = 1; /* flag para sinalizar selvagem vendo o caldeirão vazio */
                acorda_cozinheiro(); /* acorda o cozinheiro se o caldeirão estiver vazio */
                primitiva_v(&mutex); /* sai da região critica */
                primitiva_p(&cald_cheio); /* espera o caldeirão ser cheio pelo cozinheiro */
                primitiva_v(&cald_vazio); /* avisa que o caldeirão esta vazio */
            } else {
                primitiva_v(&mutex); /* caso de não ser o ultimo selvagem comendo */
                primitiva_p(&cald_cheio); /* aguarda o caldeirão ter comida para nao ter conflito com o cozinheiro */
                primitiva_v(&cald_vazio); /* avisa que o caldeirão está vazio */
            }
        } else {
            porcoes--;
            fprintf(arquivo, "Selvagem se serviu. Restam: %d porcoes\n", porcoes);
            comer();               /* selvagem come */
            primitiva_v(&mutex);   /* sai de vez da região critica */
        }
        i++;
    }
    termina_processo();
}


main() {
    abrir_arquivo();

    inicia_fila();
    inicia_semaforo(&mutex, 1);
    inicia_semaforo(&cald_vazio, M);
    inicia_semaforo(&cald_cheio, 0);

    cria_processo("Cozinheiro", cozinheiro);
    cria_processo("Selvagem", selvagem);

    inicia_sistema();
}
