#include <stdio.h>
#include <stdlib.h>

int main()
{
	int process_count, resource_count;
	int choice;
	printf("Process count: ");
	scanf("%d", &process_count);
	printf("Request count: ");
	scanf("%d", &resource_count);
	int available[resource_count];
	int work[resource_count];
	int p_req;
	int max[process_count][resource_count];
	int allocated[process_count][resource_count];
	int need[process_count][resource_count];
	int request[resource_count];
	int finished[process_count];
	int safe_sequence[process_count];
	
	
	printf("Enter the available-array:\n");
	for (int i = 0; i < resource_count; ++i){
		printf("Enter the resource %d :",i+1);
		scanf("%d", &available[i]);
	}
	printf("Enter the max-array:\n");
	for (int i = 0; i < process_count; ++i) {
		for (int j = 0; j < resource_count; ++j){
			printf("Enter the process %d max %d: ",i,j+1);
			scanf("%d", &max[i][j]);
		}
		printf("\n");
	}
	
	printf("Enter the allocated-array:\n");
	for (int i = 0; i < process_count; ++i) {
		for (int j = 0; j < resource_count; ++j){
			printf("Enter the process %d alloc %d: ",i,j+1);
			scanf("%d", &allocated[i][j]);
		}
		printf("\n");
	}
	
	
	for (int i = 0; i < process_count; ++i) {
		for (int j = 0; j < resource_count; ++j) {	
				need[i][j]=max[i][j] - allocated[i][j];
				if(need[i][j] < 0){
					printf("\nDeadlock Detected\n");
					break;
				}
		}
	}
	
	for (int i = 0; i < resource_count; ++i)
		work[i] = available[i];
	
	for (int i = 0; i < process_count; ++i)
		finished[i] = 0;
	
	int skip_count = 0;
	int finish_count = 0;
	
	int resource_check;

	 do{
		printf("\nBankers Algorithm\n");
		printf("..........................\n");
		printf("\n1. Safety Algorithm\n2. Resource Request algorithm\n3. Exit\n");
		printf("...........................\n");
		printf("\nEnter the choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:	
				for (int i = 0; skip_count != process_count ; i = (i+1) % process_count) {
					if (finished[i] == 1) { 
						skip_count++; 
						continue; 
					}
					resource_check = 1;
					for (int j = 0; j < resource_count; ++j)
						resource_check = resource_check & (need[i][j] <= work[j]);
					
					if (resource_check == 0) {
					 	skip_count++; 
					 	continue;
					 }
					for (int j = 0; j < resource_count; ++j) {
						work[j] += allocated[i][j];
					}
					skip_count = 0;	
					finished[i] = 1;			
					safe_sequence[finish_count++] = i;
				}
				if (finish_count != process_count) {
					printf("Cannot generate safe-sequence!\n");
					printf("Deadlock Detected");
					break;
				}
				printf("Safe sequence: ");
				for (int i = 0; i < process_count; ++i)
					printf("P%d ", safe_sequence[i]);
				printf("\n");
				printf("Process\t\t\t\tMAX\t\t\t\tALLOC\t\t\t\tNEED\n");
				printf(".......................................................................................................\n");
				for(int i=0;i<process_count;i++){
					printf("P%d\t\t\t\t",i+1);
					for(int j=0;j<resource_count;j++)
						printf("%d",max[i][j]);
					printf("\t\t\t\t");
					for(int j=0;j<resource_count;j++)
						printf("%d",allocated[i][j]);
					printf("\t\t\t\t");
					for(int j=0;j<resource_count;j++)
						printf("%d",need[i][j]);
					printf("\n");
				}
				break;
				
			case 2: 
				printf("Enter the process that needs to request: \n");
				scanf("%d", &p_req);
				
				
				printf("Enter request-array: \n");
				for (int i = 0; i < resource_count; ++i) {
						printf("Enter resouce %d: ",i+1);
						scanf("%d", &request[i]);
					}
				int count=0;
				for(int j=0;j<resource_count;j++){
					if(request[j] <=need[p_req][j] && request[j] <=available[j])
						count++;
					else{
						printf("\nRequest not granted\n");
						break;
					}
				}
				if(count == resource_count){
					for(int j=0;j<resource_count;j++){
						available[j]=available[j]-request[j];
						allocated[p_req][j]=allocated[p_req][j]+request[j];
						need[p_req][j]=need[p_req][j]-request[j];
					}
					printf("\nRequest Granted\n");
				}
				break;
			
			case 3:
				printf("\nExiting\n");
				break;
			
			default: 
				printf("Enter a valid choice\n");
				break;
		}
	}while(choice!=3);
}
