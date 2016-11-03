#include "parser.h"
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
