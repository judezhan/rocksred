#include <iostream>
#include <chrono>
#include <thread>
#include "include/server.h"
#include "boost/asio.hpp"

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

const unsigned int DEFAULT_THREAD_POOL_SIZE = 4;

int main() {
    unsigned short port_num = 3333;
    try {
        Server srv;
        unsigned int thread_pool_size = std::thread::hardware_concurrency() * 2;
        if (thread_pool_size == 0)
            thread_pool_size = DEFAULT_THREAD_POOL_SIZE;
        srv.start(port_num, thread_pool_size);
        std::this_thread::sleep_for(std::chrono::seconds(60));
        srv.stop();
    } catch (boost::system::system_error& e) {
        std::cout << "Error occured! Error code = " << e.code()
            << ", msg = " << e.what() << std::endl;
    }
}
