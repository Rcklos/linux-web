BIN = bin
CC = g++

all: recv send

recv:
	${CC} -o ${BIN}/$@ recver.cpp

send:
	${CC} -o ${BIN}/$@ sender.cpp

clean:
	rm -rf ${BIN}/*
