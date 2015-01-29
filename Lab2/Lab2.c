#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sigint_handler(int);

int usr1Happened;
int numChildren;
pid_t wpid;
int status;

int main(void)
{
	status = 0;
	int pid = 0;
    int i;

    printf("Number of Children: ");
    scanf("%d", &numChildren);
    printf("%d children created.\n", numChildren);

    printf("parent_pid = %d\n", getpid());

    for (i = 0; i < numChildren; ++i)
    {
        pid = fork();
        /* Stop iteration if your a child process */
        if(pid == 0) {
        	break;
        }
    }

    		if(pid == 0)	/* Child process, fork() returns PID of 0 for child */
            {
            	printf("PID = %d : Child running.\n", getpid());
            	signal(SIGUSR1, sigint_handler);
            	while(1) {

            		if(usr1Happened != 0) {
            			usr1Happened = 0;
            			break;
            		}
            	}
            }
            else if (pid < 0) {	/* fork() returned -1 (Error) */
            	printf("Fork Error\n");
            	exit(EXIT_FAILURE);
            }
            else if (pid > 0){ /* Parent process, fork() returns the ppid of the child (PID of the parent) */
            	while ((wpid = wait(&status)) > 0);
            	printf("All children gone, parent exiting...\n");
            	exit(EXIT_SUCCESS);
            }

    return EXIT_SUCCESS;
}

void sigint_handler(int signal) {
	usr1Happened = signal;

	if(usr1Happened) {
		usr1Happened = 0;
		printf("PID = %d : Child received USR1.\n", getpid());
		printf("PID = %d : Child exiting.\n", getpid());
		exit(EXIT_SUCCESS);
	}

}
