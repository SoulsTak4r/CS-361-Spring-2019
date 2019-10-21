/*
	Hamza Amjad
	hamjad2
	HW2-Simple shell
	CS361

*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "hw2.h"


void  parse_command(char *word, char **argv);
int exit_command(char **argv);
void  get_input(char *user);
void  get_pid(char **argv);

int main() {

    char  user[128]; //user
    char  *argv[128];
    char  *dir;
    char  *fromDir;
    char  *toDir;
    char buf[128];
    pid_t pid;
    int status;

    while (1) {
	// function call of user input
	get_input(user);
	//function call of parse command
        parse_command(user, argv);
        // Exit Shell of user == exit
	exit_command(argv);


	// changing directory from one to another
        if (!strcmp(argv[0], "cd"))
	{
            dir = getcwd(buf, sizeof(buf));
            fromDir = strcat(dir, "/");
            toDir = strcat(fromDir, argv[1]);

            chdir(toDir);
	    continue;
        }
	 pid = fork();	
	if(pid == 0)
	{
		get_pid(argv); //function call of pid
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("pid:%d status:%d\n", pid, WEXITSTATUS(status)); // printing pid and status, if the command is not found status is 1
	}
    }

    return 0;
}// end main

