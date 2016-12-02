#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>

std::vector<int> data;
std::atomic_bool data_ready(false);

void reader_thread()
{
    while (!data_ready.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout<<"The answer = "<<data[0]<<"\n";
}

void writer_thread()
{
    data.push_back(42);
    data_ready = true;
}

int main(int argc, char const *argv[])
{
    std::thread t1(reader_thread);
    std::thread t2(writer_thread);
    t1.join();
    t2.join();
    return 0;
}
