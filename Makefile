all: try

CC = g++

SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin

try: $(OBJ_PATH)/main.o $(OBJ_PATH)/function1.o $(OBJ_PATH)/function2.o $(OBJ_PATH)/class1.o
	$(CC) -o $(BIN_PATH)/out.x $(OBJ_PATH)/main.o $(OBJ_PATH)/function1.o $(OBJ_PATH)/function2.o $(OBJ_PATH)/class1.o

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CC) -o $(OBJ_PATH)/main.o -c $(SRC_PATH)/main.cpp

$(OBJ_PATH)/function1.o: $(SRC_PATH)/function1.cpp
	$(CC) -o $(OBJ_PATH)/function1.o -c $(SRC_PATH)/function1.cpp

$(OBJ_PATH)/function2.o: $(SRC_PATH)/function2.cpp
	$(CC) -o $(OBJ_PATH)/function2.o -c $(SRC_PATH)/function2.cpp

$(OBJ_PATH)/class1.o: $(SRC_PATH)/class1.cpp
	$(CC) -o $(OBJ_PATH)/class1.o -c $(SRC_PATH)/class1.cpp

clean:
	rm -rf $(BIN_PATH)/*
	rm -rf $(OBJ_PATH)/*
