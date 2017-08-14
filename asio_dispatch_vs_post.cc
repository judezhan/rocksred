#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

namespace asio = boost::asio;

boost::mutex mutex;
void print(boost::thread::id id, const std::string& s) {
    boost::mutex::scoped_lock lock(mutex);
    std::cout << id << s << std::endl;
}

void fB() {
    print(boost::this_thread::get_id(), " call fB");
}

void fA(asio::io_service& io_service) {
    static int selector = 0;

    ++selector;
    if (selector % 2 == 0) {
        print(boost::this_thread::get_id(), " post");
        io_service.post(fB);
    } else {
        print(boost::this_thread::get_id(), " dispatch");
        io_service.dispatch(fB);
    }
}

bool startAFunction() {
    print(boost::this_thread::get_id(), " Enter a non-empty string to run A function");

    std::string input;
    getline(std::cin, input);
    return input.length() == 0 ? false : true;
}

int main() {
    std::cout << boost::this_thread::get_id() << std::endl;

    asio::io_service io_service;
    asio::io_service::work work(io_service);

    boost::thread_group group;
    const int count = 3;
    for (int i = 0; i < count; ++i) {
        group.create_thread(boost::bind(&asio::io_service::run, &io_service));
    }

    while (startAFunction()) {
        io_service.post(boost::bind(fA, boost::ref(io_service)));
    }

    std::cout << "stop io_service" << std::endl;
    io_service.stop();
    group.join_all();

    std::cout << "end application" << std::endl;
}
