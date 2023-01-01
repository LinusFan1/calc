#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 1024
#define TOK_DELIM " "
#define LIMIT 0.001


typedef enum{
	EXPONENT,
	MODULUS,
	MULTIPLY,
	DIVIDE,
	ADD,
	SUBTRACT,
	NO_OP
}
operator;

typedef enum{
	DIF,
	INT,
	SIN,
	COS,
	TAN,
	NO_FUNC
}
func;

func toFunc(char* input){
switch (input[0]){
	case 'd':
		return DIF;
	break;	
	default:
		return 	NO_FUNC;
	break;
}
}

operator toOp(char* input){
switch (input[0]){
	case '^':
		return EXPONENT;
	break;
	case '%':
		return MODULUS;
	break;
	case '*':
		return MULTIPLY;
	break;
	case '/':
		return DIVIDE;
	break;
	case '+':
		return ADD;
	break;
	case '-':
		return SUBTRACT;
	break;
	default:
		return NO_OP;
	break;
}
}
bool operatorCheck(char* input){
return (strcmp(input,"+") == 0 || strcmp(input,"-") == 0 || strcmp(input,"*") == 0 || strcmp(input,"/") == 0 || strcmp(input,"^") == 0 || strcmp(input,"%") == 0 || input[0] == '(');
}

char* substr(char* string, int i, int j){
char* newString = malloc(sizeof(char) * ((j - i) + 1));
int k = 0;
char temp;
while (i < j + 1){
newString[k] = string[i];  
k++;
i++;
}
newString[k] = '\0';
return newString;
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
for(int h = j; h > 0; h--){
arr[i-h] = NULL;
}	
}

char** parseString(char* input){
int i = 0;
char** tokens = malloc(BUFF_SIZE * sizeof(char*));
char* token;
token = strtok(input, TOK_DELIM);
if(!token){
fprintf(stderr,"this is an error");
exit(EXIT_FAILURE);
}
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
int j = 0;
i = 0;
char* tempChar = malloc(sizeof(char) * BUFF_SIZE);
while (tokens[i] != NULL){
	if(strchr(tokens[i],'(') != NULL){
		strcpy(tempChar,tokens[i]);
		strcat(tempChar," ");
		i++;
		j++;
		while((strchr(tokens[i],')') == NULL)){
			strcat(tempChar,tokens[i]);
			if(strchr(tokens[i+1],')') != NULL){
			strcat(tempChar," ");
			}
			i++;
			j++;
			if(tokens[i] == NULL){
				fprintf(stderr,"Unpaired Delimiter");
				exit(EXIT_FAILURE);
			}
		}
			strcat(tempChar,tokens[i]);
			strcat(tempChar,"");
			printf("%s\n",tempChar);
			ctruncArr(tokens,tempChar,(i-j),j);
			i = i - j;
			j = 0;
	}	
	i++;
}
tokens[i] = NULL;
return tokens;
}

int eval(int a, int b, operator o){
int out;
switch(o){
	case 0:
		return pow(a,b);
	break;
	case 1:
		return a % b;	
	break;
	case 2:
		return a * b;
	break;
	case 3:
		return a / b;
	break;
	case 4:
		return a + b;
	break;
	case 5:
		return 	a - b;
	break;
	case 6:
	      fprintf(stderr,"Invalid Operator");
	      exit(EXIT_FAILURE);
	break;
}
}

/* char* diff(char* input, char var){
	int i = 0;	
	while(input[i] != 0){
		if(toOp(input[i]) != 6){
			switch(toOp(input[i])){
				case 0:
					input[i-1] = eval(atoi(input[i-1]),atio(input[i+1]),MULTIPLY);
			}
				}
	}
}*/

char* evalFunc(char* input, func f, char var){
switch(f){
	case 0:
//		return diff(input, var);	
	break;
	case 1:
		fprintf(stderr, "Invalid Operator");
		exit(EXIT_FAILURE);
	break;
}
}

char** evalExp(char** input, char var){
char* tempString = malloc(sizeof(char) * BUFF_SIZE);
char* cDumb = malloc(sizeof(char) * 3);
int i = 0;
int out;
while(input[i] != NULL){
	if(toOp(input[i]) != 6){
		if(strchr(input[i-1],var) != NULL && strchr(input[i+1],var) != NULL){
			input[i-1][(int)(strchr(input[i-1],var) - input[i-1])] = '\0';
			input[i+1][(int)(strchr(input[i+1],var) - input[i+1])] = '\0';
			out = eval(atoi(input[i-1]),atoi(input[i+1]),toOp(input[i]));
			snprintf(tempString, (int)((ceil(log10(out)) + 1) * sizeof(char)), "%d", out);
			cDumb[0] = var;
			cDumb[1] = '\0';
			strcat(tempString,cDumb);
			ctruncArr(input,tempString,(i-1),2);
			i--;
		}
		else if(strchr(input[i-1],var) == NULL && strchr(input[i+1],var) == NULL){
			out = eval(atoi(input[i-1]),atoi(input[i+1]),toOp(input[i]));
			snprintf(tempString, (int)((ceil(log10(out)) + 1) * sizeof(char)), "%d", out);
			ctruncArr(input,tempString,(i-1),2);
			i--;
		}
	}
//	if(toFunc(input[i]) != 1 ){
//		input[i] = evalFunc(input[i],toFunc(input[i]),var);	
//	}
	i++;
}
return input;
}

int calc(char** input){
int i = 0;
char* tempChar = malloc(sizeof(char) * BUFF_SIZE);
bool operator;
int output = 0;
for(int j = 0; j < 4; j++){
	i = 0;
	while(input[i] != NULL){
	if(operatorCheck(input[i])){
//	if(operatorCheck(input[i+1]) && (input[i][0] != '(') && (input[i+1][0] != '(')){
//		fprintf(stderr, "Arithmetic Error");
//		exit(EXIT_FAILURE);	
//	}
//	printf("Number Being Evaluated at index i: %d & j: %d\n",i,j);
//	printf("%s\n",input[i]);
//	printf("%s\n",input[i+1]);
	operator = true;
	switch(j){
		case 0:
			switch(input[i][0]){
			case '(':
				output = calc(parseString(substr(input[i],1,strchr(input[i],')') - input[i] - 1)));
				printf("%d\n",output);
				snprintf(tempChar, (int)((ceil(log10(output)) + 1) * sizeof(char)), "%d", output);
				strcpy(input[i],tempChar);
				operator = false;
			break;
			default:
				operator = false;
			break;
			}
		case 1:
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
		case 2:
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
		case 3:
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
		ctruncArr(input,tempChar,(i-1),2);
		i--;
		}
	}
	i++;
}
}
return output;
}

int main(){
char** answer = malloc(sizeof(char*) * BUFF_SIZE);
char* input = malloc(sizeof(char) * BUFF_SIZE);
char var = 'x';
while(1){
printf("Calc Program\n");
fgets(input, BUFF_SIZE, stdin);
char** parsedInput = parseString(input);
int i =0;
while(parsedInput[i] != NULL){
	printf("%s\n",parsedInput[i]);
	i++;
}
i = 0;
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
answer = evalExp(parsedInput,var);
//j = calc(parsedInput);
printf("%s\n", answer[0]);
//printf("%d\n",j);
}
return 0;
}
