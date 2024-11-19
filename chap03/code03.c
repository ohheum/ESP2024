#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  unsigned int line_num = 24;	// GPIO Pin #24

  struct gpiod_chip *chip = gpiod_chip_open_by_name("gpiochip0");
  if (!chip) {
    perror("Open chip failed\n");
    goto end;
  }

  struct gpiod_line *line = gpiod_chip_get_line(chip, line_num);
  if (!line) {
    perror("Get line failed\n");
    goto close_chip;
  }

  int ret = gpiod_line_request_input(line, "Consumer");
  if (ret < 0) {
    perror("Request line as input failed\n");
    goto release_line;
  }

    /* Read input 20 times */
  for (int i = 10; i > 0; i--) {
    int val = gpiod_line_get_value(line);
    if (val < 0) {
      perror("Read line input failed\n");
      goto release_line;
    }
    printf("Intput %d on line #%u\n", val, line_num);
    sleep(1);
  }

release_line:
  gpiod_line_release(line);
close_chip:
  gpiod_chip_close(chip);
end:
  return 0;
}
