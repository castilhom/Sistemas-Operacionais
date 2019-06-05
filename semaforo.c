
    
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define N 1000

struct timespec t;

sem_t mutex, empty, full;

int buffer[N];
int posCheia;
int posVazia;
int qtdeDadosBuffer;

void *produtor(void*);
void *consumidor(void*);

int main(void){
    srand(time(NULL));

    qtdeDadosBuffer = 0;
    posCheia = 0;
    posVazia = 0;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);


    pthread_t p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

    pthread_create(&p1, 0, produtor, NULL);
    pthread_create(&p2, 0, produtor, NULL);
    pthread_create(&p3, 0, produtor, NULL);
    pthread_create(&p4, 0, produtor, NULL);
    pthread_create(&p5, 0, produtor, NULL);
    pthread_create(&p6, 0, consumidor, NULL);
    pthread_create(&p7, 0, consumidor, NULL);
    pthread_create(&p8, 0, consumidor, NULL);
    pthread_create(&p9, 0, consumidor, NULL);
    pthread_create(&p10, 0, consumidor, NULL);

    pthread_join(p1,0);
    pthread_join(p2,0);
    pthread_join(p3,0);
    pthread_join(p4,0);
    pthread_join(p5,0);
    pthread_join(p6,0);
    pthread_join(p7,0);
    pthread_join(p8,0);
    pthread_join(p9,0);
    pthread_join(p10,0);

    exit(0);
}

int inserir_item(int carga){
    int val;
    val = rand() % 10;
    printf("\n Produzindo: %d  \n Item %d esta sendo inserido", carga, val);
    return val;
}

void apagar_item(int carga, int item){
    printf("\n Consumindo: %d  \n Item %d esta sendo removido", carga, item);
}

void insert_item(int val){
    if(qtdeDadosBuffer < N){
        buffer[posVazia] = val;
        posVazia = (posVazia + 1) % N;
        qtdeDadosBuffer = qtdeDadosBuffer + 1;
    }      
}

int remove_item(){
    int val;
    if(qtdeDadosBuffer > 0){
        val = buffer[posCheia];
        posCheia = (posCheia + 1) % N;
        qtdeDadosBuffer = qtdeDadosBuffer - 1;
        return val;
    }
}

void *produtor(void *p_arg){
    int item;

    for(int i = 0; i <= 199;i++){
        item = inserir_item(i);

        sem_wait(&empty);
        sem_wait(&mutex);
        insert_item(item);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumidor(void *p_arg){
    int item;

    for(int i = 0; i <= 199;i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = remove_item();
        sem_post(&mutex);
        sem_post(&empty);
        apagar_item(item, i);

    }
}

