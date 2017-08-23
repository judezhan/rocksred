#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

#include "boost/asio.hpp"

using namespace boost::asio;


class Service {
    public:
        Service() {};
        void handler(ip::tcp::socket& sock) {
            try {
                streambuf req_buf;
                read_until(sock, req_buf, '\n');
                int i=0;
                while (i < 1000000) {
                    ++i;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::string resp_str = "Response\n";
                write(sock, buffer(resp_str));
            } catch (boost::system::system_error& ec) {
                std::cout << "Error occured. Error code = " << ec.code().value()
                    << ", msg = " << ec.what() << std::endl;
            }
        }
};

class Acceptor {
    private:
        io_service& m_ios;
        ip::tcp::acceptor m_acceptor;

    public:
        Acceptor(io_service& ios, unsigned short port_num) :
            m_ios(ios),
            m_acceptor(m_ios, ip::tcp::endpoint(ip::address_v4::any(), port_num))
        {
            m_acceptor.listen();
        }

        void Accept() {
            ip::tcp::socket sock(m_ios);
            m_acceptor.accept(sock);
            Service svc;
            svc.handler(sock);
        }
};

class Server {
    private:
        std::atomic_bool m_stop;
        std::unique_ptr<std::thread> m_thread;
        io_service m_ios;

        void run(unsigned short port_num) {
            Acceptor acc(m_ios, port_num);
            while (!m_stop.load()) {
                std::cout << m_stop.load() << std::endl;
                acc.Accept();
                std::cout << "acc.Accept() finished!" << std::endl;
            }
        }

    public:
        Server() : m_stop(false){}
        void start(unsigned short port_num) {
            m_thread.reset(new std::thread([this, port_num] () {
                run(port_num);
            }));
        }

        void stop() {
            std::cout << "Server stop() called" << std::endl;
            m_stop.store(true);
            m_thread->join();
        }
};

int main() {
    unsigned short port_num = 3333;
    try {
        Server server;
        server.start(port_num);
        std::cout << "I am going to sleep..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "I am going to stop the server..." << std::endl;
        server.stop();
    } catch (boost::system::system_error& ec) {
        std::cout << "Error occured. Error code = " << ec.code().value()
            << ", msg = " << ec.what() << std::endl;
    }
}
