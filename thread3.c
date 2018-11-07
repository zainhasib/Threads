// Threading to find the sum and product of all elements of an array and pass it to parent for their overall // sum and display it.

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct node {
    int *p;
    int n;
};

int sum = 0;
int product = 1;

void * func1(void *p) {
    struct node * q = (struct node *)p;
    for(int i=0;i<q->n;i++) {
        sum += q->p[i];
    }
} 

void * func2(void *p) {
    struct node * q = p;
    for(int i=0;i<q->n;i++) {
        product *= q->p[q->n-1-i];
    }
} 

int main() {
    struct node n1, n2;
    pthread_t t1, t2;
    int arr[10] = {1,2,3,4,5,2,4,1,2,3};
    void **ret1;
    void **ret2;
    n1.p = arr;
    n1.n = 10;
    n2.p = arr;
    n2.n = 10;
    pthread_create(&t1, NULL, func1, (void *)&n1);
    pthread_create(&t2, NULL, func2, (void *)&n2);
    pthread_join(t1, ret1);
    pthread_join(t2, ret2);
    //sleep(1);
    printf("Total sum is : %d\n", sum + product);
    pthread_exit(&ret1);
    pthread_exit(&ret2);
    return 0;
}