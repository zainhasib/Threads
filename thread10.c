#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

pthread_mutex_t w, r;
int readcount = 0;

void * reader(void *p) {
    pthread_mutex_lock(&r);
    readcount++;
    if(readcount == 1) {
        pthread_mutex_lock(&w);
    }
    pthread_mutex_unlock(&r);
    // read
    FILE *fp;
    if((fp = fopen("sample.txt", "r+")) == NULL) {
        perror("File Open Error");
    }
    char ch;
    while((ch = getc(fp)) != EOF) {
        printf("%c", ch);
    }
    printf("\n");
    pthread_mutex_lock(&r);
    readcount--;
    if(readcount == 0) {
        pthread_mutex_unlock(&w);
    }
    pthread_mutex_unlock(&r);
}

void * writer(void *p) {
    pthread_mutex_lock(&w);
    // write
    FILE *fp;
    if((fp = fopen("sample.txt", "w+")) == NULL) {
        perror("File Open Error");
    }
    char str[20] = "Hello World";
    for(int i=0;i<strlen(str);i++) {
        putc(str[i], fp);
    }
    printf("\n");
    pthread_mutex_unlock(&w);
}

int main() {
    pthread_mutex_init(&w, NULL);
    pthread_mutex_init(&r, NULL);
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, reader, NULL);
    pthread_create(&t2, NULL, writer, NULL);
    pthread_create(&t3, NULL, reader, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    return 0;
}
