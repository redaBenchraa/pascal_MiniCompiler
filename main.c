#include "scanner.h"
#include "parser.h"


//Define shared global variables.
char current_char;
int current_line=1;
int current_char_indexline=0;
TOKEN current_token;
FILE* stream;

int main(int argc, char *argv[])
{
    stream = fopen("D:\\Projects\\C\\Pascal_MiniCompiler\\prog.txt","r");
    readChar();
    scan();
    PROGRAM();
    if(current_token.CODE == EOF_TOKEN){
        printf("\n --- SYNTAXE PASSED ---\n");
    }else {
        printf("\n --- SYNTAXE FAILED AT LINE %d(%s) ---\n",current_line,current_token.value);
    }
    getch();
}
