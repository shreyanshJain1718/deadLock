#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int uint;
struct process{
	
	char name[10];
	uint *alloc;
	uint *max;
	uint *need;
};

int main(){
	uint num_of_process, num_of_resources;
	printf("Enter number of processes: "); scanf("%d", &num_of_process);
	printf("Enter number of resources: "); scanf("%d", &num_of_resources);
	int available[num_of_resources];
	struct process prscs[num_of_process];
	for(int i=0; i < num_of_process; i++){
		prscs[i].alloc = malloc(sizeof(uint)*num_of_resources);
		prscs[i].max = malloc(sizeof(uint)*num_of_resources);
		prscs[i].need = malloc(sizeof(uint)*num_of_resources);
	}

	printf("Enter availability for resources: \n");
	for(int i=0; i < num_of_resources; i++){
		printf("Resource %d: ", i+1);
		scanf("%d", &available[i]);
		while(available[i] < 0){
			printf("	Available should be greater than 0\n");
			printf("	Re-enter availability: ");
			scanf("%d", &available[i]);
		}
	}

	printf("Enter process details: \n");
	for(int i=0; i<num_of_process; i++){
		printf("\nProcess name: "); scanf("%s", prscs[i].name);
		printf("Allocated instances of: \n");
		for(int j=0;j<num_of_resources; j++){
			printf("\tResource %d: ", j+1); scanf("%d", &prscs[i].alloc[j]);
			while(prscs[i].alloc[j] < 0){
				printf("\tAllocated resource should be non-negative\n");
				printf("\tRe-enter allocated resource: "); scanf("%d", &prscs[i].alloc[j]);
			}
		}
		printf("Maximum required instances of: \n");
		for(int j=0;j<num_of_resources; j++){
			printf("\tResource %d: ", j+1); scanf("%d", &prscs[i].max[j]);
			while(prscs[i].max[j] < 0){
				printf("\tMaximum resource required should be non-negative\n");
				printf("\tRe-enter maximum requirement: "); scanf("%d", &prscs[i].max[j]);
			}
			while(prscs[i].max[j] < prscs[i].alloc[j]){
				printf("\tMaximum requirement can't be less than allocated\n");
				printf("\tRe-enter maximum requirement: "); scanf("%d", &prscs[i].max[j]);
			}
		}
	}

	 printf("Calculating need of each process...\n");
     for(int i=0;i<num_of_process; i++){
	 	for(int j=0; j<num_of_resources; j++){
        	 prscs[i].need[j] = prscs[i].max[j] - prscs[i].alloc[j];
     	}
	 }
     printf("Calculated the need\n");

	
	printf("Checking if the system is in safe state...\n");
	int done[num_of_process];
	for(int i=0;i<num_of_process;i++) done[i] = 0;
	int safeSequence[num_of_process];
	int count_safe = 0;
	int foundSafe = 0;
	while(count_safe < num_of_process){
		foundSafe = 0;
		for(int i=0; i<num_of_process;i++){
			if(!done[i]){
				int j;
				for(j=0;j<num_of_resources;j++){
					if(prscs[i].need[j] > available[j]){
						break;
					}
				}
				if(j == num_of_resources){
					done[i] = 1;
					foundSafe = 1;
					for(int j=0;j < num_of_resources; j++){
						available[j] += prscs[i].alloc[j];
					}
					safeSequence[count_safe++] = i;
				}
			}
		}
		if(!foundSafe) break;
	}

	if(count_safe == num_of_process){
		printf("The system is in safe state\n");
		printf("The safe sequence: \n");
		for(int i=0;i<num_of_process; i++){
			printf("\t%s%s", prscs[safeSequence[i]].name, (i == num_of_process-1)? ".": " -> ");
		}
	}
	else{
		printf("System is not safe\n");
	}
	printf("\n");
	return 0;
}
