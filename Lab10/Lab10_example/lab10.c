#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include<stdbool.h>

void put_pull_rod(int signum);
void fish_eating();
void exit_game(int signum);
void escape();
int test_rand(void);

int fishNum = 0;	// counting fish number
bool boolean = false;	// used as a boolean
bool is_bite=false;
bool get=false;



int main(void){

	srand(time(0));



	struct sigaction sig_put_pull_rod;
	sig_put_pull_rod.sa_handler = put_pull_rod;
	sigemptyset(&sig_put_pull_rod.sa_mask);
    sig_put_pull_rod.sa_flags = 0;
	
	struct sigaction sig_exit_game;
	sig_exit_game.sa_handler = exit_game;
	sigemptyset(&sig_exit_game.sa_mask);
    sig_exit_game.sa_flags = 0;

	struct sigaction bit_alarm;
	memset(&bit_alarm, 0, sizeof(bit_alarm));
	bit_alarm.sa_handler = fish_eating;

	if(sigaction(SIGALRM,&bit_alarm,NULL)<0){
        perror("signal errror");
        exit(EXIT_FAILURE);
    }

	if(sigaction(SIGINT,&sig_put_pull_rod,NULL)<0){
        perror("signal errror");
        exit(EXIT_FAILURE);
    }

	if(sigaction(SIGTSTP,&sig_exit_game,NULL)<0){
        perror("signal errror");
        exit(EXIT_FAILURE);
    }

	printf("Fishing rod is ready!\n");
	//write your code here
	while(1){}
    
	return 0;
}


void put_pull_rod(int signum){
	if(!boolean){
		printf("\nPut the fishing rod\n");
		sleep(2);
		printf("Bait into water, waiting fish...\n");
		int r=test_rand();
		alarm(r%5+1);
		boolean=true;
	}else{
		printf("\nPull the fishing rod\n");
		if(is_bite){
			if(get){
				printf("Catch a Fish!!\n");
				printf("Totally caught fishes: %d\n", ++fishNum);
				alarm(1000);   //cancel alarm
			}else{
				printf("The bait was eaten!!\n");
			}
			get=false;
			is_bite=false;
		}
		boolean=false;
		printf("Fishing rod is ready!\n");
	}
}

void escape(){
	printf("The fish was escaped!!\n");
	get=false;
}

void fish_eating(){
	if(boolean){
		printf("A fish is biting,pull the fishing rod\n");
		get=true;
		is_bite=true;
		sleep(2);
		if(get){
			escape();
		}
	}	
}

void exit_game(int signum){
	printf("\nTotally caught fishes: %d\n", fishNum);
	exit(0);
}

int test_rand(void){
	return rand();
}
