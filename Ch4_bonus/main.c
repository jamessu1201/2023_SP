#include "apue.h"
#include <dirent.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define ERR 0
#define REG 1
#define DIRC 2
#define CHR 3
#define BLK 4
#define FIFO 5
#define LNK 6
#define SOCK 7
#define UNK 8


static long long int amount[10]={0};

typedef struct stack{
	char name[10000];
	struct stack *up;
}Stack;

bool is_empty(Stack *bottom){
	if(bottom->up==NULL){
		return true;
	}
	return false;
}

int size(Stack *bottom){
	int count=0;
	Stack *search=bottom->up;
	while(search!=NULL){
		count++;
		search=search->up;
	}
	return count;
}

void push(Stack *bottom,char* name){
	Stack *insert=bottom;
	while(insert->up!=NULL){
		insert=insert->up;
	}
	Stack *new=(Stack*)malloc(sizeof(Stack));
	new->up=NULL;
	strcpy(new->name,name);
	insert->up=new;
}

char* pop(Stack *bottom){
	if(is_empty(bottom)){
		printf("isempty.\n");
		return NULL;
	}
	Stack *last=bottom;
	Stack *remove=bottom->up;
	while(remove->up!=NULL){
		last=remove;
		remove=remove->up;
	}
	char* remove_name=(char *)malloc(10000*sizeof(char));
    strcpy(remove_name,remove->name);
	free(remove);
	remove=NULL;
	last->up=NULL;
	return remove_name;
}

int atr(char* filename){
    struct stat buf;
    if(lstat(filename,&buf)<0){
        err_ret("lstat error");
        return ERR;
    }
    if(S_ISREG(buf.st_mode)) return REG;
    else if(S_ISDIR(buf.st_mode)) return DIRC;
    else if(S_ISCHR(buf.st_mode)) return CHR;
    else if(S_ISBLK(buf.st_mode)) return BLK;
    else if(S_ISFIFO(buf.st_mode)) return FIFO;
    else if(S_ISLNK(buf.st_mode)) return LNK;
    else if(S_ISSOCK(buf.st_mode)) return SOCK;
    else return UNK;
}

void slice(const char *str, char *result, size_t start, size_t end){
    strncpy(result, str + start, end - start);
}

int main(int argc,char *argv[]){
    Stack *bottom=(Stack*)malloc(sizeof(Stack));   //init stack
	bottom->up=NULL;

    DIR* dirp;
    struct dirent *direntp;

    char root[]="/mnt";
    char filename[10000];
    int status=chdir(root);   //change dir to mnt
	if(status==-1) perror("Error");


    push(bottom,root);
    
    while(!is_empty(bottom)){       //use dfs to find all files
       
        char cwd[10000];
        
        strcpy(filename,pop(bottom));

        status=chdir(filename);   //change dir to filename
	    if(status==-1) perror("Error0");
        getcwd(cwd, sizeof(cwd));
        if((dirp=opendir(cwd))==NULL){
            printf("Error: %s\n",strerror(errno));
            continue;
        }
        while((direntp=readdir(dirp))!=NULL){
            int attr=atr(direntp->d_name);
            //printf("%s%s %d\n",cwd,direntp->d_name,attr);
            amount[attr]++;
            if(attr==DIRC&&strcmp(direntp->d_name,".")&&strcmp(direntp->d_name,"..")){
                char slash[]="/";
                char path[10000];
                strcpy(path,cwd);
                strcat(slash,direntp->d_name);
                strcat(path,slash);
                push(bottom,path);
            }
        }
        closedir(dirp);
    }
    
    for(int i=1;i<8;i++){
        amount[9]+=amount[i];
    }
    if (amount[9] == 0)
        amount[9] = 1; /* avoid divide by 0; print 0 for all counts */
    printf("regular files = %7lld, %5.2f %%\n", amount[1],amount[1]*100.0/amount[9]);
    printf("directories = %7lld, %5.2f %%\n", amount[2],amount[2]*100.0/amount[9]);
    printf("block special = %7lld, %5.2f %%\n", amount[3],amount[3]*100.0/amount[9]);
    printf("char special = %7lld, %5.2f %%\n", amount[4],amount[4]*100.0/amount[9]);
    printf("FIFOs = %7lld, %5.2f %%\n", amount[5],amount[5]*100.0/amount[9]);
    printf("symbolic links = %7lld, %5.2f %%\n", amount[6],amount[6]*100.0/amount[9]);
    printf("sockets = %7lld, %5.2f %%\n", amount[7],amount[7]*100.0/amount[9]);
    exit(0);
}

