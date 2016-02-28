all: client server

client: commons client.o
	g++ -Wall -o bin/client obj/exception.o obj/utils.o obj/tcp_socket.o obj/client.o

server: commons tcp_server.o registry.o server.o
	g++ -Wall -o bin/server obj/exception.o obj/utils.o obj/tcp_socket.o obj/sock_data_cb.o obj/registry.o obj/tcp_server.o obj/server.o
    	
client.o:
	g++ -Wall -c src/client.cpp -o obj/client.o

server.o:
	g++ -Wall -c src/server.cpp -o obj/server.o

tcp_server.o:
	g++ -Wall -c src/tcp_server.cpp -o obj/tcp_server.o

registry.o:
	g++ -Wall -c src/registry.cpp -o obj/registry.o

commons: exception.o utils.o tcp_socket.o sock_data_cb.o

sock_data_cb.o:
	g++ -Wall -c src/sock_data_cb.cpp -o obj/sock_data_cb.o

tcp_socket.o:
	g++ -Wall -c src/tcp_socket.cpp -o obj/tcp_socket.o

exception.o:
	g++ -Wall -c src/exception.cpp -o obj/exception.o

utils.o:
	g++ -Wall -c src/utils.cpp -o obj/utils.o

.PHONY: clean
clean:
	rm -rf bin/* obj/*
