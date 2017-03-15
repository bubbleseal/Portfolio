#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> /*named pipe*/

/*Declare booleans to true and false*/
typedef enum { false, true } bool;

#define KEEP 0
#define FORWARD 1

/*Method declarations*/
void checkPipe(int p);
bool checkMessage(char *buf, int a);
void savelog(char *buf, int lognum, int state);

/*Check if pipe is successfully created*/
void checkPipe(int p) {
	if (p != 0) 
		printf("Failed to create unnamed pipe\n");
}

/*Checks if the data belongs to the particular process*/
bool checkMessage(char *buf, int a) {
	if (atoi(buf) == a) {
		return true;
	}
	else {
		return false;
	}
}

/*Input log in log file*/
void savelog(char *buf, int lognum, int state) {
	FILE *logptr;
	time_t curt;
	time(&curt);

	/*Copy time to string and remove last \n*/
	char *tptr = ctime(&curt);
	char tbuf[26];
	strcpy(tbuf, tptr);
	tbuf[strlen(tbuf) - 1] = 0;

	/*Copy string of data that is passed in to a new array of char*/
	char nbuf[150];
	strncpy(nbuf, buf, sizeof(nbuf));

	/*Remove last \n and first 2 characters from string*/
	strtok(nbuf, "\n"); 
	memmove(nbuf, nbuf + 2, strlen(nbuf));

	/*Open log file depending on process number*/
	switch (lognum) {
	case 1:
		logptr = fopen("process_1.log","a");
		break;
	case 2:
		logptr = fopen("process_2.log", "a");
		break;
	case 3:
		logptr = fopen("process_3.log", "a");
		break;
	case 4: 
		logptr = fopen("process_0.log", "a");
		break;
	default: 
		break;
	}

	/*Copy timestamp and data into log file*/
	if (state == 0) {
		fprintf(logptr, "%s\t%s\tKEEP\n", tbuf, nbuf);
	}
	else {
		fprintf(logptr, "%s\t%s\tFORWARD\n", tbuf, nbuf);
	}
	fclose(logptr);
}

