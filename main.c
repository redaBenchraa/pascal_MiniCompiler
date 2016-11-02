#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
typedef enum{
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    EGAL_TOKEN,
    INF_TOKEN,
    SUP_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    INFEG_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    ID_TOKEN,
    NUM_TOKEN,
    EOF_TOKEN,
    COMMENT_TOKEN,
    AFF_TOKEN,
    ERROR_TOKEN
}CODES_LEX;
typedef enum {
    ERR_CAR_INC,
    ERR_FILE_VID,
    ERR_ID_LONG,
    ERR_COMMENT,
    ERR_NUMBER_FORMAT
}ERROR_LEX;
typedef struct {
    ERROR_LEX CODE_ERR;
    char message[40];
}Errors;
typedef struct {
    CODES_LEX CODE;
    char keyword[40];
}Keywords;
typedef struct {
    CODES_LEX CODE;
    char value[40];
}TOKEN;
//Global variables
char current_char;
int current_line=1;
int current_char_indexline=0;
TOKEN current_token;
FILE* stream;
//**************

//Lexical Functions
void scan();

//Syntax Functions
void IF();
void WHILE();
void READ();
void WRITE();
void AFFECT();
void EXPR();
void COND();
void TERM();
void FACT();
void INST();
void INSTS();
void BLOCK();
void VARIABLES();
void CONSTS();
void PROGRAM();
//**************

