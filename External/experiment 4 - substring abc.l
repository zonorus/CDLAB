Experiment 4

Lex program to convert the substring abc to ABC

Algorithm

1. Start the program.
2. Include the necessary header file `<stdio.h>` for input and output functions.
3. In the Lex rules section, define a pattern to match the substring `"abc"`.
4. When the pattern `"abc"` is found, print `"ABC"` as the output using `printf("ABC");`.
5. All other input text that does not match the pattern is ignored by default.
6. In the main function, call `yylex()` to start lexical analysis.
7. The Lex analyzer reads the input text character by character.
8. Whenever it encounters the substring `"abc"`, it replaces it with `"ABC"` in the output.
9. Continue processing until the entire input is scanned.
10. Stop the program.


mcet@mcet-110-020IL:~/Desktop/s7 cs$ flex exp4.l
mcet@mcet-110-020IL:~/Desktop/s7 cs$ gcc lex.yy.c
mcet@mcet-110-020IL:~/Desktop/s7 cs$ ./a.out
lets see if abc turns diff
lets see if ABC turns diff
so abcmay turn cap
so ABCmay turn cap



%{
#include <stdio.h>
%}

%%
"abc" printf("ABC");
%%

int yywrap(){}
void main(){
	yylex();
	}
	
