#include <parser.h>

void Parser::program() {
	statements();
}

void Parser::statements() {
	statement();
	lexer.lexical();
	if (lexer.get_next_token() == SEMI_COLON) {
		lexer.lexical();
		statements();
	}
}

void Parser::statement() {
	if (lexer.get_next_token() == IDENT) {
		lexer.lexical();
	} else {
		// error
	}
	if (lexer.get_next_token() == ASSIGNMENT_OP) {
		lexer.lexical();
	} else {
		// error
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

void Parser::factor() {
	if (lexer.get_next_token() == LEFT_PAREN) {
		lexer.lexical();
		expression();
		if (lexer.get_next_token() == RIGHT_PAREN) {
			lexer.lexical();
		} else {
			// error
		}
	} else if (lexer.get_next_token() == IDENT) {
		lexer.lexical();
	} else if (lexer.get_next_token() == CONST) {
		lexer.lexical();
	} else {
		// error
	}
}

Parser::Parser(Lexer lexer) : lexer(lexer) {
}

void Parser::parse() {
	lexer.lexical();
	program();
}
