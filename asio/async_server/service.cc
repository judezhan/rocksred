#include <iostream>
#include <thread>

#include "include/service.h"
#include "boost/asio.hpp"

void Service::start_handling() {
    std::cout << "Service::start_handling..." << std::endl;
    boost::asio::async_read_until(*m_sock.get(), m_request_buf, '\n', [this](const boost::system::error_code& ec, std::size_t byte_transferred){
        on_request_received(ec, byte_transferred);
    });
}

void Service::on_request_received(const boost::system::error_code& ec, std::size_t byte_transferred) {
    std::cout << "Service::on_request_received, ec = " << ec.value() << ", byte_transferred = " << byte_transferred << std::endl;
    if (ec != 0) {
        std::cout << "Error occured! Error code = " << ec.value()
            << ", msg = " << ec.message() << std::endl;
        on_finish();
        return;
    }

    // process request
    m_response = process_request(m_request_buf);

    // Initiate asynchronous write operation
    boost::asio::async_write(*m_sock.get(), boost::asio::buffer(m_response), [this](const boost::system::error_code& ec, std::size_t byte_transferred){
        on_response_sent(ec, byte_transferred);
    });
}

void Service::on_response_sent(const boost::system::error_code& ec, std::size_t byte_transferred) {
    std::cout << "Service::on_response_sent, ec = " << ec.value() << ", byte_transferred = " << byte_transferred << std::endl;
    if (ec != 0) {
        std::cout << "Error occured! Error code = " << ec.value()
            << ", msg = " << ec.message() << std::endl;
    }
    on_finish();
}

std::string Service::process_request(boost::asio::streambuf& request_buf) {
    // int i = 0;
    // while(i < 1000000) ++i;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    std::istream is(&request_buf);
    std::string request_str;
    std::getline(is, request_str);
    std::string response = "Response: " + request_str + "\n";
    return response;
}

void Service::on_finish() {
    delete this;
}
