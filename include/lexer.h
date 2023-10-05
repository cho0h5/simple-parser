#ifndef LEXER_H
#define LEXER_H

#include <fstream>

using namespace std;

enum Terminal {
	PROGRAM,
	STATEMENTS,
	STATEMENT,
	EXPRESSION,
	TERM,
	TERM_TAIL,
	FACTOR,
	FACTOR_TAIL,
};

enum Nonterminal {
	CONST,
	IDENT,
	ASSIGNMENT_OP,
	SEMI_COLON,
	ADD_OP,
	MULT_OP,
	LEFT_PAREN,
	RIGHT_PAREN,
	EOL,	// 필요한가?
};

class Lexer {
	ifstream file;

	char next_char;

	Nonterminal next_token;
	string token_string;

	public:
	Lexer(const char* filename);
	~Lexer();

	void lexical();
};

#endif
