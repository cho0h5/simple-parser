#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include <lexer.h>
#include <symbol_table.h>

using namespace std;

class Parser {
	Lexer lexer;
	SymbolTable *symbol_table;

	void program();
	void statements();
	void statement();
	void expression();
	void term_tail();
	void term();
	void factor_tail();
	void factor();

	public:
	Parser(Lexer lexer, SymbolTable *symbol_table);
	void parse();
};

#endif
