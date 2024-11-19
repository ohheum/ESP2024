#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define	CONSUMER	"Consumer"

int main(int argc, char **argv) {
  unsigned int line_num = 17;	// GPIO Pin #17

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

  int ret = gpiod_line_request_output(line, CONSUMER, 0);
  if (ret < 0) {
    perror("Request line as output failed\n");
    goto release_line;
  }

    /* Blink 20 times */
  unsigned int val = 0;
  for (int i = 20; i > 0; i--) {
    ret = gpiod_line_set_value(line, val);
    if (ret < 0) {
      perror("Set line output failed\n");
      goto release_line;
    }
    printf("Output %u on line #%u\n", val, line_num);
    sleep(1);
    val = !val;
  }

release_line:
  gpiod_line_release(line);
close_chip:
  gpiod_chip_close(chip);
end:
  return 0;
}
