BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src
FLAGS=--std=c++0x #-Wall

all: $(BIN)/ruta $(BIN)/rota $(BIN)/pega

$(BIN)/ruta: $(SRC)/main.cpp $(OBJ)/imagen.o $(OBJ)/punto.o $(OBJ)/ruta.o $(OBJ)/almacenrutas.o $(OBJ)/pais.o $(OBJ)/creadorimagenes.o
	g++ -o $(BIN)/ruta $^ -I$(INCLUDE) $(FLAGS)
$(BIN)/rota: $(SRC)/pruebarotacion.cpp $(OBJ)/imagen.o
	g++ -o $(BIN)/rota $^ -I$(INCLUDE) $(FLAGS)
$(BIN)/pega: $(SRC)/pruebapegado.cpp $(OBJ)/imagen.o
	g++ -o $(BIN)/pega $^ -I$(INCLUDE) $(FLAGS)

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	g++ -o $(OBJ)/imagen.o -c $< -I$(INCLUDE)
$(OBJ)/punto.o: $(SRC)/punto.cpp $(INCLUDE)/punto.h
	g++ -o $(OBJ)/punto.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/ruta.o: $(SRC)/ruta.cpp $(INCLUDE)/ruta.h
	g++ -o $(OBJ)/ruta.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/almacenrutas.o: $(SRC)/almacenrutas.cpp $(INCLUDE)/almacenrutas.h
	g++ -o $(OBJ)/almacenrutas.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/pais.o: $(SRC)/pais.cpp $(INCLUDE)/pais.h
	g++ -o $(OBJ)/pais.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/creadorimagenes.o: $(SRC)/creadorimagenes.cpp $(INCLUDE)/creadorimagenes.h
	g++ -o $(OBJ)/creadorimagenes.o -c $< -I$(INCLUDE) $(FLAGS)

clean:
	rm $(OBJ)/*.o
cleanall: clean
	rm $(BIN)/*
	rm -r $(DOC)/html
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

.PHONY: clean cleanall documentacion all
