#ifndef INCLUDE_SERVICE_H
#define INCLUDE_SERVICE_H

#include "boost/asio.hpp"

class Service {
    public:
        Service() {};
        void start_handler_client(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
    private:
        void handler(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
};

class Service2 {
    public:
        Service2() {};
        void start_handler_client(boost::asio::ip::tcp::socket* sock);
    private:
        void handler(boost::asio::ip::tcp::socket& sock);
};

#endif
