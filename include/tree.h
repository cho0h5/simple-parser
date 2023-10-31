#ifndef TREE_H
#define TREE_H

#include <symbol_table.h>

class Tree {
	protected:
	SymbolTable *symbol_table;

	public:
	virtual ~Tree() {};
	virtual void analyze() = 0;
	virtual Container evaluate() = 0;
	virtual int get_id_count() = 0;
	virtual int get_const_count() = 0;
	virtual int get_op_count() = 0;
	virtual void print() = 0;
};

class Statements;
class Statement;
class Expression;
class Term;
class TermTail;
class Factor;
class FactorTail;

class Program : public Tree {
	Statements *statements;

	public:
	Program(SymbolTable *symbol_table, Statements *statements);
	virtual ~Program();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class Statements : public Tree {
	Statement *statement;
	Statements *statements;

	public:
	Statements(SymbolTable *symbol_table, Statement *statement, Statements *statements);
	virtual ~Statements();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class Statement : public Tree {
	string ident;
	Expression *expression;
	bool semi_colon;

	public:
	Statement(SymbolTable *symbol_table, string ident, Expression *expression);
	virtual ~Statement();
	void set_semi_colon();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class Expression : public Tree {
	Term *term;
	TermTail *term_tail;

	public:
	Expression(SymbolTable *symbol_table, Term *term, TermTail *term_tail);
	virtual ~Expression();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class TermTail : public Tree {
	char add_or_sub;
	Term *term;
	TermTail *term_tail;

	public:
	TermTail(SymbolTable *symbol_table, char add_or_sub, Term *term, TermTail *term_tail);
	virtual ~TermTail();
	char get_add_or_sub();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class Term : public Tree {
	Factor *factor;
	FactorTail *factor_tail;

	public:
	Term(SymbolTable *symbol_table, Factor *factor, FactorTail *factor_tail);
	virtual ~Term();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class FactorTail : public Tree {
	char mult_or_div;
	Factor *factor;
	FactorTail *factor_tail;

	public:
	FactorTail(SymbolTable *symbol_table, char mult_or_div, Factor *factor, FactorTail *factor_tail);
	virtual ~FactorTail();
	char get_mult_or_div();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

class Factor : public Tree {
	Expression *expression;
	string ident;
	int number;

	public:
	Factor(SymbolTable *symbol_table, Expression *expression, string ident, int number);
	virtual ~Factor();

	virtual void analyze() override;
	virtual Container evaluate() override;
	virtual int get_id_count() override;
	virtual int get_const_count() override;
	virtual int get_op_count() override;
	virtual void print() override;
};

#endif
