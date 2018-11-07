// Addition using threading, recursion and divide and conqueror rule

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int arr[8] = {9,6,7,4,10,15,20,25};

struct node {
    int a;
    int b;
};

int s = 0;


void * add(void *p) {
    struct node *n = p;
    if(n->a == n->b) {
        s += arr[n->a];
    }else if(n->a - n->b == 1) {
        s += arr[n->a] + arr[n->b];
    }else if(n->a < n->b) {
        int mid = (n->a + n->b) /2;
        pthread_t p1, p2;
        struct node n1;
        n1.a = n->a;
        n1.b = mid;
        pthread_create(&p1, NULL, add, (void *)&n1);
        struct node n2;
        n2.a = mid + 1;
        n2.b = n->b;
        pthread_create(&p2, NULL, add, (void *)&n2);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
    }
}

int main() {
    pthread_t p;
    struct node n;
    n.a = 0;
    n.b = 7;
    pthread_create(&p, NULL, add, (void *)&n);
    pthread_join(p, NULL);
    printf("%d\n", s);
    return 0;
}