# Simple Parser
## Team
| 이름 | 학번 |
| --- | --- |
| 김경민 | |
| 조영호 | 20203458 |

## Build and Run
```bash
$ make
$ ./parser testcase/example1.txt
```
## Test Environment
- macOS 14.0 arm64 (clang 15.0.0, GNU Make 3.81)
- Debian 11 aarch64 (g++ 10.2.1, GNU Make 4.3)

## 예외처리
### Error
1. 선언되지 않은 IDENT 사용
2. Statement에서 ASSIGNMENT_OP가 나오지 않는 경우
3. Statement가 IDENT로 시작하지 않는 경우
4. $, #같은 예상치 못한 문자가 들어오는 경우

### Warning
1. +, -, *, / 연산자가 연속해서 나오는 경우 두번째 연산자부터 무시
2. 맨 마지막 Statement에서 SEMI_COLON이 나오면 제거
3. Statement 사이에 SEMI_COLON이 없는 경우 추가
