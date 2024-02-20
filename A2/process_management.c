#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

void writeOuput(char *command, char *output) {
	FILE *fp;
	fp = fopen("output.txt", "a");
	fprintf(fp, "The output of: %s : is\n", command);
	fprintf(fp, ">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
	fclose(fp);

}

int main(int argc, char *argv[]) {

	const int SIZE = 4096;
	const char *name = "OS";
	const int READ = 0;
	const int WRITE = 1;
	const char *IN_FILE_NAME = "sample_in_process.txt";

	int fd;
	char *ptr;

	fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(fd, SIZE);

	ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0) == MAP_FAILED) {
		exit(1);
	}

	pid_t pid;
	pid = fork();
	if (pid < 0) {
		exit(1);
	} else if (pid == 0) {
		FILE *fp;
		char command[255];
		fp = fopen(IN_FILE_NAME, "r");
		while (fgets(command, 255, fp)) {
			ptr += sprintf(ptr, "%s", command);
		}
		fclose(fp);
		exit(0);

	} else {
		wait(NULL);
		char *commands = (char*) ptr;

		int p1[2];
		int p2[2];
		if (pipe(p1) == -1) {
			exit(1);
		}
		if (pipe(p2) == -1) {
			exit(1);
		}

		pid_t pid2;
		pid2 = fork();
		if (pid < 0) {
			exit(1);
		} else if (pid2 == 0) {
			FILE *fp;
			char *total = strtok(commands, "\n");
			char *ouput = malloc(SIZE);
			size_t length;
			ssize_t total_bytes;

			close(p1[READ]);
			close(p2[READ]);

			while (total != NULL) {
				fp = popen(total, "r");
				total_bytes = getdelim(&ouput, &length, '\0', fp);
				pclose(fp);
				if (total_bytes != -1) {
					write(p1[WRITE], ouput, SIZE);
					write(p2[WRITE], total, SIZE);
				}
				total = strtok(NULL, "\n");
			}

			close(p1[WRITE]);
			close(p2[WRITE]);
			exit(0);
		} else {

			char *ouput = malloc(SIZE);
			char *total = malloc(SIZE);

			close(p1[WRITE]);
			close(p2[WRITE]);

			while (read(p1[READ], ouput, SIZE) > 0) {
				read(p2[READ], total, SIZE);
				writeOuput(total, ouput);
			}

			close(p1[READ]);
			close(p2[READ]);

			wait(NULL);

			if (munmap(ptr, SIZE) == -1) {
				printf("Unmap failed: %s\n", strerror(errno));
				exit(1);
			}
			if (close(fd) == -1) {
				printf("Close failed: %s\n", strerror(errno));
				exit(1);
			}
			if (shm_unlink(name) == -1) {
				printf("Error %s: %s\n", name, strerror(errno));
				exit(1);
			}

			exit(0);
		}
	}
}
