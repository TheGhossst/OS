#include <stdio.h>

#define max 20
int n,m,i,j,pg[max],fr[max],time[max],min;
int fifo(){
	int found,k=0,count=0;
	for(i=0;i<m;i++)	fr[i]=-1;
	printf("\nReference String\t\t\tFrame\t\t\tStatus\n");
	printf("..........................................................................\n");
	for(i=0;i<n;i++){
		found=0;
		printf("%d ",pg[i]);
		for(j=0;j<m;j++){
			if(fr[j] == pg[i])	found=1;
		}
		if(found == 0){
			fr[k]=pg[i];
			k=(k+1)%m;
			count++;
		}
		printf("\t\t\t\t\t");
		for(j=0;j<m;j++){
			if(fr[j] != -1)	printf("%d ",fr[j]);
		}
		if(found == 1)	printf("\t\t\tHit\n");
		else 	printf("\t\t\tMiss\n");
	}
	printf("\nThe number of page faults are : %d\n",count);
	float hitratio=100*((float)(n-count)/(float)n);
	printf("\nThe hit ratio is : %0.2f",hitratio);
}

int lru(){
	int k,flag,hit=0,miss=0,found=0;
	for(i=0;i<m;i++)	fr[i]=-1;
	printf("\nReference String\tFRAME\t\t\t\tSTATUS\n");
	printf("..........................................................................\n");
	for(i=0;i<n;i++){
		flag=1;
		printf("\n%d\t\t\t",pg[i]);
		for(j=0;j<m;j++){
			if(pg[i]==fr[j]){
				//printf("\nHIT\t");
				found=1;
				hit++;
				flag=0;
				for(k=j;k > 0;k--) fr[k]=fr[k-1];
				fr[0]=pg[i];
				break;
			}
		}
		if(flag){
			//printf("\nMISS\t");
			found =0;
			miss++;
			for(j=m-1;j>0;j--)	fr[j]=fr[j-1];
			fr[0]=pg[i];
			
		}
		for(j=0;j<m;j++){
			if(fr[j]!=-1)	printf("%d ",fr[j]);
		}
		if(found==1)	printf("\t\t\t\t\tHIT");
		else  printf("\t\t\t\t\tMISS");
	}
	printf("\n");
	printf("\nThe total page faults are: %d",miss);
	//float hit_ratio = miss/n;
	float hit_ratio=100*((float)(hit)/(float)n);
	printf("\nThe hit ratio is : %0.2f",hit_ratio);
}
void optimal(){
	int init=0,check[max];
	int k,flag,hit=0,miss=0,stats,found=0;
	for(i=0;i<m;i++)	check[i]=0;
	for(i=0;i<m;i++)	fr[i]=-1;
	printf("\nReference String\tFRAME\t\t\t\tSTATUS\n");
	printf("..........................................................................\n");
	for(i=0;i<n;i++){
		flag=1;
		printf("\n%d\t\t\t",pg[i]);
		for(j=0;j<m;j++){
			if(pg[i]==fr[j]){
				//printf("\nHIT\t");
				found=1;
				hit++;
				flag =0;
				break;
			}
		}
		if(flag){
			//printf("\nMISS\t");
			found=0;
			miss++;
			stats=m-1;
			if(init < m) fr[init++] = pg[i];
			else{
				for(j=i+1;j<n,stats==0;j++){
					for(k=0;k<m;k++){
						if(pg[i] == fr[k] && check[k]!=1){
							check[k]=1;
							stats--;
							break;
							
						}
					}
				}
			}
			for(j=0;j<m;j++){
				if(check[i] == 0) {
					fr[j]=pg[i];
					break;
				}
			}
		}
		for(j=0;j<m;j++){
			check[j]=0;
			if(fr[j]!=-1)	printf("%d ",fr[j]);
		}
		if(found == 1) printf("\t\t\t\t\tHIT");
		else  printf("\t\t\t\t\tMISS");
	}
	printf("\n");
	printf("\nThe total page fault is : %d",miss);
	float hit_ratio=100*((float)(hit)/(float)n);
	printf("\nThe hit ratio is : %0.2f",hit_ratio);
}
void main(){
	printf("Enter the number of pages: ");
	scanf("%d",&n);
	printf("Enter the reference string\n");
	printf("................................\n");
	for(i=0;i<n;i++){
		printf("Enter reference string %d: ",i+1);
		scanf("%d",&pg[i]);
	}
	printf("\nEnter the number of frames: ");
	scanf("%d",&m);
	for(int j=0;j<m;j++)	time[i]=0;
	int c;
	do{
		printf("\n\nPage Replacement Algorithms");
		printf("\n...................................\n");
		printf("\n1.FIFO\n2.LRU\n3.OPTIMAL\n4.Exit\n");
		printf("\n.....................................\n");
		printf("Enter the choice :");
		scanf("%d",&c);
		switch(c){
			case 1:
				fifo();
				break;
			case 2:
				lru();
				break;
			case 3:
				optimal();
				break;
			case 4:
				printf("\nExiting...\n");
				break;
			default:
				printf("\nInvalid Choice\n");
				break;
		}
	}while(c!=4);
}	
