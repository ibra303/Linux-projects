#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define N 10 
#define M 30
int Tmatrix[N][M];

//
void Error(char* msg){fprintf(stderr,"Error:%s\n",msg); exit(1);}

//
void* MakeIt(void* row1)
{
int row2 =*(int*)row1, i;
for(i=0;i<M;i++)
Tmatrix[row2][i]=rand() % 100;
}

//
void PrintMat(){
int row,columns;
for (row=0; row<N; row++)
{
printf("\n");
    for(columns=0; columns<M; columns++)
    {
         printf("%.2d ", Tmatrix[row][columns]);
    }
    printf("\n");
}}

//Main
int main(int argc,char* argv[])
{
int p1,i;
pthread_t thread[N];
int id1[N];
for(i=0;i<N;i++)
{
id1[i]=i;
if( ( p1 = pthread_create(&thread[i], NULL, MakeIt,(void*)&id1[i]) != 0 ))
            Error("no");
}
for (i=0;i<N;i++)
{
  pthread_join(thread[i], NULL );
}
PrintMat();
return 0;
} 
