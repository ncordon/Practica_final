BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: rota pega

rota: $(OBJ)/imagen.o $(OBJ)/pruebarotacion.o
	g++ -o $(BIN)/rota $^

pega: $(OBJ)/imagen.o $(OBJ)/pruebapegado.o
	g++ -o $(BIN)/pega $^

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	g++ -o $(OBJ)/imagen.o -c $< -I$(INCLUDE)

$(OBJ)/pruebarotacion.o: $(SRC)/pruebarotacion.cpp 
	g++ -o $(OBJ)/pruebarotacion.o -c $< -I$(INCLUDE)

$(OBJ)/pruebapegado.o: $(SRC)/pruebapegado.cpp 
	g++ -o $(OBJ)/pruebapegado.o -c $< -I$(INCLUDE)

clean:
	rm $(OBJ)/*.o
cleanall: clean
	rm $(BIN)/*
	rm -r $(DOC)/html
doc:
	doxygen $(DOC)/doxys/Doxyfile
