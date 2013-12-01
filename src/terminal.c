#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

#include "signal_r.h"
#include "gcc_attributes.h"
#include "ansi_colors.h"
#include "logger_syslog.h"
#include "config_parser.h"

#define NUM_THREADS 2


struct thread_data {
    char *s_message;
    char *thread_args[];
};

struct thread_data obj;


static __packed __pure __noreturn void clearScreen() {
    system("clear");
}

__packed int hasSpace(char x[]);

__noreturn void *task0(void *message);
__noreturn void *task1(void *message);


__packed __pure int __e_syslog();

inline __packed char * vardparse__(char *mesg1, ... );

__packed int read_config();


pthread_t worker0, worker1;


#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("O3")
int main(int argc, char *argv[]) {

    clearScreen();

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", KGRN);
            printf("Help MAN page ->\n");
            system("cat /usr/share/applications/README.txt");
            printf("%s\n", RESETCOLOR);
            exit(0);
        }

        if (strcmp(argv[1], "--config") == 0) {
            printf("%s\n", KYEL);
            printf("configuring from .ini file ....\n");
            

            if (read_config() != 0) {

                errorLogger();
                exit(-1);
        
            }
            
            printf("%s\n", RESETCOLOR);

            exit(0);
        }
    }

    setsigHl();
    
    logger();

    if (read_config() != 0) {

        errorLogger();
        exit(-1);
        
    }
    

   /* 
    if (argc > 0) {
        if (argv[1] == (char *) "help") {
            printf("Help MAN page ->\n");
            system("cat /usr/share/applications/README.txt");
        }

        if (argv[1] == (char *) "config") {
            printf("configuring from .ini file");
        }
    }
    */
    

    char *username = getenv("LOGNAME");
    char *shell = getenv("SHELL");
    char *term = getenv("TERM");

    char *user = getenv("USER");

    if (username == NULL || shell == NULL || 
                term == NULL || user == NULL) {

        glogger(1);

        return EXIT_FAILURE;
    }

    printf("%s\n", KRED);


    printf("USERNAME -> %s\n", username);
    printf("USER -> %s\n", user);
    printf("SHELL -> %s\n", shell);
    printf("TERM -> %s\n", term);
    printf("PWD -> %s\n", getenv("PWD"));


    char c[256];

    // 2 looping structs --fail -> repetitive acts -double actions

    while (1) {
        for (;;) {

            printf("%s%s@repl:$ ", KGRN, username);
            printf("%s", RESETCOLOR);

            //scanf("%s", c);

            gets(c); // remove "\n" on getting char
            strtok(c, "\n");

                

            if (strcmp(c, "EXIT") == 0 || strcmp(c, "E") == 0 || strncmp(c, "exit", 4) == 0) {
                exit(0);
            }

            if (strcmp(c, "cd") == 0) {
                char cdt[12];
                printf("Enter dir: ");
                scanf("%s", (char *) &cdt);
                chdir(cdt);
            }

            if (strcmp(c, "ls") == 0 || strcmp(c, "ll") == 0 || strcmp(c, "l") == 0) {
                system("ls --color");
                break;
            }

                // string cpy -- check file
                // colors
                // malloc char *c then free -- on exit() --clean up on signal
                // cleanup _resources --files
                // dynamic allocation
                // char *
                // char []
                // logging --syslog
                // ctrl + L to clear screen --signal


            // #pragma omp parallel private(obj.s_message)
            obj.s_message = (char *) c;

                
            if (hasSpace(c)) {
                worker0 = pthread_create(&worker0, NULL,
                task0, (void *) &obj);
            } else {
                worker0 = pthread_create(&worker1, NULL,
                task1, (void *) &obj);
            }
                

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
    // pthread_cond_wait();
}

void *task1(void *message) {

    // char * g_message = (char *) message;
    // system((char *) g_message);
    //waitpid();
    // go back to thread pool -> message queue -> pull task
    //wait(1);

    char *r_message;
    //char *thread_arg1;
    //char *thread_arg2;

    struct thread_data *_data;
    _data = (struct thread_data *) message;

    r_message = _data->s_message;

    //system(r_message);

    execlp(r_message, " ", NULL);

    pthread_exit(NULL);
}


__packed __pure int __e_syslog() {
    errorLogger();
    return 0;
}


int hasSpace(char x[]) {
    // if has space -- move to system
            // else use execlp
    int count = 0;
    for (count = 0; count < (int) strlen(x); count++) {
        if (x[count] == ' ') {
            return 1;
        }
    }

    return 0;
}


__packed int read_config() {

    configuration config;

    if (ini_parse("config.ini", handler, &config) < 0) {
        printf("Can't load config.ini\n");
        return 1;
    }

    printf("\n%s", KYEL);

    printf("Config loaded from config.ini: term=%i, threads=%i, Thread-model=%s\n",
            config.term, config.threads, config.model);

    printf("name=%s, email=%s, version=%i",
            config.name, config.email, config.version);

    printf("\n %s", RESETCOLOR);

    return 0;
}
