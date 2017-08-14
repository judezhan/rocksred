#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "glog/logging.h"

using namespace boost::asio;

io_service service;

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
    io_service::strand strand1(service), strand2(service);
    for (int i=0; i<50; ++i) {
        service.post(strand1.wrap(boost::bind(func, i)));
    }
    for (int i=50; i<100; ++i) {
        service.post(strand2.wrap(boost::bind(func, i)));
    }

    boost::thread_group threads;
    for (int i=0; i<3; ++i) {
        threads.create_thread(worker_thread);
    }
    boost::this_thread::sleep(boost::posix_time::millisec(500));
    threads.join_all();
    return 0;
}
