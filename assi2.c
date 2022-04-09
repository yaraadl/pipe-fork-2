#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define MSG_SIZE 20
#define R 0
#define W 1

int main(){
int xx=0;
int *sum=&xx;
for(int i=0;i<10;i++){
int pipefd[2];
if(pipe(pipefd)<0){
perror("Pipe error:! \n");
exit(1);
}
//NO Errors
pid_t pid=fork();
if(pid<0){
perror("Fork Error!");
exit(1);
}
else if(pid == 0){
int  *number;
printf("Enter Number In Chiled:");
scanf("%d",&*number);
*sum=*sum+*number;
close(pipefd[R]);
write(pipefd[W],number,MSG_SIZE);
close(pipefd[W]);
}
else{
int x;
char in_buffer[MSG_SIZE];
close(pipefd[W]);
while(read(pipefd[R],in_buffer,MSG_SIZE) >0){
printf("Parent read data:\n");
x=(int)*in_buffer;
}
close(pipefd[R]);
wait(NULL);
if(i==9){
*sum=*sum+x;
printf("Sum = %d\n",*sum);
break;
}
else{
break;
}
}
}
return 0;
}
