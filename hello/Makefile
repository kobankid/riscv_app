CC=riscv64-unknown-elf-gcc
CFLAGS=-march=rv64ifdv -mabi=lp64d

.Phony: all
.Phony: clean

all: a.out

a.out: main.c
	${CC} ${CFLAGS} $^

clean:
	rm -rf ./a.out

