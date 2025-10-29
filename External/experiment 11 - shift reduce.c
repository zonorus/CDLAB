Algorithm for Experiment 11: Shift Reduce Parser

1. Start the program.

2. Display the grammar rules:
   E → E + E
   E → E * E
   E → (E)
   E → id

3. Read the input string from the user.

4. Initialize an empty stack `stk[]` and copy the input string into `a[]`.

5. Print the table header showing columns for Stack, Input, and Action.

6. Repeat for each symbol in the input string:
   a. If the current and next characters are ‘i’ and ‘d’, treat them as the token “id”.

   * Push “id” onto the stack.
   * Remove these two characters from the input string.
   * Print the current state with action “SHIFT->id”.
   * Call the `check()` function to perform reductions.
     b. Otherwise, push the current symbol (operator or parenthesis) onto the stack.
   * Remove that symbol from the input string.
   * Print the current state with action “SHIFT->symbols”.
   * Call `check()` to attempt reductions.

7. Function `check()` performs reductions based on grammar rules:
   a. Set action to “REDUCE TO E”.
   b. Scan the stack for the following patterns and replace them with ‘E’:
   i. `id` → E
   ii. `E+E` → E
   iii. `E*E` → E
   iv. `(E)` → E
   c. After each reduction, print the updated stack, remaining input, and the action performed.

8. Continue shifting and reducing until the input is completely processed and only one symbol (E) remains in the stack.

9. End the program when all reductions are complete.


mcet@mcet-110-020IL:~/Desktop/s7 cs$ ./a.out
GRAMMAR is E->E+E 
 E->E*E 
 E->(E) 
 E->id

Enter input string : id+id*id+id

Stack		Input		Action

$id		  +id*id+id$		SHIFT->id
$E		  +id*id+id$		REDUCE TO E
$E+		   id*id+id$		REDUCE TO Esymbols
$E+id		     *id+id$		REDUCE TO Eid
$E+E		     *id+id$		REDUCE TO E
$E		     *id+id$		REDUCE TO E
$E*		      id+id$		REDUCE TO Esymbols
$E*id		        +id$		REDUCE TO Eid
$E*E		        +id$		REDUCE TO E
$E		        +id$		REDUCE TO E
$E+		         id$		REDUCE TO Esymbols
$E+id		           $		REDUCE TO Eid
$E+E		           $		REDUCE TO E
$E		           $		REDUCE TO E


#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], act[10], stk[15], id[20];

void check();

int main() {
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    printf("\nEnter input string : ");
    scanf("%s", a);

    c = strlen(a);
    strcpy(act, "SHIFT->");
    printf("\nStack\t\tInput\t\tAction\n");

    for (k = 0, i = 0; j < c; k++, i++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t\t%s$\t\t%sid", stk, a, act);
            check();
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t\t%s$\t\t%ssymbols", stk, a, act);
            check();
        }
    }
    return 0;
}

void check() {
    strcpy(act, "REDUCE TO E");

    // E -> id
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, act);
            j++;
        }
    }

    // E -> E+E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, act);
            i = i - 2;
        }
    }

    // E -> E*E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, act);
            i = i - 2;
        }
    }

    // E -> (E)
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, act);
            i = i - 2;
        }
    }
}

