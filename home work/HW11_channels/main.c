#include "header.h"

#define NAME "/tmp/buff.txt"

int main() {
	int fifo_fd;
	pid_t pid;
	char buff[1024];
	char str[80]; 
	char *args[40];
	char *run[20]; 
	char *path;
	int i = 0;
	int n = 0; 
	int p = 0; // Определяет сколько комманд было записано
	path = getenv("PWD"); 
	mkfifo(NAME, 0666);
	fifo_fd = open(NAME, O_RDWR);
	do {
		printf("%s$ ", path);
		fgets(str, 255, stdin);
		str[strlen(str) - 1] = '\0';
		args[0] =  strtok(str, " ");
		// Разбиваю строку на аргументы
		while(args[i] != NULL) {
			args[++i] = strtok(NULL, " ");
		
		}
		/* Идем в цикле for по аргументам и смотрим если это не конец строки и
		 * это не | , то записывам этот аргумент в run.
		 * run хранит название комманды и его аргументы.*/
		for(int j = 0; j <= i;  j++)  {
			if(args[j] == NULL) {
				if(p == 0) {
					execvp(run[0], run);
				} else {
					run[n] = NAME;
					//run[n+1] = NULL;
					execvp(run[0], run);	
				}
				break;
			}
			/* если аргумент == | это значит, что далее последует следующая команда
			 * и одновременно определяет, что предыдущая команда закончилась.*/
			if(strcmp(args[j], "|") == 0) {
				p++;
		                pid = fork();
		                if(pid == 0) {
		                        run[n] = NULL;
		                        dup2(fifo_fd, 1);
		                        execvp(run[0], run);
		                } else {
		                        wait(NULL);
					n = 0;

		                }
		        } else {
				run[n] = args[j];
				n++;
			}
		}
	}while(1);
}
