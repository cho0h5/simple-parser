#ifndef TREE_H
#define TREE_H

enum ProductionRule {
	FIRST,
	SECOND,
	THIRD,
}

class Tree {
	SymbolTable symbol_table;

	public:
	virtual int evaluate();
	virtual int get_const_count();
	virtual int get_op_count();
	virtual void print();
	virtual void drop();
}

class Program : public Tree {
	Statements statements;
}

class Statements : public Tree {
	ProductionRule rule;
	Statement statement;
	Statements statements;
}

class Statement : public Tree {
	string ident;
	Expression expression;
}

class Expression : public Tree {
	Term term;
	TermTail term_tail;
}

class TermTail : public Tree {
	ProductionRule rule;
	char add_or_sub;
	Term term;
	TermTail term_tail;
}

class Term : public Tree {
	Factor factor;
	FactorTail factor_tail;
}

class FactorTail : public Tree {
	ProductionRule rule;
	char mult_or_div;
	Factor factor;
	FactorTail factor_tail;
}

class Factor : public Tree {
	ProductionRule rule;
	Expression expression;
	string ident;
	int const;
}

#endif
