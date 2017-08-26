#include <iostream>

#include "boost/asio.hpp"

boost::asio::io_service ioservice;
boost::asio::ip::tcp::resolver resolv(ioservice);
boost::asio::ip::tcp::socket tcp_socket(ioservice);
std::array<char, 4096> bytes;

void read_handler(const boost::system::error_code& ec, std::size_t byte_transferred) {
    if (!ec) {
        std::cout << byte_transferred << " bytes readed!" << std::endl;
        std::cout.write(bytes.data(), byte_transferred);
        tcp_socket.async_read_some(boost::asio::buffer(bytes), read_handler);
    } else {
        std::cout << "Error occured! Error code = " << ec.value() << ", msg = "
            << ec.message() << std::endl;
    }
}

void write_handler(const boost::system::error_code& ec, std::size_t byte_transferred) {
    if (!ec) {
        std::cout << byte_transferred << " bytes writed!" << std::endl;
        tcp_socket.async_read_some(boost::asio::buffer(bytes), read_handler);
    } else {
        std::cout << "Error occured! Error code = " << ec.value() << ", msg = "
            << ec.message() << std::endl;
    }
}

void connect_handler(const boost::system::error_code& ec) {
    if (!ec) {
        std::string r = "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
        // boost::asio::write(tcp_socket, boost::asio::buffer(r));
        boost::asio::async_write(tcp_socket, boost::asio::buffer(r), write_handler);
    } else {
        std::cout << "Error occured! Error code = " << ec.value() << ", msg = "
            << ec.message() << std::endl;
    }
}

void resolve_handler(const boost::system::error_code& ec, boost::asio::ip::tcp::resolver::iterator it) {
    if (!ec) {
        tcp_socket.async_connect(*it, connect_handler);
    } else {
        std::cout << "Error occured! Error code = " << ec.value() << ", msg = "
            << ec.message() << std::endl;
    }
}

int main() {
    boost::asio::ip::tcp::resolver::query q("theboostcpplibraries.com", "80");
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();
}
