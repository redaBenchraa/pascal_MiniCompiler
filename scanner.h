#include "header.h"
void initTokent(CODES_LEX code,char* value);
void Error(ERROR_LEX ERR);
void readChar();
void consumeComment();
void consumeSeperators();
void isKeyword(char *word);
void readWord();
void isOther();
void readNum();
void printToken();
void scan();
extern char* PROG_KEYWORDS[19];
extern char SYMBOLS[13];
extern Errors PROG_ERR[5];
