#include <iostream>
#include "glog/logging.h"

int main() {
    FLAGS_log_dir = "/tmp/test/";
    google::InitGoogleLogging("GlogTest");
    for (int i=0; i<100; i++) {
        switch(i % 3) {
            case 0:
                LOG(ERROR) << "Hello Error" << i << std::endl;
                break;
            case 1:
                LOG(WARNING) << "Hello WARNING" << i << std::endl;
                break;
            case 2:
                LOG(INFO) << "Hello INFO" << i << std::endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
