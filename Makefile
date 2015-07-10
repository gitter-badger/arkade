NAME = arkade
CC = clang
C_SRC = $(wildcard src/*.c)
C_FLAGS = -Wall -Wextra -std=c99
EXE_OUT = bin/${NAME}

all: clean
	${CC} ${C_SRC} ${C_FLAGS} -o ${EXE_OUT}

clean:
	@rm -rf bin/