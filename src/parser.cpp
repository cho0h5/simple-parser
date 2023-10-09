#include <parser.h>

void Parser::program() {
	cout << "Enter <program>\n";	// debug
	statements();
	cout << "Exit <program>\n";	// debug
}

void Parser::statements() {
	cout << "Enter <statements>\n";	// debug
	statement();
	if (lexer.get_next_token() == SEMI_COLON) {
		lexer.lexical();
		statements();
	}
	cout << "Exit <statements>\n";	// debug
}

void Parser::statement() {
	cout << "Enter <statement>\n";	// debug
	if (lexer.get_next_token() == IDENT) {
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
	cout << "Exit <statement>\n";	// debug
}

void Parser::expression() {
	cout << "Enter <expression>\n";	// debug
	term();
	term_tail();
	cout << "Exit <expression>\n";	// debug
}

void Parser::term_tail() {
	cout << "Enter <term_tail>\n";	// debug
	if (lexer.get_next_token() == ADD_OP) {
		lexer.lexical();
		term();
		term_tail();
	}
	cout << "Exit <term_tail>\n";	// debug
}

void Parser::term() {
	cout << "Enter <term>\n";	// debug
	factor();
	factor_tail();
	cout << "Exit <term>\n";	// debug
}

void Parser::factor_tail() {
	cout << "Enter <factor_tail>\n";	// debug
	if (lexer.get_next_token() == MULT_OP) {
		lexer.lexical();
		factor();
		factor_tail();
	}
	cout << "Exit <factor_tail>\n";	// debug
}

void Parser::factor() {
	cout << "Enter <factor>\n";	// debug
	if (lexer.get_next_token() == LEFT_PAREN) {
		lexer.lexical();
		expression();
		if (lexer.get_next_token() == RIGHT_PAREN) {
			lexer.lexical();
		} else {
			cout << "error\n";	// error
		}
	} else if (lexer.get_next_token() == IDENT) {
		lexer.lexical();
	} else if (lexer.get_next_token() == CONST) {
		lexer.lexical();
	} else {
		cout << "error\n";	// error
	}
	cout << "Exit <factor>\n";	// debug
}

Parser::Parser(Lexer lexer) : lexer(std::move(lexer)) {
}

void Parser::parse() {
	lexer.lexical();
	program();
}
