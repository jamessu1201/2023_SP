#include "apue.h"
#include <sys/wait.h>
#include<string.h>

static void	sig_int(int);		/* our signal-catching function */
int
main(void)
{
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
						if(!strcmp(ins,"cd")){
							int status=chdir(thing);
							if(status==-1) perror("Error");
							else printf("%s %%",getcwd(cwd, sizeof(cwd)));continue;
						}else{
							if(thing!=NULL) execlp(ins,ins,thing,(char *)0);
							else execlp(buf, buf, (char *)0);
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

		void
sig_int(int signo)
{
		printf("interrupt\n%% ");
}

