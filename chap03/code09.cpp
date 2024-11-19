#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    // 스레드 생성 및 실행
    std::thread t(hello);  // hello() 함수가 새로운 스레드에서 실행됨

    // 스레드가 완료될 때까지 기다림
    t.join();

    return 0;
}