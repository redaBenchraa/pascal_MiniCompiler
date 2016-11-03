#ifndef A_HEADER
    #define A_HEADER
    #include<stdio.h>
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
        ELSE_TOKEN,
        FOR_TOKEN,
        REPEAT_TOKEN,
        UNTIL_TOKEN,
        CASE_TOKEN,
        TO_TOKEN,
        DOWNTO_TOKEN,
        OF_TOKEN,
        DP_TOKEN,
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
        char value[40];
    }TOKEN;

    //Shared global variables
    extern char current_char;
    extern int current_line;
    extern int current_char_indexline;
    extern TOKEN current_token;
    extern FILE* stream;
    extern char* PROG_KEYWORDS[19];
    extern char SYMBOLS[13];
    extern Errors PROG_ERR[5];

#endif
