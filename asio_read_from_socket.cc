#include <iostream>
#include "boost/asio.hpp"

using namespace boost::asio;

int main() {
    char buff[1024];

    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("123.125.114.144"), 80);
    // ip::tcp::socket sock(service, ep);
    ip::tcp::socket sock(service);
    sock.connect(ep);
    sock.write_some(buffer("GET /index.html\r\n"));
    std::cout << "Socket available " << sock.available() << std::endl;
    size_t size = sock.read_some(buffer(buff));
    std::cout << "Size readed " << size << std::endl;
}
