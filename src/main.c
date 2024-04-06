#include <pthread.h>		// -lpthread

#include <signal.h>

#include "config.h"
#include "pcm_capture.h"
#include "vad_moatt.h"

#define MAX_SEM_COUNT 1

#define SUCCESS 0
#define FAILURE 1

/* rtos global variables */
pthread_t pcm_sampling_hndl;
pthread_t vad_hndl;

/* function prototypes */
// void sig_handler(int signum);
int init_mutexes(struct application_attributes* attrs);

/* signal handler for ^C: closing all files, windows, mutexes, etc. */
// void sig_handler(int signum)
// {
//     if (signum != SIGINT) {
// 		printf("Invalid signum %d\n", signum);
// 	}

//     pthread_cancel(pcm_sampling_hndl);
//     pthread_cancel(vad_hndl);

//     pthread_mutex_destroy(&mx_sync1);
//     pthread_mutex_destroy(&signal_buffer_lock);

//     sem_destroy(&sx_vadLock1);
//     sem_destroy(&sx_vadLock2);

//     printf("\nBye\n");
//     exit(0);
// }

int init_mutexes(struct application_attributes* attrs)
{
    pthread_mutexattr_t signal_buffer_lock_attr;

    sem_init(&attrs->raw_buffer_ready, MAX_SEM_COUNT, 0);
    sem_init(&attrs->raw_buffer_copied, MAX_SEM_COUNT, 1);

    // if (pthread_mutex_init(&signal_buffer_lock, &signal_buffer_lock_attr) != 0) {
    //     printf("Mutex init failed!\n");
    //     return FAILURE;
    // }

    // if (pthread_mutex_init(&mx_sync1, NULL) != 0) {
    //     printf("Mutex init failed!\n");
    //     return FAILURE;
    // }

    return SUCCESS;
}

int main()
{
    // signal(SIGINT, sig_handler);

    struct application_attributes attrs;

    printf("Initializing semaphores and mutexes\r\n");
    if (init_mutexes(&attrs) == FAILURE) {
        printf("Initialization failed\r\n");
        // todo: go to exit sequence
        return 0;
    }

    // TODO does it need to be casted to void?
    pthread_create(&pcm_sampling_hndl, NULL, &pcm_sampling_thrd, (void *)&attrs);
    pthread_create(&vad_hndl, NULL, &vad_moatt_thrd, (void *)&attrs);

    while (1);

    pthread_join(pcm_sampling_hndl, NULL);
    pthread_join(vad_hndl, NULL);

    return 0;
}
