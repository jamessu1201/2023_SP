#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

int main()
{
	FILE* sum;
	int total_sum=0;
	pid_t pid[5];
	int year=5, week=52, day=7;

	sum = fopen("sum.txt", "w");
	fprintf(sum, "%d\n", 0);
	fclose(sum);

	/**********************************************************/

	//Implement your code.

	TELL_WAIT();

	for(int i=0;i<5;i++){
		if((pid[i]=fork())<0){
			err_sys("fork error");
		}else if(pid[i]==0){	//child
			for(int j=1;j<=52;j++){
				char *filename;
				sprintf(filename,"%d-%02d.txt",i+1,j);   //if less than ten add 0
				//printf("%s\n",filename);
				FILE *fp = fopen(filename, "r");
				for(int k=0;k<7;k++){
					int sum=0;
					for(int l=0;l<96;l++){
						int a=0;
						fscanf(fp,"%d",&a);
						sum+=a;
					}
					//printf("%d\n",sum);
					WAIT_PARENT();
					accumulation(sum);
					TELL_PARENT(getppid());
				}
    			fclose(fp);
			}
			exit(0);
		}else{		//parent
			for(int j=0;j<52*7;j++){
				TELL_CHILD(pid[j%5]);
				WAIT_CHILD();
			}
		}
	}




	/**********************************************************/

	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
	printf("Day_Average = %d\n",total_sum/(year*week*day));
	fclose(sum);

	return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{
	FILE* sum;
	int tmp=0;

	sum = fopen("sum.txt", "r+");
	fscanf(sum, "%d", &tmp);

	tmp += d_sum;

	rewind(sum);
	fprintf(sum, "%d", tmp);
	fclose(sum);

	return;
}
