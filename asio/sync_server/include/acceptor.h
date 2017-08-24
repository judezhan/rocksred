#ifndef INCLUDE_ACCEPTOR_H
#define INCLUDE_ACCEPTOR_H

#include "boost/asio.hpp"

class Acceptor {
    private:
        boost::asio::io_service& m_ios;
        boost::asio::ip::tcp::acceptor m_acceptor;
    public:
        Acceptor(boost::asio::io_service& ios, unsigned short port_num);
        void Accept();
};

#endif
