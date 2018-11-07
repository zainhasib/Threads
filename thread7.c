// Semaphore

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

int counter = 0;
sem_t st;

void * func(void *p) {
    int *n = p;
    for(int i = 0;i<*n;i++) {
        sem_wait(&st);
        counter++;
        sem_post(&st); 
    }
}

int main() {
    pthread_t t1,t2;
    int a = 1000040;
    int b = 1000040;
    sem_init(&st, 0, 1);
    pthread_create(&t1, NULL, func, (void *)&a);
    pthread_create(&t2, NULL, func, (void *)&b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%d\n", counter);
    return 0;
}