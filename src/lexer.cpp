#include <lexer.h>

Lexer::Lexer(const char* filename) {
  file.open(filename, ios::in | ios::binary);
  file.get(next_char);
}

bool Lexer::is_open() {
  return file.is_open();
}

void Lexer::lexical() {
  token_string.clear();
  if (file.eof()) {
    file.close();
    next_token = END_OF_FILE;
    return;
  }
  while (next_char <= 32) {
    file.get(next_char);
    if (file.eof()) {
      file.close();
      next_token = END_OF_FILE;
      return;
    }
  }
  if (isdigit(next_char)) {
    while (isdigit(next_char) && !file.eof()) {
      token_string.push_back(next_char);
      file.get(next_char);
    }
    next_token = CONST;
    return;
  }
  if (isalpha(next_char)) {
    while ((isalpha(next_char) || isdigit(next_char)) && !file.eof()) {
      token_string.push_back(next_char);
      file.get(next_char);
    }
    next_token = IDENT;
    return;
  }
  if (next_char == ':') {
    token_string.push_back(next_char);
    file.get(next_char);
    if (next_char == '=') {
      token_string.push_back(next_char);
      file.get(next_char);
      next_token = ASSIGNMENT_OP;
      return;
    }
    next_token = UNKNOWN;
    return;
  }
  if (next_char == ';') {
    token_string.push_back(next_char);
    file.get(next_char);
    next_token = SEMI_COLON;
    return;
  }
  if (next_char == '+' || next_char == '-') {
    token_string.push_back(next_char);
    file.get(next_char);
    if (isdigit(next_char)) {
      while (isdigit(next_char) && !file.eof()) {
        token_string.push_back(next_char);
        file.get(next_char);
      }
      next_token = CONST;
      return;
    }
    next_token = ADD_OP;
    return;
  }
  if (next_char == '*' || next_char == '/') {
    token_string.push_back(next_char);
    file.get(next_char);
    next_token = MULT_OP;
    return;
  }
  if (next_char == '(') {
    token_string.push_back(next_char);
    file.get(next_char);
    next_token = LEFT_PAREN;
    return;
  }
  if (next_char == ')') {
    token_string.push_back(next_char);
    file.get(next_char);
    next_token = RIGHT_PAREN;
    return;
  }
  next_token = UNKNOWN;
  file.get(next_char);
  return;
}


Terminal Lexer::get_next_token() {
  return next_token;
}

string Lexer::get_token_string() {
  return token_string;
}
