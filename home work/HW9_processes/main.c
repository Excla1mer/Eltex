#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>       
int main() {
	pid_t pid;
	int *wstatus;	
	pid = fork();
	if(pid == 0) {
		pid = fork();
		if(pid == 0) {
			printf("C3: I am alive!\n");
			printf("C3: my pid %d\n",  getpid());
			printf("C3: my Ppid \t%d\n", getppid());
			printf("C3: end\n");
			return 0;
		}
		else {
			printf("C1: I am alive!\n");
			printf("C1: my pid %d\n",  getpid());
			printf("C1: my Ppid \t%d\n", getppid());
			wait(wstatus);
			printf("C1: end\n");
			return 0;
		}
	
	}
       	else {
			
			pid = fork();
			if(pid == 0) {
				pid = fork();
				if(pid == 0) {
				
					printf("C4: I am alive!\n");
					printf("C4: my pid %d\n",  getpid());
					printf("C4: my Ppid \t%d\n", getppid());
					printf("C4: end\n");
					return 0;
				
				
				}
				else {
					pid = fork();
					if(pid == 0) {
					
						printf("C5: I am alive!\n");
						printf("C5: my pid %d\n",  getpid());
						printf("C5: my Ppid \t%d\n", getppid());
						printf("C5: end\n");
						return 0;
					}
					else  {
					
						printf("C2: I am alive!\n");
						printf("C2: my pid %d\n",  getpid());
						printf("C2: my Ppid \t%d\n", getppid());
						printf("C2: wait chailds\n");
						wait(wstatus);
						wait(wstatus);
						printf("C2: end\n");
						return 0;
					}
				}
			}
			else
			{
				printf("P: I  am dad!\n");
				printf("P: my pid %d\n", getpid());
				printf("P: wait chailds\n");
				wait(wstatus);
				wait(wstatus);
				printf("P: end\n");
			}
	
	} 
       	

}
