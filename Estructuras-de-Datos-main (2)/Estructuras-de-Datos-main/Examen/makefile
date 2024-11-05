
banderas = -Wall -Werror -pedantic -std=c99
folders = -Ilib/Listas
libfolder = -Llib/s
lib = -liblista_doble

SRC = examen.c
OBJ = examen.o

examen: $(OBJ)
	gcc $(banderas) $(OBJ) -o examen $(folders) $(libfolder) $(lib)

clean:
	rm -f $(OBJ) examen
