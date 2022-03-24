/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.17. 
*/
#include <stdio.h>

typedef enum {read, write, id, literal, becomes,
                add, sub, mul, div, lparen, rparen, eof} token;

extern char token_image[];

char* names[] = {"read", "write", "id", "literal", "becomes",
                "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

static token input_token;

void error() {
    printf("syntax error\n");
    exit(1);
}

void match(token expected) {
    if (input_token == expected) {
//        printf("matched %s", names[input_token]);
//        if (input_token == id || input_token == literal)
//            printf(": %s", token_image);
//        printf("\n");
        input_token = scan();
    	printf ("the token is %s \n", names[input_token]);
    }
    else error();
}

void program();
void stmt_list();
void stmt();
void expr();
void term_tail();
void term();
void factor_tail();
void factor();
void add_op();
void mult_op();

void program() {
   // printf("predict program\n");
    switch (input_token) {
        case id:
        case read:
        case write:
        case eof:
            stmt_list();
            match(eof);
            break;
        default: error();
    }
}

void stmt_list() {
    //printf("predict stmt_list\n");
    switch (input_token) {
        case id:
        case read:
        case write:
            stmt();
            stmt_list();
            break;
        case eof:
            break;          /*  epsilon production */
        default: error();
    }
}

void stmt() {
    //printf("predict stmt\n");
    switch (input_token) {
        case id:
            match(id);
            match(becomes);
            expr();
            break;
        case read:
            match(read);
            match(id);
            break;
        case write:
            match(write);
            expr();
            break;
        default: error();
    }
}

void expr() {
    //printf("predict expr\n");
s->indentPrint(1, L"expr", print);
	int subtotal = term();
	while (token == static_cast<int>(L'+') || token == static_cast<int>(L'-'))
	{
		int saveOp = token;
		token = lex->getToken();
		if (static_cast<int>(saveOp) == L'+')
		{
			subtotal += expr();
		}
		else if (static_cast<int>(saveOp) == L'-')
		{
			subtotal -= expr();
		}
		else
		{
			std::wcout << L"error: " << static_cast<wchar_t>(saveOp) << L"  expected '+'  or '-' " << std::endl;
		}
		s->push_op(saveOp);
	}
	s->indentPrint(-1, L"expr", print);
	return subtotal;
}

void term_tail() {
    //printf("predict term_tail\n");
    switch (input_token) {
        case add:
        case sub:
            add_op();
            term();
            term_tail();
            break;
        case rparen:
        case id:
        case read:
        case write:
        case eof:
            break;          /*  epsilon production */
        default: error();
    }
}

void term() {
  //  printf("predict term\n");
 	std::wcout << L"The Output is:" << std::endl;
	s->indentPrint(1, L"term", print);
	int subtotal = factor();
	while (token == static_cast<int>(L'*') || token == static_cast<int>(L'/') || token == static_cast<int>(L'^') || token == static_cast<int>(L'%'))
	{
		int saveOp = token;
		token = lex->getToken();
		if (static_cast<int>(saveOp) == L'*')
		{
			subtotal *= term();
		}
		else if (static_cast<int>(saveOp) == L'/')
		{
			subtotal = subtotal / term();
		}
		else if (static_cast<int>(saveOp) == L'^')
		{
			subtotal = static_cast<int>(std::pow(subtotal,term()));
		}
		else if (static_cast<int>(saveOp) == L'%')
		{
			subtotal = subtotal % term();
		}
		else
		{
			std::wcout << L"error: " << static_cast<wchar_t>(saveOp) << L"  expected '*'  or '/' " << std::endl;
		}
		s->push_op(saveOp);
	}
	s->indentPrint(-1, L"term", print);
	return subtotal;
}

void factor_tail() {
//    printf("predict factor_tail\n");
    switch (input_token) {
        case mul:
        case div:
            mult_op();
            factor();
            factor_tail();
            break;
        case add:
        case sub:
        case rparen:
        case id:
        case read:
        case write:
        case eof:
            break;          /*  epsilon production */
        default: error();
    }
}

void factor() {
//    printf("predict factor\n");
	s->indentPrint(1, L"factor", print);
	int subtotal = 0;
	if (token == static_cast<int>(L'('))
	{
		token = lex->getToken();
		// if(print) System.out.println("Lexeem: "+lex.type()+":"+lex.tokenStr());
		subtotal = expr();
		if (token == static_cast<int>(L')'))
		{
			token = lex->getToken();
			// if(print) System.out.println("Lexeem: "+lex.type()+":"+lex.tokenStr());
		}
		else
		{
			std::wcout << L"closing ')' expected" << std::endl;
		}
	}
	else if (lex->type() == TokenType::Identifer)
	{
		token = lex->getToken();
	}
	else if (lex->type() == TokenType::Number)
	{
		token = lex->getToken();
		// if(print) System.out.println("Lexeem: "+lex.type()+":"+ lex.tokenStr());
		subtotal = static_cast<int>(lex->value());
		s->stack.push(L" " + std::to_wstring(static_cast<int>(lex->value())));
	}
	else
	{
		std::wcout << L"factor expected" << std::endl;
	}
	s->indentPrint(-1, L"factor", print);
	return subtotal;
}

void add_op() {
//    printf("predict add_op\n");
    switch (input_token) {
        case add:
            match(add);
            break;
        case sub:
            match(sub);
            break;
        default: error();
    }
}

void mult_op() {
//    printf("predict mult_op\n");
    switch (input_token) {
        case mul:
            match(mul);
            break;
        case div:
            match(div);
            break;
        default: error();
    }
}

int main() {
    input_token = scan();
    printf ("the token is %s \n", names[input_token]);
    program();
}