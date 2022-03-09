#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include<stdlib.h>
void Error(char* msg){fprintf(stderr,"Error:%s\n",msg); exit(1);}
sem_t sem0,sem1,sem2,sem3,main1;
//Calls make the connection
void Calls(int City1, int City2){
sem_wait(&main1);// no connections is allowed until Calls function is made the write connection
if((City1 == 2 || City2 == 3) &&  (City1 == 3 || City2 == 2)) { // if the connection is between haifa and tsfat
sem_wait(&sem0);
sem_wait(&sem1);
sem_wait(&sem2);
sem_wait(&sem3);}
else{
if(City1==0||City2==0)
sem_wait(&sem0);
if(City1==1||City2==1)
sem_wait(&sem1);
if(City1==2||City2==2)
sem_wait(&sem2);
if(City1==3||City2==3)
sem_wait(&sem3);
}
sem_post(&main1);
printf("%d started to talk with %d\n", City1, City2);
sleep(1); 
printf("%d finished to talk with %d\n", City1, City2);
if((City1 == 2 || City2 == 3) &&  (City1 == 3 || City2 == 2)) {// if the connection is between haifa and tsfat
sem_post(&sem0);
sem_post(&sem1);
sem_post(&sem2);
sem_post(&sem3);}
else{
if(City1==0||City2==0)
sem_post(&sem0);
if(City1==1||City2==1)
sem_post(&sem1);
if(City1==2||City2==2)
sem_post(&sem2);
if(City1==3||City2==3)
sem_post(&sem3);
}
}
//
void *Func(void* City){
int city =*(int*)City;
while(1){
int pick = rand()%4;
while(city == pick)// city can not make connection with it self
pick = rand()%4;
Calls(city,pick);
}
}
//
int main(){
sem_init(&main1,0,1);
sem_init(&sem0,0,1);
sem_init(&sem1,0,1);
sem_init(&sem2,0,1);
sem_init(&sem3,0,1);
pthread_t sec[4];
int secIndex[4],i;
for(i=0;i<4;i++){
secIndex[i]=i;
if(pthread_create(&sec[i], NULL, Func,(void*)&secIndex[i])!=0)
Error("thread fail"); 
}
sleep(20);
return 0;
}



