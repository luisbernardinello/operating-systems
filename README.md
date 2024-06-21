![Unesp](https://img.shields.io/badge/BCC-UNESP-Bauru.svg)
![License](https://img.shields.io/badge/Code%20License-MIT-blue.svg)
# Operating Systems :cyclone::cyclone:

![operating-systems](https://socialify.git.ci/luisbernardinello/operating-systems/image?description=1&font=Rokkitt&language=1&name=1&owner=1&pattern=Floating%20Cogs&theme=Light)

## :telescope: What will you find? :telescope:

This repository contains a C language microkernel project


<br>


## Highlights:

1. **MS-DOS files in TC directory with TurboC Compiler.**
2. **Microkernel program to simulate Round-robin algorithm.**
3. **The dining savage problem.**



### (PT) Resumo em Português

Este projeto implementa um núcleo de um sistema operacional para o DOS que permite a multiprogramação usando o algoritmo Round Robin. O DOS, por ser monoprogramado por natureza, não possui suporte nativo à multiprogramação. Este núcleo, quando executado no DOS, permite que vários processos sejam escalonados de maneira aparente simultânea (multiparalelismo aparente). O projeto utiliza DOSBox e Turbo C como compilador.

O objetivo deste projeto é criar um sistema operacional básico que permita a execução de múltiplos processos de forma alternada, utilizando o algoritmo de escalonamento Round Robin proporcionando um ambiente multiprogramado no DOS.

Esta documentação serve para auxiliar outros alunos que possam ter alguma dificuldade durante o desenvolvimento de um núcleo multiprogramado para o DOS.


## Núcleo

### Arquivos na pasta Núcleo

1. Arquivos referentes ao programa `prco_ex.c` no qual foi aplicado o caso clássico de produtor-consumidor conhecido como o "Jantar dos Selvagens". Para esse programa pertencem os seguintes arquivos: `prco_ex.exe`, `prco_ex.obj`, `prco_ex.prj` e `jantselv.txt`.
2. Arquivos referentes ao programa `teste.c`. Para esse programa pertencem os seguintes arquivos: `teste.exe`, `teste.obj`, `teste.prj`.
3. Arquivos referentes ao `nucleo.c` no qual foi desenvolvido o núcleo propriamente dito. Para esse programa pertencem os seguintes arquivos: `nucleo.obj`, `nucleo.h`.

### Arquivos na pasta Exercs

1. Arquivos referentes ao programa `esc_co.c` no qual foi aplicado o caso de teste para o Algoritmo Escalonador. Para esse programa pertencem os seguintes arquivos: `esc_co.exe`, `esc_co.obj`, `esc_co.prj`.
2. Arquivos referentes ao programa `tictac_m.c` no qual foi aplicado o caso de teste para a função transfer, limitada por um intervalo desejado. Para esse programa pertencem os seguintes arquivos: `tictac_m.exe`, `tictac_m.obj`, `tictac_m.prj`.
3. Arquivos referentes ao programa `tictac.c` no qual de modo análogo ao caso do arquivo `tictac_m.c` se trata de um caso de teste para o transfer, porém sem a limitação de intervalo. Para esse programa pertencem os seguintes arquivos: `tictac.exe`, `tictac.obj`, `tictac.prj`.




## Detalhamento do diretório Núcleo


### PRCO_EX.C

O problema a seguir advém do livro **"Concurrent Programming"** (Gregory R. Andrews. Concurrent Programming: Principles and Practice. Addison-Wesley, 1991.) e se trata de uma implementação adaptada ao presente núcleo desenvolvido.

O problema recebe o título de **"O problema do jantar dos selvagens"** (The dining savage problem).

A seguir é apresentada uma breve descrição do problema:

"Uma tribo de selvagens jantam juntos ao redor de um grande caldeirão contendo M porções de um ensopado de missionário cozido. Quando um selvagem quer comer, ele se serve de uma porção no caldeirão, a não ser que o caldeirão esteja vazio. Se o caldeirão estiver vazio, o selvagem acorda o cozinheiro e então aguarda o cozinheiro completar novamente o caldeirão. Após encher o caldeirão, o cozinheiro retorna ao seu sono". (tradução livre).

#### definição de constante:


~~~
#define M 10
~~~


Definição da constante `M` como 10, que representa a capacidade do caldeirão, ou seja, o número de porções de comida que o caldeirão pode conter.

#### variáveis globais:

~~~
int porcoes = 0;
semaforo mutex;
semaforo cald_vazio;
semaforo cald_cheio;
int caldeirao_vazio = 1;
~~~


Define as variáveis globais que serão usadas no programa. `porcoes` armazena o número de porções no caldeirão e é inicializada como 0. `mutex` é o semáforo para exclusão mútua. `cald_vazio` e `cald_cheio` são semáforos para controlar o estado do caldeirão. `caldeirao_vazio` se trata de uma flag que indica se o selvagem vê o caldeirão vazio.

#### abrir_arquivo:


~~~
void abrir_arquivo() {
arquivo = fopen("jantselv.txt", "w");
if (arquivo == NULL) {
exit(1);
}
}
~~~


A função `abrir_arquivo` abre o arquivo `jantselv.txt` para escrita. Se a abertura do arquivo vier a falhar, o programa é encerrado.

#### fechar_arquivo:

~~~
void fechar_arquivo() {
if (arquivo != NULL) {
fclose(arquivo);
}
}
~~~


A função `fechar_arquivo` por sua vez fecha o arquivo de saída se ele estiver aberto.

#### encher_caldeirao:

~~~
void encher_caldeirao() {
porcoes += M;
caldeirao_vazio = 0;
fprintf(arquivo, "Cozinheiro levanta e enche o caldeirao com %d porções de missionario.\n", M);
}
~~~


A função `encher_caldeirao` enche o caldeirão com `M` porções e define a flag `caldeirao_vazio` como 0. Também grava a mensagem da ação que está ocorrendo no arquivo de saída.

#### dormir:

~~~
void dormir() {
fprintf(arquivo, "Cozinheiro esta dormindo.\n");
}
~~~


A função `dormir` simula o cozinheiro dormindo, grava a mensagem de ação de dormir no arquivo de saída.

#### acorda_cozinheiro:

~~~
void acorda_cozinheiro() {
fprintf(arquivo, "Selvagem ficou sem comida e acordou o cozinheiro.\n");
}
~~~


A função `acorda_cozinheiro` simula o ato do selvagem estar sem comida e acordar o cozinheiro porque viu que o caldeirão está vazio. Ela grava a mensagem de ação de ficar sem comida e acordar o cozinheiro no arquivo de saída.

#### comer:

~~~
void comer() {
fprintf(arquivo, "Selvagem esta comendo.\n");
}
~~~


A função `comer` grava no arquivo de saída a ação de que um selvagem está comendo.

#### cozinheiro:


~~~
void far cozinheiro() {
while (1) {
primitiva_p(&cald_vazio); /* espera o caldeirao ficar vazio /
primitiva_p(&mutex); / entra na regiao critica /
if (porcoes == 0) {
encher_caldeirao(); / enche o caldeirao somente se estiver vazio /
}
primitiva_v(&mutex); / sai da regiao critica /
primitiva_v(&cald_cheio); / avisa que o caldeirao esta cheio /
dormir(); / cozinheiro volta a dormir */
}
termina_processo();
}
~~~


A função `cozinheiro` representa o processo produtor no produtor-consumidor, neste problema representa o cozinheiro, que enche o caldeirão quando ele está vazio. O cozinheiro espera até que o caldeirão esteja vazio usando `primitiva_p` no semáforo `cald_vazio`, entra na seção crítica com `primitiva_p` no semáforo `mutex`, e enche o caldeirão se ele estiver vazio. Depois disso, sai da região crítica com `primitiva_v` no semáforo `mutex`, sinaliza que o caldeirão está cheio com `primitiva_v` no semáforo `cald_cheio`, e por fim volta a dormir.

#### selvagem:

~~~
void far selvagem() {
int i = 0;
while (i < 50) {
primitiva_p(&mutex); /* entra na regiao critica /
if (porcoes == 0) {
if (!caldeirao_vazio) {
caldeirao_vazio = 1; / flag para sinalizar selvagem vendo o caldeirao vazio /
acorda_cozinheiro(); / acorda o cozinheiro se o caldeirao estiver vazio /
primitiva_v(&mutex); / sai da regiao critica /
primitiva_p(&cald_cheio); / espera o caldeirao ser cheio pelo cozinheiro /
primitiva_v(&cald_vazio); / avisa que o caldeirao esta vazio /
} else {
primitiva_v(&mutex); / caso de nao ser o ultimo selvagem comendo /
primitiva_p(&cald_cheio); / aguarda o caldeirao ter comida para nao ter conflito com o cozinheiro /
primitiva_v(&cald_vazio); / avisa que o caldeirao esta vazio /
}
} else {
porcoes--;
fprintf(arquivo, "Selvagem se serviu. Restam: %d porcoes\n", porcoes);
comer(); / selvagem come /
primitiva_v(&mutex); / sai de vez da regiao critica */
}
i++;
}
termina_processo();
}
~~~


A função `selvagem` representa o processo consumidor no produtor-consumidor. Neste problema ela representa os selvagens, que consomem as porções do caldeirão. O selvagem entra na região crítica com `primitiva_p` no semáforo `mutex`. Se o caldeirão estiver vazio e a flag `caldeirao_vazio` não estiver definida, a flag é alterada (selvagem viu caldeirão vazio), acorda o cozinheiro com `acorda_cozinheiro`, sai da seção crítica com `primitiva_v` no semáforo `mutex`, e espera o caldeirão ser enchido com `primitiva_p` no semáforo `cald_cheio`, depois avisa que o caldeirão está vazio com `primitiva_v` no semáforo `cald_vazio`. Se o caldeirão não estiver vazio, o selvagem então decrementa o número de porções de ensopado de missionário, grava a ação (mensagem) no arquivo de saída, come com a função `comer`, e por fim sai da região crítica com `primitiva_v` no semáforo `mutex`.



### NUCLEO.C

#### descritor_proc:

~~~ typedef struct desc_p {
char nome[35];
struct desc_p *fila_sem;
struct desc_p *prox_desc;
PTR_DESC contexto;
enum { ativo, bloq_p, terminado } estado;
} DESCRITOR_PROC;

typedef DESCRITOR_PROC *PTR_DESC_PROC;
~~~

O descritor de processo se trata de uma estrutura usada para armazenar as informações que são necessárias para gerenciar os processos. O nome do processo é armazenado em `nome`, enquanto `fila_sem` e `prox_desc` são os ponteiros que permitem a organização dos processos nas filas. O contexto do processo, que inclui o estado, é armazenado em `contexto`, e o estado atual do processo é mantido em `estado`, que pode ser ativo, bloqueado ou terminado.

#### semaforo:

```
typedef struct {
int s;
PTR_DESC_PROC Q;
} semaforo;
```


A estrutura de semáforo foi utilizada para a sincronização entre os processos. O campo `s` se trata de um contador que indica o número de recursos que estão disponíveis, enquanto `Q` é uma fila referente aos processos que estão bloqueados esperando pelo semáforo.

#### aponta_reg_crit:


~~~
typedef struct {
unsigned bx1, es1;
} regis;

typedef union k {
regis x;
char far *y;
} APONTA_REG_CRIT;

APONTA_REG_CRIT a;
~~~


A estrutura `regis` armazena registros utilizados no contexto do núcleo do sistema operacional. A união `aponta_reg_crit` utilizada permite acessá-los, o que facilita a manipulação dos mesmos durante a execução do núcleo do SO.

#### inicia_semaforo:

~~~
void far inicia_semaforo(semaforo *sem, int n) {
sem->s = n;
sem->Q = NULL;
}
~~~


A função `inicia_semaforo` executa a inicialização de um semáforo com um valor inicial `n`. O contador do semáforo `s` é definido com o valor `n` e a fila de processos `Q` é inicializada como nula.

#### inicia_fila:

~~~
void far inicia_fila() {
prim = NULL;
}
~~~


A função `inicia_fila` se trata de uma função auxiliar que inicializa a fila de processos, definindo o ponteiro para o primeiro `prim` como nulo.

#### cria_processo:

~~~
void far cria_processo(char nomeP[35], void far (*proc)()) {
PTR_DESC_PROC p_aux;
p_aux = (PTR_DESC_PROC)malloc(sizeof(struct desc_p));
strcpy(p_aux->nome, nomeP);
p_aux->estado = ativo;
p_aux->contexto = cria_desc();
newprocess(proc, p_aux->contexto);
p_aux->fila_sem = NULL;
p_aux->prox_desc = NULL;
if (prim == NULL) {
prim = p_aux;
p_aux->prox_desc = p_aux;
} else {
PTR_DESC_PROC p = prim;
while (p->prox_desc != prim)
p = p->prox_desc;
p->prox_desc = p_aux;
}
p_aux->prox_desc = prim;
}
~~~


A função `cria_processo` cria um novo processo com o nome `nomeP` e a função `proc`. Um novo descritor de processo é alocado dinamicamente e inicializado com o nome e estado do processo. O contexto do processo é criado e a função do processo é associada a ele. Por fim, O descritor do novo processo adicionado na fila de processos.

#### termina_processo:

~~~
void far termina_processo() {
disable();
prim->estado = terminado;
enable();
while (1);
}
~~~


A função `termina_processo` tem a função de terminar o processo atual. O estado do processo atual da fila (que contém `prim`) é definido como terminado e é feito um loop infinito, aguardando que o escalonador selecione outro processo.

#### procura_prox_ativo:

~~~
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
~~~


A função `procura_prox_ativo` procura o próximo processo ativo na fila de processos. Ele percorre a lista de descritores de processo começando do processo atual até o momento que encontra um processo com o estado ativo. No caso de nenhum processo ativo ser encontrado, a função retorna nulo.

#### primitiva_p:

~~~
void far primitiva_p(semaforo sem) {
PTR_DESC_PROC p_aux;
disable();
if (sem->s > 0) {
sem->s--;
} else {
prim->estado = bloq_p; / muda o estado do processo corrente para bloqueado (bloq_p) /
if (sem->Q == NULL) {
sem->Q = prim;
} else {
p_aux = sem->Q;
while (p_aux->fila_sem != NULL) / posiciona o ponteiro no ultimo elemento da fila /
p_aux = p_aux->fila_sem;
p_aux->fila_sem = prim; / insere o prim no final da fila Q */
}
p_aux = prim;
if ((prim = procura_prox_ativo()) == NULL) {
volta_dos();
}
transfer(p_aux->contexto, prim->contexto);
}
enable();
}
~~~


A função `primitiva_p` implementa a operação de semáforo conhecida como `P (down)`. Se o contador do semáforo `s` for maior que 0, ele é então decrementado. Caso não seja, o estado do processo atual é alterado para bloqueado e o processo é adicionado na fila de espera do semáforo. O próximo processo ativo é então selecionado e o contexto é transferido para ele.

#### primitiva_v:


~~~
void far primitiva_v(semaforo *sem) {
PTR_DESC_PROC p_aux;
disable();
if (sem->Q == NULL) {
sem->s++;
} else {
sem->Q->estado = ativo;
p_aux = sem->Q;
sem->Q = sem->Q->fila_sem;
p_aux->fila_sem = NULL;
}
enable();
}
~~~


A função `primitiva_v` implementa a operação `V (up)` do semáforo. Se a fila de espera do semáforo `Q` estiver vazia, o contador do semáforo `s` é incrementado. Caso contrário, o primeiro processo na fila de espera é definido como ativo e removido da fila.

#### escalador:

~~~
void far escalador() {
p_est->p_origem = d_esc;
p_est->p_destino = prim->contexto;
p_est->num_vetor = 8;
_AH = 0x34;
_AL = 0x00;
geninterrupt(0x21);
a.x.bx1 = _BX;
a.x.es1 = _ES;
while (1) {
iotransfer();
disable();
if (!*a.y) {
if ((prim = procura_prox_ativo()) == NULL)
volta_dos();
p_est->p_destino = prim->contexto;
}
enable();
}
}
~~~


A função `escalador` se trata da função principal que implementa a técnica conhecida como Round Robin. O escalonador gerencia a troca de contexto entre os processos para ocorrer a cada 55 milisegundos (interrupção 8). Ela configura o ambiente para ser feita a troca de contexto e transfere então o controle para o próximo processo ativo. No caso de nenhum processo ativo ser encontrado, o sistema retorna ao DOS.

#### inicia_sistema:

~~~
void far inicia_sistema() {
PTR_DESC d_aux;
d_esc = cria_desc();
d_aux = cria_desc();
newprocess(escalador, d_esc);
transfer(d_aux, d_esc);
}
~~~


A função `inicia_sistema` é responsável por inicializar o sistema e cria o processo do escalonador. O nome se trata de uma abstração para os programas de usuário. Ela inicializa os descritores de processo e transfere o controle para o escalonador.

#### volta_dos:


A função `volta_dos` é responsável por retornar ao DOS quando não há mais processos ativos (visto no escalonador).






---

### References
- [1] Tanenbaum. Operating Systems
- [2] Gregory R. Andrews. Concurrent Programming



---
