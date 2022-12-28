#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1024
#define TOK_DELIM " "

char* parseToks(){
int i = 0;
char *buffer = malloc(sizeof(char)*BUFF_SIZE);
int c;
	while(1){
		c = getchar();
		if(c == EOF || c == '\n'){
			buffer[i] = '\0';
		}
		else{
			buffer[i] = c;
		}
		i++;
	}
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

void switchArray(){

}

int calc(char** input){
int i = 0;
while(input[i] != NULL){
	printf("%s\n",input[i]);
	i++;
}
i = 0;
int output;
while(input[i] != NULL){
	if(strcmp(input[i],"+") == 0 || strcmp(input[i],"-") == 0 || strcmp(input[i],"*") == 0 || strcmp(input[i],"/") == 0 || strcmp(input[i],"^") == 0 || strcmp(input[i],"%") == 0){
	if(strcmp(input[i+1],"+") == 0 || strcmp(input[i+1],"-") == 0 || strcmp(input[i+1],"*") == 0 || strcmp(input[i+1],"/") == 0 || strcmp(input[i+1],"^") == 0 || strcmp(input[i+1],"%") == 0 || input[i+1] == NULL){
		fprintf(stderr, "Arithmetic Error");
		exit(EXIT_FAILURE);	
	}
	printf("%s\n",input[i-1]);
	printf("%s\n",input[i+1]);
		switch(input[i][0]){
		case '^':
			output = pow(atoi(input[i-1]),atoi(input[i+1]));
		break;
		case '%':
			output = atoi(input[i-1]) % atoi(input[i+1]);
		break;
		case '*':
			output = atoi(input[i-1]) * atoi(input[i+1]);
		break;
		case '/':
			output = atoi(input[i-1]) / atoi(input[i+1]);
		break;
		case '+':
			output = atoi(input[i-1]) + atoi(input[i+1]);
		break;
		case '-':
			output = atoi(input[i-1]) - atoi(input[i+1]);
		break;
		default:
			fprintf(stderr, "Unrecongnized Operator");
			exit(EXIT_FAILURE);
			break;
		}
		snprintf(input[i+1], (int)(log10(output) * sizeof(char)), "%d", output);
		i += 2;
	}
	else{
		i++;
	}
}
return output;
}

int main(){
printf("Calc Program\n");
char* input = malloc(sizeof(char) * BUFF_SIZE);
fgets(input, BUFF_SIZE, stdin);
char** parsedInput = parseString(input);
int j = 0;
j = calc(parsedInput);
printf("%d", j);
return 0;
}
