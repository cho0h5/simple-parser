#include <symbol_table.h>

bool SymbolTable::is_exist(string ident) {
	return table.contains(ident);
}

bool SymbolTable::get_is_unknown(string ident) {
	return table[ident].is_unknown;
}

void SymbolTable::add_ident(string ident) {
	table[ident] = Container();
}

int SymbolTable::get_value(string ident) {
	return table[ident].value;
}

void SymbolTable::set_value(string ident, int value) {
	table[ident].is_unknown = false;
	table[ident].value = value;
}
