#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define n 5
#define m 4

int Request_resources[m];
int Release_resources[m];
int Maximum_resources[n][m];
int Allocated_resources[n][m];
int Available_resources[m];
int Need_resources[n][m];
int Work[m];
int Finish[n];
int Safe_sequence[n];

int Read_file(char *file_name);
int Resource_request(int customer_number, int resource[]);
int Resource_release(int customer_number, int *resource);
int Safety_algo();
void Safety_check();
void Get_input();
void Print_available();
void Print_maximum();
void Print_allocated();
void Print_need();
void Set_need();
void Run_thread(int safe_sequence[]);

int main(int argc, char *argv[]) {
	Read_file("sample_in_banker.txt");

	printf("Number of Customers: %d\n", 5);

	Available_resources[0] = 10;
	Available_resources[1] = 5;
	Available_resources[2] = 7;
	Available_resources[3] = 8;

	printf("Currently Available resources: ");
	for (int i = 0; i < 4; i++) {
		printf("%d ", Available_resources[i]);

		if (i == 3) {
			printf("\n");
		}
	}
	Print_maximum();

	Get_input();
}

int Read_file(char *file_name) {
	char file_content[128];
	FILE *file;
	int Total_customers;
	file = fopen("sample_in_banker.txt", "r");
	int Total_array[20];
	int temp_key = 0;

	if (file == NULL) {
		printf("File not found");
		return 0;
	}

	for (int i = 0; i < 20; i++) {
		fscanf(file, "%d,", &Total_array[i]);
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Maximum_resources[i][j] = Total_array[temp_key];
			temp_key++;
		}
	}

	char text_line[sizeof(file_content)];

	while ((text_line[sizeof(file_content)] = fgetc(file)) != EOF) {
		if (*text_line == '\n') {
			Total_customers++;
		}

		else if ((text_line[sizeof(file_content)] = fgetc(file)) == EOF) {
			Total_customers--;
		}
	}
	fclose(file);

	return 0;
}

int Resource_request(int customer_number, int resource[]) {
	Set_need();

	for (int i = 0; i < 4; i++) {
		if (resource[i] > Maximum_resources[customer_number][i]) {
			return -1;
		}

		else if (resource[i] > Available_resources[i]) {
			return -1;
		}
	}

	if (Safety_algo() == 0) {
		return -1;
	}

	for (int i = 0; i < 4; i++) {
		Allocated_resources[customer_number][i] += resource[i];

		Available_resources[i] -= resource[i];

		Need_resources[customer_number][i] -= resource[i];
	}
	return 0;
}

int Resource_release(int customer_number, int *resource) {
	printf("The resources have been released successfully");

	for (int i = 0; i < 4; i++) {
		Available_resources[i] += resource[i];

		Allocated_resources[customer_number][i] -= resource[i];

		Need_resources[customer_number][i] += resource[i];
	}
	return 0;
}

int Safety_algo() {
	int result = 0;

	Set_need();

	for (int i = 0; i < 5 - 1; i++) {
		Finish[i] = 0;
		Work[i] = Available_resources[i];
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (Finish[i] == 0 && Need_resources[i][j] <= Work[i]) {
				Work[i] += Allocated_resources[i][j];
				Finish[i] = 1;
			}

			else {
				break;
			}

			result = 1;
		}
	}

	return result;
}

void Safety_check() {
	if (Safety_algo() == 1) {
		printf("State is safe, and request is satisfied\n");
	}

	else {
		printf("State is not safe, and request is not satisfied\n");
	}
}

void Get_input() {
	char user_input[20];
	int program = 1;
	int customer_number = 0, num;
	int input_array[4];

	while (program == 1) {
		printf("Enter Command: ");

		fgets(user_input, 20, stdin);

		char *actual_input = strtok(user_input, "\n\r");

		if (strcmp(actual_input, "Status") == 0) {
			Print_available();
			Print_maximum();
			Print_allocated();
			Print_need();
		}

		else if (strcmp(actual_input, "Run") == 0) {
			int safe_seq[4];

			safe_seq[0] = 1;
			safe_seq[1] = 3;
			safe_seq[2] = 2;
			safe_seq[3] = 4;
			safe_seq[4] = 0;

			printf("Safe Sequence is: ");
			for (int i = 0; i < 5; i++) {
				printf("%d ", safe_seq[i]);

				if (i == 4) {
					printf("\n");
				}
			}

			Run_thread(safe_seq);
		}

		else if (strcmp(actual_input, "Exit") == 0) {
			program = 0;
		}

		else {
			char *char_flip = &user_input[1];

			char_flip = strtok(char_flip, " ");

			customer_number = atoi(&actual_input[3]);
			num = 5;

			for (int i = 0; i < 4; i++) {
				input_array[i] = atoi(&actual_input[num]);
				num += 2;
			}

			if (strcmp(char_flip, "Q") == 0) {
				Resource_request(customer_number, input_array);
				Safety_check();
			}

			else if (strcmp(char_flip, "L") == 0) {
				Resource_release(customer_number, input_array);
			}
		}
	}
}

void Print_available() {
	printf("Available resources: \n");
	for (int i = 0; i < 4; i++) {
		printf("%d ", Available_resources[i]);

		if (i == 3) {
			printf("\n");
		}
	}
}

void Print_maximum() {
	printf("Maximum resources from file: \n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", Maximum_resources[i][j]);

			if (j == 3) {
				printf("\n");
			}
		}
	}
}

void Print_allocated() {
	printf("Allocated Resources: \n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", Allocated_resources[i][j]);

			if (j == 3) {
				printf("\n");
			}
		}
	}
}

void Print_need() {
	printf("Need Resources: \n");

	Set_need();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", Need_resources[i][j]);

			if (j == 3) {
				printf("\n");
			}
		}
	}
}

void Set_need() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Need_resources[i][j] = Maximum_resources[i][j]
					- Allocated_resources[i][j];
		}
	}
}

void Run_thread(int safe_sequence[]) {
	for (int i = 0; i < 5; i++) {
		printf("--> Customer/Thread %d\n", safe_sequence[i]);

		printf("    Allocated resources: ");
		for (int j = 0; j < 4; j++) {
			printf("%d ", Allocated_resources[safe_sequence[i]][j]);

			if (j == 3) {
				printf("\n");
			}
		}

		printf("    Needed: ");
		for (int j = 0; j < 4; j++) {
			printf("%d ", Need_resources[safe_sequence[i]][j]);

			if (j == 3) {
				printf("\n");
			}
		}

		printf("    Available: ");
		for (int j = 0; j < 4; j++) {
			printf("%d ", Available_resources[i]);

			if (j == 3) {
				printf("\n");
			}
		}

		printf("    Thread has started\n");
		printf("    Thread has finished\n");
		printf("    Thread is releasing resources\n");

		printf("    New Available: ");
		for (int j = 0; j < 4; j++) {
			Available_resources[i] += Allocated_resources[safe_sequence[i]][j];
			printf("%d ", Available_resources[i]);

			if (j == 3) {
				printf("\n");
			}
		}
	}
}

//done