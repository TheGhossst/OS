#include<stdio.h>
#include<stdlib.h>
int diskQueue[20],n,start;
void fcfs(){
    int i,seekTime=0,diff;
    printf("\nMovement of Cylinders\n");
    for(i=0;i<n;i++) {
        diff= abs(diskQueue[i+1] - diskQueue[i]);          
        printf("Move from %d to %d with seek time %d\n", diskQueue[i], diskQueue[i+1], diff);
        seekTime+=diff;
    }
    printf("\nTotal Seek Time: %d", seekTime);
    printf("\nAverage Seek Time = %f",(float) seekTime/n);
    printf("\n");
}
void sstf(){
    int visited[20],sstf_disk[20],i,seekTime=0,temp_start=start;
    for(i=0;i<n;i++)    sstf_disk[i]=diskQueue[i];
    for(i=0;i<n;i++) visited[i]=0;
    int remaining_requests = n-1;
    while (remaining_requests)
    {
        int min=17171;
        int min_track_number, position;

        for (int i = 1; i <= n; i++)
        {
            if (abs(temp_start - sstf_disk[i]) < min && visited[i]== 0){
                min = abs(temp_start - sstf_disk[i]);
                
                min_track_number = sstf_disk[i];
                position = i;
            }
            
        }
        printf("The seek time from %d to %d is %d\n",temp_start,min_track_number,min);
        temp_start = sstf_disk[position];
        visited[position] =1;
        seekTime += min;
        remaining_requests--;
    }

    printf("\nSeek Time: %d\n", seekTime);
}


void sort(int disk[20], int n){
    int i,j,temp;
    for(i=0;i<n-1;i++) {
        for(j=0;j<n-1-i;j++) {
            if(disk[j]>disk[j+1]) {
                temp = disk[j];
                disk[j] = disk[j+1];
                disk[j+1] = temp;
            }
        }
    }
}
void scan() {
    int scan_disk[20],previous;
    int i, pos, diff, seekTime = 0, current;
    for (i = 0; i < n; i++) {
        scan_disk[i] = diskQueue[i];
    }
    sort(scan_disk, n);
    for (i = 0; i < n; i++) {                                      
        if (scan_disk[i] == start) {
            pos = i;
            break;
        }
    }
    printf("Enter the previous head position : ");
    scanf("%d",&previous);
    printf("\nMovement of Cylinders\n");

    if (start < previous) {
        seekTime=0;
        for (i = pos; i > 0; i--) {
            diff = abs(scan_disk[i] - scan_disk[i - 1]);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", scan_disk[i], scan_disk[i - 1], diff);
        }
        diff = scan_disk[0];
        seekTime += diff;
        printf("Move from %d to 0 with seek time %d\n", scan_disk[0], diff);
        current = 0;
        for (i = pos+1; i <n; i++) {
            diff = abs(scan_disk[i] - current);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", current, scan_disk[i], diff);
            current = scan_disk[i];
        }
    } else {
            seekTime=0;
        for (i = pos; i < n - 1; i++) {
            diff = abs(scan_disk[i + 1] - scan_disk[i]);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", scan_disk[i], scan_disk[i + 1], diff);
        }
        diff = 199 - scan_disk[n - 1];
        seekTime += diff;
        printf("Move from %d to 199 with seek time %d\n", scan_disk[n - 1], diff);
        current = 199;
        for (i = pos - 1; i >=0; i--) {
            diff = abs(scan_disk[i] - current);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", current, scan_disk[i], diff);
            current = scan_disk[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", seekTime);
}

void cscan() {
    int cscan_disk[20];
    int i, pos, diff, seekTime = 0, current;
    int previous;

    printf("Enter the previous head movement: ");
    scanf("%d", &previous);

    for (i = 0; i < n; i++) {
        cscan_disk[i] = diskQueue[i];
    }
    sort(cscan_disk, n);
    for (i = 0; i < n; i++) {                                      
        if (cscan_disk[i] == start) {
            pos = i;
            break;
        }
    }
    printf("\nMovement of Cylinders\n");

    if (start < previous) {
        for (i = pos; i > 0; i--) {
            diff = abs(cscan_disk[i] - cscan_disk[i - 1]);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", cscan_disk[i], cscan_disk[i - 1], diff);
        }
        current = 0;
        diff = cscan_disk[0]-current;
        seekTime += diff;
        printf("Move from %d to 0 with seek time %d\n", cscan_disk[0], diff);
        current =199;
        diff=current;
        seekTime+=diff;
        printf("Move from 0 to 199 with seek time %d\n",diff);
        for (i = n - 1; i > pos; i--) {
            diff = abs(cscan_disk[i] - current);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", current, cscan_disk[i], diff);
            current = cscan_disk[i];
        }
    } else {
        for (i = pos; i < n - 1; i++) {
            diff = abs(cscan_disk[i + 1] - cscan_disk[i]);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", cscan_disk[i], cscan_disk[i + 1], diff);
        }
        current = 199;
        diff = 199 - cscan_disk[n - 1];
        seekTime += diff;
        printf("Move from %d to 199 with seek time %d\n", cscan_disk[n - 1], diff);
        current =0;
        diff=199;
        seekTime+=diff;
        printf("Move from 199 to 0 with seek time %d\n",diff);
        for (i = 0; i < pos; i++) {
            diff = abs(cscan_disk[i] - current);
            seekTime += diff;
            printf("Move from %d to %d with seek time %d\n", current, cscan_disk[i], diff);
            current = cscan_disk[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", seekTime);
}



int main() {
    int i,c;
    printf("Enter the size of Queue: ");
    scanf("%d", &n);
    printf("Enter the Requests:\n ");
    for(i=1;i<=n;i++) { 
        printf("Request %d: ",i);                                                           
        scanf("%d",&diskQueue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &diskQueue[0]);    
    start=diskQueue[0];            
    do{
        printf("\nDisk Scheduling\n.......................\n");
        printf("1.FCFS\n2.SSTF\n3.SCAN\n4.C-SCAN\n5.Exit\n..........................\n");
        printf("\nEnter the choice: ");
        scanf("%d",&c);
        switch(c){
            case 1:
                fcfs();
                break;
            case 2:
                ++n;
                sstf();
                --n;
                break;
            case 3:
                ++n;
                scan();
                --n;
                break;
            case 4:
                ++n;
                cscan();
                --n;
                break;
            case 5:
                printf("\nExit\n");
                break;
            default:
                printf("\nInvalid Choice\n");
                break;
        }
    }while(c!=5);
    return 0;
}
