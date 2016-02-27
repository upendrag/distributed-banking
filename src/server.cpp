#include "tcp_server.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    TcpServer server(76542);
    try {
        server.start();
    } catch (Exception ex) {
        Utils::print_error("server_main: "
            + ex.get_message());
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
