BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: $(OBJ)/almacenrutas.o $(OBJ)/extra.o $(OBJ)/main.o $(OBJ)/punto.o $(OBJ)/ruta.o
	g++ -o $(BIN)/rutas $^
$(OBJ)/almacenrutas.o: $(SRC)/almacenrutas.cpp $(INCLUDE)/almacenrutas.h
	g++ -o $(OBJ)/almacenrutas.o -c $< -I$(INCLUDE)
$(OBJ)/extra.o: $(SRC)/extra.cpp $(INCLUDE)/extra.h
	g++ -o $(OBJ)/extra.o -c $< -I$(INCLUDE)
$(OBJ)/main.o: $(SRC)/main.cpp 
	g++ -o $(OBJ)/main.o -c $< -I$(INCLUDE)
$(OBJ)/punto.o: $(SRC)/punto.cpp $(INCLUDE)/punto.h
	g++ -o $(OBJ)/punto.o -c $< -I$(INCLUDE)
$(OBJ)/ruta.o: $(SRC)/ruta.cpp $(INCLUDE)/ruta.h
	g++ -o $(OBJ)/ruta.o -c $< -I$(INCLUDE)
clean:
	rm $(OBJ)/*.o
doc:
	doxygen $(DOC)/doxys/Doxyfile

.PHONY: all clean doc
