build: 2048ECOS

2048ECOS: 2048ECOS.c	
	gcc -Wall 2048ECOS.c -o 2048ECOS -lncurses

.PHONY:

run:
	./2048ECOS
clean:
	rm -f 2048ECOS
