#include "boost/asio.hpp"
#include <iostream>
#include <string>

void process_request(boost::asio::ip::tcp::socket& sock) {
    boost::asio::streambuf request_buf;
    boost::system::error_code ec;

    boost::asio::read(sock, request_buf, ec);
    if (ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream is(&request_buf);
    std::string line;
    std::getline(is, line);
    std::cout << "Receive data from server: " << line << std::endl;

    const char response_buf[] = {0x48, 0x69, 0x21};
    boost::asio::write(sock, boost::asio::buffer(response_buf));
    sock.shutdown(boost::asio::socket_base::shutdown_send);
}

int main() {
    const std::string ip = "127.0.0.1";
    const int port_num = 3333;

    try {
        boost::asio::io_service service;
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
        boost::asio::ip::tcp::acceptor acceptor(service, ep);
        boost::asio::ip::tcp::socket sock(service);
        acceptor.accept(sock);
        process_request(sock);
    } catch (boost::system::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
            << ". Message = " << e.what() << std::endl;
        return e.code().value();
    }
    return 0;
}
