#include "include/server.h"
#include "include/acceptor.h"

void Server::run(unsigned short port_num) {
    Acceptor acc(m_ios, port_num);
    while (!m_stop.load()) {
        acc.Accept();
    }
}

void Server::start(unsigned short port_num) {
    m_thread.reset(new std::thread([this, port_num]() {
        run(port_num);
    }));
}

void Server::stop() {
    m_stop.store(true);
    m_thread->join();
}
