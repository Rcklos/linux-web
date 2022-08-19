BIN = bin
CC = g++

$(shell mkdir -p ${BIN})

clean:
	rm -rf ${BIN}/*
