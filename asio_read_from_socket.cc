#include <iostream>
#include "boost/asio.hpp"

using namespace boost::asio;

int main() {
    char buff[1024];

    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
    ip::tcp::socket sock(service);
    sock.connect(ep);
    sock.write_some(buffer("GET /index.html\r\n"));
    std::cout << "Socket available " << sock.available() << std::endl;
    size_t size = sock.read_some(buffer(buff));
    std::cout << "Size readed " << size << std::endl;
}
