SRC=src/add.c src/bin.c src/ascii.c
BIN=bin/add bin/bin bin/ascii
CC=cc
FLAG=-std=gnu99 -O2

all: dir $(BIN)
$(BIN): $(SRC)
	env $(CC) $(FLAG) -o bin/bin   src/bin.c
	env $(CC) $(FLAG) -o bin/add   src/add.c
	env $(CC) $(FLAG) -o bin/ascii src/ascii.c
dir:
	env mkdir -p bin

install: all
	env mkdir -p ~/.local/bin
	env cp -f bin/* ~/.local/bin

uninstall:
	env rm -f ~/.local/bin/bin
	env rm -f ~/.local/bin/add
	env rm -f ~/.local/bin/ascii

clean:
	env rm -rf bin

help:
	@env echo 'make (all)      --  compile to ./bin'
	@env echo 'make install    --  compile and install to ~/.local/bin'
	@env echo 'make uninstall  --  delete from ~/.local/bin'
	@env echo 'make clean      --  clean ./bin'
