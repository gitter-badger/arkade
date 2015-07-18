CC = clang

EXE_NAME = arkade
EXE_DIR = bin/
EXE_PATH = ${EXE_DIR}${EXE_NAME}

C_STD = 

ifeq ($(CC),gcc)
	C_STD = gnu99
else
	C_STD = c99
endif

C_SRC = $(wildcard src/*.c src/toml/*.c src/actions/*.c)
C_INCLUDE = -Iinclude/ -Iinclude/toml/
C_FLAGS = -Wall -Wextra -g -std=${C_STD} -lcurl -Wno-unused-parameter -pedantic ${C_INCLUDE} -o ${EXE_PATH}

.PHONY: clean

all: clean
	@mkdir -p ${EXE_DIR}
	${CC} ${C_SRC} ${C_FLAGS}

clean:
	@rm -f *.o
	@rm -rf bin/