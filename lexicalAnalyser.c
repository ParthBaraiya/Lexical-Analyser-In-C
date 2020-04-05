#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

// Array of Keywords
char keywords[40][10] = {
	"auto\0", "break\0", "case\0", "char\0",
	"const\0", "continue\0", "default\0", "do\0",
	"double\0", "else\0", "enum\0", "extern\0",
	"float\0", "for\0", "goto\0", "if\0",
	"int\0", "long\0", "register\0", "return\0",
	"short\0", "signed\0", "sizeof\0", "static\0",
	"struct\0", "switch\0", "typedef\0", "union\0",
	"unsigned\0", "void\0", "volatile\0", "while" , "/"};

// Array of Operators
char operators[45][10] = {
	"(\0", ")\0", "{\0", "}\0", "[\0", "]\0", ".\0",
	"+\0", "-\0", "/\0", "*\0", "%\0",
	"\\\0",
	"++\0", "--\0",
	"=\0", "+=\0", "-=\0", "*=\0", "/=\0", "%=\0",
	"==\0", "<\0", ">\0", "<=\0", ">=\0", "!=\0",
	"&\0", "|\0", "^\0", "~\0", "<<\0", ">>\0",
	"||\0", "&&\0", "!\0",
	";\0", ",\0", "?\0", ":\0", "->\0", "e"};


// Checks if parsed character is valid part of identifier or not
int isIdentifier(char c) {
	int a = (int) c;
	if ( (c >= (int) 'A' && c <= (int) 'Z') || 
	    (c >= (int) 'a' && c <= (int) 'z') || 
	    (c >= (int) '0' && c <= (int) '9') || 
	    c == '_' ) return 1;

	return 0;
}


// Checks if parsed string is a valid keyword or not
int isKeyword(char str[]) {
	int i = 0;
	int match = 1;
	while (keywords[i][0] != '/') {
		int j=0;
		match = 1;
		while(1) {
			if(keywords[i][j] != str[j] || (keywords[i][j] == '\0' && str[j] != '\0') || (keywords[i][j] != '\0' && str[j] == '\0')){
				match = 0;
				break;
			}
			if(keywords[i][j] == '\0' && str[j] == '\0') break;
			j++;
		}
		if(match == 1) return 1;
		i++;
	}
	return 0;
}


// Checks of parsed string is a valid keyword or not
int isOperator(char str[]) {
	int i = 0;
	int match = 1;
	while (operators[i][0] != 'e') {
		int j=0;
		match = 1;
		while(1) {
			if(operators[i][j] != str[j] || (operators[i][j] == '\0' && str[j] != '\0') || (operators[i][j] != '\0' && str[j] == '\0')){
				match = 0;
				break;
			}
			if(operators[i][j] == '\0' && str[j] == '\0') break;
			j++;
		}
		if(match == 1) return 1;
		i++;
	}
	return 0;
}

int isNumber(char c){
	if((int) c >= (int) '0' && (int) c <= (int) '9') return 1;
	return 0;
}


