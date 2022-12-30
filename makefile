FLAGS = -Wall
OBJ = src/main.cpp src/function.cpp

compile:
	g++ $(FLAGS) -o main $(OBJ)
	
	
clean:
	rm -f src/*.o
	rm -f main
