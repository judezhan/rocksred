#ifndef INCLUDE_SERVER_H
#define INCLUDE_SERVER_H

#include <atomic>
#include <thread>
#include "boost/asio.hpp"

class Server {
    private:
        std::atomic_bool m_stop;
        std::unique_ptr<std::thread> m_thread;
        boost::asio::io_service m_ios;
        void run(unsigned short port_num);

    public:
        Server() : m_stop(false) {};
        void start(unsigned short port_num);
        void stop();
};

#endif
