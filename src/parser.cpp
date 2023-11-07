#include <parser.h>

Program *Parser::program() {
	Statements *stmts = statements();
	return new Program(symbol_table, stmts);
}

Statements *Parser::statements() {
	if (lexer.get_next_token() == END_OF_FILE) {
		cout << "(Warning) you don't need semicolon at the end\n";
		return NULL;
	}
	Statement *stmt = statement();
	if (lexer.get_next_token() != END_OF_FILE) {
    if (lexer.get_next_token() == SEMI_COLON)
      lexer.lexical();
		Statements *stmts = statements();
		if (stmts != NULL && stmt != NULL)
			stmt->set_semi_colon();
		return new Statements(symbol_table, stmt, stmts);
	}
	return new Statements(symbol_table, stmt, NULL);
}

Statement *Parser::statement() {
  vector<string> messages;
	string ident;
	if (lexer.get_next_token() == IDENT) {
		ident = lexer.get_token_string();
		lexer.lexical();
	} else {
    messages.push_back("\e[31m(Error) IDENT expected but not found\e[37m");
    while (lexer.get_next_token() != SEMI_COLON
        && lexer.get_next_token() != END_OF_FILE)
      lexer.lexical();
    return new Statement(NULL, "", NULL, messages);
	}
	if (lexer.get_next_token() == ASSIGNMENT_OP) {
		lexer.lexical();
	} else {
		messages.push_back("\e[31m(Error) assignment operator is not found\e[37m");
    while (lexer.get_next_token() != SEMI_COLON
        && lexer.get_next_token() != END_OF_FILE)
      lexer.lexical();
    return new Statement(NULL, "", NULL, messages);
	}
	Expression *expr = expression();
	return new Statement(symbol_table, ident, expr, messages);
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
  vector<string> messages;
	Factor *ft = factor();
  if (ft == NULL)
    messages.push_back("\e[31mFactor parsing error\e[37m");
	FactorTail *fttl = factor_tail();
	return new Term(symbol_table, ft, fttl, messages);
}

FactorTail *Parser::factor_tail() {
  vector<string> messages;
	if (lexer.get_next_token() == MULT_OP) {
		char mult_or_div = lexer.get_token_string().at(0);
		lexer.lexical();
		Factor *ft = factor();
    if (ft == NULL)
      messages.push_back("\e[31mFactor parsing error\e[37m");
		FactorTail *fttl = factor_tail();
		return new FactorTail(symbol_table, mult_or_div, ft, fttl, messages);
	}
	return NULL;
}

Factor *Parser::factor() {
  vector<string> messages;
	for (;;) {
		if (lexer.get_next_token() == LEFT_PAREN) {
			lexer.lexical();
			Expression *expr = expression();
			if (lexer.get_next_token() == RIGHT_PAREN) {
				lexer.lexical();
				return new Factor(symbol_table, expr, "", 0, messages);
			}
		} else if (lexer.get_next_token() == IDENT) {
			string ident = lexer.get_token_string();
			lexer.lexical();
			return new Factor(symbol_table, NULL, ident, 0, messages);
		} else if (lexer.get_next_token() == CONST) {
			int number = stoi(lexer.get_token_string());
			lexer.lexical();
			return new Factor(symbol_table, NULL, "", number, messages);
		}

		if (lexer.get_next_token() == ADD_OP) {
      messages.push_back("\e[33m(Warning) eliminate duplicated add (or sub) operator\e[37m");
			lexer.lexical();
		} else if (lexer.get_next_token() == MULT_OP) {
      messages.push_back("\e[33m(Warning) eliminate duplicated mult (or div) operator\e[37m");
			lexer.lexical();
		} else {
			break;
		}
	}
	return NULL;
}

Parser::Parser(Lexer lexer, SymbolTable *symbol_table) : lexer(std::move(lexer)), symbol_table(symbol_table) {
}

Tree *Parser::parse() {
	lexer.lexical();
	return program();
}
