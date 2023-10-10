#include <tree.h>

//////////////// Program ////////////////

Program::Program(SymbolTable *symbol_table, Statements *statements) {
	this->symbol_table = symbol_table;
	this->statements = statements;
}

void Program::analyze() {
	statements->analyze();
}

Container Program::evaluate() {
	statements->evaluate();
	return NULL;
}

int Program::get_id_count() {
	return statements->get_id_count();
}

int Program::get_const_count() {
	return statements->get_const_count();
}

int Program::get_op_count() {
	return statements->get_op_count();
}

void Program::print() {
	statements->print();
}

void Program::drop() {
}

//////////////// Statements ////////////////

Statements::Statements(SymbolTable *symbol_table, Statement *statement, Statements *statements) {
	this->symbol_table = symbol_table;
	this->statement = statement;
	this->statements = statements;
}

void Statements::analyze() {
	statement->print();
	cout << "ID: " << statement->get_id_count() << "; ";
	cout << "CONST: " << statement->get_const_count() << "; ";
	cout << "OP: " << statement->get_op_count() << "\n";

	statement->analyze();

	if (statements != NULL) {
		cout << '\n';
		statements->analyze();
	}
}

Container Statements::evaluate() {
	statement->evaluate();
	statements->evaluate();
	return NULL;
}

int Statements::get_id_count() {
	int count = statement->get_id_count();
	if (statements != NULL) {
		count += statements->get_id_count();
	}
	return count;
}

int Statements::get_const_count() {
	int count = statement->get_const_count();
	if (statements != NULL) {
		count += statements->get_const_count();
	}
	return count;
}

int Statements::get_op_count() {
	int count = statement->get_op_count();
	if (statements != NULL) {
		count += statements->get_op_count();
	}
	return count;
}

void Statements::print() {
	statement->print();
	if (statements != NULL) {
		statements->print();
	}
}

void Statements::drop() {
}

//////////////// Statement ////////////////

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
	expression->analyze();
	symbol_table->add_ident(ident);
}

Container Statement::evaluate() {
	symbol_table->set_value(ident, expression->evaluate());
	return NULL;
}

int Statement::get_id_count() {
	return expression->get_id_count() + 1;
}

int Statement::get_const_count() {
	return expression->get_const_count();
}

int Statement::get_op_count() {
	return expression->get_op_count();
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

//////////////// Expression ////////////////

Expression::Expression(SymbolTable *symbol_table, Term *term, TermTail *term_tail) {
	this->symbol_table = symbol_table;
	this->term = term;
	this->term_tail = term_tail;
}

void Expression::analyze() {
	term->analyze();
	if (term_tail != NULL) {
		term_tail->analyze();
	}
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
	int count = term->get_id_count();
	if (term_tail != NULL) {
		count += term_tail->get_id_count();
	}
	return count;
}

int Expression::get_const_count() {
	int count = term->get_const_count();
	if (term_tail != NULL) {
		count += term_tail->get_const_count();
	}
	return count;
}

int Expression::get_op_count() {
	int count = term->get_op_count();
	if (term_tail != NULL) {
		count += term_tail->get_op_count();
	}
	return count;
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

//////////////// TermTail ////////////////

TermTail::TermTail(SymbolTable *symbol_table, char add_or_sub, Term *term, TermTail *term_tail) {
	this->symbol_table = symbol_table;
	this->add_or_sub = add_or_sub;
	this->term = term;
	this->term_tail = term_tail;
}

char TermTail::get_add_or_sub() {
	return add_or_sub;
}

void TermTail::analyze() {
	term->analyze();
	if (term_tail != NULL) {
		term_tail->analyze();
	}
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
	int count = term->get_id_count();
	if (term_tail != NULL) {
		count += term_tail->get_id_count();
	}
	return count;
}

int TermTail::get_const_count() {
	int count = term->get_const_count();
	if (term_tail != NULL) {
		count += term_tail->get_const_count();
	}
	return count;
}

int TermTail::get_op_count() {
	int count = term->get_op_count();
	if (term_tail != NULL) {
		count += term_tail->get_op_count();
	}
	return count + 1;
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

//////////////// Term ////////////////

Term::Term(SymbolTable *symbol_table, Factor *factor, FactorTail *factor_tail) {
	this->symbol_table = symbol_table;
	this->factor = factor;
	this->factor_tail = factor_tail;
}

void Term::analyze() {
	factor->analyze();
	if (factor_tail != NULL) {
		factor_tail->analyze();
	}
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
	int count = factor->get_id_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_id_count();
	}
	return count;
}

int Term::get_const_count() {
	int count = factor->get_const_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_const_count();
	}
	return count;
}

int Term::get_op_count() {
	int count = factor->get_op_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_op_count();
	}
	return count;
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

//////////////// FacotTail ////////////////

FactorTail::FactorTail(SymbolTable *symbol_table, char mult_or_div, Factor *factor, FactorTail *factor_tail) {
	this->symbol_table = symbol_table;
	this->mult_or_div = mult_or_div;
	this->factor = factor;
	this->factor_tail = factor_tail;
}

char FactorTail::get_mult_or_div() {
	return mult_or_div;
}

void FactorTail::analyze() {
	factor->analyze();
	if (factor_tail != NULL) {
		factor_tail->analyze();
	}
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
	int count = factor->get_id_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_id_count();
	}
	return count;
}

int FactorTail::get_const_count() {
	int count = factor->get_const_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_const_count();
	}
	return count;
}

int FactorTail::get_op_count() {
	int count = factor->get_op_count();
	if (factor_tail != NULL) {
		count += factor_tail->get_op_count();
	}
	return count + 1;
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

//////////////// Factor ////////////////

Factor::Factor(SymbolTable *symbol_table, Expression *expression, string ident, int number) {
	this->symbol_table = symbol_table;
	this->expression = expression;
	this->ident = ident;
	this->number = number;
}

void Factor::analyze() {
	if (expression != NULL) {
		expression->analyze();
	} else if (ident.length() != 0 && !symbol_table->is_exist(ident)) {
		symbol_table->add_ident(ident);
		cout << "(Error) undefined identifier (" << ident << ")\n";
	}
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
	if (expression != NULL) {
		return expression->get_id_count();
	} else if (ident.length() != 0) {
		return 1;
	}
	return 0;
}

int Factor::get_const_count() {
	if (expression != NULL) {
		return expression->get_const_count();
	} else if (ident.length() != 0) {
		return 0;
	}
	return 1;
}

int Factor::get_op_count() {
	if (expression != NULL) {
		return expression->get_op_count();
	} else if (ident.length() != 0) {
		return 0;
	}
	return 0;
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
