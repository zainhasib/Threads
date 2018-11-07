// Threading to print array in normal and reverse order using two different threads

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct node {
    int *p;
    int n;
};

void * func1(void *p) {
    struct node * q = (struct node *)p;
    for(int i=0;i<q->n;i++) {
        printf("Normal : %d\n", q->p[i]);
    }
} 

void * func2(void *p) {
    struct node * q = p;
    for(int i=0;i<q->n;i++) {
        printf("Reverse : %d\n", q->p[q->n-1-i]);
    }
} 

int main() {
    struct node n1, n2;
    pthread_t t1, t2;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    n1.p = arr;
    n1.n = 10;
    n2.p = arr;
    n2.n = 10;
    pthread_create(&t1, NULL, func1, (void *)&n1);
    pthread_create(&t1, NULL, func2, (void *)&n2);
    sleep(1);
    return 0;
}