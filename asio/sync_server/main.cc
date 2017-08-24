#include <iostream>
#include <thread>
#include <chrono>

#include "boost/asio.hpp"

#include "include/server.h"

using namespace boost::asio;

int main() {
    unsigned short port_num = 3333;
    try {
        Server server;
        server.start(port_num);
        std::cout << "I am going to sleep..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "I am going to stop the server..." << std::endl;
        server.stop();
    } catch (boost::system::system_error& ec) {
        std::cout << "Error occured. Error code = " << ec.code().value()
            << ", msg = " << ec.what() << std::endl;
    }
}
