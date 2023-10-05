#include <lexer.h>

Lexer::Lexer(const char* filename) {
	file.open(filename, ios::in | ios::binary);
	file.get(next_char);
}

Lexer::~Lexer() {
	file.close();
}

void Lexer::lexical() {

	file.get(next_char);
}
