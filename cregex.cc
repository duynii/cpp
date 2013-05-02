#include <sys/types.h>
#include <regex.h>
#include <stdio.h>

#define MAX_MATCHES 20 //The maximum number of matches allowed in a single string

void match(regex_t *pexp, char *sz) {
    regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
    //Compare the string to the expression
    //regexec() returns 0 on match, otherwise REG_NOMATCH
    if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {

        int i = 0;
        while(matches[i].rm_so != -1) {
            printf("\"%s\" matches characters %d - %d\n", sz, matches[i].rm_so, matches[i].rm_eo);
            ++i;
        }
    } else {
        printf("\"%s\" does not match\n", sz);
    }
}
 
int main() {
    int rv;
    regex_t exp; //Our compiled expression
    //1. Compile our expression.
    //Our regex is "-?[0-9]+(\\.[0-9]+)?". I will explain this later.
    //REG_EXTENDED is so that we can use Extended regular expressions
    rv = regcomp(&exp, "^(https?://)www(\\.www\\.)(aa)", REG_EXTENDED);
    if (rv != 0) {
        printf("regcomp failed with %d\n", rv);
    }
    //2. Now run some tests on it
    match(&exp, "https://www.www.aa");
    //3. Free it
    regfree(&exp);
    return 0;
}
