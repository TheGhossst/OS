#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid,at,bt,wt,tat,rt; 
};

bool isAllProcessesCompleted(const struct Process* processes, int n) {
    for (int i = 0; i < n; ++i) {
        if (processes[i].rt > 0) {
            return false;
        }
    }
    return true;
}

int findShortestRemainingTimeProcess(struct Process* processes, int n, int currentTime) {
    int shortestRemainingTime = 133321;
    int index = -1;

    for (int i = 0; i < n; ++i) {
        if (processes[i].at <= currentTime && processes[i].rt < shortestRemainingTime && processes[i].rt > 0) {
            shortestRemainingTime = processes[i].rt;
            index = i;
        }
    }
    return index;
}

int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; ++i) {
        int pid, at, bt;
        printf("Enter Process %d details:\n", i + 1);
        printf("PID: ");
        scanf("%d", &pid);
        printf("Arrival Time: ");
        scanf("%d", &at);
        printf("Burst Time: ");
        scanf("%d", &bt);
        processes[i].pid = pid;
        processes[i].at = at;
        processes[i].bt = bt;
        processes[i].wt = 0;
        processes[i].tat = 0;
        processes[i].rt = bt;
    }

    int currentTime = 0;
    int completed = 0;
    while (!isAllProcessesCompleted(processes, n)) {
        int index = findShortestRemainingTimeProcess(processes, n, currentTime);

        if (index == -1) {
            currentTime++;
            continue;
        }
        processes[index].rt--;
        currentTime++;

        if (processes[index].rt == 0) {
            completed++;
            processes[index].tat = currentTime - processes[index].at;
            processes[index].wt = processes[index].tat - processes[index].bt;
        }
    }
    double avgWaitingTime = 0.0;
    double avgTurnaroundTime = 0.0;
    for (int i = 0; i < n; ++i) {
        avgWaitingTime += processes[i].wt;
        avgTurnaroundTime += processes[i].tat;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }

    printf("\nAverage Waiting Time: %lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %lf\n", avgTurnaroundTime);

    return 0;
}
