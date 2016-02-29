#include "config.h"
#include "constants.h"
#include "tcp_socket.h"
#include "utils.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

void print_help(void);
void suggest_help(void);
void do_terminate(Config& cfg);

int main(int argc, char* argv[])
{
    // read config
    Config config(CONFIG_FILE);
    try {
        config.create();
    } catch (...) {
        Utils::print_error("unable to read config");
        exit(EXIT_FAILURE);
    }

    // init socket data
    SockData send_data;
    send_data.msg_t = CLIENT_TO_SERVER;

    // arguments indexes
    int arg1 = 1;
    int arg2 = 2;

    string cmd_str;

    // seed for random number
    srand(time(NULL));

    print_help();

    while (true) {
        // read command in prompt
        cout << ">> ";
        getline(cin, cmd_str);
        vector<string> cmd_args = Utils::split_str(cmd_str, " ");

        int arg_c = cmd_args.size();
        if (arg_c == 0)
            continue;
        string cmd = cmd_args.front();
   
        // Determine command type
        if (cmd == CMD_HELP) {
            print_help();
            continue;

        } else if (cmd == CMD_TERMINATE) {
            cout << "Terminating session..." << endl;
            do_terminate(config);
            cout << "Session ended" << endl;
            exit(EXIT_SUCCESS);

        } else if (cmd == CMD_CREATE) {
            if (arg_c < 2) {
                Utils::print_error(ERR_INSUFF_ARGS);
                suggest_help();
                continue;
            }

            // create data to send
            send_data.cmd_t = E_CMD_CREATE;
            Utils::copy_str_to_arr(cmd_args.at(arg1),
                send_data.filename,
                MAX_FILE_NAME_LEN);

        } else if (cmd == CMD_SEEK) {
            if (arg_c < 3) {
                Utils::print_error(ERR_INSUFF_ARGS);
                suggest_help();
                continue;
            }            
            int index;
            try {
                index = Utils::str_to_int(cmd_args.at(arg2));
            } catch (Exception ex) {
                Utils::print_error("Parsing seek index: " 
                    + ex.get_message());
                continue;
            }

            // create data to send
            send_data.cmd_t = E_CMD_SEEK;
            Utils::copy_str_to_arr(cmd_args.at(arg1),
                send_data.filename,
                MAX_FILE_NAME_LEN);
            send_data.input.number = index;

        } else if (cmd == CMD_READ) {
            if (arg_c < 3) {
                Utils::print_error(ERR_INSUFF_ARGS);
                suggest_help();
                continue;
            }            
            int length;
            try {
                length = Utils::str_to_int(cmd_args.at(arg2));
            } catch (Exception ex) {
                Utils::print_error("Parsing read length: " 
                    + ex.get_message());
                continue;
            }
            
            // create data to send
            send_data.cmd_t = E_CMD_READ;
            Utils::copy_str_to_arr(cmd_args.at(arg1),
                send_data.filename,
                MAX_FILE_NAME_LEN);
            send_data.input.number = length;

        } else if (cmd == CMD_WRITE) {
            if (arg_c < 3) {
                Utils::print_error(ERR_INSUFF_ARGS);
                suggest_help();
                continue;
            }
            string fname = cmd_args.at(arg1);

            // create data to send
            send_data.cmd_t = E_CMD_WRITE;
            Utils::copy_str_to_arr(fname,
                send_data.filename,
                MAX_FILE_NAME_LEN);
            
            // read content after file arguments
            // as text data to be written
            int data_pos = cmd_str.find(fname);
            data_pos = data_pos + fname.size() + 1; 
            string data = cmd_str.substr(data_pos,
                cmd_str.size() - data_pos);

            Utils::copy_str_to_arr(data,
                send_data.input.data,
                MAX_FILE_NAME_LEN);

        } else if (cmd == CMD_DELETE) {
            if (arg_c < 2) {
                Utils::print_error(ERR_INSUFF_ARGS);
                suggest_help();
                continue;
            }            

            // create data to send
            send_data.cmd_t = E_CMD_DELETE;
            Utils::copy_str_to_arr(cmd_args.at(arg1),
                send_data.filename,
                MAX_FILE_NAME_LEN);

        } else {
            Utils::print_error("Unknown option");
            suggest_help();
            continue;
        }

        // select server by random
        int server_num = (rand() % 3) + 1;

        // send request to server
        TcpConfig cfg = config.getTcpConfig(server_num);
        TcpSocket tcp_client(cfg.port, cfg.host);
        try {
            ReplyMessage recv_data;
            tcp_client.connect();
            tcp_client.send(&send_data, sizeof(SockData));
            tcp_client.receive(&recv_data, sizeof(ReplyMessage));
            cout << "Server " << recv_data.server_num
                << " :: " << recv_data.message << endl;
            tcp_client.close();
        } catch (Exception ex) {    
            Utils::print_error(ex.get_message());
        }
    }

    return 0;
}

void print_help(void)
{
    cout << "commands:" << endl;
    cout << "\t" <<  CMD_CREATE << " <filename>" << endl;
    cout << "\t" << CMD_SEEK << " <filename> <index>" << endl;
    cout << "\t" << CMD_READ << " <filename> <length>" << endl;
    cout << "\t" << CMD_WRITE << " <filename> <string>" << endl;
    cout << "\t" << CMD_DELETE << " <filename>" << endl;
    cout << "\t" << CMD_TERMINATE << endl;
    cout << "\t" << CMD_HELP << endl;
}

void suggest_help(void)
{
    cout << "Use 'help' for usage and commands" << endl;
}

void do_terminate(Config& config)
{
    SockData sig_term;
    sig_term.msg_t = CLIENT_TO_SERVER;
    sig_term.cmd_t = E_CMD_TERMINATE;

    for (int i = 1; i <= NUM_OF_SERVERS; ++i) {
        TcpConfig cfg = config.getTcpConfig(i);
        TcpSocket tcp_client(cfg.port, cfg.host);
        try {
            ReplyMessage recv_data;
            tcp_client.connect();
            tcp_client.send(&sig_term, sizeof(SockData));
            tcp_client.receive(&recv_data, sizeof(ReplyMessage));
            tcp_client.close();
        } catch (Exception ex) {
            // ignore errorrs;
        }
    }
}

