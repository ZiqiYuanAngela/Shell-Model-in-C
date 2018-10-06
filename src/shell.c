/*
 ============================================================================
 Name        : proj.c
 Author      : Ziqi_Yuan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

	char* args[50];
	int should_run=1;
	char str[50];//to store the input command from user
	char *token=malloc(sizeof(char));
	int w=1;//Indicate whether the parent process should wait or not
	pid_t pid;

	printf("CS149 Shell from Ziqi Yuan\n");
	fflush(stdout);
	while(should_run){
		printf("Ziqi-026>");
		//fgets(str,80,stdin);
		//scanf("%[^\n]s",str);

		gets(str,stdin);

		args[0]=strtok(str," ");
		if(strcmp(args[0],"exit")==0){//check if the user requests to exit
				should_run=0;
			}


		else{
		token=strtok(NULL," ");
		int i=1;
			while(token!=NULL ){//Fill the args array with tokens
			args[i]=token;
			token=strtok(NULL, " ");
			++i;
			}


			if(strcmp(args[i-1],"&")==0){//check if wait required or not
                 w=0;//wait not required
                 args[i-1]=NULL;
			}else{
				args[i]=NULL;
			}


			pid=fork();//create child process

			if(pid<0){//fork() error
				fprintf(stderr,"Fork failed.\n");
				return 1;
			}
			else if(pid==0){/*child process*/
                execvp(args[0],args);
				fprintf(stderr,"Exec failed.\n");
				return 1;
			}
     	    else{/*parent process*/
				if(w){
					wait(NULL);
				}

		}
		}
	}

	return EXIT_SUCCESS;
}
