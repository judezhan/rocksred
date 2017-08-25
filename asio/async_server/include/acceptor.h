#ifndef INCLUDE_ACCEPTOR_H_
#define INCLUDE_ACCEPTOR_H_

#include "boost/asio.hpp"

class Acceptor {
    private:
        boost::asio::io_service& m_ios;
        boost::asio::ip::tcp::acceptor m_acceptor;
        std::atomic_bool m_stopped;
    private:
        void init_accept();
        void on_accept(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock);
    public:
        Acceptor(boost::asio::io_service& ios, unsigned short port_num);
        void start();
        void stop();
};

#endif
