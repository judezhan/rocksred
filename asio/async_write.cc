#include <iostream>
#include <string>
#include <ctime>

#include "boost/asio.hpp"

boost::asio::io_service ios;
boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), 2014);
boost::asio::ip::tcp::acceptor acc(ios, ep);
boost::asio::ip::tcp::socket sock(ios);
std::string data;

void write_handler(const boost::system::error_code& ec, std::size_t byte_transferred) {
    if (!ec) {
        std::cout << "Write succeed! " << byte_transferred << " bytes write." << std::endl;
        sock.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    } else {
        std::cout << "Write failed! Error code = " << ec.value() << std::endl;
    }
}

void connect_handler(const boost::system::error_code& ec){
    if (!ec) {  // Accept succeed
        std::time_t now = std::time(nullptr);
        data = std::ctime(&now);
        boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);
    } else {
        std::cout << "Accept failed! Error code = " << ec.value() << std::endl;
    }
}

int main() {
    acc.listen();
    acc.async_accept(sock, connect_handler);
    ios.run();
}
