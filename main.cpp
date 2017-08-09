//
// Created by Jude.Z on 7/29/17.
//

#include <iostream>
#include "rocksdb/db.h"

int main() {
    std::cout << "Going to open db..." << std::endl;
    rocksdb::DB* db;
    rocksdb::Options ops;
    ops.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(ops, "/tmp/rocksred", &db);
    assert(status.ok());
    std::string key = "key1";
    std::string value = "value1";

    for (int i = 0; i<100; i++) {
        long long int start, end;
        start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        std::cout << "Input value: ";
//        std::cin >> value;
        value = std::to_string(i);
        if (value == "q") {
            std::cout << "Bye" << std::endl;
            break;
        }
        status = db->Put(rocksdb::WriteOptions(), key, value);
        if (status.ok()) {
            std::cout << "Write value succeed!" << std::endl;
        } else {
            std::cout << "Write value failed! (" << status.ToString() << ")" << std::endl;
        }
        status = db->Get(rocksdb::ReadOptions(), key, &value);
        if (status.ok()) {
            std::cout << "Read value succeed, current value is " << value << std::endl;
        } else {
            std::cout << "Read value failed! (" << status.ToString() << ")" << std::endl;
        }
        end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << "Time elapse: " << end - start << std::endl;
    }
    return 0;
}
