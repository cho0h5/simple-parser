// (waring) (error) 출력 위치 바꾸기

#include <iostream>

#include <lexer.h>
#include <parser.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "You must enter only one argument!\n";
		exit(0);
	}

	Lexer lexer(argv[1]);
	SymbolTable symbol_table;
	Parser parser(std::move(lexer), &symbol_table);

	Tree *parse_tree = parser.parse();

	parse_tree->analyze();
	parse_tree->evaluate();
	symbol_table.print_result();

	delete parse_tree;
}
