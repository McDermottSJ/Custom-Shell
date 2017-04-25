#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

char *prompt;

void signalHandler(int no){
	printf("Sig handler got a [%d]\n", no);
	printf("%s", prompt);
	return;
	//TODO fix prompt formatting
}

int main(int argc, char *argv[]){
	char rawInput[50];
	char *cmd[50];
	char *cmdArgs;
	int i;
	const char *token;
	char delim[2] = " ";

	//signal(SIGINT, signalHandler);


	if(argc > 1){
		prompt = argv[1];
		strcat(prompt, ">>");
	}
	else{
		prompt = "257sh>>";
	}

	while(1){
		
		//Clear out command
		printf("%s", prompt);
		
		//get raw input
		for(i=0;i<50;i++){
			rawInput[i] = NULL;
			
		}
		fgets(rawInput, sizeof(rawInput), stdin);
		rawInput[strlen(rawInput)-1] = '\0';
		
		//seperate into usable arguments
		cmd[0] = strtok(rawInput, delim);
		i = 1;
		//printf("cmd: %s\n", cmd[0]);//TODO remove
		while(cmd[i] = strtok(NULL, delim)){
			
			//printf("arg: %s\n", cmd[i]);//TODO remove
			i++;
		}

		if(strcmp(cmd[0], "exit")==0){
			raise( SIGKILL );
		}
		else if(strcmp(cmd[0], "qqq")== 0){//TODO REMOVE, For Debugging
			exit(0);
		}
		else if(strcmp(cmd[0], "pid") == 0){
			
		}
		else if(strcmp(cmd[0], "ppid") == 0){
			
		}
		else if(strcmp(cmd[0], "cd") == 0){
			
		}
		else{
			int returnCode;
			int pid = fork();
			if(pid < 0){
				printf("forking error.");
				returnCode = 1;
				continue;
			}else if(pid = 0){
				if(execvp(cmd[0], cmd)){
					printf("command execution error");
					exit(1);
				}
				exit(0);
			}else{
				wait(&returnCode);
			}

			printf("executed with return code %d\n", returnCode);
			returnCode = 666;
			//fflush(0);
		}
	}
}
