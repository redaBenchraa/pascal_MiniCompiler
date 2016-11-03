#include "scanner.h"

char* PROG_KEYWORDS[19]={"program","const","var","begin","end","if","then","while","do","read","write","else","for","repeat","until","case","to","downto","of"};
char SYMBOLS[13]={':',';','.','+','-','*','/',',','=','<','>','(',')'};
Errors PROG_ERR[5]={
    {ERR_CAR_INC,"caractere inconnu"},
    {ERR_FILE_VID,"fichier vide"},
    {ERR_ID_LONG,"Identificateur trop long"},
    {ERR_COMMENT,"Pas de cloture du commentaire"},
    {ERR_NUMBER_FORMAT,"deux virgules"}
};

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
        }else ungetc(1,stream);
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
    initTokent(ERROR_TOKEN,"ERROR_TOKEN");
    }else{
        char symbol[2];
        readChar();
        symbol[0] = SYMBOLS[i];
        if((i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]) == INF_TOKEN || i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]) == SUP_TOKEN) && current_char == '=') {
            symbol[1] = '=';
            initTokent(i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0])+4,symbol);
            readChar();
        }else if(i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]) == INF_TOKEN && current_char == '>')  {
            initTokent(DIFF_TOKEN,"<>");
            readChar();
        }else if(i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]) == DP_TOKEN && current_char == '=')  {
            initTokent(AFF_TOKEN,":=");
            readChar();
        }else {
            symbol[1] = '\0';
            initTokent(i+sizeof(PROG_KEYWORDS)/sizeof(PROG_KEYWORDS[0]),symbol);
        }
    }
    if(current_char == -1){
        initTokent(EOF_TOKEN,"END OF FILE");
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
