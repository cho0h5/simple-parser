#include <parser.h>

Program *Parser::program() {
	Statements *stmts = statements();
	return new Program(symbol_table, stmts);
}

Statements *Parser::statements() {
	Statement *stmt = statement();
	if (lexer.get_next_token() == SEMI_COLON) {
		lexer.lexical();
		Statements *stmts = statements();
		return new Statements(symbol_table, stmt, stmts);
	}
	return new Statements(symbol_table, stmt, NULL);
}

Statement *Parser::statement() {
	string ident;
	if (lexer.get_next_token() == IDENT) {
		ident = lexer.get_token_string();
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
	Expression *expr = expression();
	return new Statement(symbol_table, ident, expr);
}

Expression *Parser::expression() {
	Term *tm = term();
	TermTail *tmtl = term_tail();
	return new Expression(symbol_table, tm, tmtl);
}

TermTail *Parser::term_tail() {
	if (lexer.get_next_token() == ADD_OP) {
		char add_or_sub = lexer.get_token_string().at(0);
		lexer.lexical();
		Term *tm = term();
		TermTail *tmtl = term_tail();
		return new TermTail(symbol_table, add_or_sub, tm, tmtl);
	}
	return NULL;
}

Term *Parser::term() {
	Factor *ft = factor();
	FactorTail *fttl = factor_tail();
	return new Term(symbol_table, ft, fttl);
}

FactorTail *Parser::factor_tail() {
	if (lexer.get_next_token() == MULT_OP) {
		char mult_or_div = lexer.get_token_string().at(0);
		lexer.lexical();
		Factor *ft = factor();
		FactorTail *fttl = factor_tail();
		return new FactorTail(symbol_table, mult_or_div, ft, fttl);
	}
	return NULL;
}

Factor *Parser::factor() {
	if (lexer.get_next_token() == LEFT_PAREN) {
		lexer.lexical();
		Expression *expr = expression();
		if (lexer.get_next_token() == RIGHT_PAREN) {
			lexer.lexical();
			return new Factor(symbol_table, expr, "", 0);
		} else {
			cout << "error\n";	// error
		}
	} else if (lexer.get_next_token() == IDENT) {
		if (symbol_table->is_exist(lexer.get_token_string()) == false) {
			cout << "error: undefined ident (" << lexer.get_token_string() << ")\n";	// error: undefined ident
			symbol_table->add_ident(lexer.get_token_string());
		}
		lexer.lexical();
		return new Factor(symbol_table, NULL, lexer.get_token_string(), 0);
	} else if (lexer.get_next_token() == CONST) {
		int number = stoi(lexer.get_token_string());
		lexer.lexical();
		return new Factor(symbol_table, NULL, "", number);
	} else {
		cout << "error\n";	// error
	}
}

Parser::Parser(Lexer lexer, SymbolTable *symbol_table) : lexer(std::move(lexer)), symbol_table(symbol_table) {
}

Tree *Parser::parse() {
	lexer.lexical();
	return program();
}
