#include <stdio.h>

#define MIN_TEMP -50
#define MAX_TEMP 100
#define STEP 5
#define HEADING "Celsius\tFahrenheit\n"

main() {
  double cel, fahr;

  printf(HEADING);
  for (cel = MAX_TEMP; cel >= MIN_TEMP; cel -= STEP) {
    // Double it, remove a tenth, and add 32.
    fahr = 2 * cel * (9.0 / 10.0) + 32;
    printf("%.2f\t%.2f\n", cel, fahr);
  }
}
