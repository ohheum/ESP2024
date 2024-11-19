#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <atomic>
using namespace gpiod;

int main() {
    auto bulk = chip("gpiochip0", chip::OPEN_BY_NAME).get_lines({ 5, 6 });

    bulk.request({ "monitor",
        line_request::EVENT_BOTH_EDGES,
        line_request::FLAG_BIAS_PULL_UP });

    while (true) {
        // wait for events and get bulk of lines on which events occured
        auto changed = bulk.event_wait(std::chrono::seconds::max());
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