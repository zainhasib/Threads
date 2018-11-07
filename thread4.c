// Merge Sort using threading recursion

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int arr[] = {9,6,7,4,10,15,20,25};
int sum = 0;
int newarr[8];

int s1 = 0, s2 = 0;

struct node {
    int a;
    int b;
};

void merge(int l, int mid, int h) {
    int p=0;
    int i=0,j=0;
    for(i=l, j=mid; i<mid && j<h;) {
        if(arr[i] < arr[j]) {
            newarr[p++] = arr[i++];
        }else {
            newarr[p++] = arr[j++];
        }
    }
    while(i<mid) {
        newarr[p++] = arr[i++];
    }
    while(j<h) {
        newarr[p++] = arr[j++];
    }
    for(int t=l;t<p;t++) {
        arr[t] = newarr[t];
    }
}

void * add(void *p) {
    struct node *n = p;
    if(n->a < n->b) {
        int mid = (n->a+n->b)/2;
        pthread_t p1, p2;
        struct node n1;
        n1.a = n->a;
        n1.b = mid;
        pthread_create(&p1, NULL, add, (void *)&n1);
        struct node n2;
        n2.a = mid+1;
        n2.b = n->b;
        pthread_create(&p2, NULL, add, (void *)&n2);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
        merge(n->a, mid, n->b);
    } 
}

int main() {
    pthread_t p;
    struct node n;
    n.a = 0;
    n.b = 7;
    pthread_create(&p, NULL, add, (void *)&n);
    pthread_join(p, NULL);
    printf("The array is : \n");
    for(int i=0;i<8;i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}