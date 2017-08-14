#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "glog/logging.h"
using namespace boost::asio;

io_service service;

void init_logger() {
    FLAGS_logtostderr = true;
}

void func(int i) {
    LOG(INFO) << "Func called with i=" << i << std::endl;
}

void dispatch_and_post() {
    for (int i=0; i<10; i += 2) {
        service.post(boost::bind(func, i + 1));
        service.dispatch(boost::bind(func, i));
    }
}

int main() {
    service.post(boost::bind(dispatch_and_post));
    service.run();
}
