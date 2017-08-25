#include <iostream>
#include "include/server.h"

Server::Server() {
    m_work.reset(new boost::asio::io_service::work(m_ios));
}

void Server::start(unsigned short port_num, unsigned int thread_pool_size) {
    assert(thread_pool_size > 0);
    std::cout << "Server start with thread pool size = " << thread_pool_size << std::endl;

    // Create and start acceptor
    acc.reset(new Acceptor(m_ios, port_num));
    acc->start();

    // Create specified number of threads and add them to pool
    for (unsigned int i = 0; i < thread_pool_size; ++i) {
        std::unique_ptr<std::thread> th(new std::thread([this](){
            m_ios.run();
        }));
        m_thread_pool.push_back(std::move(th));
    }
}

void Server::stop() {
    acc->stop();
    m_ios.stop();

    for (auto& th : m_thread_pool) {
        th->join();
    }
}
