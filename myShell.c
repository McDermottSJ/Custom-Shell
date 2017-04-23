#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

char *prompt;

void signalHandler(int no){
	printf("Sig handler got a [%d]\n", no);
	printf("%s", prompt);
	return;
}

int main(int argc, char *argv[]){
	char rawInput[50];
	char *input[50][50];
	int count = 0;

	signal(SIGINT, signalHandler);


	if(argc > 1){
		prompt = argv[1];
		strcat(prompt, ">>");
	}
	else{
		prompt = "257sh>>";
	}

	while(1){
		printf("%s", prompt);
		scanf("%s\n", &rawInput);
		printf("%s", rawInput);		
		printf("%s", strtok(rawInput, " "));

		
		while(strtok(NULL, " ")){
			count++;
			printf(input);
		}

		if(strcmp(rawInput, "exit")==0){
			raise( SIGKILL );//TODO why cant I use SIGKILL?
		}
		else if(strcmp(rawInput, "qqq")== 0){//TODO REMOVE, For Debugging
			exit(0);
		}
		else if(strcmp(rawInput, "pid") == 0){
			
		}
		else if(strcmp(rawInput, "ppid") == 0){
			
		}
		else if(strcmp(rawInput, "cd") == 0){
			
		}
		else{
			//fork();
			//execvp(input, test[]);
			//wait();
			//fflush(0);
		}

		printf("%s%s\n", prompt, rawInput);
	}
}
