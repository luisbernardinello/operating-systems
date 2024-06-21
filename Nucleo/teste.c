/* teste.c */
#include <nucleo.h> 
#include <stdio.h>

void far processo1() {
	
	int i = 0;
	while (i < 10000) {
		printf("processo 1 ");
		i++;
	}
	
	termina_processo();
}


void far processo2() { 

	int i = 0;
	while (i < 10000) {
		printf("processo 2 ");
		i++;
	}
	
	termina_processo();
}


void far processo3() {
	
	int i = 0;
	while (i < 10000) {
		printf("processo 3 ");
		i++;
	}
		
	termina_processo();
}

int main () {
	
	cria_processo("p1", processo1);
	cria_processo("p2", processo2);
	cria_processo("p3", processo3);
	
	inicia_sistema();	
}



