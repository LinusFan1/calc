#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 1024
#define TOK_DELIM " "

bool operatorCheck(char* input){
return (strcmp(input,"+") == 0 || strcmp(input,"-") == 0 || strcmp(input,"*") == 0 || strcmp(input,"/") == 0 || strcmp(input,"^") == 0 || strcmp(input,"%") == 0);
}

char** parseString(char* input){
int i = 0;
char** tokens = malloc(BUFF_SIZE * sizeof(char*));
char* token;
token = strtok(input, TOK_DELIM);
while(token != NULL){
	tokens[i] = token;
	i++;
	if(!tokens){
		fprintf(stderr, "Allocation Error");
		exit(EXIT_FAILURE);
	}
	token = strtok(NULL,TOK_DELIM);
}
tokens[i] = NULL;
return tokens;
}

void ctruncArr(char** arr, char* input, int i, int j){
//printf("index: %d\n", i);
char* temp;
strcpy(arr[i],input);
i = i+j+1;
while(arr[i] != NULL){
temp = arr[i];
//printf("temp: %s at index: %d\n",temp,i);
arr[i-j] = temp;
i++;
}
for(j; j > 0; j--){
arr[i-j] = NULL;
}	
}

int calc(char** input){
int i = 0;
char* tempChar = malloc(sizeof(char) * BUFF_SIZE);
bool operator;
int output;
for(int j = 0; j < 3; j++){
i = 0;
while(input[i] != NULL){
//	printf("Value: %s at index: %d\n",input[i],i);
	i++;
}
	i = 0;
	while(input[i] != NULL){
	if(operatorCheck(input[i])){
	if(operatorCheck(input[i+1])){
		fprintf(stderr, "Arithmetic Error");
		exit(EXIT_FAILURE);	
	}
//	printf("Numbers Being Evaluated at index i: %d & j: %d\n",i,j);
//	printf("%s\n",input[i-1]);
//	printf("%s\n",input[i+1]);
	operator = true;
	switch(j){
		case 0:
			switch(input[i][0]){
			case '^':
				output = pow(atoi(input[i-1]),atoi(input[i+1]));
			break;
			case '%':
				output = atoi(input[i-1]) % atoi(input[i+1]);
			break;
			default:
				operator = false;
			break;
			}
		break;
		case 1:
			switch(input[i][0]){
			case '*':
				output = atoi(input[i-1]) * atoi(input[i+1]);
			break;
			case '/':
				output = atoi(input[i-1]) / atoi(input[i+1]);
			break;
			default:
				operator = false;
			break;
			}
		break;
		case 2:
			switch(input[i][0]){
			case '+':
				output = atoi(input[i-1]) + atoi(input[i+1]);
			break;
			case '-':
				output = atoi(input[i-1]) - atoi(input[i+1]);
			break;
			default:
				operator = false;
			break;
			}
		break;
		default:
			fprintf(stderr, "Out Of Bounds index");
			exit(EXIT_FAILURE);
			break;
		}
		if(operator){
		snprintf(tempChar, (int)((ceil(log10(output)) + 1) * sizeof(char)), "%d", output);
	//	printf("Output:%s\n",tempChar);
		ctruncArr(input,tempChar,(i-1),2);
		i -= 2;
		}
		i += 2;
	}
	else{
		i++;
	}
}
}
return output;
}

int main(){
char* input = malloc(sizeof(char) * BUFF_SIZE);
while(1){
printf("Calc Program\n");
fgets(input, BUFF_SIZE, stdin);
char** parsedInput = parseString(input);
int i =0;
if(strcmp(input,"exit") == 0 || strcmp(input,"Exit") == 0){
	fprintf(stdout, "Exiting Calc....\n");
	exit(EXIT_SUCCESS);
}
while(parsedInput[i] != NULL){
if((!operatorCheck(parsedInput[i])) && (((int)parsedInput[i][0] < 47) || ((int)parsedInput[i][0] > 57))){
fprintf(stderr, "Unrecognized Operator\n");
exit(EXIT_FAILURE);
}
i++;
}
int j = 0;
j = calc(parsedInput);
printf("%d\n", j);
}
return 0;
}
