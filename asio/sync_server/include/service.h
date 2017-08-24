#ifndef INCLUDE_SERVICE_H
#define INCLUDE_SERVICE_H

#include "boost/asio.hpp"

class Service {
    public:
        Service() {};
        void handler(boost::asio::ip::tcp::socket& sock);
};

#endif
