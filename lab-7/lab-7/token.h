typedef struct token {
	int type; //== 1 - operator, == 0 - number; 
	char symbol;
	int number;
} token_t;