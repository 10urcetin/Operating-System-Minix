/*
20200808006 - İbrahim Baymaz
20200808033 - Bedirhan Tonğ
20200808050 - Onur Çetin
20200808067 - Şeyhmus Alataş
*/


#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct {
    int id;
    int* cpu_bursts;
    int* io_bursts;
    int num_bursts;
} Process;

// Function to calculate average turnaround time
float calculateAverageTurnaroundTime(Process* processes, int num_processes) {
    float total_turnaround_time = 0;
    for (int i = 0; i < num_processes; ++i) {
        total_turnaround_time += processes[i].cpu_bursts[processes[i].num_bursts - 1];
    }
    return total_turnaround_time / num_processes;
}

// Function to calculate average waiting time
float calculateAverageWaitingTime(Process* processes, int num_processes) {
    float total_waiting_time = 0;
    for (int i = 0; i < num_processes; ++i) {
        total_waiting_time += processes[i].io_bursts[0];
    }
    return total_waiting_time / num_processes;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read the number of processes
    int num_processes;
    fscanf(file, "%d", &num_processes);

    // Allocate memory for the array of processes
    Process* processes = (Process*)malloc(num_processes * sizeof(Process));

    // Read process information from the file
    for (int i = 0; i < num_processes; ++i) {
        int process_id;
        fscanf(file, "%d:", &process_id);

        processes[i].id = process_id;

        // Read cpu and io bursts
        int cpu_burst, io_burst;
        int num_bursts = 0;

        // Read until -1 is encountered
        while (fscanf(file, "(%d,%d);", &cpu_burst, &io_burst) == 2 && io_burst != -1) {
            ++num_bursts;
        }

        // Allocate memory for bursts
        processes[i].cpu_bursts = (int*)malloc(num_bursts * sizeof(int));
        processes[i].io_bursts = (int*)malloc(num_bursts * sizeof(int));

        // Reset file pointer to process bursts again
        fseek(file, -1, SEEK_CUR);

        // Read bursts again
        for (int j = 0; j < num_bursts; ++j) {
            fscanf(file, "(%d,%d);", &cpu_burst, &io_burst);
            processes[i].cpu_bursts[j] = cpu_burst;
            processes[i].io_bursts[j] = io_burst;
        }

        processes[i].num_bursts = num_bursts;
    }

    // Close the file
    fclose(file);

    // Implement FCFS scheduling algorithm
    //int current_time = 0;

    // Calculate turnaround and waiting times
    float average_turnaround_time = calculateAverageTurnaroundTime(processes, num_processes);
    float average_waiting_time = calculateAverageWaitingTime(processes, num_processes);

    // Print results
    printf("Average Turnaround Time: %.2f \n", average_turnaround_time);
    printf("Average Waiting Time: %.2f \n", average_waiting_time);

    // Free allocated memory
    for (int i = 0; i < num_processes; ++i) {
        free(processes[i].cpu_bursts);
        free(processes[i].io_bursts);
    }
    free(processes);

    return 0;
}
