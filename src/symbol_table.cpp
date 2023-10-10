#include <symbol_table.h>

void Container::add(Container container) {
	is_unknown = is_unknown && container.is_unknown;
	value = value + container.value;
}

void Container::sub(Container container) {
	is_unknown = is_unknown && container.is_unknown;
	value = value - container.value;
}

void Container::mult(Container container) {
	is_unknown = is_unknown && container.is_unknown;
	value = value * container.value;
}

void Container::div(Container container) {
	is_unknown = is_unknown && container.is_unknown;
	value = value / container.value;
}

void Container::print() {
	if (is_unknown) {
		cout << "Unknown";
	} else {
		cout << value;
	}
}

bool SymbolTable::is_exist(string ident) {
	return table.contains(ident);
}

void SymbolTable::add_ident(string ident) {
	table[ident] = Container();
}

Container SymbolTable::get_value(string ident) {
	return table[ident];
}

void SymbolTable::set_value(string ident, Container container) {
	table[ident] = container;
}

void SymbolTable::print_result() {
	cout << "\nResult ==> ";
	for (auto e : table) {
		cout << e.first << ": ";
		e.second.print();
		cout << "; ";
	}
	cout << '\n';
}
