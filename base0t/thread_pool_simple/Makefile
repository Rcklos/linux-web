OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include
CC=g++

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

INC_LOG=log
CFLAGS=-g -Wall -I$(INC_DIR) -I$(INC_LOG)
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC))
TARGET = main

VPATH=$(SRC_DIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(addprefix $(OBJ_DIR)/, $(OBJS) $(CFLAGS))

%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $(OBJ)/$@

.PHONY: clean
clean:
	rm -rf $(BIN)/$(TARGET) $(OBJ_DIR)/*.o

# main: log.o thread_pool.o
# 	g++ -o bin/$@ obj/$^
#
# thread_pool.o: thread_pool.cpp
# 	g++ -o obj/$@ -c thread_pool.cpp
#
# log.o: log/log.cpp
# 	g++ -o obj/$@ -c log/log.cpp
