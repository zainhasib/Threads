// Peterson's Algo

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int counter = 0;
int flag[2] = {0,0};
int turn; 

void * func1(void *p) {
    int *n = p;
    for(int i = 0;i<*n;i++) {
        flag[0] = 1;
        turn = 1;
        while(flag[1] && turn==1);
        counter++;
        flag[0] = 0;
    }
}

void * func2(void *p) {
    int *n = p;
    for(int i = 0;i<*n;i++) {
        flag[1] = 1;
        turn = 0;
        while(flag[0] && turn==0);
        counter++;
        flag[1] = 0;
    }
}

int main() {
    pthread_t t1,t2;
    int a = 100200;
    int b = 100800;
    pthread_create(&t1, NULL, func1, (void *)&a);
    pthread_create(&t2, NULL, func2, (void *)&b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%d\n", counter);
    return 0;
}