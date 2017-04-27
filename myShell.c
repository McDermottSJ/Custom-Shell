#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>


char *prompt;

//****************************************************************************
//function: parseString
//description: takes a string and breaks it into an array of strings based on a deliminator
//
//input: a input string (char array), an output array of strings (2d char array), and a deliminator given as a string
//output: N/A
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


//****************************************************************************
//function: printPrompt
//description: determins the current folder and appends it to the current prompt (either the user defined or the defualt one) and prints it
//
//input: N/A
//output: N/A
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


//****************************************************************************
//function: signalHandler
//description: Handles the SIG INTERUPT signal (ctrl C)
//
//input: N/A
//output: N/A
void signalHandler(int no){
	printf("\nSignal handler caught a [%d]\n", no);
	return;
}

int main(int argc, char *argv[]){
	char rawInput[50];
	char *cmd[50];
	int i;
	char delim[2] = " ";

	signal(SIGINT, signalHandler);

	//Check if user requested a prompt
	if(argc > 1){
		prompt = argv[1];
	}
	else{
		prompt = "257sh";
	}

	while(1){
		printPrompt();	
		
		//clear all the input
		for(i=0;i<50;i++){
			rawInput[i] = NULL;
			
		}
		//take in the input, take out the new line, and append a null terminator
		fgets(rawInput, sizeof(rawInput), stdin);
		rawInput[strlen(rawInput)-1] = '\0';
		
		//check for null input
		if(strcmp(rawInput, "") == 0){
			printf("%n");
			continue;
		}
		
		//change the string to an array of commands and args
		parseString(rawInput, cmd, delim);
		
		//test for non-default commands
		if(strcmp(cmd[0], "exit")==0){
			raise( SIGKILL );
		}
		else if(strcmp(cmd[0], "pid") == 0){
			printf("%d\n", getpid());	
		}
		else if(strcmp(cmd[0], "ppid") == 0){
			printf("%d\n", getppid());
		}
		else if(strcmp(cmd[0], "cd") == 0){
			if(cmd[1]){
				chdir(cmd[1]);//if there is an argument, change the directory
			}
			else{//else get the current and print it out
				char dir[50];
				getcwd(dir, 50);
				printf("%s\n", dir);
			}
		}
		//built in commands
		else{
			int returnCode = 0;
			pid_t pid;
			
			//create a child proccess to execute the command
			if((pid = fork()) < 0){
				printf("forking error.\n");
				continue;
			}else if(pid == 0){
				if(execvp(*cmd, cmd)){//execute the command
					printf("command execution error\n");//if it does not compute, return an error
					exit(1);
				}

				exit(0);
			}else{
				wait(&returnCode);//wait for child
			}

			printf("executed with return code %d\n", returnCode);
			
			
		}
	}
}
