prog:fonction.o enigmes.o
	gcc enigmes.o fonction.o -o prog -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL
enigmes.o:enigmes.c
	gcc -c enigmes.c
fonction.o:fonction.c
	gcc -c fonction.c
