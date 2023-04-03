#include <stdio.h>
#include <stdlib.h>

struct Process {
    char name[10];
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int status; // 0: not arrived, 1: ready, 2: completed
};

int main() {
    int n, i, j, time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    float average_waiting_time, average_turnaround_time;
    struct Process processes[10], temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\nEnter the details of process P%d:\n", i + 1);
        printf("\n..............................\n");
        //sprintf(processes[i].name, "P%d", i + 1);
        printf("Process Name: ");
        scanf("%s",processes[i].name);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].status = 0;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
            else if (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    printf("\nPrioirty Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\t\tWaiting Time\n");
    printf("-----------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        int min = -1;
        for (j = 0; j < n; j++) {
            if (processes[j].status == 0 && processes[j].arrival_time <= time) {
                if (min == -1 || processes[j].priority < processes[min].priority) {
                    min = j;
                }
            }
        }
        if (min == -1) {
            time++;
            i--;
            continue;
        }
        processes[min].status = 1;
        processes[min].completion_time = time + processes[min].burst_time;
        processes[min].turnaround_time = processes[min].completion_time - processes[min].arrival_time;
        processes[min].waiting_time = processes[min].turnaround_time - processes[min].burst_time;
        total_waiting_time += processes[min].waiting_time;
        total_turnaround_time += processes[min].turnaround_time;
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[min].name, processes[min].arrival_time, processes[min].burst_time, processes[min].completion_time, processes[min].turnaround_time, processes[min].waiting_time);
        time = processes[min].completion_time;
        processes[min].status = 2;
    }
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    for (i = 0; i < n; i++){
        printf("%d -> [%s] -> %d", processes[i].completion_time - processes[i].burst_time, processes[i].name, processes[i].completion_time);
        printf("\n");
    }
    printf("\n");
    printf("\nAverage Waiting Time: %f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %f\n", (float)total_turnaround_time / n);
}