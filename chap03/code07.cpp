#include <gpiod.hpp>
#include <iostream>
#include <unistd.h>

int main() {
    gpiod::chip chip("/dev/gpiochip0");
    gpiod::line line = chip.get_line(17);
    
    gpiod::line_request req ;
    req.request_type = gpiod::line_request::DIRECTION_INPUT;
    req.consumer = "example-input";
    line.request(req);
    
    while (true) {
        int val = line.get_value();  // High 상태
        std::cout << "Pin set to " << val << "\n";
        sleep(2);
    }

    return 0;
}