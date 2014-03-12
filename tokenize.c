#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*This function checks to see whether a character is in a particular set*/
int charIsInSet(char c, char * set) {
        int len = strlen(set);
        int i;
        for(i=0; i<len; i++) {
                if (c == set[i]) {
                        return 1;
                }
        }
        return 0;
}

/* This function checks to see if a character is an escape character */
int charIsEscapeChar(char c) {
        char * delim = "\n\t\v\b\r\f\a\\\"";
        return charIsInSet(c, delim);
}

/*This function converts an escape character to its hex code */
char * convertCharToHex(char str) {
        /*"[0x00]"*/
        int i = str;
        int len = 6;
        char * hex = calloc(sizeof(char), len+1);
        sprintf(hex, "[0x%02x]", i);
        hex[len] = '\0';
        return hex;
}

/*This function shifts the characters in a string to the left by an amount shamt */
char *genShift(char *str, int shamt)
{
	str += shamt;		
	return str;
}

/*This function gets the next token from the string holding the characters of the file*/
char *createNewToken(char *str,char *token)
{
	/*
		1) Count until you find a non-alnum.
		2) Copy the characters between ptr2 and ptr1 into token.
		3) Attach \0 at the end of token
		4) Shift all characters in str to the left by the difference between ptr2 and ptr1.
	 */
	int i;
	i = 0;
	char *test;

	if(!isalnum(str[i]))
	{
		while(!isalnum(str[i]))
		{
			test = convertCharToHex(str[i]);	
			str = genShift(str,1);
		}
	}
	
	while(isalnum(str[i]))
	{
		token[i] = str[i];
		i++;
	}

	token[i] = '\0';
	return str;
}
/*This function returns the total number of characters in the file*/
int getCharCount(FILE *myFile)
{
        char c;
        int charCount;
        charCount = 0;
        while((c = getc(myFile)) != EOF)
        {
                charCount++;
        }
        rewind(myFile);

        return charCount;
}

/*This function initializes a string with all the characters from the file*/	
void initStr(char *str, FILE *myFile)
{

	int i;
	i = 0;	
	char current;
	current = fgetc(myFile);
	
	while(current != EOF)
	{

		str[i] = tolower(current);
		current = fgetc(myFile);
		i++;
	}
	
	str[i] = '\0';
}


/*This function shifts the fileString over by a number of characters equal 
to the length of the token. Once the last token is retrieved, this function 
returns null to signify the end of the tokenization. */
char *shiftStr(char *str, char *token)
{
	char *beg;
        char *tok;
        int tokenLength = strlen(token);
        beg = str;
        tok = &str[tokenLength];
     
	char *endCheck;
	endCheck = tok;
	int isAlphaNum;
	isAlphaNum = 0;

	while(*endCheck != '\0') 
	{
		if(isalnum(*endCheck))
			isAlphaNum = 1; // If it is alpha numeric, DO NOT END THE STRING
		endCheck++;
	}

	if(isAlphaNum == 0)
	{	
		str = NULL; // Tokenization over. Return
		return str;
	}

        while(*tok != '\0') // Shift the characters to the left until tok hits null.
        {
                *beg = *tok;
                beg++;
                tok++;
        }
    
        *(beg++) = '\0';
	return str;
}

/* This is the main function used to process the different files. 
	It does the following:
		1) Open the file
		2) Retrieve a token from the file string
		3) Shift the file string to the left in order to get the next string

*/
void processFile(char *path, FILE *bufferPtr)
{
	FILE *myFile;
	myFile = fopen(path,"r");

	// Got the number of characters in the file
	int charCount;
	charCount = getCharCount(myFile);	

	char str[charCount]; // stores all the characters from the file
	char *strPtr = str; // a reference to the file string
	char token[charCount]; // token string initialized with the length of the file string (just incase).
	initStr(str,myFile); // loaded all the characters from the file into a character array

	while(strPtr != NULL)
	{		
		/* token gets modified in each of the following function calls, 
		even if it doesn't get returned */
		strPtr = createNewToken(str,token); // returns reference to the modified file string
		strPtr = shiftStr(strPtr,token); // also returns reference to the modified file string
		printf("Token is: %s\n",token);	
		fprintf(bufferPtr,path);
		fprintf(bufferPtr," ");
		fprintf(bufferPtr,token);
		fprintf(bufferPtr,"\n");
		process(token,path);
	}

	fclose(myFile); // close the file
}