Errors PROG_ERR[5]={
    {ERR_CAR_INC,"caractere inconnu"},
    {ERR_FILE_VID,"fichier vide"},
    {ERR_ID_LONG,"Identificateur trop long"},
    {ERR_COMMENT,"Pas de cloture du commentaire"},
    {ERR_NUMBER_FORMAT,"deux virgules"}
};
char* PROG_KEYWORDS[11]={"program","const","var","begin","end","if","then","while","do","read","write"};
char SYMBOLS[12]={';','.','+','-','*','/',',','=','<','>','(',')'};
void initTokent(CODES_LEX code,char*value){
    current_token.CODE = code;
    strcpy(current_token.value,value);
}
void Error(ERROR_LEX ERR){
    printf( "Error N%d : %s - LINE : %d\n", ERR, PROG_ERR[ERR].message,current_line);
}
void readChar(){
    current_char = fgetc(stream);
    current_char_indexline++;
}
void consumeComment(){
    readChar();
    while(1){
        if(current_char == '\n') {
            current_line++;
            current_char_indexline = 0;
        }
        if(current_char == '*'){
            readChar();
            if(current_char == '}'){
                break;
                readChar();
            }
        }else if(current_char == '{'){
            readChar();
            if(current_char == '*') consumeComment();
        }
        if(current_char == -1){
            current_token.CODE = ERROR_TOKEN;
            Error(ERR_COMMENT);
            exit(0);
            break;
        } else readChar();
    }
}
void consumeSeperators(){
    while(current_char == ' ' || current_char == '\t' || current_char == '\n'){
        if( current_char == '\n') {
            current_line++;
            current_char_indexline = 0;
        }
        readChar();
    }
    if( current_char == '{') {
        readChar();
        if(current_char == '*') {
            consumeComment();
            readChar();
        }
    }
    while(current_char == ' ' || current_char == '\t' || current_char == '\n'){
        if( current_char == '\n') {
            current_line++;
            current_char_indexline = 0;
        }
        readChar();
    }
}
void isKeyword(char *word){
    int i=0;
    for(i = 0; i<sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]) && strcmp(word,PROG_KEYWORDS[i]) != 0;i++ );
    if( i == sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0])) initTokent(ID_TOKEN,word);
    else initTokent(i,word);
}
void readWord(){
    char *result = (char*) malloc(sizeof(char));
    result[0] = current_char;
    int i=1;
    readChar();
    while(isalnum(current_char) || current_char == '_'){
        result = (char*) realloc(result,++i*sizeof(char));
        result[i-1] = current_char;
        readChar();
    }
    result[i] = '\0';
    isKeyword(result);
}
void isOther(){
    int i;
    for(i=0;i<sizeof(SYMBOLS)/sizeof(SYMBOLS[0]) && current_char != SYMBOLS[i];i++);
    if(i == sizeof(SYMBOLS)/sizeof(SYMBOLS[0])){
        if(current_char == ':'){
            readChar();
            if(current_char == '=') {
                readChar();
                initTokent(AFF_TOKEN,":=");
            }else initTokent(ERROR_TOKEN,"ERROR_TOKEN");
        } else initTokent(ERROR_TOKEN,"ERROR_TOKEN");
    }else{
        char symbol[2];
        readChar();
        symbol[0] = SYMBOLS[i];
        if((i+11 == INF_TOKEN || i+11 == SUP_TOKEN) && current_char == '=') {
            symbol[1] = '=';
            initTokent(i+15,symbol);
            readChar();
        }else if(i+11 == INF_TOKEN && current_char == '>')  {
            initTokent(DIFF_TOKEN,"<>");
            readChar();
        }else {
            symbol[1] = '\0';
            initTokent(i+11,symbol);
        }
    }
}
void readNum(){
    char *result = (char*) malloc(sizeof(char));
    result[0] = current_char;
    int i=1,point = 0;
    readChar();
    while((isdigit(current_char) || current_char == '.')){
        if(current_char == '.') point ++;
        result = (char*) realloc(result,++i*sizeof(char));
        result[i-1] = current_char;
        readChar();
    }
    result[i] = '\0';
    if(point > 1){
           Error(ERR_NUMBER_FORMAT);
           initTokent(ERROR_TOKEN,result);

    }else initTokent(NUM_TOKEN,result);
}
void printToken(){
    printf("%d : %s\n",current_token.CODE,current_token.value);
}
void scan(){
    consumeSeperators();
    if(isalpha(current_char)) readWord();
    else if(isdigit(current_char)) readNum();
    else isOther();
    printToken();
}
//SYNTAX
void Test_Token(CODES_LEX code){
    if (current_token.CODE == code)
    {
        scan();
    }
    else{
        printf("ERROR  at position (%d-%d)[ %s] \n",current_line,current_char_indexline-1,current_token.value);
        exit(0);
    }
}
void EXPR(){

}
void COND(){

}
void READ(){
    Test_Token(READ_TOKEN);
    Test_Token(PO_TOKEN);
    Test_Token(ID_TOKEN);
    while( current_token.CODE == ID_TOKEN){
        if(current_token.CODE== PF_TOKEN)
            Test_Token(VIR_TOKEN);
    }
    Test_Token(PF_TOKEN);
}
void WRITE(){
    Test_Token(WRITE_TOKEN);
    Test_Token(PO_TOKEN);
    EXPR();
    while(current_token.CODE == PF_TOKEN){
        Test_Token(VIR_TOKEN);
        EXPR();
    }
    Test_Token(PF_TOKEN);
}
void IF(){
    Test_Token(IF_TOKEN);
    COND();
    Test_Token(THEN_TOKEN);
}
void AFFECT(){
    Test_Token(ID_TOKEN);
    Test_Token(AFF_TOKEN);
    EXPR();
}
void INST(){
    switch (current_token.CODE) {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:
        AFFECT();
        break;
    case IF_TOKEN:
        IF();
        break;
    case WHILE_TOKEN:
        WHILE();
        break;
    case WRITE_TOKEN:
        WRITE();
        break;
    case READ_TOKEN:
        READ();
        break;
    default: //
        break;
    }
}
void WHILE(){
    Test_Token(WHILE_TOKEN);
    COND();
    Test_Token(DO_TOKEN);
    INST();
}
void CONSTS() {
    switch (current_token.CODE) {
    case CONST_TOKEN:
        scan();
        Test_Token(ID_TOKEN);
        Test_Token(EGAL_TOKEN);
        Test_Token(NUM_TOKEN);
        Test_Token(PV_TOKEN);
        while (current_token.CODE == ID_TOKEN){
            scan();
            Test_Token(EGAL_TOKEN);
            Test_Token(NUM_TOKEN);
            Test_Token(PV_TOKEN);
        };
        break;
    case VAR_TOKEN : //
        break;
    case BEGIN_TOKEN : //
        break;
    default:
        printf("ERROR at (%d,%d)[%s]\n",current_line,current_char_indexline,current_token.value);
        break;
    }
}
void VARIABLES() {
    switch (current_token.CODE) {
    case VAR_TOKEN:
        scan();
        Test_Token(ID_TOKEN);
        while(current_token.CODE == VIR_TOKEN){
                scan();
                Test_Token(ID_TOKEN);
        }
        Test_Token(PV_TOKEN);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        printf("ERROR at (%d,%d)[%s]\n",current_line,current_char_indexline,current_token.value);
        break;
    }
}
void INSTS(){
    Test_Token(BEGIN_TOKEN);
    INST();
    while(current_token.CODE == PV_TOKEN){
        INST();
    }
    Test_Token(END_TOKEN);
}
void BLOCK(){
    CONSTS();
    VARIABLES();
    INSTS();
}
void PROGRAM(){
    Test_Token(PROGRAM_TOKEN);
    Test_Token(ID_TOKEN);
    Test_Token(PV_TOKEN);
    BLOCK();
    Test_Token(PT_TOKEN);
}

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
