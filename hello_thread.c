#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *vagrs);
void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
void Pthread_join(pthread_t thread, void **value_ptr);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
    Pthread_join(tid, NULL);
    exit(0);
}

void *thread(void *vargs)
{
    printf("Hello, world!\n");
    return NULL;
}

void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    int res;
    if ((res = pthread_create(thread, attr, start_routine, arg)) != 0)
        perror("pthread_create");
}

void Pthread_join(pthread_t thread, void **value_ptr)
{
    int res;
    if ((res = pthread_join(thread, value_ptr)) != 0)
        perror("pthread_join");
}