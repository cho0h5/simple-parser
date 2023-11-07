# Simple Parser
## `main`
```cpp
int main(int argc, char **argv) {
  // (...생략...)
  Lexer lexer(argv[1]);
  SymbolTable symbol_table;
  Parser parser(std::move(lexer), &symbol_table);
  // (...생략...)
  
  // 1. parse하여 parse_tree 생성
  Tree *parse_tree = parser.parse();

  // 2. ID, CONST, OP 개수 세기 및 정의되지 않은 식별자 사용 여부 확인
  parse_tree->analyze();

  // 3. 모든 Statement 평가
  parse_tree->evaluate();

  // 4. symbol_table에 담긴 변수들의 값 출력
  symbol_table.print_result();

  // (...생략...)
}
```
