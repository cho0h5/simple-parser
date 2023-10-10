#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>

#include <lexer.h>
#include <symbol_table.h>
#include <tree.h>

using namespace std;

class Parser {
	Lexer lexer;
	SymbolTable *symbol_table;

	Program *program();
	Statements *statements();
	Statement *statement();
	Expression *expression();
	TermTail *term_tail();
	Term *term();
	FactorTail *factor_tail();
	Factor *factor();

	public:
	Parser(Lexer lexer, SymbolTable *symbol_table);
	Tree *parse();
};

#endif
