Experiment 6 

Valid arithmetic expression

Algorithm

1. Start the program.
2. Include the necessary header files `<stdio.h>` and `<stdlib.h>` for input/output and standard functions.
3. Initialize a flag variable to detect syntax errors during parsing.
4. Define the tokens used by the parser:

   * `NUMBER` for numeric values.
   * `ID` for identifiers (variables).
5. Specify operator precedence and associativity:

   * `+` and `-` have left associativity.
   * `*` and `/` have left associativity and higher precedence.
6. Define grammar rules for arithmetic expressions:
   a. The start symbol `E` represents a complete expression and calls non-terminal `T`.
   b. The non-terminal `T` handles all valid combinations of operands and operators:

   * `T + T`, `T - T`, `T * T`, `T / T` for binary operations.
   * `- NUMBER` or `- ID` for unary minus.
   * `( T )` for expressions within parentheses.
   * `NUMBER` or `ID` as valid individual operands.
7. In each reduction step, perform the corresponding arithmetic operation or return values appropriately (though actual computation is not the main goal here).
8. If any syntax error occurs during parsing, invoke `yyerror()` to display an error message and set the error flag.
9. In the main function:
   a. Prompt the user to enter an arithmetic expression.
   b. Call `yyparse()` to start parsing using YACC.
   c. If no errors are detected (`flag == 0`), print “Expression is valid.”
   d. Otherwise, print “Expression is invalid.”
10. The associated Lex program recognizes the tokens and passes them to the parser:

    * Numbers → `NUMBER`
    * Identifiers → `ID`
    * Operators and parentheses → corresponding character tokens
    * Whitespace → ignored
11. Continue until the entire input expression is processed.
12. Stop the program.


mcet@mcet-110-020IL:~/Desktop/s7 cs$ yacc -d validarithmetic.y
mcet@mcet-110-020IL:~/Desktop/s7 cs$ flex validarithmetic.l
mcet@mcet-110-020IL:~/Desktop/s7 cs$ cc lex.yy.c y.tab.c -ll
mcet@mcet-110-020IL:~/Desktop/s7 cs$ ./a.out



%{
#include <stdio.h>
#include <stdlib.h>
int flag = 0;
int yylex();
void yyerror(const char *s) {
    flag = 1;
    fprintf(stderr, "Error: %s\n", s);
}
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
E:
    T { return 0; }
;

T:
      T '+' T { $$ = $1 + $3; }
    | T '-' T { $$ = $1 - $3; }
    | T '*' T { $$ = $1 * $3; }
    | T '/' T { $$ = $1 / $3; }
    | '-' NUMBER { $$ = -$2; }
    | '-' ID     { $$ = -$2; }  // Note: You don't assign values to IDs anywhere
    | '(' T ')'  { $$ = $2; }
    | NUMBER     { $$ = $1; }
    | ID         { $$ = $1; }   // Again, no symbol table handling
;

%%

int main() {
    printf("Enter the expression:\n");
    yyparse();

    if (flag == 0)
        printf("\nExpression is valid.\n");
    else
        printf("\nExpression is invalid.\n");

    return 0;
}

