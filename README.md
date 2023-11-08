# Simple Parser
## Team
| 이름 | 학번 |
| --- | --- |
| 김경민 | 20224680 |
| 조영호 | 20203458 |

## Build and Run
```bash
$ make
$ ./parser testcase/example1.txt
```
## Test Environment
| OS | Architecture | Compiler | Make |
| --- | --- | --- | --- |
| macOS 14.0 | arm64 | clang 15.0.0 | GNU Make 3.81 |
| Debian 11 | aarch64 | g++ 10.2.1 | GNU Make 4.3 |
| Rocky Linux 9.2 | x86_64 | g++ 11.3.1 | GNU Make 4.3 |
| Arch Linux | x86_64 | g++ 13.2.1 | GNU Make 4.4.1 |

## Exception Handling
### Error
1. 선언되지 않은 `IDENT` 사용
  - `./testcase/example2.txt`
2. `Statement`에서 `ASSIGNMENT_OP`가 나오지 않는 경우
  - `./testcase/only_colon.txt`
3. `Statement`가 `IDENT`로 시작하지 않는 경우
  - `./testcase/start_without_ident1.txt`
  - `./testcase/start_without_ident2.txt`
4. `$`, `#`같은 예상치 못한 문자가 들어오는 경우
  - `./testcase/unknown_op.txt`

### Warning
1. `+`, `-`, `*`, `/` 연산자가 연속해서 나오는 경우 두번째 연산자부터 무시
  - `./testcase/add_double.txt`
  - `./testcase/double_mult.txt.txt`
  - `./testcase/example4.txt`
  - `./testcase/operators.txt`
2. 맨 마지막 `Statement`에서 `SEMI_COLON`이 나오면 제거
  - `./testcase/semicolon_at_the_end.txt`
3. `Statement` 사이에 `SEMI_COLON`이 없는 경우 추가
  - `./testcase/no_op.txt`
  - `./testcase/no_semicolon1.txt.txt`
  - `./testcase/no_semicolon2.txt`

### ETC
1. Decimal 음수 처리
  - `./testcase/negative_const.txt.txt`
  - `./testcase/positive_const.txt`
