#include "apue.h"
#include<fcntl.h>

#define	BUFFSIZE	16384

int main(void)
{
		int		n;
		char	buf[BUFFSIZE];

		char location[]="/dev/null";
        int fd=open(location,O_RDWR);
		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
				
				if (write(fd, buf, n) != n)
						err_sys("write error");
		}

		if (n < 0)
				err_sys("read error");

		exit(0);
}
