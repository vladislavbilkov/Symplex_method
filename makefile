FLAGS = $$( pkg-config --cflags gtk4 ) 
OBJ = src/main.c
LIBS = $$( pkg-config --libs gtk4 ) 

compile:
	gcc $(FLAGS) -o main $(OBJ) $(LIBS)
	
clean:
	rm -f main
