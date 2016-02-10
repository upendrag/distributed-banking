all: client server

client: client.o
	g++ -o bin/client obj/client.o

server: server.o
	g++ -o bin/server obj/server.o
    	
client.o:
	g++ -c src/client.cpp -o obj/client.o

server.o:
	g++ -c src/server.cpp -o obj/server.o

.PHONY: clean
clean:
	rm -rf bin/* obj/*
