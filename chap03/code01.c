#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");  // GPIO 칩 열기
    if (!chip) {
        perror("Failed to open GPIO chip");  return 1;
    }

    struct gpiod_line *line = gpiod_chip_get_line(chip, 17); // GPIO 라인 가져오기 (예: 17번 핀)
    if (!line) {
        perror("Failed to get GPIO line");
        gpiod_chip_close(chip);  return 1;
    }

    if (gpiod_line_request_output(line, "example-output", 0) < 0) { // 라인을 출력 모드로 설정
        perror("Failed to request GPIO line as output");
        gpiod_chip_close(chip);   return 1;
    }

    gpiod_line_set_value(line, 1);  // High
    printf("GPIO set to HIGH\n");

    sleep(2);

    gpiod_line_set_value(line, 0);  // Low
    printf("GPIO set to LOW\n");

    gpiod_chip_close(chip);     // 리소스 정리
    return 0;
}