int main(int argc, char *argv[]){
	printf("Welcome to my OS assignment 1 program.\n");

	/*Remove all log files if they exist*/
	remove("process_1.log");
	remove("process_2.log");
	remove("process_3.log");
	remove("process_0.log");

	/*Declare variables*/
	char buf[150], dir[200];
	pid_t pid, cpid, lastpid; 
	FILE *file_ptr;
	int fifo;

	/*Create unnamed pipes*/
	int fdA[2];
	int fdB[2];
	int fdC[2];
	int p1 = pipe(fdA);
	int p2 = pipe(fdB);
	int p3 = pipe(fdC);

	/*Check unnamed pipe creation*/
	checkPipe(p1);
	checkPipe(p2);
	checkPipe(p3);

	/* Check numbers of arguments */
	if (argc != 2) {
		perror("Invalid amount of arguments");
		exit(-1);
	}

	/*Check if file chosen exists*/
	if (access(argv[1], F_OK) == -1) {
		perror("File doesn't exist.\n");
		exit(-1);
	}

	/*Get directory for named pipe*/
	char* cwd = getcwd(dir, sizeof(dir));
	if (cwd == NULL) {
		perror("Load failed: Directory not found.\n");
		exit(-1);
	}
	/*Add a subfolder to contain named pipe*/
	strcat(dir, "/pipe");

	/*Check if file exists to store named pipe*/
	if (access(dir, F_OK) == 0) { 
		/*Delete file if file exists*/
		if (remove(dir) != 0) {
			perror("Deletion failed\n");
			exit(-1);
		}
	} 

	 /*Create named pipe if file doesn't exist*/
	if (mkfifo(dir, 0600) == -1) {
		perror("Failed to create named pipe(fifo)\n");
		exit(-1);
	}

	/*fork process 1*/
	pid = fork();
	if(pid == -1){
		perror("Failed to fork Process 1\n");
		exit(-1);
	}
	else if(pid == 0) { /*Process 1*/

		/*Fork process 2*/
		cpid = fork(); 
		if (cpid == -1) {
			perror("Failed to fork Process 2\n");
			exit(-1);
		}
		else if(cpid == 0) { /*Process 2*/
			/*close unrelated pipes*/
			close(fdA[0]);
			close(fdA[1]);
			close(fdC[0]);
			close(fdC[1]);

			/*Open FIFO (named pipe)*/
			fifo = open(dir, O_WRONLY);

			/*Close related I/0*/
			close(fdB[1]);

			/*Read string from pipe 2*/
			while (read(fdB[0], buf, sizeof(buf))>0) {
				/*If data is not for process 2, write data to process 3*/
				if (checkMessage(buf, 2)) {
					savelog(buf, 2, KEEP);
				}
				else {
					if (write(fifo, buf, sizeof(buf)) == -1) {
						printf("Failed to write to named pipe: %s\n",buf);
					}
					else {
						savelog(buf, 2, FORWARD);
					}
				}
			}

			close(fdB[0]);
			close(fifo);
			exit(0);
		}
		else { /*Process 1*/
			/*Close unrelated pipes*/
			close(fdC[0]);
			close(fdC[1]);

			/*Close related I/0*/
			close(fdA[1]);
			close(fdB[0]);

			/*Read string from pipe 1*/
			while(read(fdA[0],buf,sizeof(buf))>0){
				/*If data is not for process 1, write data to process 2*/
				if (checkMessage(buf, 1)) {
					savelog(buf, 1, KEEP);
				}
				else{
					if (write(fdB[1], buf, sizeof(buf)) == -1) {
						printf("Failed to write to pipe 2: %s\n", buf);
					}
					else {
						savelog(buf, 1, FORWARD);
					}
				}
			}

			close(fdA[0]);
			close(fdB[1]);

			wait(NULL);
			exit(0);
		}
	}
	else { /*Process 0*/
		/*Fork process 3*/
		lastpid = fork();
		if (lastpid == -1) {
			perror("Failed to fork Process 3\n");
			exit(-1);
		}
		else if (lastpid == 0) { /*Process 3*/
			/*Close unrelated pipes*/
			close(fdA[0]);
			close(fdA[1]);
			close(fdB[0]); 
			close(fdB[1]);

			/*Close related I/0*/
			close(fdC[0]);
			fifo = open(dir, O_RDONLY);

			/*Read string from fifo*/
			while (read(fifo, buf, sizeof(buf)) > 0) {
				/*If data is not for process 3, write data to process 0*/
				if (checkMessage(buf, 3)) {
					savelog(buf, 3, KEEP);
				}
				else{
					if (write(fdC[1], buf, sizeof(buf)) == -1) {
						printf("Failed to write to pipe 3: %s\n", buf);
					}
					else {
						savelog(buf, 3, FORWARD);
					}
				}
			}
			close(fifo);
			exit(0);
		}
		else /*Process 0*/ 
		{
			/*Close unrelated pipes*/
			close(fdB[0]);
			close(fdB[1]);

			/*Close related I/0*/
			close(fdA[0]);
			
			/*open file*/
			file_ptr = fopen(argv[1],"r");

			if (!file_ptr)
				perror("No such file\n");
			while (fgets(buf, sizeof(buf), file_ptr)) {
				/*write string to pipe 1*/
				if (write(fdA[1], buf, sizeof(buf)) == -1) {
					printf("Failed to write to pipe 1: %s\n", buf);
				}
			}

			/*Close related I/0*/
			close(fdA[1]);
			close(fdC[1]);

			/*Read data from process 3*/
			while (read(fdC[0], buf, sizeof(buf)) > 0) {
					savelog(buf, 4, KEEP);
			}

			close(fdC[0]);
			wait(NULL);
			exit(0);
		}
		fclose(file_ptr);
	}
	printf("End of program");
	return 0;
}


