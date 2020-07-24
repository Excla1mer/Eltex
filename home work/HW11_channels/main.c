#include "header.h"

int main(int argc, char * argv[]) {
	int pipefd[2];
	pid_t pid;
	char str[255] = "Hello world!";
	char *path;
	path = getenv("PWD");
	//strncat(path, "/main.c", 10);
	char *const parmList[] = {path, "header.h", NULL};
     	char *const envParms[2] = {NULL, NULL};
	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	int tmp;
	tmp = dup(STDOUT_FILENO);
	/*printf("%d\n", STDOUT_FILENO);
	printf("%d\n", pipefd[1]);
	dup2(pipefd[1], STDOUT_FILENO);*/
//	write(tmp, STDOUT_FILENO, sizeof(int));
	//printf("%d\n", STDOUT_FILENO);
	pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(pid == 0) {
	//	printf("Child\n");
		execve("/bin/cat", parmList, envParms);
		perror("EXEC");
		//close(pipefd[1]);
		//char str1[255];
		//while(read(pipefd[1], str1, 255) > 0)
			//write(STDOUT_FILENO, str1, 1);
		//dup2(tmp, pipefd[1]);
		//printf("C:%s\n", str1);
		//write(STDOUT_FILENO, "\n", 1);
		//close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	} else {
		//printf("Parrent\n");
		//write(tmp, "hello\n", 6);
		//close(pipefd[0]);
		//write(pipefd[1], str, sizeof(str));
		//close(pipefd[1]);
		wait(NULL);
		_exit(EXIT_SUCCESS);
	
	}
}
