#include <iostream>
#include <chrono>
#include <thread>

#include "boost/asio.hpp"
#include "boost/asio/steady_timer.hpp"

void run_service(boost::asio::io_service& ios) {
    ios.run();
}

int main() {
    boost::asio::io_service ios;
    boost::asio::steady_timer timer1(ios, std::chrono::seconds(5));
    timer1.async_wait([](const boost::system::error_code& ec) {
        std::cout << "5 seconds" << std::endl;
    });
    boost::asio::steady_timer timer2(ios, std::chrono::seconds(3));
    timer2.async_wait([](const boost::system::error_code& ec) {
        std::cout << "3 seconds" << std::endl;
    });
    std::thread t(run_service, std::ref(ios));
    t.detach();
    // t.join();
    for (int i=0; i<10; ++i) {
        std::cout << i << std::endl;
    }
    for (int j=0; j < 10; ++j) {
        std::cout << "j = " << j << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
