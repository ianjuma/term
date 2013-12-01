#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define NUM_THREADS 2


struct thread_data {
    char *s_message;
    char *thread_args[];
};

struct thread_data obj;


void *task0(void *message);
void *task1(void *message);

pthread_t worker0, worker1;

int main(int argc, char *argv[]) {

    if (argc > 0) {
        if (argv[1] == (char *) "help") {
            printf("Help MAN page ->\n");
            system("cat /usr/share/applications/README.txt");
        }

        if (argv[1] == (char *) "config") {
            printf("configuring from .ini file");
        }
    }

	while (1) {
        for (;;) {

            char c;
    		printf("synod@synod:$ ");
    		c = getchar();

    		if ( c == 'E') {
    			exit(0);
    		}

            obj.s_message = (char *) c;
            
            worker0 = pthread_create(&worker0, NULL,
                task0, (void *) &obj);

    		//system((char *) c[0]);

            //execlp("ls", "-l", NULL);

        }
	}

    pthread_exit(NULL);

	return 0;
}

void *task0(void *message) {
    char *r_message;
    //char *thread_arg1;
    //char *thread_arg2;

    struct thread_data *_data;
    _data = (struct thread_data *) message;

    r_message = _data->s_message;

    //if ( thread_args)
    //thread_arg1 = data->thread_args[0];
    //thread_arg2 = data->thread_args[1];

    //execlp(r_message, "" ,NULL);
    system(r_message);

    //execlp("ls", "-l", NULL);
    pthread_exit(NULL);
}

void *task1(void *message) {
    char * g_message = (char *) message;
    system((char *) g_message);
    //waitpid();
    // go back to thread pool -> message queue -> pull task
    //wait(1);
    pthread_exit(NULL);
}

