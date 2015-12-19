#ifndef __TOKEN__
#define __TOKEN__

typedef struct _token {
	int type; //== 1 - operator, == 0 - number; 
	char symbol;
	int number;
} token;

#endif