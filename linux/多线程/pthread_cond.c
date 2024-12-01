#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

typedef struct Msg
{
    char* str;
    int x;
    int y;
} Msg;

static const int MAX_QUEUE_SIZE = 10;

Msg msg_queue[MAX_QUEUE_SIZE];

int queue_size = 0;

void* producer(void* arg)
{
    printf("producer create\n");
    while (1)
    {
        pthread_mutex_lock(&mutex);
        //printf("producer size %d\n", queue_size);
        while (queue_size >= MAX_QUEUE_SIZE)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        char str[20];
        snprintf(str, 20, "this is %dth msg", queue_size);
        printf("producer %s\n", str);
        Msg msg = {
            .str = str,
            .x = 0,
            .y = 0,
        };
        msg_queue[queue_size] = msg;
        queue_size++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    printf("consumer create\n");
    while (1)
    {
        pthread_mutex_lock(&mutex);
        //printf("consumer size %d\n", queue_size);
        while (queue_size <= 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        Msg msg = msg_queue[queue_size - 1];
        printf("msg[%d][%d]: %s\n", msg.x, msg.y, msg.str);
        queue_size--;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main()
{
    printf("hello\n");
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}

