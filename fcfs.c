#include <stdio.h>
struct Process
{
    int pid,arrival_time,burst_time;
    int waiting_time,turn_around_time;
};

void fcfs(struct Process processes[], int n)
{
    int i, total_wait_time = 0, total_turnaround_time = 0, time = 0;
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    printf("0");
    for (i = 0; i < n; i++)
    {
        if (time < processes[i].arrival_time)
        {
            time = processes[i].arrival_time;
        }
        printf(" -> [P%d] -> %d", processes[i].pid, time + processes[i].burst_time);
        total_wait_time += time - processes[i].arrival_time;
        processes[i].waiting_time=time-processes[i].arrival_time;
        total_turnaround_time += time + processes[i].burst_time - processes[i].arrival_time;
        processes[i].turn_around_time=time+processes[i].burst_time-processes[i].arrival_time;
        time += processes[i].burst_time;
    }
    printf("\n\n");
    printf("\nProcess\t\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time\n");
    for(i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d",i+1,processes[i].arrival_time,processes[i].burst_time,processes[i].turn_around_time,processes[i].waiting_time);
        printf("\n");
    }
    printf("\n\nAverage waiting time: %.2f", (float)total_wait_time / n);
    printf("\nAverage turnaround time: %.2f", (float)total_turnaround_time / n);
}

void main()
{
    int n, i;
    struct Process processes[10];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d: ", i + 1);
        printf("\n.................\n");
        printf("Arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
    }
    fcfs(processes, n);
}

