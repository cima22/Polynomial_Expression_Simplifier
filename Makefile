all: try

CC = g++
VERSION = c++17

SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin

try: $(OBJ_PATH)/main.o $(OBJ_PATH)/expr.o $(OBJ_PATH)/var.o $(OBJ_PATH)/expr_parent.o $(OBJ_PATH)/expr_child.o
	$(CC) -o $(BIN_PATH)/out.x $(OBJ_PATH)/main.o $(OBJ_PATH)/expr.o $(OBJ_PATH)/var.o $(OBJ_PATH)/expr_parent.o $(OBJ_PATH)/expr_child.o

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CC) -o $(OBJ_PATH)/main.o -c $(SRC_PATH)/main.cpp

$(OBJ_PATH)/var.o: $(SRC_PATH)/var.cpp
	$(CC) -o $(OBJ_PATH)/var.o -c $(SRC_PATH)/var.cpp

$(OBJ_PATH)/expr.o: $(SRC_PATH)/expr.cpp
	$(CC) -o $(OBJ_PATH)/expr.o -c $(SRC_PATH)/expr.cpp

$(OBJ_PATH)/expr_parent.o: $(SRC_PATH)/expr_parent.cpp
	$(CC) -o $(OBJ_PATH)/expr_parent.o -c $(SRC_PATH)/expr_parent.cpp

$(OBJ_PATH)/expr_child.o: $(SRC_PATH)/expr_child.cpp
	$(CC) -o $(OBJ_PATH)/expr_child.o -c $(SRC_PATH)/expr_child.cpp

clean:
	rm -rf $(BIN_PATH)/*
	rm -rf $(OBJ_PATH)/*
