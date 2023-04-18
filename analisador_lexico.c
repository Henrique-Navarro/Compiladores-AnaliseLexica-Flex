/*DEFINIÇÃO*/
%{
    #include <stdio.h>
    #include <stdlib.h>
    int count_reserv=0, count_op=0, count_tipos=0, count_const=0, count_id=0, count_num=0, count_invalid=0, linha=0;
%}

DIGITO          [0-9]+                   
ID              [a-zaA-Z]([a-zaA-Z0-9])*
ESPACO          [ \n\t\r]+

%x comentario

/*REGRAS*/
%%

programa {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA PROGRAMA\n", yytext);}
inicio {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA INICIO\n", yytext);}
fimprograma {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA FIMPROGRAMA\n", yytext);}
leia {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA LEIA\n", yytext);}
escreva {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA ESCREVA\n", yytext);}

se {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA SE\n", yytext);}
entao {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA ENTAO\n", yytext);}
senao {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA SENAO\n", yytext);}
fimse {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA FIMSE\n", yytext);}

enquanto {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA ENQUANTO\n", yytext);}
faca {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA FACA\n", yytext);}
fimenquanto {count_reserv++; printf("[%11s] \t->\t PALAVRA RESERVADA FIMENQUANTO\n", yytext);}

"+" {count_op++; printf("[%11s] \t->\t OPERADOR MAIS\n", yytext);}
"-" {count_op++; printf("[%11s] \t->\t OPERADOR MENOS\n", yytext);}
"*" {count_op++; printf("[%11s] \t->\t OPERADOR MULTIPLICACAO\n", yytext);}
"div" {count_op++; printf("[%11s] \t->\t OPERADOR DIVISAO\n", yytext);}

"<" {count_op++; printf("[%11s] \t->\t OPERADOR MENOR\n", yytext);}
"==" {count_op++; printf("[%11s] \t->\t OPERADOR IGUAL\n", yytext);}
">" {count_op++; printf("[%11s] \t->\t OPERADOR MAIOR\n", yytext);}

"e" {count_op++; printf("[%11s] \t->\t OPERADOR E\n", yytext);}
"ou" {count_op++; printf("[%11s] \t->\t OPERADOR OU\n", yytext);}
"nao" {count_op++; printf("[%11s] \t->\t OPERADOR NAO\n", yytext);}

"<-" {count_op++; printf("[%11s] \t->\t OPERADOR ATRIBUICAO\n", yytext);}
";" {count_op++; printf("[%11s] \t->\t OPERADOR PONTO VIRGULA\n", yytext);}
"(" {count_op++; printf("[%11s] \t->\t ABERTURA PARANTESE\n", yytext);}
")" {count_op++; printf("[%11s] \t->\t FECHAMENTO PARANTESE\n", yytext);}
"{" {count_op++; printf("[%11s] \t->\t ABERTURA CHAVES\n", yytext);}
"}" {count_op++; printf("[%11s] \t->\t FECHAMENTO CHAVES\n", yytext);}

"inteiro"|"logico" {count_tipos++; printf("[%11s] ->\t TIPO VARIAVEL\n", yytext);}
"V" {count_const++; printf("[%11s] \t->\t CONSTANTE V\n", yytext);}
"F" {count_const++; printf("[%11s] \t->\t CONSTANTE F\n", yytext);}

{ID} {count_id++; printf("[%11s] \t->\t IDENTIFICADOR\n", yytext);}
{DIGITO} {count_num++; printf("[%11s] \t->\t DIGITO\n", yytext);}

{ESPACO} {/*NADA*/}

"//".* {/*NADA*/}

"/*" BEGIN(comentario); 
<comentario>"*/" BEGIN(INITIAL);
<comentario>. {/*NADA*/}

{DIGITO}+{ID}+ {count_invalid++; printf("[%11s] \t->\t ERRO NOME DE ID INVALIDO\n", yytext);}
. {count_invalid++; printf("[%11s] \t->\t ERRO SIMBOLO Ñ RECONHECIDO\n", yytext);}

%%

/*SUBROTINAS*/
void total_count(){    
    printf("\nTotal Palavras Reservadas: %d\n", count_reserv);
    printf("Total Operadores: %d\n", count_op);
    printf("Total Tipos: %d\n", count_tipos);
    printf("Total Constantes: %d\n", count_const);
    printf("Total Identificadores: %d\n", count_id);
    printf("Total Números: %d\n", count_num);
    printf("Total Inválidos: %d\n", count_invalid);
    printf("Total Tokens Válidos: %d\n",count_reserv+count_op+count_tipos+count_const+count_id+count_num);
}

void main(){
    FILE *f_in = fopen("./codes/avaliacao.simples", "r");
    //FILE *f_in = fopen("./codes/teste01.txt", "r");
    yyin = f_in;

    if(f_in == NULL){
        printf("Erro ao ler arquivo!\n");
    }
    else{    
        printf("Arquivo lido com sucesso!\n");
        yylex();
    }
    total_count();
    fclose(f_in);    
}