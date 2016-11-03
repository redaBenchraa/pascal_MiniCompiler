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
    stream = fopen("C:\\Users\\Reda BENCHRAA\\Documents\\Pascal_Compiler\\prog.txt","r");
    readChar();
    while(current_char != -1){
        scan();
        getch();
    }

    /*
    PROGRAM();
    if(current_token.CODE == EOF_TOKEN){
        printf("\n --- SYNTAXE PASSED ---\n");
    }else {
        printf("\n --- SYNTAXE FAILED AT LINE %d(%s) ---\n",current_line,current_token.value);
    }
    getch();*/
}
