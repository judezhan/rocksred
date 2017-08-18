#include "boost/asio.hpp"

int main() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 5000);
    boost::asio::ip::tcp::acceptor acc(service, ep.protocol());
    acc.bind(ep);
    acc.listen(3);
    boost::asio::ip::tcp::socket sock(service);
    acc.accept(sock);
    return 0;
}
