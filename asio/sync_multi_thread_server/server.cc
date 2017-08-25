#include <thread>
#include <iostream>
#include "include/server.h"
#include "include/acceptor.h"

void Server::stop() {
    m_stop.store(true);
    m_thread->join();
}

void Server::start(unsigned short port_num) {
    std::cout << "Server start..." << std::endl;
    m_thread.reset(new std::thread([this, port_num]() {
        run(port_num);
    }));
}

void Server::run(unsigned short port_num) {
    std::cout << "Server run..." << std::endl;
    while (!m_stop.load()) {
        Acceptor acc(m_ios, port_num);
        acc.Accept();
    }
    std::cout << "Going to stop server..." << std::endl;
}
