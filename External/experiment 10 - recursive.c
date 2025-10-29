Algorithm for Experiment 10: Recursive Descent Parser

1. Start the program.

2. Display the grammar used (eliminated from left recursion):
   E  → T E'
   E' → + T E' | ε
   T  → F T'
   T' → * F T' | ε
   F  → (E) | id

3. Read the input arithmetic expression as a string.

4. Initialize index `i = 0` and error flag `error = 0`.

5. Call function `E()` to start parsing (as E is the start symbol).

6. After parsing, check:
   a. If the entire input is consumed and `error == 0`, print “Accepted.”
   b. Otherwise, print “Rejected” with an appropriate error message.

7. Function E():
   a. Call `T()` to parse a term.
   b. Call `Eprime()` to check for additional terms joined by '+'.

8. Function Eprime():
   a. Skip any spaces.
   b. If the next symbol is '+':
   i. Consume '+' and skip spaces.
   ii. Call `T()` to parse the next term.
   iii. Recursively call `Eprime()` to handle further additions.
   c. If no '+', return (ε production).

9. Function T():
   a. Call `F()` to parse a factor.
   b. Call `Tprime()` to check for further factors multiplied by '*'.

10. Function Tprime():
    a. Skip any spaces.
    b. If the next symbol is '*':
    i. Consume '*' and skip spaces.
    ii. Call `F()` to parse the next factor.
    iii. Recursively call `Tprime()` to handle further multiplications.
    c. If no '*', return (ε production).

11. Function F():
    a. Skip any spaces.
    b. If the next symbol is an alphabet, accept it as an identifier and increment `i`.
    c. Else if the symbol is '(':
    i. Consume '(' and skip spaces.
    ii. Call `E()` to evaluate the expression inside parentheses.
    iii. Skip spaces and check for closing ')'.
    iv. If ')' is missing, set `error = 1` and print “Missing closing parenthesis.”
    d. If neither an identifier nor '(', set `error = 1` and print “Expected identifier or '('.”

12. Return control back to `main()` after parsing completes.

13. End the program.


mcet@mcet-110-020IL:~/Desktop/s7 cs$ gcc exp10.c
mcet@mcet-110-020IL:~/Desktop/s7 cs$ ./a.out

Grammar without left recursion:
	E  -> T E'
	E' -> + T E' | ε
	T  -> F T'
	T' -> * F T' | ε
	F  -> (E) | id

Enter an arithmetic expression (e.g., a+a*a): a+(a*a)

Accepted...!!!


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100 // Increased buffer size

char input[MAX_INPUT];
int i, error;

void E();
void Eprime();
void T();
void Tprime();
void F();

int main() {
    printf("\nGrammar without left recursion:\n");
    printf("\tE  -> T E'\n");
    printf("\tE' -> + T E' | ε\n");
    printf("\tT  -> F T'\n");
    printf("\tT' -> * F T' | ε\n");
    printf("\tF  -> (E) | id\n");

    printf("\nEnter an arithmetic expression (e.g., a+a*a): ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    // Remove trailing newline from fgets
    input[strcspn(input, "\n")] = '\0';

    i = 0;
    error = 0;
    E();

    if (i == strlen(input) && error == 0)
        printf("\nAccepted...!!!\n");
    else
        printf("\nRejected...!!! Reason: %s\n",
               error ? "Invalid syntax" : "Incomplete expression");

    return 0;
}

void E() {
    T();
    Eprime();
}

void Eprime() {
    // Skip whitespace
    while (input[i] == ' ') i++;
    if (input[i] == '+') {
        i++;
        while (input[i] == ' ') i++; // Skip whitespace after +
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    // Skip whitespace
    while (input[i] == ' ') i++;
    if (input[i] == '*') {
        i++;
        while (input[i] == ' ') i++; // Skip whitespace after *
        F();
        Tprime();
    }
}

void F() {
    // Skip whitespace
    while (input[i] == ' ') i++;
    if (isalpha(input[i])) { // Restrict id to letters
        i++;
    } else if (input[i] == '(') {
        i++;
        while (input[i] == ' ') i++; // Skip whitespace
        E();
        while (input[i] == ' ') i++; // Skip whitespace
        if (input[i] == ')')
            i++;
        else {
            error = 1;
            printf("Error: Missing closing parenthesis\n");
        }
    } else {
        error = 1;
        printf("Error: Expected identifier or '('\n");
    }
}
