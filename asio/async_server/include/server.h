#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include <thread>
#include <memory>

#include "acceptor.h"
#include "boost/asio.hpp"

class Server {
    private:
        boost::asio::io_service m_ios;
        std::unique_ptr<boost::asio::io_service::work> m_work;
        std::unique_ptr<Acceptor> acc;
        std::vector<std::unique_ptr<std::thread>> m_thread_pool;
    public:
        Server();
        void start(unsigned short port_num, unsigned int thread_pool_size);
        void stop();
};

#endif
