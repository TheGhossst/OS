#include <stdio.h>

struct process{
	char name[20];
	int pid,arrival_time,burst_time,remaining_time;
	int completion_time,turnaround_time,waiting_time;
	int status,priority;
};
int q[100],front=0,rear=0,n;
void fcfs(struct process processes[20]){
	int i;
	
	int total_wait_time=0,total_turnaround_time=0,time=0;
	for(i=0;i<n;i++){
		if(time<processes[i].arrival_time)
			time=processes[i].arrival_time;
		total_wait_time+=time-processes[i].arrival_time;
		total_turnaround_time+=time+processes[i].burst_time-processes[i].arrival_time;
		processes[i].waiting_time=time-processes[i].arrival_time;
		processes[i].turnaround_time=time+processes[i].burst_time-processes[i].arrival_time;
		time+=processes[i].burst_time;
	}
	printf("\nFirst come first serve scheduling\n");
	printf("\nPID\t\tWaiting Time\t\tTurnaround Time\n");
	printf("\n.......................................................\n");
	for(i=0;i<n;i++){
		printf("%s\t\t%d\t\t\t\t%d\n",processes[i].name,processes[i].waiting_time,processes[i].turnaround_time);
	}
	printf("\nAvg waiting time is: %f",(float)total_wait_time/n);
	printf("\nAvg turnaround time is: %f\n",(float)total_turnaround_time/n);
}	
void sjf(struct process proces[20]){
		struct process temp;
		struct process *processes=proces;
		int i,j,min;
		int total_wait_time=0,total_turnaround_time=0,time=0;
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++){
				if(processes[i].arrival_time>processes[j].arrival_time){
					temp=processes[i];
					processes[i]=processes[j];
					processes[j]=temp;
				}
			}
		}
		for(i=0;i<n;i++){
			min=-1;
			for(j=0;j<n;j++){
				if(processes[j].status==0 && processes[j].arrival_time<=time){
					if(min==-1 || processes[j].burst_time<processes[min].burst_time){
							min=j;
					}
				}
			}
			if(min==-1){
				time++;
				i--;
				continue;
			}
			processes[min].status=1;
			processes[min].completion_time=time+processes[min].burst_time;
			processes[min].turnaround_time=processes[min].completion_time-processes[min].arrival_time;
			processes[min].waiting_time=processes[min].turnaround_time-processes[min].burst_time;
			total_wait_time+=processes[min].waiting_time;
			total_turnaround_time+=processes[min].turnaround_time;
			time=processes[min].completion_time;
			processes[min].status=2;
		}
		printf("\nShortest Job First scheduling\n");
		printf("\nName\t\tWaiting Time\t\tTurnaround Time\n");
		printf("\n.......................................................\n");
		for(i=0;i<n;i++){
			printf("%s\t\t%d\t\t\t\t%d\n",processes[i].name,processes[i].waiting_time,processes[i].turnaround_time);
		}
		printf("\nAvg waiting time is: %f",(float)total_wait_time/n);
		printf("\nAvg turnaround time is: %f\n",(float)total_turnaround_time/n);
		
}
void pri(struct process processes[20]){
		struct process temp;
		int i,j,min;
		int total_wait_time=0,total_turnaround_time=0,time=0;
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++){
				if(processes[i].arrival_time>processes[j].arrival_time){
					temp=processes[i];
					processes[i]=processes[j];
					processes[j]=temp;
				}
			}
		}
		for(i=0;i<n;i++){
			min=-1;
			for(j=0;j<n;j++){
				if(processes[j].status==0 && processes[j].arrival_time<=time){
					if(min==-1 || processes[j].priority<processes[min].priority){
							min=j;
					}
				}
			}
			if(min==-1){
				time++;
				i--;
				continue;
			}
			processes[min].status=1;
			processes[min].completion_time=time+processes[min].burst_time;
			processes[min].turnaround_time=processes[min].completion_time-processes[min].arrival_time;
			processes[min].waiting_time=processes[min].turnaround_time-processes[min].burst_time;
			total_wait_time+=processes[min].waiting_time;
			total_turnaround_time+=processes[min].turnaround_time;
			time=processes[min].completion_time;
			processes[min].status=2;
		}
		printf("\nPriority scheduling\n");
		printf("\nName\t\tWaiting Time\t\tTurnaround Time\n");
		printf("\n.......................................................\n");
		for(i=0;i<n;i++){
			printf("%s\t\t%d\t\t\t\t%d\n",processes[i].name,processes[i].waiting_time,processes[i].turnaround_time);
		}
		printf("\nAvg waiting time is: %f",(float)total_wait_time/n);
		printf("\nAvg turnaround time is: %f\n",(float)total_turnaround_time/n);
}
void enqu(int pid){
	q[rear]=pid;
	rear=(rear+1)%100;
}
int dequ(){
	if(front==rear)
		return -1;
	int returnpos=q[front];
	front=(front+1)%100;
	return returnpos;
}
void roundrobin(struct process proc[20]){
	int i,time_slice,j,wt=0,tat=0;
	/*struct process proc[100];
	printf("\nEnter the number of processes :");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Process %d",i+1);
		printf("\n................\n");
		printf("Enter the arrival time of process %d :",i+1);
		scanf("%d",&proc[i].arrival_time);
		printf("Enter the burst time of process %d :",i+1);
		scanf("%d",&proc[i].burst_time);
		proc[i].pid=i+1;
		proc[i].remaining_time=proc[i].burst_time;
		printf("\n");
	}*/
	printf("\nEnter the time slice :");
	scanf("%d",&time_slice);
	int time=0,process_left=n,local_time=0,pos=-1;
	for(i=0;i<n;i++)
		if(proc[i].arrival_time==time)
			enqu(i);
	while(process_left){
		if(local_time==0){
			if(pos!=-1)
				enqu(pos);
			pos=dequ();
		}
		for(i=0;i<n;i++){
			if(proc[i].arrival_time > time)
				continue;
			if(i==pos)
				continue;
			if(proc[i].remaining_time==0)
				continue;
			proc[i].waiting_time++;
			proc[i].turnaround_time++;
		}
		if(pos!=-1){
			proc[pos].remaining_time--;
			proc[pos].turnaround_time++;
			if(proc[pos].remaining_time==0){
				process_left--;
				local_time=-1;
				pos=-1;
			}
		}
		else
			local_time=-1;
		time++;
		local_time=(local_time+1)%time_slice;
		for(j=0;j<n;j++){
			if(proc[j].arrival_time==time)
				enqu(j);
		}
	}
	printf("\nProcess Info:\n");
	printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\n");
	printf("\n...............................................\n");
	for(i=0;i<n;i++){	   printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].pid,proc[i].arrival_time,proc[i].burst_time,proc[i].waiting_time,proc[i].turnaround_time);
	tat+=proc[i].turnaround_time;
	wt+=proc[i].waiting_time;
	}
	printf("\n");
	printf("The Average Watiting Time is: %f",(float)wt/n);
	printf("The Average TurnAround Time is: %0.4f",(float)tat/n);
}
void main(){
	int c;
	struct process processes[20],temp;
	printf("\nEnter the number of processes: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		printf("\nEnter details of process %d: ",i+1);
		printf("\n.......................\n");
		printf("Enter name of the process: ");
		scanf("%s",processes[i].name);
		printf("Enter the arrival time: ");
		scanf("%d",&processes[i].arrival_time);
		printf("Enter the burst time: ");
		scanf("%d",&processes[i].burst_time);
		processes[i].status=0;
		printf("Enter the priority: ");
		scanf("%d",&processes[i].priority);
		processes[i].pid=i+1;
		processes[i].remaining_time=processes[i].burst_time;
		processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
	}
	printf("\nScheduling Menu\n");
	printf("\n.............................\n");
	printf("\n1.First Come First Serve Scheduling\n2.Shortest Job First Scheduler\n3.Priority Scheduler\n4.Round Robin\n5.Exit");
	printf("\n..............................\n");
	do{
		printf("\nEnter the choice: ");
		scanf("%d",&c);
		switch(c){
			case 1:
				fcfs(processes);
				break;
			case 2:
				sjf(processes);
				break;
			case 3:
				pri(processes);
				break;
			case 4:
				roundrobin(processes);
				break;
			case 5:
				printf("Exit\n");
				break;
			default:
				printf("Invalid Choice\n");
				break;
				
		}
	}while(c!=5);
}	