#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <map>

using namespace std;

struct Container {
	bool is_unknown;
	int	value;

	Container() : is_unknown(true), value(0) {}
};

class SymbolTable {
	map<string, Container> table;

	public:
	bool is_exist(string ident);
	bool get_is_unknown(string ident);
	void add_ident(string ident);
	int get_value(string ident);
	void set_value(string ident, int value);
};

#endif
