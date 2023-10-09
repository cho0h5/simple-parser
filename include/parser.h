#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include <lexer.h>

using namespace std;

class Parser {
	Lexer lexer;

	void program();
	void statements();
	void statement();
	void expression();
	void term_tail();
	void term();
	void factor_tail();
	void factor();

	public:
	Parser(Lexer lexer);
	void parse();
};

#endif
