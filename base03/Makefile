include config.mk

writev:
	${CC} -o ${BIN}/$@ writev_resp.cpp

sendfile:
	${CC} -o ${BIN}/$@ sendfile.cpp

echo:
	${CC} -o ${BIN}/$@ splice_echo_server.cpp

tee:
	${CC} -o ${BIN}/$@ tee_echo_server.cpp
