#include <iostream>

#include <lexer.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "You must enter only one argument!\n";
		exit(0);
	}

	Lexer lexer(argv[1]);

	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
	lexer.lexical();
	cout << lexer.get_next_token() << ":\t";
	cout << lexer.get_token_string() << '\n';
}
