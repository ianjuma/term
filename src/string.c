#define _PROGRAM_NAME str

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include "ansi_colors.h"
#include "gcc_attributes.h"

__packed __pure int __e_syslog() {
    return 0;
}


int main(int argc, char *argv[]) {
    char x[256];

    //x = "ls";


    char *user_name;
    //user_name = (char *)malloc(20*sizeof(char));

    user_name = getenv("USER");
    if (user_name == NULL) {
        return EXIT_FAILURE;
    }

    while (1) {

        // --CWD
        //char cwd[8];
        //getcwd(cwd, sizeof(cwd));
        //fprintf(stdout, "%s\n", cwd);


        printf("%s%s:repl -> ", KGRN, user_name);
        printf("%s", RESETCOLOR);
        //printf("%sgreen\n", KGRN);

        //fgets(x, 2, stdin); -->seg fault
        //fgets(x, 256, stdin); --> seg fault

        gets(x);
        char *tmp;

        //strcpy((char *) x, tmp);
        char *arg2;

        // int count // for loop initial dec
        int count = 0;

        for (count;count < (int) strlen((char *) x); count++) {
            if (x[count] == ' ') {
                int pos = count;
                for (pos; pos < strlen((char *) x); pos++) {
                    strcat(arg2, (char *) x[pos]);
                }
            }
        }

        if ( (char) x == "cd") {
            chdir("cd");
        }

        if (x == "exit") {
            exit(0);
        }


        system(x);
        //free(user_name);
        
        //execlp(x, " ", NULL); -> returns control

        //printf("\n"); --> no need for line
    }
    printf("%s \n",x);

    return 0;
}
