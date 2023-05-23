#include "apue.h"

int main(void)
{

	int c;
	int count=0;
	fprintf(stdout, "getc/putc\n");
	while( (c = getc(stdin)) != EOF ){
		if(putc(c,stdout) == EOF)
			err_sys("output error");
		count++;
	}
		
	if(ferror(stdin))
		err_sys("input error");

	fprintf(stdout,"count:%d\n",count);
	exit(0);
}

