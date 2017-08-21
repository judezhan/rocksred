#include "boost/asio.hpp"
#include <iostream>
#include <string>

void communicate(boost::asio::ip::tcp::socket& sock) {
    const char request_data[] = {0x48, 0x65, 0x0, 0x6c, 0x6c, 0x6f};
    boost::asio::write(sock, boost::asio::buffer(request_data));
    sock.shutdown(boost::asio::socket_base::shutdown_send);
    boost::asio::streambuf response_buf;
    boost::system::error_code ec;
    boost::asio::read(sock, response_buf, ec);

    std::istream is(&response_buf);
    std::string line;
    std::getline(is, line);

    std::cout << "Receive data from server: " << line << std::endl;

    if (ec == boost::asio::error::eof) {
        printf("All msg received");
    } else {
        throw boost::system::system_error(ec);
    }
}

int main() {
    const std::string ip = "127.0.0.1";
    const int port_num = 3333;

    try {
        boost::asio::io_service service;
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port_num);
        boost::asio::ip::tcp::socket sock(service);
        sock.connect(ep);
        communicate(sock);
    } catch (boost::system::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
            << ". Message = " << e.what() << std::endl;
        return e.code().value();
    }
    return 0;
}
