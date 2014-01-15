BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: $(OBJ)/imagen.o $(OBJ)/pruebaimagen.o
	g++ -o $(BIN)/Practica_final $^

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	g++ -o $(OBJ)/imagen.o -c $< -I$(INCLUDE)

$(OBJ)/pruebaimagen.o: $(SRC)/pruebaimagen.cpp 
	g++ -o $(OBJ)/pruebaimagen.o -c $< -I$(INCLUDE)

clean:
	rm $(OBJ)/*.o
doc:
	doxygen $(DOC)/doxys/Doxyfile
