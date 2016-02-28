#include "constants.h"
#include "tcp_socket.h"
#include "utils.h"

#include <iostream>

using namespace std;

void print_help(string);
void suggest_help(string);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        Utils::print_error("Too few argumemts");
        suggest_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    string cmd(argv[1]);

    // init socket data
    SockData send_data;

    // Determine command type
    if (cmd == CMD_HELP) {
        print_help(argv[0]);
        exit(EXIT_SUCCESS);
    } else if (cmd == CMD_TERMINATE) {
        send_data.cmd_t = E_CMD_TERMINATE;
    } else if (cmd == CMD_CREATE) {
        if (argc < 3) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            

        // create data to send
        send_data.cmd_t = E_CMD_CREATE;
        Utils::reset_copy_arr(send_data.filename, argv[2],
            MAX_FILE_NAME_LEN);

    } else if (cmd == CMD_SEEK) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        int index;
        try {
            index = Utils::str_to_int(argv[3]);
        } catch (Exception ex) {
            Utils::print_error("Parsing seek index: " 
                + ex.get_message());
            exit(EXIT_FAILURE);
        }

        // create data to send
        send_data.cmd_t = E_CMD_SEEK;
        Utils::reset_copy_arr(send_data.filename, argv[2],
            MAX_FILE_NAME_LEN);
        send_data.input.number = index;

    } else if (cmd == CMD_READ) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        int length;
        try {
            length = Utils::str_to_int(argv[3]);
        } catch (Exception ex) {
            Utils::print_error("Parsing read length: " 
                + ex.get_message());
            exit(EXIT_FAILURE);
        }
        
        // create data to send
        send_data.cmd_t = E_CMD_READ;
        Utils::reset_copy_arr(send_data.filename, argv[2],
            MAX_FILE_NAME_LEN);
        send_data.input.number = length;

    } else if (cmd == CMD_WRITE) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }

        // create data to send
        send_data.cmd_t = E_CMD_WRITE;
        Utils::reset_copy_arr(send_data.filename, argv[2],
            MAX_FILE_NAME_LEN);
        Utils::reset_copy_arr(send_data.input.data, argv[3],
            MAX_WRITE_LEN);

    } else if (cmd == CMD_DELETE) {
        if (argc < 3) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            

        // create data to send
        send_data.cmd_t = E_CMD_DELETE;
        Utils::reset_copy_arr(send_data.filename, argv[2],
            MAX_FILE_NAME_LEN);

    } else {
        Utils::print_error("Unknown option");
        suggest_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    TcpSocket tcp_client(76542);
    try {
        char recv_data[256];
        tcp_client.connect();
        tcp_client.send(&send_data, sizeof(SockData));
        tcp_client.receive(&recv_data, 256);
        cout << recv_data << endl;
        tcp_client.close();
    } catch (Exception ex) {    
        Utils::print_error(ex.get_message());
        exit(EXIT_FAILURE);
    }

    return 0;
}

void print_help(string app_name)
{
    cout << "usage: " << app_name << " <option> ..." << endl;
    cout << "options:" << endl;
    cout << "\t" <<  CMD_CREATE << " <filename>" << endl;
    cout << "\t" << CMD_SEEK << " <filename> <index>" << endl;
    cout << "\t" << CMD_READ << " <filename> <length>" << endl;
    cout << "\t" << CMD_WRITE << " <filename> <string>" << endl;
    cout << "\t" << CMD_DELETE << " <filename>" << endl;
    cout << "\t" << CMD_TERMINATE << endl;
    cout << "\t" << CMD_HELP << endl;
}

void suggest_help(string app_name)
{
    cout << "Run '" << app_name << " help' for usage and options" << endl;
}
