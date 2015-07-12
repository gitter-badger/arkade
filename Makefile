CC = clang

C_SRC = $(wildcard src/*.c) \
		$(wildcard src/toml/*.c)
INCLUDES =  -Iincludes/ \
			-Iincludes/toml/

C_FLAGS = -Wall -Wextra -Wno-unused-parameter -std=c99 ${INCLUDES} -lcurl

NAME = arkade
EXE_OUT_DIR = bin/
EXE_OUT = ${EXE_OUT_DIR}${NAME}

all: clean
	@mkdir -p ${EXE_OUT_DIR}
	${CC} ${C_SRC} ${C_FLAGS} -o ${EXE_OUT}

clean:
	@rm -rf bin/