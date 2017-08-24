#include <iostream>
#include <chrono>
#include <thread>
#include "include/service.h"

void Service::start_handler_client(std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
    std::thread th([this, sock]() {
        handler(sock);
    });
    th.detach();
}

void Service::handler(std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
    try {
        boost::asio::streambuf request;
        boost::asio::read_until(*sock.get(), request, '\n');
        std::string line;
        std::istream is(&request);
        std::getline(is, line);
        std::cout << "[" << std::this_thread::get_id() << "] Reading data from client: " << line << std::endl;
        int i = 0;
        while (i < 1000000) {
            ++i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string response = "Response\n";
        boost::asio::write(*sock.get(), boost::asio::buffer(response));
    } catch (boost::system::system_error& ec) {
        std::cout << "Error occured. Error code = " << ec.code()
            << ", msg = " << ec.what() << std::endl;
    }
}

void Service2::start_handler_client(boost::asio::ip::tcp::socket* sock) {
    std::thread th([this, sock]() {
        try {
            boost::asio::streambuf request;
            boost::asio::read_until(*sock, request, '\n');
            int i = 0;
            while (i < 1000000) {
                ++i;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::string response = "Response\n";
            boost::asio::write(*sock, boost::asio::buffer(response));
        } catch (boost::system::system_error& ec) {
            std::cout << "Error occured. Error code = " << ec.code()
                << ", msg = " << ec.what() << std::endl;
        }
    });
    th.detach();
}

// void Service2::start_handler_client(boost::asio::ip::tcp::socket* sock) {
//     try {
//         boost::asio::streambuf request;
//         boost::asio::read_until(*sock, request, '\n');
//         int i = 0;
//         while (i < 1000000) {
//             ++i;
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(500));
//         std::string response = "Response\n";
//         boost::asio::write(*sock, boost::asio::buffer(response));
//     } catch (boost::system::system_error& ec) {
//         std::cout << "Error occured. Error code = " << ec.code()
//             << ", msg = " << ec.what() << std::endl;
//     }
// }

void Service2::handler(boost::asio::ip::tcp::socket& sock) {
    try {
        boost::asio::streambuf request;
        boost::asio::read_until(sock, request, '\n');
        int i = 0;
        while (i < 1000000) {
            ++i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string response = "Response\n";
        boost::asio::write(sock, boost::asio::buffer(response));
    } catch (boost::system::system_error& ec) {
        std::cout << "Error occured. Error code = " << ec.code()
            << ", msg = " << ec.what() << std::endl;
    }
}
