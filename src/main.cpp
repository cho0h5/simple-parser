#include <iostream>

#include <lexer.h>
#include <parser.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "You must enter only one argument!\n";
		exit(0);
	}

	Lexer lexer(argv[1]);
	Parser parser(std::move(lexer));

	parser.parse();
}
