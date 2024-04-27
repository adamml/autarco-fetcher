.PHONY: build

build:
	gcc -Os -s -m32 -I./include  main.c ./src/autarco.c ./src/conf_reader.c -o autarco.exe -ansi -lkernel32 -Lcurl