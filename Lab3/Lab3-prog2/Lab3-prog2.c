#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

int main(void) {
	int wakeupNum;		// Number of children to wake up
	int i;				// Control how many times sem_post is called
	sem_t *semaphore;	// Semaphore from program 1

	/* Attempt to open the semaphore from the first program */
	 semaphore = sem_open("semaphore",O_CREAT,0644,1);
	 /* Error message if sem_open fails */
	 if(semaphore == SEM_FAILED)
	    {
	      perror("unable to open semaphore");
	      sem_unlink(semaphore);
	      exit EXIT_FAILURE;
	    }
	 /* Continue prompting for number of threads to wake */
	while(wakeupNum != 0) {	// Exit when wakeupNum == 0
		printf("How many processes would you like to wake?(enter 0 to exit)\n");
		scanf("%d", &wakeupNum);	// Retrieve wakeupNum from stdin

		/* increment the semaphore by the number specified */
		for(i=0; i<wakeupNum; ++i)
			sem_post(semaphore);
	  }
	return EXIT_SUCCESS;
}
