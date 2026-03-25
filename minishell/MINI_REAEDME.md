*This project has been created as part of the 42 curriculum by inhlee.*


# minishell

## Description
**minishell** is a small Unix shell implemented in C as part of the 42 curriculum.  
The goal is to reproduce core shell behaviors such as command execution, pipelines, redirections, environment variable expansion, and signal handling, while following strict constraints on allowed functions and memory management.

### Key Features
- Prompt + interactive input (Readline)
- Command execution via `execve` using `PATH`
- Builtins:
  - `echo` (with `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Pipes (`|`)
- Redirections: input/output and append (`<`, `>`, `>>`)
- Here-document (`<<`)
- Quote handling:
  - Single quotes `'...'` prevent interpretation and expansion inside
  - Double quotes `"..."` allow `$` expansion
  - Unclosed quotes are detected and not interpreted
- Environment variable expansion (`$VAR`) and last status (`$?`)
- Signal behavior similar to bash for interactive mode (e.g., `Ctrl-C`, `Ctrl-\`)

---

## Instructions
make		- creating object files and compiling object files
make clean	- object files remove
make fclean	- executable file and execute make clean
make re		- execute make fclean and make

###Run
./minishell

## Resources
man pages:
	bash(1),
	fork(2), execve(2), waitpid(2)
	pipe(2), dup2(2), open(2), close(2)
	signal(2)
Readline documentation:
	GNU Readline Library Manual

## How AI was used
Debugging assistance: interpreting Valgrind output and reasoning about file descriptor lifetime issues (e.g., SIGPIPE causes).
Documentation: drafting this README structure and wording.


## project structure
src/lexer/	— tokenization, quote rules, splitting operators
src/parser/	— syntax validation, AST or command list building
src/expander/	— $VAR and $? expansion
src/executor/ 	— pipelines, redirections, heredoc, builtins, execve
includes/ 	— headers
libft/ 		— custom libft

###lexer
lexer의 체크는 사용자가 명령어를 입력시 쿼츠"'를 이용하여 작성시 형식에 맞지 않으면 쿼츠의 형식에 맞지 않는 형식이라고 에러 뱉음

쿼츠 기준 " " ' '을 기준으로 토큰을 나눈다

쿼츠 기준 커맨드를 토큰형식으로 나눈 후 pipe가 있으면 pipe기준으로 해당 토큰을 나눈다(해당 pipe가 형식에 맞는 pipe인지 확인 ex)"|" '|'  찾으면 해당 위치를 반환 찾은 파이프의 위치까지 token을 다시 만듬

파이프형식으로 나눈후 문제가 없으면 redirect 기준으로 토큰을 나눔 파이프 형식으로 먼저 이유는
파이프별 토큰을 나눈 후 해당 리다이렉트가 어느 파이프의 영역에 실행하는 redirect형식인지 알기 위해서 


###parser
lexer기준 나눈 토큰을 parser로 새로 생성하게 된다  파이프 기준나눈 토큰을 하나의 파서로 만든다 

나눠진 parser를 공백을 기준으로 나누어 토큰을 생성한다 

###ex

cataert || sefes cvb | "zxc" <zxc | 'asd' | $dgf >> asd"zxc"

따옴표 기준으로 나누는 함수
[cataert || sefes cvb | ]
["zxc"]
[ <zxc | ]
['asd']
[ | $dgf >> asd]
["zxc"]
  
파이프 기준으로 나누는 함수
[cataert ]
[||]
[ sefes cvb ]
[|]
[ ]
["zxc"]
[ <zxc ]
[|]
[ ]
['asd']
[ ]
[|]
[ $dgf >> asd]
["zxc"]
 
 리디렉트 기준으로 나누는 함수
[cataert ]
[||]
[ sefes cvb ]
[|]
[ ]
["zxc"]
[ ]
[<]
[zxc ]
[|]
[ ]
['asd']
[ ]
[|]
[ $dgf ]
[>>]
[ asd]
["zxc"]
 
파이프 기준으로 다시 합치는 함수
[cataert ]

[ sefes cvb ]

[ ]
["zxc"]
[ ]
[<]
[zxc ]

[ ]
['asd']
[ ]

[ $dgf ]
[>>]
[ asd]
["zxc"]
 
따옴표가 없던 애들을 스페이스 기준으로 나눠주는 함수
[cataert]
[]

[]
[sefes]
[]
[cvb]
[]

[]
["zxc"]
[]
[<]
[zxc]
[]

[]
['asd']
[]

[]
[$dgf]
[]
[>>]
[]
[asd]
["zxc"]

zero, double 쿼츠만 환경변수를 치환하는 함수 key_value[0] = $dgf, key_value[1] = "echo asd"
[cataert]
[]

[]
[sefes]
[]
[cvb]
[]

[]
["zxc"]
[]
[<]
[zxc]
[]

[]
['asd']
[]

[]
[echo asd]
[]
[>>]
[]
[asd]
["zxc"]
 
따옴표가 없던 애들을 스페이스 기준으로 나눠주는 함수
[cataert]
[]

[]
[sefes]
[]
[cvb]
[]

[]
["zxc"]
[]
[<]
[zxc]
[]

[]
['asd']
[]

[]
[echo]
[]
[asd]
[]
[>>]
[]
[asd]
["zxc"]

리디렉트를 제외한 띄어쓰기가 없는 token을 합치는 함수
[cataert]
[]

[]
[sefes]
[]
[cvb]
[]

[]
["zxc"]
[]
[<]
[zxc]
[]

[]
['asd']
[]

[]
[echo]
[]
[asd]
[]
[>>]
[]
["asdzxc"]

isspace만 있는 token을 띄어쓰기 token으로 바꿔주는 함수

띄어쓰기 다 지우기
[cataert]

[sefes]
[cvb]

["zxc"]
[<]
[zxc]

['asd']

[echo]
[asd]
[>>]
["asdzxc"]

parsing 된 구조체의 redir와 pipe의 형식이 맞는지 확인하는 함수

redir뒤에 파일 이름 형식이 맞는지 확인
parse 사이(pipe 사이)에 값이 올바른지 확인

parsing 된 구조체를 순회하며 heredoc이 있으면 열어주고 redir 구조체에 연결해주는 함수
<<a <<b			>

heredoc을 제외한 다른 파일들을 열어주는 함수
열면서 heredoc을 추가했던 redir 구조체에 위치에 맞게 추가
out은 따로 추가
파일 열기에 실패한 파일이 있다면 그 파일 정보를 redir의 맨 뒤에 연결


###single Pipe
"싱글(파이프라인)"

built-in을 부모에서 실행하여 부모의 프로세스의 값이 변하기 때문
싱글이면 execve로 실패하면 종료하기 때문에 fork를 따고 실행 
떄문에 빌트인이 아니면 싱글 포크실행
그래서 파이프가 없기 때문에 파일을 오픈하고 실행

###multi Pipe
"멀티(파이프라인)"
어차피 각 스테이지가 fork된 자식에서 돌아감

그 자식에서 built_in()을 호출해서 built-in을 실행

built-in이면 더 할 게 없으니 자식이 exit (부모가 아니라 자식)

“파일 open을 자식에서 한다”
파이프라인은 각 독립 프로세스니까 해당 파이프의 리다이렉션도 자식프로세스에서 실행 

자식에서 open+dup2로 stdin/stdout을 확정한 뒤, stdout을 파이프 write로 연결해서 다음 단계로 넘김
