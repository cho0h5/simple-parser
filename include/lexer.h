#ifndef LEXER_H
#define LEXER_H

#include <iostream>	// debug
#include <fstream>

using namespace std;

enum Nonterminal {
  PROGRAM,
  STATEMENTS,
  STATEMENT,
  EXPRESSION,
  TERM,
  TERM_TAIL,
  FACTOR,
  FACTOR_TAIL,
};

enum Terminal {
  CONST,        // any decimal numbers
  IDENT,        // any names conforming to C identifier rule
  ASSIGNMENT_OP,// :=
  SEMI_COLON,   // ;
  ADD_OP,       // + | -
  MULT_OP,      // * | /
  LEFT_PAREN,   // (
  RIGHT_PAREN,  // )
  END_OF_FILE,  // EOF
  UNKNOWN,      // unknown token
};

class Lexer {
  ifstream file;

  char next_char;

  Terminal next_token;
  string token_string;

  public:
  Lexer(const char* filename);
  bool is_open();

  void lexical();
  Terminal get_next_token();
  string get_token_string();
};

#endif
