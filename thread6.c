// Mutex in threading 

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int counter = 0;
pthread_mutex_t mt;

void * func(void *p) {
    int *n = p;
    for(int i = 0;i<*n;i++) {
        pthread_mutex_lock(&mt);
        counter++;
        pthread_mutex_unlock(&mt); 
    }
}

int main() {
    pthread_t t1,t2;
    int a = 1000040;
    int b = 1000040;
    pthread_mutex_init(&mt, NULL);
    pthread_create(&t1, NULL, func, (void *)&a);
    pthread_create(&t2, NULL, func, (void *)&b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%d\n", counter);
    return 0;
}