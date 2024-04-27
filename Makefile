.PHONY: build

build:
	gcc -Os -s -I./include  main.c ./src/autarco.c ./src/conf_reader.c -o autarco.exe -ansi -L. -lcurl