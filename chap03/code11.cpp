#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <atomic>
using namespace gpiod;

void monitor_gpio(gpiod::line_bulk bulk, std::atomic<bool> & running) {
    // struct gpiod_line_event event;
    // 이벤트 요청 (상승/하강 에지 모두 감지)
    // line.request({gpiod::line_request::EVENT_BOTH_EDGES, "gpio-monitor"});
    // struct timespec ts = { 1, 0 };
    // int ret = gpiod_line_request_rising_edge_events(line, "Consumer");
    // int i = 0;
    while (running) {
        // wait for events and get bulk of lines on which events occured
        auto changed = bulk.event_wait(std::chrono::nanoseconds(1000));
        // iterate lines in bulk
        for (const auto &line : changed) {
            std::cout << "Change detected on GPIO line " << line.offset() << std::endl;
            // read events occured on a line
            auto events = line.event_read_multiple();
            // iterate events
            for (const auto &event : events) {
                std::cout << "\ttype: " << event.event_type << std::endl;
            }
        }
    }
}

int main() {

    chip chip("gpiochip0", chip::OPEN_BY_NAME);
    line_bulk bulk = chip.get_lines({ 5, 6 });
    // auto bulk = chip("gpiochip0", chip::OPEN_BY_NAME).get_lines({ 5, 6 });

    bulk.request({ "monitor",
        line_request::EVENT_BOTH_EDGES,
        line_request::FLAG_BIAS_PULL_UP });


    // // GPIO 칩 열기
    // struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0"); 

    // // GPIO 라인 가져오기 (예: 17번 핀)
    // struct gpiod_line *line = gpiod_chip_get_line(chip, 17);

    // 프로그램 종료 신호를 위한 atomic 변수
    std::atomic<bool> running(true);

    // GPIO 모니터링을 위한 스레드 생성
    std::thread monitor_thread(monitor_gpio, std::ref(bulk), std::ref(running));

    // 프로그램이 종료되면 모니터링 스레드 종료
    std::cout << "Press Enter to stop monitoring..." << std::endl;
    std::cin.get();
    
    // 종료 신호 보내기
    running = false;

    // 스레드 종료 대기
    monitor_thread.join();

    return 0;
}