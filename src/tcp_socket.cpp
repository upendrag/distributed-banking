#include "tcp_socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

TcpSocket::TcpSocket(std::string host, int port)
: host(host), port(port)
{ }

TcpSocket::~TcpSocket() throw (Exception)
{
    if (sock_fd > -1)
        ::close(sock_fd);
}

void TcpSocket::init(void) throw (Exception)
{
    // create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        throw Exception("unable to create socket", true);

    // get host's DNS entry
    host_entry = gethostbyname(host.c_str());
    if (!host_entry)
        throw Exception("no such host " + host, true);
    
    // build host's internet address
    memset(&host_addr, 0, sizeof(host_addr));
    host_addr.sin_family = AF_INET;
    memcpy((char *)&host_addr.sin_addr.s_addr, host_entry->h_addr,
        host_entry->h_length);
    host_addr.sin_port = htons(port);

    // create a connection with the host
    connect();
}

void TcpSocket::close(void) throw (Exception)
{
    ::close(sock_fd);
}

void TcpSocket::send(SockData* data) throw (Exception)
{
    int bytes_written = write(sock_fd, data, sizeof(SockData));
    if (bytes_written < 0)
        throw Exception("cannot send data", true);
}

std::string TcpSocket::receive(void) throw (Exception)
{
    char buf[MAX_DATA_LEN] = {0};
    int bytes_read = read(sock_fd, &buf, MAX_DATA_LEN);
    if (bytes_read < 0)
        throw Exception("cannot receive data", true);
    std::string data(buf);
    return data;
}

void TcpSocket::connect(void) throw (Exception)
{
    int success = ::connect(sock_fd, (struct sockaddr*)&host_addr,
        sizeof(host_addr));
    if (success < 0)
        throw Exception("unable to connect to host", true);
}
