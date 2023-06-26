

#include <stdio.h>
#include <unistd.h>
//#include <sys/wait.h>
#define size 10
int main(){
	int pipe1[2],pipe2[2],pipe3[2];
	pid_t p2,p3;
	if(pipe(pipe1) == -1 || pipe(pipe2)== -1 || pipe(pipe3) == -1){
		printf("\nPipe Failed");
		return 1;
	}
	p2=fork();
	if(p2<0){
		printf("Fork failed");
		return 2;
	}
	else if(p2==0){
		int values[size];
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe3[0]);
		close(pipe3[1]);
		while(read(pipe1[0],values,sizeof(int)*size) <=0);
		printf("\nProcess 2\n");
		printf(".....................\n");
		printf("\nReading from pipe1\n");
		printf("\nThe integers stored in pipe1 are: ");
		for(int i=1;i<=values[0];i++){
			printf("%d   ",values[i]);
			values[i]=values[i]*values[i];
		}
		
		write(pipe2[1],&values,sizeof(int)*size);
		printf("\nWritting to pipe2\n");
		close(pipe1[0]);
		close(pipe2[1]);
		return 3;
	}
	p3=fork();
	if(p3<0){
		printf("Fork failed");
		return 2; 
	}
	else if(p3==0){
		int values[size],sum=0;
		
		while(read(pipe2[0],values,sizeof(int)*size) <=0);
		printf("\nProcess 3\n");
		printf(".....................\n");
		printf("\nReading from pipe2\n");
		printf("\nThe integers stored in pipe2 are: ");
		for(int i=1;i<=values[0];i++){
			printf("%d   ",values[i]);
			sum+=values[i];
		}
		//printf("\nSum is: %d",sum);
		
		write(pipe3[1],&sum,sizeof(int));
		printf("\nWritting to pipe3\n");
		close(pipe2[0]);
		close(pipe3[1]);
		return 3;
	}
	close(pipe1[0]);
	close(pipe2[0]);
	close(pipe2[1]);
	close(pipe3[1]);
	
	int values[size],sum;
	printf("\nProcess 1\n");
	printf(".....................\n");
	printf("\nEnter the number of inputs: ");
	scanf("%d",&values[0]);
	for(int i=1;i<=values[0];i++){
		printf("Enter the integer %d: ",i);
		scanf("%d",&values[i]);
	}
	write(pipe1[1],values,sizeof(int)*size);
	printf("\nWritting to pipe1\n");
	wait(NULL);
	wait(NULL);
	printf("\nProcess 1\n");
	printf(".....................\n");
	read(pipe3[0],&sum,sizeof(int));
	printf("\nReading from pipe3\n");
	printf("\nThe sum stored in pipe3 is: %d\n",sum);
	close(pipe1[1]);
	close(pipe3[0]);
	return 0;
}
			
				
