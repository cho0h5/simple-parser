#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <map>

using namespace std;

class Container {
	bool is_unknown;
	int	value;

	public:
	Container() : is_unknown(true), value(0) {}

	void add(Container container);
	void sub(Container container);
	void mult(Container container);
	void div(Container container);
	void print();
};

class SymbolTable {
	map<string, Container> table;

	public:
	bool is_exist(string ident);
	void add_ident(string ident);
	Container get_value(string ident);
	void set_value(string ident, Container container);
};

#endif
