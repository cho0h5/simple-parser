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
	return Container();
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

Program::~Program() {
	delete statements;
}

//////////////// Statements ////////////////

Statements::Statements(SymbolTable *symbol_table, Statement *statement, Statements *statements) {
	this->symbol_table = symbol_table;
	this->statement = statement;
	this->statements = statements;
}

void Statements::analyze() {
  if (statement != NULL) {
    statement->print();
    statement->print_messages();
    cout << "ID: " << statement->get_id_count() << "; ";
    cout << "CONST: " << statement->get_const_count() << "; ";
    cout << "OP: " << statement->get_op_count() << "\n";

    statement->analyze();
  } else  {
    cout << "This statement is not parsed\n";
    cout << "ID: " << 0 << "; ";
    cout << "CONST: " << 0 << "; ";
    cout << "OP: " << 0 << "\n";
  }

	if (statements != NULL) {
		cout << '\n';
		statements->analyze();
	}
}

Container Statements::evaluate() {
  if (statement != NULL)
    statement->evaluate();
	if (statements != NULL) {
		statements->evaluate();
	}
	return Container();
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

Statements::~Statements() {
	delete statement;
	delete statements;
}

//////////////// Statement ////////////////

Statement::Statement(SymbolTable *symbol_table, string ident, Expression *expression, vector<string> messages) {
	this->symbol_table = symbol_table;
	this->ident = ident;
	this->expression = expression;
	this->semi_colon = false;
  this->messages = messages;
}

void Statement::set_semi_colon() {
	semi_colon = true;
}

void Statement::analyze() {
  if (expression == NULL) return;
	expression->analyze();
	symbol_table->add_ident(ident);
}

Container Statement::evaluate() {
  if (expression != NULL)
    symbol_table->set_value(ident, expression->evaluate());
	return Container();
}

int Statement::get_id_count() {
  if (expression != NULL)
    return expression->get_id_count() + 1;
  return 0;
}

int Statement::get_const_count() {
  if (expression != NULL)
    return expression->get_const_count();
  return 0;
}

int Statement::get_op_count() {
  if (expression != NULL)
    return expression->get_op_count();
  return 0;
}

void Statement::print() {
  if (expression == NULL) {
    cout << "This statement is not parsed\n";
    return;
  }
	cout << ident << " := ";
	expression->print();
	if (semi_colon) {
		cout << " ;";
	}
	cout << '\n';
}

void Statement::print_messages() {
  if (expression != NULL) {
    expression->print_messages();
    return;
  }

  for (auto message: messages) {
    cout << message << '\n';
  }
}

Statement::~Statement() {
	delete expression;
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

void Expression::print_messages() {
  term->print_messages();
  if (term_tail != NULL) {
    term_tail->print_messages();
  }
}

Expression::~Expression() {
	delete term;
	delete term_tail;
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

void TermTail::print_messages() {
  term->print_messages();
  if (term_tail != NULL) {
    term_tail->print_messages();
  }
}

TermTail::~TermTail() {
	delete term;
	delete term_tail;
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

void Term::print_messages() {
  factor->print_messages();
  if (factor_tail != NULL) {
    factor_tail->print_messages();
  }
}

Term::~Term() {
	delete factor;
	delete factor_tail;
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

void FactorTail::print_messages() {
  factor->print_messages();
  if (factor_tail != NULL) {
    factor_tail->print_messages();
  }
}

FactorTail::~FactorTail() {
	delete factor;
	delete factor_tail;
}

//////////////// Factor ////////////////

Factor::Factor(SymbolTable *symbol_table, Expression *expression, string ident, int number, vector<string> messages) {
	this->symbol_table = symbol_table;
	this->expression = expression;
	this->ident = ident;
	this->number = number;
  this->messages = messages;
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

void Factor::print_messages() {
  for (auto message: messages) {
    cout << message << '\n';
  }
}

Factor::~Factor() {
	delete expression;
}
