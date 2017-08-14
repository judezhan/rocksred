#include <iostream>
#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "glog/logging.h"

using namespace boost::asio;

io_service service;
boost::mutex m;

void init_logger() {
    FLAGS_logtostderr = true;
}

void func(int i) {
    LOG(INFO) << "func called with i=" << i << "/" << boost::this_thread::get_id() << std::endl;
}

void worker_thread() {
    service.run();
}

int main() {
    init_logger();

    for (int i=0; i<10; i++) {
        service.post(boost::bind(func, i));
    }
    worker_thread();

    // boost::thread_group threads;
    // for (int i=0; i<3; i++) {
    //     threads.create_thread(worker_thread);
    // }
    boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
    // threads.join_all();
}
