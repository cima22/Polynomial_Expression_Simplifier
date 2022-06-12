all: try

CC = g++
VERSION = c++17

SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin

try: $(OBJ_PATH)/main.o $(OBJ_PATH)/expr.o $(OBJ_PATH)/var.o $(OBJ_PATH)/varExpr.o $(OBJ_PATH)/constExpr.o
	$(CC) -o $(BIN_PATH)/out.x $(OBJ_PATH)/main.o $(OBJ_PATH)/expr.o $(OBJ_PATH)/var.o $(OBJ_PATH)/varExpr.o $(OBJ_PATH)/constExpr.o

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CC) -o $(OBJ_PATH)/main.o -c $(SRC_PATH)/main.cpp

$(OBJ_PATH)/var.o: $(SRC_PATH)/var.cpp
	$(CC) -o $(OBJ_PATH)/var.o -c $(SRC_PATH)/var.cpp

$(OBJ_PATH)/expr.o: $(SRC_PATH)/expr.cpp
	$(CC) -o $(OBJ_PATH)/expr.o -c $(SRC_PATH)/expr.cpp

$(OBJ_PATH)/varExpr.o: $(SRC_PATH)/varExpr.cpp
	$(CC) -o $(OBJ_PATH)/varExpr.o -c $(SRC_PATH)/varExpr.cpp

$(OBJ_PATH)/constExpr.o: $(SRC_PATH)/constExpr.cpp
	$(CC) -o $(OBJ_PATH)/constExpr.o -c $(SRC_PATH)/constExpr.cpp

clean:
	rm -rf $(BIN_PATH)/*
	rm -rf $(OBJ_PATH)/*
