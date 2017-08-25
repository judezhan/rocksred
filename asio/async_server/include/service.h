#ifndef INCLUDE_SERVICE_H_
#define INCLUDE_SERVICE_H_

#include "boost/asio.hpp"

class Service {
    private:
        void on_request_received(const boost::system::error_code& ec, std::size_t byte_transferred);
        std::string process_request(boost::asio::streambuf& request_buf);
        void on_response_sent(const boost::system::error_code& ec, std::size_t byte_transferred);
        void on_finish();
    private:
        std::shared_ptr<boost::asio::ip::tcp::socket> m_sock;
        std::string m_response;
        boost::asio::streambuf m_request_buf;

    public:
        Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock) : m_sock(sock) {};
        void start_handling();
};

#endif
