#include <iostream>
#include <thread>
#include "include/acceptor.h"
#include "include/service.h"

Acceptor::Acceptor(boost::asio::io_service& ios, unsigned short port_num) :
    m_ios(ios),
    m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num)) {
        m_acceptor.listen();
    }

void Acceptor::Accept() {
    std::cout << "[" << std::this_thread::get_id() << "] Going to call accept..." << std::endl;
    std::shared_ptr<boost::asio::ip::tcp::socket> sock_ptr(new boost::asio::ip::tcp::socket(m_ios));
    m_acceptor.accept(*sock_ptr.get());
    std::cout << "[" << std::this_thread::get_id() << "] Accept called..." << std::endl;
    (new Service) -> start_handler_client(sock_ptr);
}

Acceptor2::Acceptor2(boost::asio::io_service& ios, unsigned short port_num) :
    m_ios(ios),
    m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num)) {
        m_acceptor.listen();
    }

void Acceptor2::Accept() {
    boost::asio::ip::tcp::socket sock(m_ios);
    m_acceptor.accept(sock);
    (new Service2) -> start_handler_client(&sock);
}
