#include "constants.h"
#include "tcp_server.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void on_client_data(SockData* c_data);

int main(int argc, char* argv[])
{
    SockData client_data;
    SockDataCb client_sock_cb;
    client_sock_cb.subscribe(&on_client_data, &client_data);

    TcpServer server(76542, &client_sock_cb);
    try {
        server.start();
    } catch (Exception ex) {
        Utils::print_error("server_main: "
            + ex.get_message());
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

void on_client_data(SockData* c_data)
{
    cout << c_data->filename << endl;

    switch(c_data->cmd_t) {
        case E_CMD_CREATE:
            break;
        case E_CMD_SEEK:
            break;
        case E_CMD_READ:
            break;
        case E_CMD_WRITE:
            break;
        default:
            break;
    }
}
