CC = clang

EXE_NAME = arkade
EXE_DIR = bin/
EXE_PATH = ${EXE_DIR}${EXE_NAME}

C_SRC = $(wildcard src/*.c src/toml/*.c src/actions/*.c)
C_INCLUDE = -Iinclude/ -Iinclude/toml/
C_FLAGS = -Wall -Wextra -std=c99 -lcurl -Wno-unused-parameter ${C_INCLUDE} -o ${EXE_PATH}

.PHONY: clean

all: clean
	@mkdir -p ${EXE_DIR}
	${CC} ${C_SRC} ${C_FLAGS}

clean:
	@rm -f *.o
	@rm -rf bin/