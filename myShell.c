#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>


char *prompt;

void parseString(char *input, char *output[], char delim[]){
	int i = 0;

	//seperate into usable arguments
	output[0] = strtok(input, delim);
	i = 1;
	while(output[i] = strtok(NULL, delim)){
		i++;
	}
	output[i]='\0';
	
}

void printPrompt(){
	char dir[50];
	char *path[50];
	char delim[2] = "/";
	int i;

	getcwd(dir, 50);
	parseString(dir, path, delim);
	
	for(i =0; i < 50; i++){
		if(path[i] == NULL){
			break;
		}
	}

	printf("%s@%s>> ", prompt, path[i-1]);
	return;
}

void signalHandler(int no){
	printf("\nSignal handler caught a [%d]\n", no);
	return;
	//TODO fix prompt formatting
}

int main(int argc, char *argv[]){
	char rawInput[50];
	char *cmd[50];
	int i;
	char delim[2] = " ";

	signal(SIGINT, signalHandler);


	if(argc > 1){
		prompt = argv[1];
	}
	else{
		prompt = "257sh";
	}

	while(1){
		printPrompt();	
		
		//get raw input
		for(i=0;i<50;i++){
			rawInput[i] = NULL;
			
		}
		fgets(rawInput, sizeof(rawInput), stdin);
		rawInput[strlen(rawInput)-1] = '\0';
		
		if(strcmp(rawInput, "") == 0){
			printf("%n");
			continue;
		}

		parseString(rawInput, cmd, delim);
		
		/*
		//seperate into usable arguments
		cmd[0] = strtok(rawInput, delim);
		i = 1;
		//printf("cmd: %s\n", cmd[0]);//TODO remove
		while(cmd[i] = strtok(NULL, delim)){
			
			//printf("arg: %s\n", cmd[i]);//TODO remove
			i++;
		}
		cmd[i]='\0';
		*/
		if(strcmp(cmd[0], "exit")==0){
			raise( SIGKILL );
		}
		else if(strcmp(cmd[0], "qqq")== 0){//TODO REMOVE, For Debugging
			exit(0);
		}
		else if(strcmp(cmd[0], "pid") == 0){
			printf("%d\n", getpid());	
		}
		else if(strcmp(cmd[0], "ppid") == 0){
			printf("%d\n", getppid());
		}
		else if(strcmp(cmd[0], "cd") == 0){
			if(cmd[1]){
				chdir(cmd[1]);
			}
			else{
				char dir[50];
				getcwd(dir, 50);
				printf("%s\n", dir);
			}
		}
		else{
			int returnCode = 0;
			pid_t pid;
			
			
			if((pid = fork()) < 0){
				printf("forking error.\n");
				continue;
			}else if(pid == 0){
				if(execvp(*cmd, cmd)){
					printf("command execution error\n");
					exit(1);
				}

				exit(0);
			}else{
				wait(&returnCode);
			}

			printf("executed with return code %d\n", returnCode);
			
			
		}
	}
}
