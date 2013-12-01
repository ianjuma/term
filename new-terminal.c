#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

#include "signal_r.h"
#include "gcc_attributes.h"
#include "ansi_colors.h"
#include "logger_syslog.h"
#include "config_parser.h"


struct arg_data {
    char *s_message;

    char *m_arg1[3];

    char *thread_args[];
};

struct arg_data obj;

int *status = NULL;

__packed int hasSpace(char x[]);

static __pure void main_arg(int argc, char **argv);

static __packed __pure __noreturn void clearScreen();

__packed __pure int __e_syslog();


inline int variadic__execute(char *args_data, ... );

__packed int read_config();

static inline int parser(char arg_data[]);

pid_t worker0;


#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("O3")
int main(int argc, char *argv[], char **env) {

    clearScreen();
    setsigHl();
    logger();

    main_arg(argc, argv);

    if (read_config() != 0) {
        errorLogger();
        exit(-1);
    }
    

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
                chdir(c);
            }

            if (strcmp(c, "ls") == 0 || strcmp(c, "ll") == 0 || strcmp(c, "l") == 0) {
                system("ls --color");
                break;
            }


            // #pragma omp parallel private(obj.s_message)
            obj.s_message = (char *) c;

            parser(c);
            variadic__execute( (char *) c);

                
            if (hasSpace(c)) {
                
            } else {
                
            }
        
        }
    }


    pthread_exit(NULL);

    return 0;
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


static __packed __pure __noreturn void clearScreen() {
    system("clear");
}


static __pure void main_arg(int argc, char **argv) {

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

}

inline int variadic__execute(char *args_data, ... ) {
    // fork -exec
    // check --> assume 3 args MAX
    // on success return 0;

    worker0 = fork();

    if (worker0 == 0) {
        //system(obj.s_message);

        execlp(obj.m_arg1[0], obj.m_arg1[1], NULL);
        wait(status);
    }

    return 0;
}

static inline int parser(char arg_data[]) {

    int count = 0;

    int assign_count;

    for (assign_count = 0; assign_count < 2; assign_count++) {
        for (count = 0; count < (int) strlen(arg_data); count++) {
            if (arg_data[count] == ' ') {
                int count_inner;
                for(count_inner = 0; count_inner < count; count_inner++) {

                    strcat(obj.m_arg1[assign_count], (char *) &arg_data[count_inner]);

                }
            }
            count = count + 1;

        }
    }

    return 0;
}


/*
worker0 = fork();
    if (worker0 == 0) {
    system(obj.s_message);
    wait(status);
}
*/