/* Recursive descent parser for area and parameter calc.*/

typedef int area_parameter;
area_parameter expr(void);

char token;

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void error(const char *msg) {
    fputs(msg, stderr);
    exit(1);
}

// match expected and move ahead
void match(char expected) {
    if (token == expected) {
        token = getchar();
        return;
    }

    fprintf(stderr, "Expected %c, got %c", expected, token);
    exit(1);
}


area_parameter factor(void) {
    area_parameter value;

    if (token == '(') {
        match('(');
        value = expr();
        match(')');

    } else if (isdigit(token) || token == '+' || token == '-') {
        ungetc(token, stdin);
        scanf("%d", &value);
        token = getchar();
    } else {
        error("bad factor");
    }

    return value;
}

area_parameter term(void) {
    area_parameter value = factor();

    while (token == '*' || token == '/') {
        switch(token) {
        case '*':
            match('*');

            value *= factor();
            break;

        case '/':
            match('/');
            value /= factor();
            break;

        default:
            error("bad term");
        }
    }

    return value;
}

area_parameter expr() {
    area_parameter value = term();

    if (token == '+' || token == '-') {
        switch(token) {
        case '+':
            match('+');
            value += term();
            break;

        case '-':
            match('-');
            value -= term();
            break;
        default:
            error("bad expr '+' or '-' or '*' expected");
        }
    }

    return value;
}

int main(void) {

    token = getchar();
    area_parameter result = expr();
    printf(" Area or Perimeter result: %d\n", result);

    return 0;
}
