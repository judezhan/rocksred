#include <iostream>

#include "include/service.h"
#include "include/acceptor.h"
#include "boost/asio.hpp"

Acceptor::Acceptor(boost::asio::io_service& ios, unsigned short port_num) :
    m_ios(ios),
    m_acceptor(boost::asio::ip::tcp::acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num))),
    m_stopped(false) {}

void Acceptor::start() {
    m_acceptor.listen();
    init_accept();
}

void Acceptor::stop() {
    m_stopped.store(true);
}

void Acceptor::init_accept() {
    std::shared_ptr<boost::asio::ip::tcp::socket> sock_ptr(new boost::asio::ip::tcp::socket(m_ios));
    m_acceptor.async_accept(*sock_ptr.get(), [this, sock_ptr](const boost::system::error_code& ec){
        on_accept(ec, sock_ptr);
    });
}

void Acceptor::on_accept(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock_ptr) {
    if (ec != 0) {
        std::cout << "Error occured! Error code = " << ec.value()
            << ", msg = " << ec.message() << std::endl;
    } else {
        (new Service(sock_ptr)) -> start_handling();
    }

    // Init next async accpet operation if acceptor has not been stopped yet.
    if (!m_stopped.load()) {
        init_accept();
    } else {
        m_acceptor.close();
    }
}
