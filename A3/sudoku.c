#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define true 1
#define false 0
int g_sequence = false;

int y_sequence = true;

void* firstline(void *param) {
	int *secondline = (int*) param;
	int bools[9] = { 0 };
	for (int i = 0; i < 9; i++) {
		if (g_sequence == true)
			printf("%d ", secondline[i]);

	}
	if (g_sequence == true)
		printf("\n");

	for (int i = 0; i < 9; i++) {
		int index = secondline[i] - 1;
		if (index < 0 || index >= 9) {
			y_sequence = false;
			break;
		}
		if (bools[index] != 0) {
			y_sequence = false;
			pthread_exit(0);
		} else if (bools[index] == 0) {
			bools[index] = 1;
		}
	}
	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	int puzzle[9][9];
	FILE *file;
	char character;
	file = fopen("sample_in_sudoku.txt", "r");

	if (file == NULL) {
		printf("ERROR - Could not open file.\n");
		return -1;
	}

	int f = 0, c = 0;
	while ((character = getc(file)) != EOF) {
		int curr = (int) character - 48;
		if (curr == -38) {
			f++;
		}
		if (curr > 0 && curr < 10) {
			puzzle[f][c % 9] = curr;
			c++;
		}
	}
	fclose(file);

	printf("Sudoku Puzzle Solution is:");
	for (int i = 0; i < 9; i++) {
		printf("\n");
		for (int j = 0; j < 9; j++) {
			printf("%d ", puzzle[i][j]);
		}
	}

	pthread_t tid[27];
	pthread_attr_t attr[27];
	for (int i = 0; i < 27; i++) {
		pthread_attr_init(&attr[i]);
	}

	int *row1 = (int*) malloc((9) * sizeof(int));
	int *row2 = (int*) malloc((9) * sizeof(int));
	int *row3 = (int*) malloc((9) * sizeof(int));
	int *row4 = (int*) malloc((9) * sizeof(int));
	int *row5 = (int*) malloc((9) * sizeof(int));
	int *row6 = (int*) malloc((9) * sizeof(int));
	int *row7 = (int*) malloc((9) * sizeof(int));
	int *row8 = (int*) malloc((9) * sizeof(int));
	int *row9 = (int*) malloc((9) * sizeof(int));

	int *column1 = (int*) malloc((9) * sizeof(int));
	int *column2 = (int*) malloc((9) * sizeof(int));
	int *column3 = (int*) malloc((9) * sizeof(int));
	int *column4 = (int*) malloc((9) * sizeof(int));
	int *column5 = (int*) malloc((9) * sizeof(int));
	int *column6 = (int*) malloc((9) * sizeof(int));
	int *column7 = (int*) malloc((9) * sizeof(int));
	int *column8 = (int*) malloc((9) * sizeof(int));
	int *column9 = (int*) malloc((9) * sizeof(int));

	int *box1 = (int*) malloc((9) * sizeof(int));
	int *box2 = (int*) malloc((9) * sizeof(int));
	int *box3 = (int*) malloc((9) * sizeof(int));
	int *box4 = (int*) malloc((9) * sizeof(int));
	int *box5 = (int*) malloc((9) * sizeof(int));
	int *box6 = (int*) malloc((9) * sizeof(int));
	int *box7 = (int*) malloc((9) * sizeof(int));
	int *box8 = (int*) malloc((9) * sizeof(int));
	int *box9 = (int*) malloc((9) * sizeof(int));

	int *rows[9] = { row1, row2, row3, row4, row5, row6, row7, row8, row9 };
	int *columns[9] = { column1, column2, column3, column4, column5, column6,
			column7, column8, column9 };
	int *boxes[9] = { box1, box2, box3, box4, box5, box6, box7, box8, box9 };

	for (int index = 0; index < 9; index++) {
		for (int i = 0; i < 9; i++) {
			rows[index][i] = puzzle[index][i];
			columns[index][i] = puzzle[i][index];
		}
		pthread_create(&tid[index], &attr[index], firstline,
				(void*) rows[index]);
		pthread_create(&tid[index + 9], &attr[index + 9], firstline,
				(void*) columns[index]);
	}

	int g = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int k = 0;
			for (int r = (i % 3) * 3; r < (i % 3) * 3 + 3; r++) {
				for (int c = (j % 3) * 3; c < (j % 3) * 3 + 3; c++) {
					boxes[g][k] = puzzle[r][c];
					k++;
				}
			}
			pthread_create(&tid[g + 18], &attr[g + 18], firstline,
					(void*) boxes[g]);
			g++;
		}
	}

	for (int i = 0; i < 27; i++) {
		pthread_join(tid[i], NULL);
	}
	if (y_sequence == true)
		printf("\nSudoku puzzle is valid\n");
	else if (y_sequence == false)
		printf("\nSudoku puzzle is not valid\n");
}