// Main Function
void main() {

	int INSUFFICIENT_SPACE = 0;

	// Stores previous fetched character
	char prev_char;

	// Determine that we should fetch next character from file or not
	// If 1 then fetch new character from file
	// Else Get Character stored in prev_char
	int getnext = 1;
	int i=0;

	// Determine if given file has data in it or not
	// if 0 then file has data else not
	int hasData = 0;


	// Stack data
	int MAX_CHAR = 10;
	int CURR_CHAR = 0;
	char *char_stack;

	// File data
	char f_name[30]; // File name
	FILE *file;

	printf("Enter file name: ");
	gets(f_name);

	file = fopen(f_name, "r");

	// Checks if file is exist or not
	if (file == NULL) {
		printf("File can not open.");
	}
	else {
		// Stores first character of file in c;
		char c = fgetc(file);

		while (c != EOF) {
			// Allocate a memory block of size  MAX_CHAR*sizeof(char)
			char_stack = (char *)calloc(MAX_CHAR, sizeof(char));
			
			// Checks if memory is successfully allocated or not
			if(char_stack == NULL) {
				INSUFFICIENT_SPACE = 1;
				break;
			}
			
			// Initialize block with \0
			for(i=0;i<MAX_CHAR;i++) {
				char_stack[i] = '\0';
			}


			// Assign new or previous character to first place in char_stack according to getnext and prev_char
			if (getnext == 1) char_stack[CURR_CHAR++] = c;
			else {
				char_stack[CURR_CHAR++] = prev_char;
				getnext = 1;
			}
			
			// printf("Currunt stack: %s", char_stack);

			// Removes next line character and blank spaces
			if(char_stack[CURR_CHAR-1] == ' ' || char_stack[CURR_CHAR-1] == '\n' || char_stack[CURR_CHAR-1] == '\t'){
					
			}

			// String Check
			else if (char_stack[0] == '\"') {
				
				// printf("Inside string check........................................\n\n");
				// Confirms file has data
				hasData = 1;
				printf("\"");

				// Fetch next character from file
				char sc = fgetc(file);

				// Flag which determien whether string is validd or not
				// If String Starts with " s well as end with " then string is valid else not
				int isValid = 0;

				// Runs untill reaches end of file or encounter " operator
				while (sc != EOF) {

					// If character is other than " then print it
					if (sc != '\"') printf("%c", sc);

					// If character is " then change isValid flag to 1 and break the loop printing valid string info.
					else {
						isValid = 1;
						printf("\" is a valid String Litral.\n\n");
						break;
					}

					// Fetch next character from file
					sc = fgetc(file);
				}
				if (isValid == 0) printf(" is a invalid.");

				// printf("Exit String check.");
			}
		
			// Operator Check
			else if (isOperator(char_stack) == 0) {

				// printf("Inside Keyword and Identifier check........................................................... \n\n\n\n");

				// Flag which determines string stored in char_stack is valid identifier or not
				int isId = 1;

				// Flag which determines string stored in char_stack is valid number or not
				int isNum = 1;

				// Confirms file has data
				hasData = 1;

				// Checks if string stored in char_stack is valid identifier or not and change isId flag according to it
				// If its invalid then isId will be changed to 0
				if(isIdentifier(char_stack[0]) == 0) isId = 0;

				if(!(isNumber(char_stack[0]))) isNum = 0;

				// Stores next character of file in sc
				char sc[2] = {fgetc(file),'\0'};
				
				while (sc[0] != EOF) {

					// printf("Current character: %c\n\n", sc[0]);

					// Checks if fetched character is a valid operator or not
					// If it is a valid operator then set prev_char and getnext variables and break the loop
					if (isOperator(sc)) {
						prev_char = sc[0];
						getnext = 0;
						break;
					}

					// If blank space is encountered then break the loop
					if (sc[0] == ' ') break;


					// Checks is character is a valid number or not
					// It will help to decide whether string is valid number or not
					if(!isNumber(sc[0])) isNum = 0;

					// Checks is character is a valid identifier or not
					// It will help to decide whether string is valid identifier or not
					else if (!isIdentifier(sc[0])) isId = 0;


					// If char_stack is full then increase the size of it by 10 blocks
					// and update MAX_CHAR of this stack and also initialize newly alloated memory with \0
					if (CURR_CHAR >= MAX_CHAR) {
						char_stack = realloc(char_stack, (MAX_CHAR+10) * sizeof(char));
						if(char_stack == NULL){
							INSUFFICIENT_SPACE = 1;
							break;
						}
						// printf("Size Increased\n");
						int OLD_SIZE = MAX_CHAR;
						MAX_CHAR += 10;
						for (i = OLD_SIZE; i < MAX_CHAR; i++) char_stack[i] = '\0';
					}

					// Store fetch character at the end of stack and increase CURR_CHAR pointer
					char_stack[CURR_CHAR++] = sc[0];

					// printf("Currunt stack: %s\n\n",char_stack);
					
					//Fetch next character from file
					sc[0] = fgetc(file);
				}

				if(INSUFFICIENT_SPACE) break;
				// Flag to determine string is a valid keyword or not
				int isKey;


				// Checks if first character of stack is a number or not
				// If it is a number then string will be invalid identifier
				if ((int) char_stack[0] >= (int) '0' && (int) char_stack[0] <= (int) '9') isId = 0;
				
				// Flag to determin whether given string stored in stack is valid keyword or not
				else isKey = isKeyword(char_stack);

				if(isNum) printf("%s is a valid number/constant. \n\n",char_stack);
				else if(isKey == 1) printf("%s is a valid Keyword\n\n",char_stack);
				else if(isId == 1) printf("%s is a valid Identifier\n\n",char_stack);
				else if (isKey == 0 && isId == 0) printf("%s is a invalid Identifier\n\n",char_stack);

				// printf("Exit keyword and identifier check.");
			// Operator check
			} else if(isOperator(char_stack) == 1){

				// printf("Inside Operator check............................................................\n\n\n\n");
				// Fetch new Character from file
				char sc[2] = {fgetc(file),'\0'};
				
				// If character stroed in stack is / and newly fetched character is also /
				// Then that line will consider as comment and will be eliminated
				if(char_stack[CURR_CHAR-1] == '/' && sc[0] == '/'){

					// Fetch next character
					char ch = fgetc(file);

					while((int) ch != -1){
						
						// If line break is encountered then break the loop
						if(ch == '\n') break;

						// Fetch new Character from file
						ch = fgetc(file);
					}
				}
				// If character stroed in stack is / and newly fetched character is *
				// Then that line will consider as multiline comment and all lines till */ will be eliminated
				else if(char_stack[CURR_CHAR-1] == '/' && sc[0] == '*'){
					
					//Fetch next character from file
					char ch = fgetc(file);

					while(ch != EOF){
						
						// Id fetched character is * then fetch next character
						// if it is / then break the loop else continue the loop
						if(ch == '*'){
							char nch = fgetc(file);
							if(nch == '/') break;
						}

						// Fetch next character from file
						ch = fgetc(file);
					}
					// printf("Outside Multi Comment Check\n\n");	
				
				// If its not a operator for comment then check for other characters
				} else {

					// Confirms file has data
					hasData = 1;

					while(sc[0] != EOF){

						// printf("Current character: %c\n\n", sc[0]);
						// If char_stack is full then increase the size of it by 10 blocks
						// and update MAX_CHAR of this stack and also initialize newly alloated memory with \0
						if (CURR_CHAR >= MAX_CHAR) {
							char_stack = realloc(char_stack, (MAX_CHAR+10) * sizeof(char));
							if(char_stack == NULL){
								INSUFFICIENT_SPACE = 1;
								break;
							}
							int OLD_SIZE = MAX_CHAR;
							MAX_CHAR += 10;
							for (i = OLD_SIZE; i < MAX_CHAR; ++i) char_stack[i] = '\0';
						}

						// Stores fetched character into stack and increase pointer
						char_stack[CURR_CHAR++] = sc[0];
						
						// If String in char_stack and newly fetch character are not operator
						// Then we can say that string befor adding new character was a operator
						// and new character is not a operator
						// So replace last character of string (which is new character) by \0
						// Store new character in prev_char and change getnext flag
						if(isOperator(char_stack) == 0 && isOperator(sc) == 0){
							char_stack[CURR_CHAR-1] = '\0';
							prev_char = sc[0];
							getnext = 0;
							break;

						// If string in char_stack is not a operator but new character is a operator
						// Then we can say previous string and new character is a seperate operator
						// So print previous string and remove from stack and add new character at first place
						// and update CURR_STACK pointer
						} else if(isOperator(char_stack) == 0 && isOperator(sc) == 1) {
							for(i=0;i<CURR_CHAR-1;i++){
								printf("%c",char_stack[i]);
								char_stack[i] = '\0';
							}
							printf(" is a valid Operator.\n\n");
							char_stack[0] = char_stack[CURR_CHAR-1];
							char_stack[CURR_CHAR-1] = '\0';
							CURR_CHAR = 1;
						}

						// printf("Current stack: %s\n\n", char_stack);
						sc[0] = fgetc(file);
					}

					if(INSUFFICIENT_SPACE) break;
					
					// Above loop will only break if file ends or if block executes
					// If if block executers then we can say that string stored in stack is a valid operator
					// and print it
					for(i=0;i<CURR_CHAR;i++) printf("%c", char_stack[i]);
					printf("Is a valid Operator.\n\n");
				}
			} else printf("Unknown Character Or String.\n\n");
			
			// Free the stack and reset CURR_CHAR and MAX_CHAR to 1;
			free(char_stack);
			CURR_CHAR = 0;
			MAX_CHAR = 10;

			// Get next character from file
			if(getnext == 1) c = fgetc(file);
		}
		if(INSUFFICIENT_SPACE) printf("Insufficient space to run program.");
	}
	if(!hasData) printf("Your file has no data.");
	int f_close = fclose(file);
	free(char_stack);
	getch();
}
