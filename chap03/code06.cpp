#include <gpiod.hpp>
#include <iostream>
#include <unistd.h>
int main() {
    // GPIO 칩 열기
    gpiod::chip chip("/dev/gpiochip0");
    
    // GPIO 라인 가져오기 (예: 17번 핀)
    gpiod::line line = chip.get_line(17);
    
    // 라인을 출력 모드로 요청
    gpiod::line_request req = gpiod::line_request();
    req.request_type = gpiod::line_request::DIRECTION_OUTPUT;
    req.consumer = "example-output";
    line.request(req);
    
    // GPIO 값 설정
    line.set_value(1);  // High 상태
    std::cout << "Pin set to HIGH\n";
    sleep(2);
    line.set_value(0);  // Low 상태
    std::cout << "Pin set to LOW\n";
    
    // 라인 해제
    line.release();

    return 0;
}