#include <iostream>
#include <chrono>
#include <thread>
#include "include/service.h"

void Service::handler(boost::asio::ip::tcp::socket& sock) {
    try {
        boost::asio::streambuf req_buf;
        boost::asio::read_until(sock, req_buf, '\n');
        int i=0;
        while (i < 1000000) {
            ++i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string resp_str = "Response\n";
        write(sock, boost::asio::buffer(resp_str));
    } catch (boost::system::system_error& ec) {
        std::cout << "Error occured. Error code = " << ec.code().value()
            << ", msg = " << ec.what() << std::endl;
    }
}
