#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#include <vector>
#include <string>
#include <sstream>

#define TRUE 1
#define FALSE 0
#define PORT 8888

class ClientState {
    public:
        ClientState() : sock(-1), login(false) {}
        ClientState(int s) : sock(s), login(false) {}

        int sock;
        bool login;
        std::string user;
};


int main() {
    struct sockaddr_in address;
    std::vector<ClientState> client_socket;

    //create a master socket
    int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (master_socket < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    int opt = TRUE;
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    puts("Waiting for connections ...");

    while (TRUE) {
        //set of socket descriptors
        fd_set readfds;
        FD_ZERO(&readfds);                  //clear the socket set
        FD_SET(master_socket, &readfds);    //add master socket to set
        int max_sd = master_socket;

        //add child sockets to set
        for (size_t i = 0; i < client_socket.size(); ++i) {
            FD_SET(client_socket[i].sock, &readfds);
            max_sd = std::max(max_sd, client_socket[i].sock);
        }

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        //else its some IO operation on some other socket :)
        for (std::vector<ClientState>::iterator p = client_socket.begin(); p != client_socket.end(); ) {
            char buffer[1024]; //data buffer of 1K

            if (FD_ISSET(p->sock, &readfds)) {
                //Check if it was for closing , and also read the incoming message
                int valread = recv(p->sock, buffer, sizeof(buffer), 0);
                if (valread <= 0) {
                    printf("valread <= 0");
                    //Somebody disconnected , get his details and print
                    socklen_t addrlen = sizeof(address);
                    getpeername(p->sock, (struct sockaddr*)&address, (socklen_t*)&addrlen);

                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(p->sock);
                    p = client_socket.erase(p);
                } else {
                    printf("valread > 0");
                    if (!p->login) {
                        printf("!p->login");
                        const char *message ="username:";
                        send(p->sock , message , strlen(message), 0);
                        int n = recv(p->sock, buffer, sizeof(buffer), 0);
                        if (n > 2) { // account for trailing \r\n
                            p->login = true;
                            p->user.assign(buffer, n - 2);
                            std::ostringstream os;
                            os << "Welcome " << p->user << " to our server, no password required\r\n";
                            std::string str = os.str();
                            send(p->sock, &str[0], str.size(), 0);
                        }
                    } else {
                        printf("p->login");
                        int n = recv(p->sock, buffer, sizeof(buffer), 0);
                        if (n > 2) { // account for trailing \r\n
                            std::ostringstream os;
                            os << "Hello " << buffer << " \r\n";
                            std::string str = os.str();
                            send(p->sock, &str[0], str.size(), 0);
                        }
                    }
                    ++p;
                }
            } else {
                ++p;
            }
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            //accept the incoming connection
            socklen_t addrlen = sizeof(address);
            int new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            //send new connection greeting message
            const char *message = "Welcome to the server\r\n";
            if (send(new_socket, message, strlen(message), 0) != (long)strlen(message)) {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            client_socket.push_back(new_socket);
        }
    }

    return 0;
}
