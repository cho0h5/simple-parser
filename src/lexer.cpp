#include <lexer.h>

// := 식별할 때 예외처리 필요
// 아무것도 식별 룰에 안 걸릴 때 예외처리 필요
// 음수 처리?
// 식별자에 밑줄 처리

Lexer::Lexer(const char* filename) {
	file.open(filename, ios::in | ios::binary);
	file.get(next_char);
}

void Lexer::lexical() {
	token_string.clear();
	if (file.eof()) {
		file.close();
		next_token = END_OF_FILE;
		print_string();
		return;
	}
	while (next_char <= 32) {
		file.get(next_char);
		if (file.eof()) {
			file.close();
			next_token = END_OF_FILE;
			print_string();
			return;
		}
	}
	if (isdigit(next_char)) {
		while (isdigit(next_char) && !file.eof()) {
			token_string.push_back(next_char);
			file.get(next_char);
		}
		next_token = CONST;
		print_string();
		return;
	}
	if (isalpha(next_char)) {
		while ((isalpha(next_char) || isdigit(next_char)) && !file.eof()) {
			token_string.push_back(next_char);
			file.get(next_char);
		}
		next_token = IDENT;
		print_string();
		return;
	}
	if (next_char == ':') {
		token_string.push_back(next_char);
		file.get(next_char);
		if (next_char == '=') {
			token_string.push_back(next_char);
			file.get(next_char);
			next_token = ASSIGNMENT_OP;
			print_string();
			return;
		}
		// 예외처리 필요
	}
	if (next_char == ';') {
		token_string.push_back(next_char);
		file.get(next_char);
		next_token = SEMI_COLON;
		print_string();
		return;
	}
	if (next_char == '+' || next_char == '-') {
		token_string.push_back(next_char);
		file.get(next_char);
		next_token = ADD_OP;
		print_string();
		return;
	}
	if (next_char == '*' || next_char == '/') {
		token_string.push_back(next_char);
		file.get(next_char);
		next_token = MULT_OP;
		print_string();
		return;
	}
	if (next_char == '(') {
		token_string.push_back(next_char);
		file.get(next_char);
		next_token = LEFT_PAREN;
		print_string();
		return;
	}
	if (next_char == ')') {
		token_string.push_back(next_char);
		file.get(next_char);
		next_token = RIGHT_PAREN;
		print_string();
		return;
	}
	// 예외처리 필요
}


Terminal Lexer::get_next_token() {
	return next_token;
}

string Lexer::get_token_string() {
	return token_string;
}

void Lexer::print_string() {
	cout << get_token_string() << ' ';
}
