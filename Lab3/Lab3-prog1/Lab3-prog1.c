/******************************************************************************
 * Author: Kyle Chisholm
 * Title: Lab3-prog1
 * Date: 05/02/2015
 * Course: CST8244 Real-Time Programming
 * Instructor: Douglas King
 *****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <process.h>
#include <fcntl.h>



#define KEY 1000
/******************************************************************************
 *  Prototypes
 *****************************************************************************/
void sigint_handler(int);
void* function(void*);
/******************************************************************************
 * Global Variables
 *****************************************************************************/
int numChildren;		// Number of child processes
sem_t *semaphore; 		// Semaphore for threads
key_t key;
char *shm, *s;

// sem_init(&semaphore, 0, 0); to initialize a semaphore
// sem_wait(&semaphore);  Waits on a semaphore, wakes upon sem_post()
// sem_post(&semaphore);	Increments value of semaphore and wakes up blocked process waiting on it (if any)
// sem_getValue(&semaphore, &tempVar); tempVar stores the value from the semaphore
// sem_destroy(&semaphore); Destroys the semaphore (make sure nothing is waiting on it before it is destroyed!)


/******************************************************************************
 * 	Main
 *****************************************************************************/
int main(void)
{
	key = 1000;
	pthread_attr_t attr;	// shared thread attribute struct
    int i, j;				// iterators
    semaphore = sem_open("semaphore", O_CREAT, 0600, 0);
    if(semaphore == SEM_FAILED) {
    	printf("Error creating semaphore.");
    	return EXIT_FAILURE;
    }
    //sem_init(&semaphore, 1, 0);
    signal(SIGUSR1, sigint_handler);
    /* Prompt user for number of child threads to create */
    printf("Number of Children: ");
    scanf("%d", &numChildren);
    printf("%d children created.\n", numChildren);
    /* create an array of thread objects (for joining) */
    pthread_t threads[numChildren];
    /* Who's your daddy? */
    printf("Parent : TID=%d PID=%d\n", pthread_self(), getpid());
    /* Iterate and create as many threads as the user entered */
    for (i = 0; i < numChildren; ++i)
    {
    	/* Initialize the attribute struct for each new thread */
    	pthread_attr_init(&attr);
    	/* Create the threads */
    	pthread_create( &threads[i], &attr, &function, NULL );
    }

    /* Join all threads to the parent process, this enables the parent to
     * continue running until all threads die, or it is manually terminated */
    for(j=0; j<numChildren; ++j)
       	pthread_join(threads[j], NULL);

    return EXIT_SUCCESS;
}
/******************************************************************************
 * Functions
 *****************************************************************************/
/* Threads execute here */
void*  function( void*  arg )
{
	printf("Child : SELF = %d TID = %d : Child running.\n", pthread_self(), gettid());	// Print all threads
	/* Infinite loop for threads to continue executing until parent dies */
	while(1) {
		/* Print the thread ID */
		printf("Thread #%d Waiting...\n", gettid());
		/* threads Halt on this line, waiting for the semaphore to incriment */
		sem_wait(semaphore);
		/* Only after sem_post() will an unblocked thread reach this code */
		printf("Thread #%d Resuming...\n", pthread_self());
		/* Sleep for 5 seconds */
		sleep(5);
	}

   return EXIT_SUCCESS;
}
/* Signal handler */
void sigint_handler(int signal) {

	if(signal == SIGUSR1) {
		printf("PID = %d : Parent received USR1.\n", getpid());
		exit(EXIT_SUCCESS);
	}

}
