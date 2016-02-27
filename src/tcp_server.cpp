#include "tcp_server.h"

#include <iostream> //TODO: remove

TcpServer::~TcpServer() throw (Exception)
{
    main_socket.close();
}

void TcpServer::start(void) throw (Exception)
{
    // bind
    main_socket.bind();
    
    // listen
    main_socket.listen();

    // accept
    TcpSocket client_socket;
    int client_len;
    while (true) {
        main_socket.accept(client_socket, client_len);

        SockData data;
        client_socket.receive(&data, sizeof(SockData));
        std::cout << data.filename << std::endl;
        client_socket.send((void *)"Success", 10);
        client_socket.close();
    }
}

