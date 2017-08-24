#include <iostream>
#include <thread>
#include <chrono>

#include "include/server.h"

int main() {
    const unsigned short port_num = 3333;
    try {
        Server srv;
        srv.start(port_num);
        std::this_thread::sleep_for(std::chrono::seconds(20));
        srv.stop();
    } catch (boost::system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code()
            << ", msg = " << e.what() << std::endl;
    }
}
