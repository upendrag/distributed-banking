all: client server

client: commons client.o
	g++ -o bin/client obj/exception.o obj/utils.o obj/client.o

server: commons tcp_server.o server.o
	g++ -o bin/server obj/exception.o obj/utils.o obj/tcp_server.o obj/server.o
    	
client.o:
	g++ -c src/client.cpp -o obj/client.o

server.o:
	g++ -c src/server.cpp -o obj/server.o
tcp_server.o:
	g++ -c src/tcp_server.cpp -o obj/tcp_server.o

commons: exception.o utils.o

exception.o:
	g++ -c src/exception.cpp -o obj/exception.o

utils.o:
	g++ -c src/utils.cpp -o obj/utils.o

.PHONY: clean
clean:
	rm -rf bin/* obj/*
