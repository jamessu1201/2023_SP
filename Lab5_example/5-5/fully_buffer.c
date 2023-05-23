#include "apue.h"

int main(void)
{
	char buf[MAXLINE];

	memset( buf, '\0', sizeof( buf ));
	fprintf(stdout, "fully buffer\n");
	setvbuf(stdin, NULL, _IOFBF, 1024);
    setvbuf(stdout, NULL, _IOFBF, 1024);

	int count=0;

	while( (fgets(buf,MAXLINE,stdin)) != NULL ){
		if(fputs(buf,stdout) == EOF)
			err_sys("output error");
		count++;
	}
		
	if(ferror(stdin))
		err_sys("input error");

	fprintf(stdout,"count:%d\n",count);

	exit(0);
}

