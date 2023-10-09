#include <parser.h>

void Parser::program() {
	statements();
}

void Parser::statements() {
	statement();
	if (lexer.get_next_token() == SEMI_COLON) {
		lexer.lexical();
		statements();
	}
}

void Parser::statement() {
	if (lexer.get_next_token() == IDENT) {
		symbol_table->add_ident(lexer.get_token_string());
		lexer.lexical();
	} else {
		cout << "error\n";	// error
	}
	if (lexer.get_next_token() == ASSIGNMENT_OP) {
		lexer.lexical();
	} else {
		cout << "error\n";	// error
	}
	expression();
}

void Parser::expression() {
	term();
	term_tail();
}

void Parser::term_tail() {
	if (lexer.get_next_token() == ADD_OP) {
		lexer.lexical();
		term();
		term_tail();
	}
}

void Parser::term() {
	factor();
	factor_tail();
}

void Parser::factor_tail() {
	if (lexer.get_next_token() == MULT_OP) {
		lexer.lexical();
		factor();
		factor_tail();
	}
}

void Parser::factor() {
	if (lexer.get_next_token() == LEFT_PAREN) {
		lexer.lexical();
		expression();
		if (lexer.get_next_token() == RIGHT_PAREN) {
			lexer.lexical();
		} else {
			cout << "error\n";	// error
		}
	} else if (lexer.get_next_token() == IDENT) {
		if (symbol_table->is_exist(lexer.get_token_string()) == false) {
			cout << "error: undefined ident (" << lexer.get_token_string() << ")\n";	// error: undefined ident
			symbol_table->add_ident(lexer.get_token_string());
		}
		lexer.lexical();
	} else if (lexer.get_next_token() == CONST) {
		lexer.lexical();
	} else {
		cout << "error\n";	// error
	}
}

Parser::Parser(Lexer lexer, SymbolTable *symbol_table) : lexer(std::move(lexer)), symbol_table(symbol_table) {
}

void Parser::parse() {
	lexer.lexical();
	program();
}
