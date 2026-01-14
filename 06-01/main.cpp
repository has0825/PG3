#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
int current_step = 1;

void thread_work(int id) {

    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [id] { return current_step == id; });


    std::cout << "thread " << id << std::endl;


    current_step++;

    lock.unlock();
    cv.notify_all();
}

int main() {

    std::thread t1(thread_work, 1);
    std::thread t2(thread_work, 2);
    std::thread t3(thread_work, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}