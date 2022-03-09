#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

int number;
long int* counters;
void* func1();
void* func2(void* idx);
void Error(char* msg){fprintf(stderr,"Error:%s\n",msg); exit(1);}

int main(int argc,char* argv[])
{
if(argc < 2)
Error("Not Good");
//
number = atoi(argv[1]);
int i;
counters = (long int*)malloc(sizeof(long int) * number);
if ( !counters )
Error("malloc error");
  

pthread_t *p;
p = (pthread_t*)malloc(sizeof(pthread_t) * (number+1));
if ( !p )
Error("malloc error");

//creates
pthread_create(&p[number+1],NULL,func1,NULL);
for(i=0;i<number;i++){
counters[i]=0;
if (pthread_create(&p[i],NULL,func2,(void*)&counters[i])!=0){Error("thread error");}
}
sleep(20);
free(counters);
return 0;
}

// print counters every 2 sec
void* func1(void* arr){
int i,now;
while(now < 20){
printf("\nPrint number %d : \n",(now/2)+1);
now+=2;
for(i=0;i<number;i++){
printf("thread number %d can tell about counter now is: %ld\n",i+1,counters[i]);
}
sleep(2);
}
}
// as timelife for thread keep counter ++ 
void* func2(void* idx){
while(1)
*(int*)idx+=1;
}
