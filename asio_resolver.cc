#include <iostream>
#include "boost/asio.hpp"

int main() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::resolver resolver(service);
    boost::asio::ip::tcp::resolver::query query("www.google.com", "80");
    std::cout << "Start to query..." << std::endl;
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint ep = *it;
    std::cout << "Finish query..." << std::endl;
    std::cout << ep.address().to_string() << ":" << ep.port() << "/" << ep.protocol().protocol()<< std::endl;
    return 0;
}
