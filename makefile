BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src
FLAGS=--std=c++0x #-Wall

all: $(BIN)/ruta

$(BIN)/ruta: $(SRC)/main.cpp $(OBJ)/imagen.o $(OBJ)/punto.o $(OBJ)/ruta.o $(OBJ)/almacenrutas.o
	g++ -o $(BIN)/ruta $^ -I$(INCLUDE) $(FLAGS)

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	g++ -o $(OBJ)/imagen.o -c $< -I$(INCLUDE)
$(OBJ)/punto.o: $(SRC)/punto.cpp $(INCLUDE)/punto.h
	g++ -o $(OBJ)/punto.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/ruta.o: $(SRC)/ruta.cpp $(INCLUDE)/ruta.h
	g++ -o $(OBJ)/ruta.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/almacenrutas.o: $(SRC)/almacenrutas.cpp $(INCLUDE)/almacenrutas.h
	g++ -o $(OBJ)/almacenrutas.o -c $< -I$(INCLUDE) $(FLAGS)

clean:
	rm $(OBJ)/*.o
cleanall: clean
	rm $(BIN)/*
	rm -r $(DOC)/html
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

.PHONY: clean cleanall documentacion all
