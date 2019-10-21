#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// get the input the of the user
void  get_input(char *user)
{
        printf("CS361 >");
        fgets(user, 128, stdin); // 128 characters limit
        if(user[strlen(user) - 1] == '\n')
	{
                user[strlen(user) -1] = '\0';
	}
}


// parse the user command
void  parse_command(char *word, char **argv) {

	while (*word != '\0') {
		while (*word == ' ')
		{
			*word++ = '\0';
		}
		*argv++ = word;

		while (*word != '\0' && *word != ' ')
		{
			word++;
		}
	}
	*argv = '\0';
}

int exit_command(char **argv)
{
	if(!strcmp(argv[0], "exit")) //if the user type exit then exit the shell
	{
		exit(0);
	}
	return 0;
}

// checking pid
void get_pid(char **argv)
{
	if(execvp(*argv, argv) < 0)
	{
		printf("%s: Command not found \n", argv[0]);	// check if the command is valid
		exit(1);
	}

}
