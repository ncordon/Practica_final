BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src
FLAGS=--std=c++11

all: $(BIN)/rota $(BIN)/pega $(BIN)/rutas

$(BIN)/rota: $(OBJ)/imagen.o $(OBJ)/pruebarotacion.o
	g++ -o $(BIN)/rota $^

$(BIN)/pega: $(OBJ)/imagen.o $(OBJ)/pruebapegado.o
	g++ -o $(BIN)/pega $^

$(BIN)/rutas: $(OBJ)/almacenrutas.o $(OBJ)/usorutas.o $(OBJ)/punto.o $(OBJ)/ruta.o
	g++ -o $(BIN)/rutas $^

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	g++ -o $(OBJ)/imagen.o -c $< -I$(INCLUDE)
$(OBJ)/pruebarotacion.o: $(SRC)/pruebarotacion.cpp 
	g++ -o $(OBJ)/pruebarotacion.o -c $< -I$(INCLUDE)
$(OBJ)/pruebapegado.o: $(SRC)/pruebapegado.cpp 
	g++ -o $(OBJ)/pruebapegado.o -c $< -I$(INCLUDE)

$(OBJ)/punto.o: $(SRC)/punto.cpp $(INCLUDE)/punto.h
	g++ -o $(OBJ)/punto.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/ruta.o: $(SRC)/ruta.cpp $(INCLUDE)/ruta.h
	g++ -o $(OBJ)/ruta.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/almacenrutas.o: $(SRC)/almacenrutas.cpp $(INCLUDE)/almacenrutas.h
	g++ -o $(OBJ)/almacenrutas.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/usorutas.o: $(SRC)/usorutas.cpp 
	g++ -o $(OBJ)/usorutas.o -c $< -I$(INCLUDE) $(FLAGS)

clean:
	rm $(OBJ)/*.o
cleanall: clean
	rm $(BIN)/*
	rm -r $(DOC)/html
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

.PHONY: clean cleanall documentacion all