#include <iostream>

#include <lexer.h>
#include <parser.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "You must enter only one argument!\n";
		exit(0);
	}

	Lexer lexer(argv[1]);

	Terminal next_token;
	lexer.lexical();
	next_token = lexer.get_next_token();
	while (next_token != END_OF_FILE) {
		cout << lexer.get_next_token() << ":\t";
		cout << lexer.get_token_string() << '\n';
		lexer.lexical();
		next_token = lexer.get_next_token();
	}
}
