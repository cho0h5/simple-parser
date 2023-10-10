#include <tree.h>

Program::Program(SymbolTable *symbol_table, Statements *statements) {
	this->symbol_table = symbol_table;
	this->statements = statements;
}

void Program::analyze() {
}

Container Program::evaluate() {
	statements->evaluate();
}

int Program::get_id_count() {
}

int Program::get_const_count() {
}

int Program::get_op_count() {
}

void Program::print() {
	statements->print();
}

void Program::drop() {
}

Statements::Statements(SymbolTable *symbol_table, Statement *statement, Statements *statements) {
	this->symbol_table = symbol_table;
	this->statement = statement;
	this->statements = statements;
}

void Statements::analyze() {
}

Container Statements::evaluate() {
	statement->evaluate();
	statements->evaluate();
}

int Statements::get_id_count() {
}

int Statements::get_const_count() {
}

int Statements::get_op_count() {
}

void Statements::print() {
	statement->print();
	if (statements != NULL) {
		statements->print();
	}
}

void Statements::drop() {
}

Statement::Statement(SymbolTable *symbol_table, string ident, Expression *expression) {
	this->symbol_table = symbol_table;
	this->ident = ident;
	this->expression = expression;
	this->semi_colon = false;
}

void Statement::set_semi_colon() {
	semi_colon = true;
}

void Statement::analyze() {
}

Container Statement::evaluate() {
	symbol_table->set_value(ident, expression->evaluate());
}

int Statement::get_id_count() {
}

int Statement::get_const_count() {
}

int Statement::get_op_count() {
}

void Statement::print() {
	cout << ident << " := ";
	expression->print();
	if (semi_colon) {
		cout << " ;";
	}
	cout << '\n';
}

void Statement::drop() {
}

Expression::Expression(SymbolTable *symbol_table, Term *term, TermTail *term_tail) {
	this->symbol_table = symbol_table;
	this->term = term;
	this->term_tail = term_tail;
}

void Expression::analyze() {
}

Container Expression::evaluate() {
	Container container1 = term->evaluate();
	if (term_tail == NULL) return container1;
	Container container2 = term_tail->evaluate();

	if (term_tail->get_add_or_sub() == '+') {
		container1.add(container2);
	} else {
		container1.sub(container2);
	}

	return container1;
}

int Expression::get_id_count() {
}

int Expression::get_const_count() {
}

int Expression::get_op_count() {
}

void Expression::print() {
	term->print();
	if (term_tail != NULL) {
		cout << ' ';
		term_tail->print();
	}
}

void Expression::drop() {
}

TermTail::TermTail(SymbolTable *symbol_table, char add_or_sub, Term *term, TermTail *term_tail) {
	this->symbol_table = symbol_table;
	this->add_or_sub = add_or_sub;
	this->term = term;
	this->term_tail = term_tail;
}

void TermTail::analyze() {
}

Container TermTail::evaluate() {
	Container container1 = term->evaluate();
	if (term_tail == NULL) return container1;
	Container container2 = term_tail->evaluate();

	if (term_tail->get_add_or_sub() == '+') {
		container1.add(container2);
	} else {
		container1.sub(container2);
	}

	return container1;
}

int TermTail::get_id_count() {
}

int TermTail::get_const_count() {
}

int TermTail::get_op_count() {
}

void TermTail::print() {
	cout << add_or_sub << ' ';
	term->print();
	if (term_tail != NULL) {
		cout << ' ';
		term_tail->print();
	}
}

void TermTail::drop() {
}

char TermTail::get_add_or_sub() {
	return add_or_sub;
}

Term::Term(SymbolTable *symbol_table, Factor *factor, FactorTail *factor_tail) {
	this->symbol_table = symbol_table;
	this->factor = factor;
	this->factor_tail = factor_tail;
}

void Term::analyze() {
}

Container Term::evaluate() {
	Container container1 = factor->evaluate();
	if (factor_tail == NULL) return container1;
	Container container2 = factor_tail->evaluate();

	if (factor_tail->get_mult_or_div() == '*') {
		container1.mult(container2);
	} else {
		container1.div(container2);
	}

	return container1;
}

int Term::get_id_count() {
}

int Term::get_const_count() {
}

int Term::get_op_count() {
}

void Term::print() {
	factor->print();
	if (factor_tail != NULL) {
		cout << ' ';
		factor_tail->print();
	}
}

void Term::drop() {
}

FactorTail::FactorTail(SymbolTable *symbol_table, char mult_or_div, Factor *factor, FactorTail *factor_tail) {
	this->symbol_table = symbol_table;
	this->mult_or_div = mult_or_div;
	this->factor = factor;
	this->factor_tail = factor_tail;
}

void FactorTail::analyze() {
}

Container FactorTail::evaluate() {
	Container container1 = factor->evaluate();
	if (factor_tail == NULL) return container1;
	Container container2 = factor_tail->evaluate();

	if (factor_tail->get_mult_or_div() == '*') {
		container1.mult(container2);
	} else {
		container1.div(container2);
	}

	return container1;
}

int FactorTail::get_id_count() {
}

int FactorTail::get_const_count() {
}

int FactorTail::get_op_count() {
}

void FactorTail::print() {
	cout << mult_or_div << ' ';
	factor->print();
	if (factor_tail != NULL) {
		cout << ' ';
		factor_tail->print();
	}
}

void FactorTail::drop() {
}


char FactorTail::get_mult_or_div() {
	return mult_or_div;
}

Factor::Factor(SymbolTable *symbol_table, Expression *expression, string ident, int number) {
	this->symbol_table = symbol_table;
	this->expression = expression;
	this->ident = ident;
	this->number = number;
}

void Factor::analyze() {
}

Container Factor::evaluate() {
	if (expression != NULL) {
		return expression->evaluate();
	} else if (ident.length() != 0) {
		return symbol_table->get_value(ident);
	}
	return Container(number);
}

int Factor::get_id_count() {
}

int Factor::get_const_count() {
}

int Factor::get_op_count() {
}

void Factor::print() {
	if (expression != NULL) {
		cout << '(';
		expression->print();
		cout << ')';
	} else if (ident.length() != 0) {
		cout << ident;
	} else {
		cout << number;
	}
}

void Factor::drop() {
}
