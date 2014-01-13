SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c

all: $(BIN)/rota

$(BIN)/rota: $(OBJ)/rota.o
	g++ -o $(BIN)/rota $^

$(OBJ)/rota.o: $(SRC)/pruebarotacion.cpp
	g++ -o $(OBJ)/rota.o -c $^ -I$(INC)


# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
