#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#define LEFT(i,N) (i+N-1)%N    //מקרו המגדיר את מספר השכן משמאל
#define RIGHT(i,N) (i+1)%N    //מקרו המגדיר את מספר השכן מימין
#define THINKING 0    //פפילוסוף אוכל
#define MAX_TIME 5    //זמן מקסימלי שמותר לבזבז על אוכל ו/או חשיבה
int N;    //מספר פילוסופיםילוסוף חושב
#define HUNGRY 1    //פילוסוף רעב (בהמתנה למקלות
#define EATING 2    //
sem_t *mutex = NULL; //מצביע לסמפור בינארי
sem_t *eaters = NULL;    //מערך סמפורים של פילוסופים
int* state = NULL;    //מערך שלמים לקביעת מצב פילוסוף (אוכל, רעב, חושב
// eating method
void eat(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is eating...\n", i + 1);
        sleep(time);
        printf("Philosopher #%d stopped eating...\n", i + 1);
}
//thinking method
void think(int i) {
        int time = rand() % MAX_TIME;
        printf("Philosopher #%d is thinking...\n", i + 1);
        sleep(time);
}
// if philosfer is hungry check if he can start eat
void test(int i) {
        if(state[i]==HUNGRY && state[LEFT(i,N)]!=EATING && state[RIGHT(i,N)]!=EATING){
        state[i]=EATING;    
        sem_post(&eaters[i]);
        }
}
void take_sticks(int i) {
        sem_wait(mutex); 
        state[i]=HUNGRY;        
        test(i); 
        sem_post(mutex); 
        if(state[i]!=EATING)
               sem_wait(&eaters[i]);// 
}
void put_sticks(int i) {
        sem_wait(mutex); 
        state[i]=THINKING;   
        test(LEFT(i,N)); 
        test(RIGHT(i,N)); 
        sem_post(mutex);
}

void* philosopher(void* arg) {
        int i = *((int*)arg);
        while (1 == 1) { 
               think(i); 
                take_sticks(i);
                eat(i); 
                put_sticks(i); 
        }
}
int main(int argc, char* argv[]) {
       void*  result;
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <NUMBER_OF_PHILOSOPHERS>\n", argv[0]);
                return 1;
        }
N = atoi(argv[1]); 
        if (N <= 1){fprintf(stderr,"Error by transformation of the argument...\n"); return 2;}

        mutex = (sem_t*)malloc(sizeof(sem_t));
        if (sem_init(mutex, 0, 1) != 0) { 
                fprintf(stderr, "Error by creating semaphore...\n");        return 3;
        }
eaters = (sem_t*)malloc(sizeof(sem_t)*N);
        state = (int*)malloc(sizeof(int)*3); 

        memset(state, 0, N);

        srand(time(NULL));
        pthread_t *philosophers = (pthread_t*)malloc(N * sizeof(pthread_t)); 
int i;
        for (i = 0; i < N; i++) {
                if (sem_init(&eaters[i], 0, 0) != 0) {  
                        fprintf(stderr, "Error by creating semaphore...\n");           return 3;
                }
        }
for (i = 0; i < N; i++) {
                if (pthread_create(&philosophers[i], NULL, philosopher, (void*)&i) != 0) {
                        fprintf(stderr, "Error by creating thread\n");            return 2;
                }
           usleep(100000);
       }
for (i = 0; i < N; i++) {
          if (pthread_join(philosophers[i], &result) != 0) {
fprintf(stderr, "Error by joining thread\n");
return 3;
          }
    }
    return 0;
}
