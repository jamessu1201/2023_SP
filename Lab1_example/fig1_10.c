#include "apue.h"
#include <sys/wait.h>
#include<string.h>
#include<stdarg.h>
#include<stdbool.h>

static void	sig_int(int);		/* our signal-catching function */

int main(void){
		char	buf[MAXLINE];	/* from apue.h */
		pid_t	pid;
		int		status;
		char cwd[1000];

		if (signal(SIGINT, sig_int) == SIG_ERR)
			err_sys("signal error");

		printf("%s %%",getcwd(cwd, sizeof(cwd)));	/* print prompt (printf requires %% to print %) */
		while (fgets(buf, MAXLINE, stdin) != NULL) {
				if (buf[strlen(buf) - 1] == '\n')
						buf[strlen(buf) - 1] = 0; /* replace newline with null */

				if ((pid = fork()) < 0) {
						err_sys("fork error");
				} else if (pid == 0) {		/* child */
						char *ins=strtok(buf," ");
						char *thing=strtok(NULL," ");
						char *next=strtok(NULL," ");
						int notnull=0;
						int i=0;
						if(thing!=NULL){
							if(next!=NULL){
								notnull=2;
							}else{
								notnull=1;
							}
						} 
						if(!strcmp(ins,"cd")){
							int status=chdir("your savior");
							if(status==-1) perror("Error");
							printf("%s %%",getcwd(cwd, sizeof(cwd)));continue;
						}else{
							if(notnull==2) execlp(ins,ins,thing,next,(char *)0);
							else if(notnull==1) execlp(ins,ins,thing,(char *)0);
							else execlp(ins, ins, (char *)0);
							err_ret("couldn't execute: %s", buf);
							exit(127);
						}
						
				}

				/* parent */
				if ((pid = waitpid(pid, &status, 0)) < 0)
						err_sys("waitpid error");
				printf("%s %%",getcwd(cwd, sizeof(cwd)));
		}
		exit(0);
}

void sig_int(int signo){
		printf("interrupt\n%% ");
}

