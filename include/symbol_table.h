#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>

using namespace std;

struct Container {
	bool is_unknown;
	int	value;
}

class SymbolTable {
	map<string, Container>;

	public:
	bool is_exist(string);
	bool get_is_unknown(string);
	int get_value(string);
	void set_value(string);
}

#endif
