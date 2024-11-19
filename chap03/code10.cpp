#include <iostream>
#include <thread>

void print_number(int n) {
    std::cout << "Number: " << n << std::endl;
}

int main() {
    std::thread t(print_number, 10);  // 인자 10을 전달
    t.join();

    return 0;
}